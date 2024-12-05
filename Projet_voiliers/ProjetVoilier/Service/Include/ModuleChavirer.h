#ifndef MODULECHAVIRER_H
#define MODULECHAVIRER_H
#include "MySPI.h"
#include "MyUSART.h"


void ModuleChavirer_Init(SPI_TypeDef * SPI, USART_TypeDef *USART);
	
void ModuleChavirer_Run(USART_TypeDef *USART);



#endif