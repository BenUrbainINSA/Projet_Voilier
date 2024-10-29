#include "stm32f10x.h"
#include "MyADC.h"


void MyADC_Init(ADC_TypeDef * ADC,char channel,char Te,TIM_TypeDef * Timer,char mode ){
	
	//active les clocks
	if (ADC==ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}else if (ADC==ADC2){
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
	
	
	if (mode == Single_Not_Cont){
		
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
	
	//mise en place du trigger externe 
	//creation du signal d'horloge 
	
	if (Timer == TIM1){
		MyTimer_Base_Init(Timer,6,1,My_timer_Up); //on crée un timer a 12Mhz voire un potentiel paramétrage de la periode
		MyTimer_PWM(Timer,1,PWM_mode_2); //on paramètre un signal PWM en mode 2 sur la chanel 1 du timer  
	}else if (Timer==TIM2){
		MyTimer_Base_Init(Timer,6,1,My_timer_Up); //on crée un timer a 12Mhz voire un potentiel paramétrage de la periode
		MyTimer_PWM(Timer,2,PWM_mode_2); //on paramètre un signal PWM en mode 2 sur la chanel 2 du timer  
	 
	}else if (Timer==TIM3){
		MyTimer_Base_Init(Timer,6,1,My_timer_Up); //on crée un timer a 12Mhz voire un potentiel paramétrage de la periode
		MyTimer_PWM(Timer,1,PWM_mode_2); //on paramètre un signal PWM en mode 2 sur la chanel 1 du timer  
		TIM3->CR2 &= ~TIM_CR2_MMS;             // Effacer les bits MMS
    TIM3->CR2 |= TIM_CR2_MMS_1;            // Configurer TRGO pour le signal de mise à jour
	}else if (Timer==TIM4){
		MyTimer_Base_Init(Timer,6,1,My_timer_Up); //on crée un timer a 12Mhz voire un potentiel paramétrage de la periode
		MyTimer_PWM(Timer,4,PWM_mode_2); //on paramètre un signal PWM en mode 2 sur la chanel 4 du timer  

	}

	Set_PWM_Duty_Cycle(Timer,50,2); //on paramètre un duty cycle de 50% sur le signal d'horloge du chanel 1 du timer 
	MyTimer_Base_Start(Timer)
	
	//activation du trigger externe 
	ADC->CR2 |= ADC_CR2_EXTTRIG;
	ADC->CR2 &= ~(ADC_CR2_EXTSEL); //efface les bit sur le selcteur de trigger 
	
	//on paramètre l'event de trigger en fonction du timer 
	if (Timer == TIM1){
		ADC->CR2 &= ~(ADC_CR2_EXTSEL); //on utilise le CC1 donc tous les bits a zero (pg si c redondant au moins c compréhensible) 
	}else if (Timer==TIM2){
		ADC->CR2 |= (ADC_CR2_EXTSEL_0|ADC_CR2_EXTSEL_1);  //triggert sur le CC2 event du timer 2 
	}else if (Timer==TIM3){
		ADC->CR2 |= (ADC_CR2_EXTSEL_2); //tigger sur le TRGO envent du timer 3 
	}else if (Timer==TIM4){
		ADC->CR2 |= (ADC_CR2_EXTSEL_0|ADC_CR2_EXTSEL_2); //trigger sur le CC4 du Timer4 
	}
	
	
	//activation de l'interuption sur EOC
	ADC->CR1 |= ADC_CR1_EOCIE;  // bit d'interuption à 1 
	//on active l'interuption dans la NVIC 
	NVIC_EnableIRQ(ADC1_2_IRQn);
	NVIC_SetPriority(ADC1_2_IRQn,5); //on met la prio a 5 mais on peut changer 
	
	
	//Activation de l'ADC
	ADC->CR2 |=ADC_CR2_ADON;	
	}
}

void MyADC_StartConv(ADC_TypeDef * ADC){
	ADC->CR2|= ADC_CR2_SWSTART; //on demarre la conversation 
}

uint16_t MyADC_Read(ADC_TypeDef * ADC){
	uint16_t Result =0;
	if (!(ADC->SR & ADC_SR_EOC)){
		Result= ADC->DR;   //on prend uniquement les 16 1er bits 
	}
	return Result;
}

void ADC1_2_IRQHandler(void){
	if (ADC1->SR & ADC_SR_EOC){
		 ADC1->SR &= ~(ADC_SR_EOC);  // Effacer le flag EOC
	}else if (ADC2->SR & ADC_SR_EOC) {
		 ADC1->SR &= ~(ADC_SR_EOC);  // Effacer le flag EOC
	}
}

