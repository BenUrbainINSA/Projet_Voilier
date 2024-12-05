#include "GestionTransmission.h"

#define T 25 
char Payload[T];

void GestionTransmission_Init(){
	GestionBatterie_Init();
	MyTimer_Base_Init(TIM1,400, 5000,My_timer_Up);  //set un timer de 3sec 
	MyTimer_Base_Start(TIM1);    //on utilise le timer 
	MyTimer_ActiveIT (TIM1,0x05,GestuinTransmission_Trans);

}

void GestuinTransmission_Trans(){
	
		float angle =0;
		GestionBatterie_Read(ADC1,USART1);
		
		snprintf(Payload,T, "Deg %0.2f\n", angle);	
		MyUSART_Send(USART1,Payload);
	
}
	

