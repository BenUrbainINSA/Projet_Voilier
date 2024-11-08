#include "stm32f10x.h"
#include "MyEncoder.h"



void MyEncoder_Base_Init(TIM_TypeDef * Timer,unsigned short ARR){
	
			if (Timer==TIM1){
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN ;
      }
      else if (Timer==TIM2){
            RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
      }
      else if (Timer == TIM3){
            RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
      }
      else if (Timer == TIM4){
            RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
      } 
			MyGPIO_Init(GPIOA,'0',In_Floating,In,None);   //setup PA0 et PA1 en floating input 
			MyGPIO_Init(GPIOA,'1',In_Floating,In,None);
			
			MyGPIO_Init(GPIOB,'3',In_Floating,In,None); //on va mettre en place une interuption EXTIx sur le PA3 dans driver GPIO
			
      Timer->ARR=ARR-1;   //pas de préscaler car on utilise uniquement le registre ARR
			
			Timer->SMCR |= TIM_SMCR_SMS_0|TIM_SMCR_SMS_1;   //SMS = 011 pour conter sur TI1 et TI2
			Timer->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC2P); //Mode non inverter pour TI1 et TI2
			Timer->CCMR1 |= (TIM_CCMR1_CC1S_0);  // CC1S = 01, TI1FP1 sur TI1
			Timer->CCMR1 |= (TIM_CCMR1_CC2S_0);  // CC2S = 01, TI2FP2 sur TI2
			Timer->CCMR1 &= ~(TIM_CCMR1_IC1F | TIM_CCMR1_IC2F);  // IC1F = 0000, IC2F = 0000   Filtre d'entrée, à modifier si on a des pbs de bruit
			Timer->CR1 |= TIM_CR1_CEN;  //ENABLE le conteur  
			

}   

int16_t Get_MyEncoder(TIM_TypeDef * Timer){    //renvois la valeure de l'encodeur 
	return (int16_t)Timer->CNT;
}

float Get_MyEncoder_In_Deg(TIM_TypeDef * Timer){
	int ARR = Timer->ARR;
	int Encoder_value = Timer->CNT;
	
	return (Encoder_value)/4;

}

void Reset_MyEncoder(TIM_TypeDef * Timer){
	Timer->CNT=0;
}


