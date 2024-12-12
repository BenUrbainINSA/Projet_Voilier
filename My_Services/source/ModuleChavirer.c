#include "ModuleChavirer.h"
#include "MySPI.h"
#include "MyUSART.h"


void ModuleChavirer_Init(SPI_TypeDef * SPI){

	MySPI_Init(SPI2);
	
	MySPI_Clear_NSS();
	MySPI_Send(0x00|0x2C);
	MySPI_Send(0x0A);
	MySPI_Set_NSS();
	/*
	MySPI_Clear_NSS();
	MySPI_Send(0x80|0x2C);
	BW_RATE=MySPI_Read();
	MySPI_Set_NSS();
	*/

	MySPI_Clear_NSS();
	MySPI_Send(0x00|0x2D);
	MySPI_Send(0x0F);
	MySPI_Set_NSS();
	
}



int ModuleChavirer_Run(){
	
	int chav=0;
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
		
	if ((X>29000 | X<-29000) | (Y>29000 | Y<-29000)) {
		chav=1;
	} else {
		chav=0;
	}
		
	return chav;
}
