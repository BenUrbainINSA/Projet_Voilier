#include "stm32f10x.h"
#include "MyUSART.h"
#include "Driver_GPIO.h"


void MyUSART_Init(USART_TypeDef *USART, int BaudRate){
	
	int Fclk;
	if (USART==USART1){
		//Clocker le périph USART
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			
		//Config pins : pour USART1 Tx=PA9, Rx=PA10
		MyGPIO_Init (GPIOA , 9, AltOut_Ppull, Out50Mhz, None);
		MyGPIO_Init (GPIOA , 10, In_Floating, In, None);
			
		//Defnir le Baud rate Bd = Fclk/BRR
		Fclk=72000000; //APB2 periph => Fclk=72Mhz
		USART1->BRR=Fclk/BaudRate;
		
		//Config interruption sur la réception d'un message sur Rx
		NVIC_EnableIRQ(USART1_IRQn);
		NVIC_SetPriority(USART1_IRQn, 5);
	}
	else if (USART==USART2){
		RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			
		MyGPIO_Init (GPIOA , 2, AltOut_Ppull, Out50Mhz, None);
		MyGPIO_Init (GPIOA , 3, In_Floating, In, None);
			
		Fclk=35000000; //APB1 periph => Fclk=36Mhz
		USART2->BRR=Fclk/BaudRate;
		
		NVIC_EnableIRQ(USART2_IRQn);
		NVIC_SetPriority(USART2_IRQn, 5);
	}
	else if (USART==USART3){
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		
		MyGPIO_Init (GPIOB , 10, AltOut_Ppull, Out50Mhz, None);
		MyGPIO_Init (GPIOA , 11, In_Floating, In, None);
			
		Fclk=36000000; //APB1 periph => Fclk=36Mhz
		USART3->BRR=Fclk/BaudRate;
		
		NVIC_EnableIRQ(USART3_IRQn);
		NVIC_SetPriority(USART3_IRQn, 5);
	}
  //Bit de stop = 1 par defaut (rien à faire)
	
	//UE = USART Enable, TE=Transmit Enable, RE=Receive Enable, RXNEIE= Interrupt Enable on RXNE (Received data)
	USART->CR1|=USART_CR1_UE|USART_CR1_TE|USART_CR1_RE|USART_CR1_RXNEIE;
}

void MyUSART_Send(USART_TypeDef *USART, char *message){
	
	//*message = contenu du message[i] , si = 0 : TRUE : on sort , si =/ 0 : FALSE on continue
	while(*message){
		USART->DR=*message++; 									//Charge message[i] et incrémente le pointeur
		while (!(USART->SR & USART_SR_TXE));  	//dans registre USART SR : TXE = 1 => Data is fully transferred
	}
}

volatile signed char USART1data;

void USART1_IRQHandler(void) {
	//Normalement l'interruption est cleared en lisant dans DR uniquement
	USART1data =USART1->DR;
	//MyUSART_Send(USART1, &USART1data); //pour tester la bonne réception
}

volatile char USART2data;
void USART2_IRQHandler(void) {
	USART2data =USART2->DR;
	MyUSART_Send(USART2, &USART2data);
}

volatile char USART3data;
void USART3_IRQHandler(void) {
	USART3data =USART3->DR;
	MyUSART_Send(USART3, &USART3data);
}