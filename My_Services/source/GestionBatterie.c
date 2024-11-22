#include "GestionBatterie.h"

void GestionBatterie_Init(){
	MyGPIO_Init(GPIOC,0,In_Floating,In,None);
	MyADC_Init(ADC1,10,Te_1_5,Single_Not_Cont);
	MyUSART_Init(USART1,9600);
}


double GestionBatterie_Read(ADC_TypeDef * ADC,USART_TypeDef *USART){
	double value = MyADC_Read(ADC);
	
}

