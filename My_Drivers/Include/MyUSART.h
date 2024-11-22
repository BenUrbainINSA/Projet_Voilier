#ifndef MYUSART_H
#define MYUSART_H
#include "stm32f10x.h"

/*
	@Brief : Fonction qui configure les périph USART 1, USART 2, USART 3 :
					-pour la réception via la configurations des interruptions
					-pour l'envoi de message
	@Note :  	USART 1 : Tx = PA9 , Rx = PA10
						USART 2 : Tx = PA2 , Rx = PA3
						USART 3 : Tx = PB10 , Rx = PB11
	@Parr in : USARTx, Baud rate
	@Parr out : --
	@Exemple : MyUSART_Init(USART1, 9600);
*/

void MyUSART_Init(USART_TypeDef *USART, int BaudRate);


/*
	@Brief : Fonction qui permet d'envoyer une chaine de charactère sur Tx
	@Parr in : USARTx, message
	@Parr out : --
	@Exemple : MyUSART_Send(USART1, "Bonjour");
*/

void MyUSART_Send(USART_TypeDef *USART, char *message);

/*
	@Brief : 	Interruptions qui permettent de récupérer ce qui arrive sur la broche Rx
	@Parr in : --
	@Parr out : USARTxdata
*/

//extern : permet de partager une variable globale
//volatile : mieux pour des modifications aléatoires

extern volatile signed char USART1data;
void USART1_IRQHandler(void);

extern volatile char USART2data;
void USART2_IRQHandler(void);

extern volatile char USART3data;
void USART3_IRQHandler(void);

#endif