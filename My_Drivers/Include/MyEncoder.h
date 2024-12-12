#ifndef MYENCODER_H
#define MYENCODER_H

#include "stm32f10x.h"
#include "Driver_GPIO.h"

#define ENCODER_RESOLUTION 360
#define OFFSET_ENCODER 0 //186
//on paramètre l'encodeur en quadrature donc SMS=011, paramètre statique , de meme on va utiliser PA0 et PA1 pour les channels du timer 

/*
@Brief : Initialise le timer pour fonctionner en mode encodeur.
@Note
@Paramin : Timer = Pointeur vers le timer à utiliser 
					 ARR = Valeur maximale du compteur (Auto-Reload Register), correspondant à la plage de comptage de l'encodeur.
@Paramout
@Example : MyEncoder_Base_Init(TIM1, 4*360); 
*/

void MyEncoder_Base_Init(TIM_TypeDef * Timer,unsigned short ARR);   

/*
@Brief : Récupère la valeur brute actuelle de l'encodeur.
@Note
@Paramin : Timer = Pointeur vers le timer configuré pour le mode encodeur.
@Paramout : Retourne un entier signé (int16_t) correspondant à la valeur brute de l'encodeur.
@Example : int16_t position = Get_MyEncoder(TIM2);
*/

int16_t Get_MyEncoder(TIM_TypeDef * Timer);

/*
@Brief : Convertit la valeur brute de l'encodeur en degrés.
@Note
@Paramin : Timer = Pointeur vers le timer configuré pour le mode encodeur.
@Paramout : Retourne un entier représentant la position angulaire de l'encodeur en degrés.
@Example : int position_deg = Get_MyEncoder_In_Deg(TIM2);
*/

int Get_MyEncoder_In_Deg(TIM_TypeDef * Timer);



/*
@Brief : Réinitialise la valeur de l'encodeur à 0.
@Note
@Paramin : Timer = Pointeur vers le timer configuré pour le mode encodeur.
@Paramout
@Example : Reset_MyEncoder(TIM2); 
*/

void Reset_MyEncoder(TIM_TypeDef * Timer);

#endif