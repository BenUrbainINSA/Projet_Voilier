#ifndef GESTIONBATTERIE_H
#define GESTIONBATTERIE_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"
#include "MyADC.h"
#include "MyUSART.h"
#include <string.h>
#include <stdio.h>

void GestionBatterie_Init();


void GestionBatterie_Read(ADC_TypeDef * ADC,USART_TypeDef *USART);


#endif