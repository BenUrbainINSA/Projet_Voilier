#include "stm32f10x.h"
#include "MyTimer.h"

int main ( void )
{
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN ; //EN timer2 
//	TIM2->PSC=5000-1; 
//	TIM2->ARR=7200-1; //scale de 36 000 000 pour avoir 500ms de periode 
//	TIM2->CR1 |=0x1 ; 
//	TIM2->CR1 &=~(0x1<<4);
	
	MyTimer_Base_Init(TIM3,7200, 5000,My_timer_Up);
	MyTimer_Base_Start(TIM3);
	MyTimer_ActiveIT (TIM3,0x2);
	
	
	
	while (1)
	{
	
	}
}
