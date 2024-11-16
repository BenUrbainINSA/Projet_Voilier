#include "stm32f10x.h"
#include "MyEncoder.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyUSART.h"

int main ( void )
{
	
	MyUSART_Init(USART1, 9600);
	
	MyUSART_Send(USART1, "Bonjour");
	
	
	while (1)
	{
		
	}
}
