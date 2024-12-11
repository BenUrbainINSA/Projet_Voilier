#include "My_Application.h"

#define T 25 
char Mes[T];



int k=0;
int update=0;
float angle =0.0;
int Encoder_value;
int chavirage =0;


void App_Init(){
	GestionVoile_Init();
	//GestionTransmission_Init();
	GestionBatterie_Init();
	
	MyTimer_Base_Init(TIM1,2000, 7200,My_timer_Up);  //set un timer de 3sec 
	MyTimer_Base_Start(TIM1);    //on utilise le timer 
	MyTimer_ActiveIT (TIM1,0x05,CallBack);
	ModulePlateau_Init();
	ModuleChavirer_Init(SPI2);
	}

void App_Run(){
	if (update==1){
		update=0;
		
		if (k%15==0){
			GestionBatterie_Read(ADC1,USART1);
			
			snprintf(Mes,T, "Deg %0.2f\n", angle);	
			MyUSART_Send(USART1,Mes);
			k=0;
		}
		
		if (k%1 ==0){
			chavirage=ModuleChavirer_Run();
			Encoder_value=Get_MyEncoder_In_Deg(TIM2);
			angle=GestionVoile_Direction(Encoder_value,chavirage);
			
			if (chavirage==1){
				MyUSART_Send(USART1,"JE CHAVIRE\n");
			}
			ModulePlateau_Tourner();
			
		}
		
	}
}


void CallBack(){
		k++;
		update=1;
}