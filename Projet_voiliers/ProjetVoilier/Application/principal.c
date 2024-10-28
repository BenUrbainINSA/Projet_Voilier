#include "stm32f10x.h"
#include "MyEncoder.h"
#include "Driver_GPIO.h"

int main ( void )
{
	float Encoder_value;
	MyEncoder_Base_Init(TIM2,4*360);
	MyGPIO_Active_EXTI2_IT(0x0f,Reset_MyEncoder);   //reset l'encodeur quand Z vaut 1 !
	while (1)
	{
		Encoder_value=Get_MyEncoder_In_Deg(TIM2);
	}
}
