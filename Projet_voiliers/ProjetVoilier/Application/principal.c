#include "stm32f10x.h"
#include "My_Application.h"

int gpio;
float angle_prev=0.0;
double read_adc=0.0;

int main ( void )
{
	App_Init();
	
	while (1)
	{
		
	App_Run();

		}

	}
