#ifndef MYUSART_H
#define MYUSART_H
#include "stm32f10x.h"

/*
@Brief : Configure un périphérique USART pour la communication série.
@Note : Initialise l'USART pour la transmission et la réception, avec gestion des interruptions pour Rx.
        Les broches associées sont :
        - USART1 : Tx = PA9, Rx = PA10
        - USART2 : Tx = PA2, Rx = PA3
        - USART3 : Tx = PB10, Rx = PB11
@Paramin : 
    USART = Pointeur vers le périphérique USART à configurer (USART1, USART2, USART3).
    BaudRate = Vitesse de communication en bauds (par ex. : 9600, 115200. Ici on prendra tout le temps 9600).
@Paramout : 
@Example : MyUSART_Init(USART1, 9600);
*/
void MyUSART_Init(USART_TypeDef *USART, int BaudRate);

/*
@Brief : Envoie une chaîne de caractères sur la broche Tx.
@Note :
@Paramin : 
    USART = Pointeur vers le périphérique USART configuré (USART1, USART2, USART3).
    message = Pointeur vers la chaîne de caractères à transmettre.
@Paramout : 
@Example : MyUSART_Send(USART1, "Hello World!");
*/
void MyUSART_Send(USART_TypeDef *USART, char *message);



/*
@Brief : Gestionnaire d'interruption pour USART1.
@Note : Récupère les données reçues sur la broche Rx de USART1. 
        La variable globale `USART1data` contient la donnée reçue.
@Paramin : 
@Paramout : 
@Example : void USART1_IRQHandler(void) { // Traitement ici. }
*/

extern volatile signed char USART1data;
void USART1_IRQHandler(void);


/*
@Brief : Gestionnaire d'interruption pour USART2.
@Note : Récupère les données reçues sur la broche Rx de USART2.
        La variable globale `USART2data` contient la donnée reçue.
@Paramin : 
@Paramout : 
@Example : void USART2_IRQHandler(void) { // Traitement ici. }
*/


extern volatile char USART2data;
void USART2_IRQHandler(void);



/*
@Brief : Gestionnaire d'interruption pour USART3.
@Note : Récupère les données reçues sur la broche Rx de USART3.
        La variable globale `USART3data` contient la donnée reçue.
@Paramin : 
@Paramout : 
@Example : void USART3_IRQHandler(void) { // Traitement ici. }
*/

extern volatile char USART3data;
void USART3_IRQHandler(void);

#endif