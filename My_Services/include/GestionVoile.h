#ifndef GESTIONVOILE_H
#define GESTIONVOILE_H

#include "stm32f10x.h"
#include "MyEncoder.h"
#include "MyServo.h"

#define Voile0deg 10



void GestionVoile_Init();

void GestionVoile_Direction(int Encoder);


#endif