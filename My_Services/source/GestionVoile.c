#include "GestionVoile.h"


void GestionVoile_Init(){
	MyEncoder_Base_Init(TIM2,4*360);
	MyGPIO_Active_EXTI3_IT(0x01,Reset_MyEncoder);   //reset l'encodeur quand Z vaut 1 !
	MyServo_init(TIM4);

}



void GestionVoile_Direction(int Encoder){
		
		float duty_cycle;
		float angle_voile_deg; 

	
		if (((Encoder<=180) && (Encoder>=45))){
			angle_voile_deg = (0.6667)*Encoder - 30.0;      
			duty_cycle = 5.0 + (0.0557)*angle_voile_deg;
			MyServo_set(TIM4,duty_cycle);	
		}
		else if ((Encoder<=315) && (Encoder>=180)){
			angle_voile_deg = -(0.6667)*Encoder + 210;  
			duty_cycle = 5.0 + (0.0557)*angle_voile_deg;
			MyServo_set(TIM4,duty_cycle);	
		}
		else{	
			MyServo_set(TIM4,Voile0deg);
		}


}