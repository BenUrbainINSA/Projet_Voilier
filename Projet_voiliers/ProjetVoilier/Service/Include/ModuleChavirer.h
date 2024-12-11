#ifndef MODULECHAVIRER_H
#define MODULECHAVIRER_H
#include "MySPI.h"
#include "MyUSART.h"


void ModuleChavirer_Init(SPI_TypeDef * SPI);
	
int ModuleChavirer_Run();



#endif