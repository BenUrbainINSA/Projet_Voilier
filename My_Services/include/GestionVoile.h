#ifndef GESTIONVOILE_H
#define GESTIONVOILE_H

#include "stm32f10x.h"
#include "MyEncoder.h"
#include "MyServo.h"

#define Voile0deg 5  



void GestionVoile_Init(void);

void GestionVoile_Direction(int Encoder);


#endif