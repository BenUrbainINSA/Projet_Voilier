#ifndef MYADC_H
#define MYADC_H

#include "stm32f10x.h"
#include "MyTimer.h"



/*
Channel : Canal de conversion de (0 à 15)
Te : temps d'echanteillonage
Timer : Timer utilisé pour le triger externe 
mode : modes de fonctionnement de l'adc 

*/

//TE  nombe de cycle : ex 1_5 = 1.5 cycles 
#define Te_1_5 0x0
#define Te_7_5 0x1
#define Te_13_5 0x2
#define Te_28_5 0x3
#define Te_41_5 0x4
#define Te_55_5 0x5
#define Te_71_5 0x6
#define Te_239_5 0x7 


//MODE
#define Single_Not_Cont 0x0
#define Single_Cont  0x01


/*
@Brief : Initialise l'ADC pour un canal et une configuration spécifiques.
@Note
@Paramin : ADC = pointeur vers le périphérique ADC à configurer
					 channel = Canal ADC à utiliser
					 Te = Temps d'échantillonage, on utilisera les constantes Te_1_5,...
					 mode = mode de fonctionnement de l'ADC (on utilisera seulement le Single_Not_Cont)

@Paramout
@Example : MyADC_Init(ADC1, 5, Te_13_5, Single_Not_Cont); 
*/
void MyADC_Init(ADC_TypeDef * ADC,char channel,char Te,char mode );


/*
@Brief : Démarre la conversion ADC.
@Note
@Paramin: ADC = Pointeur vers le périphérique ADC à utiliser.
@Paramout
@Example : MyADC_StartConv(ADC1); 
*/

void MyADC_StartConv(ADC_TypeDef * ADC);

/*
@Brief : Lit le résultat de la conversion ADC.
@Note
@Paramin : ADC = Pointeur vers le périphérique ADC à lire.
@Paramout : Retourne un entier représentant la valeur numérique convertie (comprise entre 0 et 4095).
@Example : int adc_value = MyADC_Read(ADC1); 
*/
int MyADC_Read(ADC_TypeDef * ADC);
//void ADC1_2_IRQHandler(void);



#endif

