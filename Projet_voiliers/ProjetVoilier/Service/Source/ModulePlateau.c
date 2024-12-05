#include "ModulePlateau.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyUSART.h"

void ModulePlateau_Init(){
	MyUSART_Init(USART1, 9600);
	MyGPIO_Init (GPIOC, 3, Out_Ppull, Out10Mhz, 0);
	MyGPIO_Init (GPIOA, 0, AltOut_Ppull, Out10Mhz, 0);
	MyTimer_Base_Init(TIM3, 36, 100, My_timer_Up);
	MyTimer_PWM(TIM3, 1, PWM_mode_1);
}


void ModulePlateau_Tourner(){
	
  //bit de sens		//PWM plateau
	MyTimer_Base_Start(TIM3);
	if (USART1data>=0){
		MyGPIO_Reset (GPIOC, 3);
		Set_PWM_Duty_Cycle(TIM3, USART1data, 1);
	}
	else if (USART1data<0){
		MyGPIO_Set (GPIOC, 3);
		Set_PWM_Duty_Cycle(TIM3, -USART1data, 1);
	}
}

