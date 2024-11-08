#include "stm32f10x.h"

void MyTimer_Base_Init(TIM_TypeDef * Timer,unsigned short ARR,unsigned short PSC,char Type){
      
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
      
      if (Type==0x1){
            Timer->CR1 &=~(0x1<<4);
      }else {
            Timer->CR1 |=(0x1<<4);
      }
                  
      Timer->PSC=PSC-1;
      Timer->ARR=ARR-1;       
      
}

void(*pFnc)(void); //pointeur de fonction 

void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void(*IT_function)(void)){
      Timer->DIER |= TIM_DIER_UIE;  //enable le bit d'interuption du timer
      pFnc=IT_function;
	
      if (Timer==TIM2){
            NVIC_EnableIRQ(TIM2_IRQn);
            NVIC_SetPriority(TIM2_IRQn,Prio);   
      }
      else if (Timer == TIM3){
            NVIC_EnableIRQ(TIM3_IRQn);
            NVIC_SetPriority(TIM3_IRQn,Prio);
      }
      else if (Timer == TIM4){
            NVIC_EnableIRQ(TIM4_IRQn);
            NVIC_SetPriority(TIM4_IRQn,Prio);
      }
			else if (Timer == TIM1){
            NVIC_EnableIRQ(TIM1_UP_IRQn);
            NVIC_SetPriority(TIM1_UP_IRQn,Prio);
      }
      
}

void MyTimer_PWM(TIM_TypeDef * Timer,char Channel,char mode){
			if (Channel == 1){
					Timer->CCMR1 &= ~TIM_CCMR1_OC1M;  // Effacer les bits OC1M
					
				if (mode == 0x6){  //mode 1
					Timer->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
				}else{ //mode2
					Timer->CCMR1 |= TIM_CCMR1_OC1M;
				}
				
				Timer->CCMR1 &= ~TIM_CCMR1_OC1PE;  // Activer le préchargement
        Timer->CCER |= TIM_CCER_CC1E;  // Activer la sortie du canal 1
				
			}else if (Channel == 2) {
				
					Timer->CCMR1 &= ~TIM_CCMR1_OC2M;  // Effacer les bits OC1M
					
				if (mode == 0x6){  //mode 1
					Timer->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
				}else{ //mode2
					Timer->CCMR1 |= TIM_CCMR1_OC2M;
				}
				
				Timer->CCMR1 &= ~TIM_CCMR1_OC2PE;  // Activer le préchargement
        Timer->CCER |= TIM_CCER_CC2E;  // Activer la sortie du canal 1
				
			}
			else if (Channel == 3) {
				
					Timer->CCMR2 &= ~TIM_CCMR2_OC3M;  // Effacer les bits OC1M
					
				if (mode == 0x6){  //mode 1
					Timer->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
				}else{ //mode2
					Timer->CCMR2 |= TIM_CCMR2_OC3M;
				}
				
				Timer->CCMR1 &= ~TIM_CCMR2_OC3PE;  // Activer le préchargement
        Timer->CCER |= TIM_CCER_CC3E;  // Activer la sortie du canal 1
				
			}
			else if (Channel == 4) {
				
					Timer->CCMR2 &= ~TIM_CCMR2_OC4M;  // Effacer les bits OC1M
					
				if (mode == 0x6){  //mode 1
					Timer->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
				}else{ //mode2
					Timer->CCMR2 |= TIM_CCMR2_OC4M;
				}
				
				Timer->CCMR1 &= ~TIM_CCMR2_OC4PE;  // Activer le préchargement
        Timer->CCER |= TIM_CCER_CC4E;  // Activer la sortie du canal 1
				
			}
			
}

void Set_PWM_Duty_Cycle(TIM_TypeDef * Timer,char valeur, char channel){
	
			if (channel == 1){
				Timer->CCR1= (Timer->ARR * valeur)/100;

			}else if (channel == 2) {
				Timer->CCR2= (Timer->ARR * valeur)/100;
			}
			else if (channel == 3) {
				Timer->CCR3= (Timer->ARR * valeur)/100;
				
			}else if (channel == 4){
				Timer->CCR4= (Timer->ARR * valeur)/100;
			}

}


void TIM2_IRQHandler(void){
      TIM2->SR &= ~TIM_SR_UIF;
			if (pFnc !=0){     // quand on a interrruption -> on appelle pfnc 
					(*pFnc)();
			}
}
void TIM3_IRQHandler(void){
      TIM3->SR &= ~TIM_SR_UIF;
			if (pFnc !=0){
					(*pFnc)();
			}
}

void TIM4_IRQHandler(void){
      TIM4->SR &= ~TIM_SR_UIF;
			if (pFnc !=0){
					(*pFnc)();
			}
}

void TIM1_UP_IRQHandler(void){
		TIM1->SR &= ~TIM_SR_UIF;
		if (pFnc !=0){
					(*pFnc)();
			}
}


