#ifndef GESTIONVOILE_H
#define GESTIONVOILE_H

#include "stm32f10x.h"
#include "MyEncoder.h"
#include "MyServo.h"

#define Voile0deg 5  


/*
@Brief : Permet d'initialiser l'encodeur, le timer et le GPIO associéà la gestion de la voile (TIM2 pour l'exception et TIM4 pour le servo)
@Note
@Paramin
@Paramout
@Example : GestionVoile_Init();
*/
void GestionVoile_Init(void);

/*
@Brief : Tire la voile selon la direction de la girouette
@Note
@Paramin : Encoder = Valeur de l'encodeur en degrés
@Paramout : chavire = variable permettant de savoir si le bâteau chavire (0 ou 1)
@Example
*/
float GestionVoile_Direction(int Encoder,int chavire);



#endif