#include "stm32f10x.h"
#include "MyUSART.h"
#include "ModulePlateau.h"

int pwm =0;

int main ( void )
{
	ModulePlateau_Init();	
	while (1)
	{
		ModulePlateau_Tourner();	
	}
}
