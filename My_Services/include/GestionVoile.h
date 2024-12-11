#ifndef GESTIONVOILE_H
#define GESTIONVOILE_H

#include "stm32f10x.h"
#include "MyEncoder.h"
#include "MyServo.h"

#define Voile0deg 5  


/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void GestionVoile_Init(void);

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
float GestionVoile_Direction(int Encoder,int chavire);



#endif