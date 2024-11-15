#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyGPIO_Init (GPIO_TypeDef * GPIO , char GPIO_Pin, char GPIO_Conf, char type, int Pull ){

		if (GPIO == GPIOA){
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		}
		else if(GPIO == GPIOB){
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN ;
		}
		else if (GPIO == GPIOC){
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;
		}
		else if (GPIO == GPIOD){
			RCC->APB2ENR |= RCC_APB2ENR_IOPDEN ;
		}
		else {
			RCC->APB2ENR |= RCC_APB2ENR_IOPEEN ;
		}
		
		//Setup config 
		if (GPIO_Pin<=7){    //on est dans le crl 
			GPIO->CRL &= ~(0xF<<GPIO_Pin*4); //initialisation a zero
			GPIO->CRL |= (type<<GPIO_Pin*4);  // initialisation en in ou out 2mhz 
			GPIO->CRL |= (GPIO_Conf<<(GPIO_Pin*4 + 2)); //setup le CNF	
		}else{
			GPIO->CRH &= ~(0xF<<(GPIO_Pin-8)*4); //initialisation a zero
			GPIO->CRH |= (type<<(GPIO_Pin-8)*4);  // initialisation en in ou out 2mhz 
			GPIO->CRH |= (GPIO_Conf<<((GPIO_Pin-8)*4 + 2)); //setup le CNF	
		}
		
		//Pull UP/Down setup 
		if (Pull == 1 ) {
			GPIO->ODR |= (1<<GPIO_Pin);
		}else if (Pull == -1) {
			GPIO->ODR &= ~(1<<GPIO_Pin);
		}

}

int MyGPIO_Read (GPIO_TypeDef * GPIO, char GPIO_Pin){
	int Out=0;
	unsigned int IDR = GPIO->IDR;
	IDR &= (1<< GPIO_Pin);
	
	if (IDR==1<<GPIO_Pin){
		Out = 1;
	}	
	return Out;
}

void MyGPIO_Set (GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO->ODR |= (1<<GPIO_Pin);
}
void MyGPIO_Reset (GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO->ODR &= ~(1<<GPIO_Pin);
}

void MyGPIO_Toggle (GPIO_TypeDef * GPIO, char GPIO_Pin){
	unsigned int ODR = GPIO->ODR;
	ODR &=(1<< GPIO_Pin);
	if (ODR == 1<<GPIO_Pin){
		GPIO->ODR &= ~(1<<GPIO_Pin);
	}else{
		GPIO->ODR |= (1<<GPIO_Pin);
	}
}



void(*pFnc2)(TIM_TypeDef * Timer); //pointeur de fonction pour l'interuption 

void MyGPIO_Active_EXTI3_IT(char Prio, void(*IT_function)(TIM_TypeDef * Timer)){
	
	pFnc2=IT_function;
	
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; //on active l'horloge 
	AFIO->EXTICR[2] &= ~(0xF); // clear exti2 bits 
	AFIO->EXTICR[2] |= AFIO_EXTICR2_EXTI4_PA; // op paramètre Exti2 sur PA 
	
	//Déclanchement de EXTI2 sur front montant 
	EXTI->IMR |= EXTI_IMR_MR4;  //on active le trigger sur la ligne 2 
	EXTI->RTSR |= EXTI_RTSR_TR4; //on active le triger sur front montant 
	EXTI->FTSR &= ~EXTI_FTSR_TR4; // on désactive le trigger sur front descendant
	
	// Configurer l'interruption NVIC pour EXTI2
  NVIC_EnableIRQ(EXTI4_IRQn);            // Activer l'IRQ EXTI2
  NVIC_SetPriority(EXTI4_IRQn, Prio);    // Définir la priorité
	
}

void EXTI4_IRQHandler(void){
	
      EXTI->PR = ~EXTI_PR_PR2;  //abaissement du flag d'interuption 
			TIM_TypeDef *timer = TIM2; // on utilise TIM2
			if (pFnc2 !=0){     // quand on a interrruption -> on appelle pfnc 
					(*pFnc2)(timer);
			}
}

