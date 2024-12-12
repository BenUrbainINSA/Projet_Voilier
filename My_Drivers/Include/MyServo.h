#ifndef MYSERVO_H
#define MYSERVO_H

#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

/*
@Brief : Initialise le timer pour contr�ler un servo-moteur.
@Note :
@Paramin : 
    Timer = Pointeur vers le timer � configurer.
@Paramout : 
@Example : MyServo_init(TIM2);
*/
void MyServo_init(TIM_TypeDef * Timer);

/*
@Brief : D�finit la position du servo-moteur en ajustant le rapport cyclique du signal PWM.
@Note : Le rapport cyclique contr�le la position angulaire du servo. 
        Typiquement, une plage de 1ms � 2ms correspond � 0 - 180�
@Paramin : 
    Timer = Pointeur vers le timer configur� pour le mode PWM.
    duty = Rapport cyclique en pourcentage (dans notre cas il sera toujours compris entre 5% et 10% pour un angle entre 90 et 180�
@Paramout : 
@Example : MyServo_set(TIM2, 7.5);
*/
void MyServo_set(TIM_TypeDef * Timer,float duty);


#endif 