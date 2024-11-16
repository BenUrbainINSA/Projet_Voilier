#include "ModulePlateau.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"

void ModulePlateau_Tourner(int Sens, int Vitesse){
	
  //bit de sens
	MyGPIO_Init (GPIOC, 3, Out_Ppull, Out10Mhz, 0);
	if (Sens){
	MyGPIO_Reset (GPIOC, 3);
	}
	else{
	MyGPIO_Set (GPIOC, 3);
	}
	
	//PWM plateau
	MyGPIO_Init (GPIOA, 0, AltOut_Ppull, Out10Mhz, 0);
	MyTimer_Base_Init(TIM2, 36, 100, My_timer_Up);
	MyTimer_PWM(TIM2, 1, PWM_mode_1);
	MyTimer_Base_Start(TIM2);
	Set_PWM_Duty_Cycle(TIM2, Vitesse, 1);
}