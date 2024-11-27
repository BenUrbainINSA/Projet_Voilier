#include "GestionBatterie.h"


#define Taille 50 
char Message[Taille];

void GestionBatterie_Init(){
	MyGPIO_Init(GPIOC,0,In_Floating,In,None);
	MyADC_Init(ADC1,10,Te_1_5,Single_Not_Cont);
	MyUSART_Init(USART1,9600);
}


void GestionBatterie_Read(ADC_TypeDef * ADC,USART_TypeDef *USART){
	MyADC_StartConv(ADC);
	double value = MyADC_Read(ADC)*3.3*13;  //adc codé sur 12 bits
	value*=0.0002441;
	snprintf(Message,Taille, "%.2f V\n", value);
	
	MyUSART_Send(USART1,Message);
}

