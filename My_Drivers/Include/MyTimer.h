#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"
#define My_timer_Up 0x1
#define My_timer_Down 0x0
#define PWM_mode_1 0x6
#define PWM_mode_2 0x7

void MyTimer_Base_Init(TIM_TypeDef * Timer,unsigned short ARR,unsigned short PSC,char Type);
void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio,void(*IT_function)(void));

void MyTimer_PWM(TIM_TypeDef * Timer,char Channel,char mode);
void Set_PWM_Duty_Cycle(TIM_TypeDef * Timer,float valeur, char channel);


void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);




#define MyTimer_Base_Start(Timer) (Timer->CR1 |=0x1);
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &=~(0x1));


#endif