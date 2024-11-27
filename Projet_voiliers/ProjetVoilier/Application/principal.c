#include "stm32f10x.h"
#include "MyUSART.h"
#include "ModulePlateau.h"
#include "MySPI.h"

int data;

int main ( void )
{
	
	char X0=0;
	
	MySPI_Init(SPI1);
	MySPI_Set_NSS();
	MySPI_Send(0x00);
	
	X0=MySPI_Read();

	
	MySPI_Clear_NSS();
	
	while (1)
	{
		
	}
}
