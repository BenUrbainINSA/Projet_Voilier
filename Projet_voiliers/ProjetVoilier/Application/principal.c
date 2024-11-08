#include "stm32f10x.h"
#include "MyEncoder.h"
#include "Driver_GPIO.h"

float Encoder_value;
int gpio;

int main ( void )
{
	MyEncoder_Base_Init(TIM2,4*360);
	MyGPIO_Active_EXTI3_IT(0x01,Reset_MyEncoder);   //reset l'encodeur quand Z vaut 1 !
	while (1)
	{
		Encoder_value=Get_MyEncoder_In_Deg(TIM2);
		gpio = MyGPIO_Read(GPIOA,4);
	}
}
