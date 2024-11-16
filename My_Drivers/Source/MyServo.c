#include "MyServo.h"



void MyServo_init(TIM_TypeDef * Timer){  //on va utiliser timer 4 et channel 1 donc sortie sur PB6
	MyGPIO_Init(GPIOB,6,AltOut_Ppull,Out2Mhz,None);
	MyTimer_Base_Init(Timer,5000,288,My_timer_Up);
	MyTimer_Base_Start(Timer);
	MyTimer_PWM(Timer,1,PWM_mode_2);
	Set_PWM_Duty_Cycle(Timer,15/2,1); //on place le servo a 0 
}
void MyServo_set(TIM_TypeDef * Timer,float duty){
	//float angleTOdutyCycle = 100-((1.5+ angle/360)*10)/2;
	float dutyCycle =100-duty;
	Set_PWM_Duty_Cycle(Timer,dutyCycle,1);
}
