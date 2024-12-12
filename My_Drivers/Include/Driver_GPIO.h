#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

#define In_Floating 0x1
#define In_PullUpDown 0x2
#define In_Analog 0x0
#define Out_Ppull 0x0
#define Out_OD 0x1
#define AltOut_Ppull 0x2
#define AltOut_0D 0x3

#define In 0x0
#define Out2Mhz 0x2
#define Out10Mhz 0x1
#define Out50Mhz 0x3

#define Up 1
#define Down -1
#define None 0


/* 
type : Si c'est en In ou en Out xMhz 
Pull : correspond au niveau de l'�tage Pull Up/down si utilis� (Up/Down) sinon (None)
*/

/*
@Brief Initialise le GPIOx,avec le pin les param�tres demand�s
@Note  ---
@Paramin  GPIO_TypeDef * GPIO
					Char GPIO_Pin
					char GPIO_Conf
					char type
					int Pull
@Paramout ---
@Example MyGPIO_Init (GPIOA,1,In_PullUpDwn,In,Up)  : Pin 1 de GPIOA en mode mode Input Pull up
*/
void MyGPIO_Init (GPIO_TypeDef * GPIO , char GPIO_Pin, char GPIO_Conf, char type, int Pull);

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
int MyGPIO_Read (GPIO_TypeDef * GPIO, char GPIO_Pin);

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void MyGPIO_Set (GPIO_TypeDef * GPIO, char GPIO_Pin);

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void MyGPIO_Reset (GPIO_TypeDef * GPIO, char GPIO_Pin);

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void MyGPIO_Toggle (GPIO_TypeDef * GPIO, char GPIO_Pin);


/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void MyGPIO_Active_EXTI3_IT(char Prio, void(*IT_function)(TIM_TypeDef * Timer));   // EXTIx avec x=2 car on veut param�trer sur PA02, pas 

/*
@Brief 
@Note
@Paramin
@Paramout
@Example
*/
void EXTI2_IRQHandler(void);

#endif