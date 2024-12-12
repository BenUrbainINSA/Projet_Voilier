#ifndef MODULECHAVIRER_H
#define MODULECHAVIRER_H
#include "MySPI.h"
#include "MyUSART.h"



/*
@Brief : Initialise l'accéléromètre du voilier avec le module SPI
@Note
@Paramin : SPI = Pointeur vers le périphérique SPI utilisé (Ici ce sera SPI2)
@Paramout
@Example : ModuleChavirer_Init(SPI2);
*/

void ModuleChavirer_Init(SPI_TypeDef * SPI);
	
	
/*
@Brief : Fonction qui notifie si le voilier chavire
@Note
@Paramin 
@Paramout : 1 si le voilier chavire, 0 sinon.
@Example : ModuleChavirer_Run();
*/	
	
int ModuleChavirer_Run();



#endif