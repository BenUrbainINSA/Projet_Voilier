#include "stm32f10x.h"
#include "ModulePlateau.h"
#include "MySPI.h"
#include "MyUSART.h"
#include "ModuleChavirer.h"

int data;

int main ( void )
{
	/*
	short X=0;
	short Y=0;
	
	char X0;
	char X1;
	char Y0;
	char Y1;
	
	char BW_RATE;
	
	MyUSART_Init(USART1, 9600);
	
	MySPI_Init(SPI1);
	
	MySPI_Clear_NSS();
	MySPI_Send(0x00|0x2C);
	MySPI_Send(0x0A);
	MySPI_Set_NSS();
	
	MySPI_Clear_NSS();
	MySPI_Send(0x80|0x2C);
	BW_RATE=MySPI_Read();
	MySPI_Set_NSS();
	*/
/*
	MySPI_Clear_NSS();
	MySPI_Send(0x00|0x2D);
	MySPI_Send(0x0F);
	MySPI_Set_NSS();
	*/
	ModuleChavirer_Init(SPI1, USART1);
	
	while (1)
	{
		/*
		MySPI_Clear_NSS();
		MySPI_Send(0xC0|0x34);
		X0=MySPI_Read();
		X1=MySPI_Read();
		Y0=MySPI_Read();
		Y1=MySPI_Read();
		X=X0<<8|X1;
		Y=Y0<<8|Y1;
		MySPI_Set_NSS();
		
		if ((X>10000 | X<-10000) | (Y>10000 | Y<-10000)) {
			MyUSART_Send(USART1, "CHAVIREMENT !!!");
		}*/
		ModuleChavirer_Run(USART1);
	}
}
