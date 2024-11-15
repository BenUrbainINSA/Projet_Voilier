#ifndef MYENCODER_H
#define MYENCODER_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"

#define ENCODER_RESOLUTION 360
#define OFFSET_ENCODER 186

//on paramètre l'encodeur en quadrature donc SMS=011, paramètre statique , de meme on va utiliser PA0 et PA1 pour les channels du timer 
void MyEncoder_Base_Init(TIM_TypeDef * Timer,unsigned short ARR);   
int16_t Get_MyEncoder(TIM_TypeDef * Timer);

float Get_MyEncoder_In_Deg(TIM_TypeDef * Timer);

void Reset_MyEncoder(TIM_TypeDef * Timer);

#endif