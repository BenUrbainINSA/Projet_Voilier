#include "stm32f10x.h"
#include "MyUSART.h"
#include "ModulePlateau.h"

int pwm =0;

int main ( void )
{
	
	MyUSART_Init(USART1, 9600);
	//tester la réception sur Rx
	MyUSART_Send(USART1, "Bonjour");
	//tester l'envoie sur Tx
	
	ModulePlateau_Init();
	
	
	while (1)
	{

		ModulePlateau_Tele(USART1data);
			
	
	}
}
