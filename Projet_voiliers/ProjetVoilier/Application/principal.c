#include "stm32f10x.h"
#include "GestionVoile.h"


int Encoder_value;
int gpio;
float angle =0.0;
float angle_prev=0.0;

int main ( void )
{
//	MyEncoder_Base_Init(TIM2,4*360);
//	MyGPIO_Active_EXTI3_IT(0x01,Reset_MyEncoder);   //reset l'encodeur quand Z vaut 1 !
	
//	MyServo_init(TIM4);
	GestionVoile_Init();
	
	
	while (1)
	{
	Encoder_value=Get_MyEncoder_In_Deg(TIM2);
		//Encoder_value=Encoder_value-196;
//		gpio = MyGPIO_Read(GPIOA,4);
//		if (angle != angle_prev){
//			MyServo_set(TIM4,angle);
//			angle_prev= angle;

	GestionVoile_Direction(Encoder_value);
		
		}

	}
