#include "ModuleChavirer.h"
#include "MySPI.h"
#include "MyUSART.h"


void ModuleChavirer_Init(SPI_TypeDef * SPI, USART_TypeDef *USART){
	MyUSART_Init(USART, 9600);
	MySPI_Init(SPI);
	MySPI_Clear_NSS();
	MySPI_Send(0x00|0x2C);
	MySPI_Send(0x0A);
	MySPI_Set_NSS();
	
}



void ModuleChavirer_Run(USART_TypeDef *USART){
	short X=0;
	short Y=0;
	
	char X0;
	char X1;
	char Y0;
	char Y1;
	
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
		MyUSART_Send(USART, "CHAVIREMENT !!!");
	}
}
