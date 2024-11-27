#include "stm32f10x.h"
#include "MyADC.h"


void MyADC_Init(ADC_TypeDef * ADC,char channel,char Te,char mode ){
	
	//active les clocks
	if (ADC==ADC1) {
		RCC->CFGR |=RCC_CFGR_ADCPRE_DIV6 ;  //adc prescaler à 6
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
		
	}else if (ADC==ADC2){
		RCC->CFGR |=RCC_CFGR_ADCPRE_DIV6 ;
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
	
	
	if (mode == Single_Not_Cont){
	
	//Activation de l'ADC
		ADC->CR2 |=ADC_CR2_ADON;	
	//calibration 
		
	ADC->CR2 |= ADC_CR2_CAL;
	while ((ADC->CR2 & ADC_CR2_CAL)==ADC_CR2_CAL){}
	}	
	
	//paramétrage du channel 
	ADC->SQR3 &= ~(ADC_SQR3_SQ1);   //on initalise le registre de channel pour la 1ere et unique convertion
	ADC->SQR3 |=channel;  //on ecrit les bit du channel dans SQ1 (pas besoin de décalage car 1ere element
	
	// paramétrage de Te 
	if (channel <=9){
		ADC->SMPR2 &=~(ADC_SMPR2_SMP0 <<(channel *3));  //reset les bits du canal 
		ADC->SMPR2 |=(Te <<(channel *3));
	}else{
		ADC->SMPR1 &=~(ADC_SMPR1_SMP10 <<(channel-10 *3));  //reset les bits du canal 
		ADC->SMPR1 |= (Te <<((channel-10) *3));
	}
	
	//paramétrage en mode not continous 
	ADC->CR2 &= ~(ADC_CR2_CONT);
	
	//activation du trigger externe 
	ADC->CR2 |= ADC_CR2_EXTTRIG;
	
	ADC->CR2 &= ~(ADC_CR2_EXTSEL); //efface les bit sur le selcteur de trigger   deja aligné a droite 
	ADC->CR2 |=ADC_CR2_EXTSEL_0|ADC_CR2_EXTSEL_1|ADC_CR2_EXTSEL_2;

	
	
}

void MyADC_StartConv(ADC_TypeDef * ADC){     //a modifier en ajoutant le read en ent mettant le parametrage du trigger dedans.
	ADC->CR2|= ADC_CR2_SWSTART; //on demarre la conversation 
}

int MyADC_Read(ADC_TypeDef * ADC){
	int Result =0.0;
	
	while ((ADC->SR & ADC_SR_EOC) !=ADC_SR_EOC){}
	Result= ADC->DR;   //on prend uniquement les 16 1er bits 
	ADC->SR &= ~(ADC_SR_EOC);
	return Result;
}

//void ADC1_2_IRQHandler(void){
//	if (ADC1->SR & ADC_SR_EOC){
//		 ADC1->SR &= ~(ADC_SR_EOC);  // Effacer le flag EOC
//	}else if (ADC2->SR & ADC_SR_EOC) {
//		 ADC1->SR &= ~(ADC_SR_EOC);  // Effacer le flag EOC
//	}
//}

