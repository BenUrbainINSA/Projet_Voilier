#ifndef MYENCODER_H
#define MYENCODER_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"

#define ENCODER_RESOLUTION 360
#define OFFSET_ENCODER 0 //186
//on param�tre l'encodeur en quadrature donc SMS=011, param�tre statique , de meme on va utiliser PA0 et PA1 pour les channels du timer 

/*
@Brief : Initialise le timer pour fonctionner en mode encodeur.
@Note
@Paramin : Timer = Pointeur vers le timer � utiliser 
					 ARR = Valeur maximale du compteur (Auto-Reload Register), correspondant � la plage de comptage de l'encodeur.
@Paramout
@Example : MyEncoder_Base_Init(TIM1, 4*360); 
*/

void MyEncoder_Base_Init(TIM_TypeDef * Timer,unsigned short ARR);   

/*
@Brief : R�cup�re la valeur brute actuelle de l'encodeur.
@Note
@Paramin : Timer = Pointeur vers le timer configur� pour le mode encodeur.
@Paramout : Retourne un entier sign� (int16_t) correspondant � la valeur brute de l'encodeur.
@Example : int16_t position = Get_MyEncoder(TIM2);
*/

int16_t Get_MyEncoder(TIM_TypeDef * Timer);

/*
@Brief : Convertit la valeur brute de l'encodeur en degr�s.
@Note
@Paramin : Timer = Pointeur vers le timer configur� pour le mode encodeur.
@Paramout : Retourne un entier repr�sentant la position angulaire de l'encodeur en degr�s.
@Example : int position_deg = Get_MyEncoder_In_Deg(TIM2);
*/

int Get_MyEncoder_In_Deg(TIM_TypeDef * Timer);



/*
@Brief : R�initialise la valeur de l'encodeur � 0.
@Note
@Paramin : Timer = Pointeur vers le timer configur� pour le mode encodeur.
@Paramout
@Example : Reset_MyEncoder(TIM2); 
*/

void Reset_MyEncoder(TIM_TypeDef * Timer);

#endif