#ifndef MYSERVO_H
#define MYSERVO_H

#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void MyServo_init(TIM_TypeDef * Timer);

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void MyServo_set(TIM_TypeDef * Timer,float duty);


#endif 