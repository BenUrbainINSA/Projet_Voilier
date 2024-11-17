#include "stm32f10x.h"
#include "MyEncoder.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "MyUSART.h"
#include "ModulePlateau.h"

int main ( void )
{
	
	//MyUSART_Init(USART1, 9600);
	//tester la réception sur Rx
	//MyUSART_Send(USART1, "Bonjour");
	//tester l'envoie sur Tx
	
	//Gestion de la commande du plateau avec télécommande
	if (USART1data<0){
		ModulePlateau_Tourner(Droite, USART1data);
	}
	else if (USART1data>0){
		ModulePlateau_Tourner(Gauche, -USART1data);
	}
	else if (USART1data==0){
		ModulePlateau_Stopper();
	}
	
	while (1)
	{
		
	}
}
