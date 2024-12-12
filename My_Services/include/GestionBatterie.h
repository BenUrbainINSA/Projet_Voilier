#ifndef GESTIONBATTERIE_H
#define GESTIONBATTERIE_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyADC.h"
#include "MyUSART.h"
#include "MyTimer.h"
#include <string.h>
#include <stdio.h>


/*
@Brief : Initialise le GPIOC, l'ADC1 et l'USART1 pour lire l'état de la batterie du voilier
@Note
@Paramin 
@Paramout
@Example : GestionBatterie_Init();
*/

void GestionBatterie_Init();


/*
@Brief : Renvoie la valeur de tension de la batterie lue par l'ADC sur le moniteur
@Note
@Paramin : ADC = Pointeur vers le périphérique ADC à utiliser.
					 USART = Pointeur vers le périphérique USART à utiliser.
@Paramout
@Example : GestionBatterie_Read(ADC1,USART1);
*/

void GestionBatterie_Read(ADC_TypeDef * ADC,USART_TypeDef *USART);


#endif