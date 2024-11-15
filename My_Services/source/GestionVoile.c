#include "GestionVoile.h"


void GestionVoile_Init(){
	MyEncoder_Base_Init(TIM2,4*360);
	MyGPIO_Active_EXTI3_IT(0x01,Reset_MyEncoder);   //reset l'encodeur quand Z vaut 1 !
	MyServo_init(TIM4);

}

void GestionVoile_Direction(int Encoder){
		
		int duty_cycle;
	
		if ((Encoder<=180) || (Encoder>=45)){
			duty_cycle = ((2/3)*Encoder*-0.1)+10;
			MyServo_set(TIM4,duty_cycle);	
		}
		else{	
			MyServo_set(TIM4,Voile0deg);
		}


}
