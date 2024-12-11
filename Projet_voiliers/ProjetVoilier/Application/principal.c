#include "stm32f10x.h"
#include "ModulePlateau.h"
//#include "MySPI.h"
//#include "MyUSART.h"
#include "ModuleChavirer.h"

int data;

int main ( void )
{
	int ILCHAVIRE=0;

	ModulePlateau_Init();
	ModuleChavirer_Init(SPI2);
	
	while (1)
	{

		ModulePlateau_Tourner();
		ILCHAVIRE=ModuleChavirer_Run();
	}
}
