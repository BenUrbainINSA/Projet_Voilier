#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h"
#define My_timer_Up 0x1
#define My_timer_Down 0x0
#define PWM_mode_1 0x6
#define PWM_mode_2 0x7


/*
@Brief : Initialise le timer en mode de base.
@Note : 
@Paramin : 
    Timer = Pointeur vers le timer à configurer (par exemple TIM1, TIM2, etc.).
    ARR = Valeur maximale du compteur (Auto-Reload Register).
    PSC = Valeur du prescaler pour diviser l'horloge.
    Type = Mode de comptage (My_timer_Up pour comptage ascendant, My_timer_Down pour descendant).
@Paramout : 
@Example : MyTimer_Base_Init(TIM2, 0xFFFF, 72, My_timer_Up);
*/
void MyTimer_Base_Init(TIM_TypeDef * Timer,unsigned short ARR,unsigned short PSC,char Type);

/*
@Brief : Active une interruption pour le timer spécifié.
@Paramin : 
    Timer = Pointeur vers le timer à configurer.
    Prio = Priorité de l'interruption (0 = priorité élevée).
    IT_function = Fonction de rappel à exécuter lors de l'interruption.
@Paramout : 
@Example : MyTimer_ActiveIT(TIM2, 1, MyCallbackFunction);
*/
void MyTimer_ActiveIT(TIM_TypeDef * Timer, char Prio,void(*IT_function)(void));

/*
@Brief : Configure le timer pour le mode PWM.
@Note : 
@Paramin : 
    Timer = Pointeur vers le timer à configurer.
    Channel = Canal PWM (1, 2, 3 ou 4).
    mode = Mode PWM (PWM_mode_1 ou PWM_mode_2).
@Paramout : 
@Example : MyTimer_PWM(TIM2, 1, PWM_mode_1);
*/
void MyTimer_PWM(TIM_TypeDef * Timer,char Channel,char mode);

/*
@Brief : Définit le rapport cyclique (duty cycle) pour un canal PWM.
@Note : 
@Paramin : 
    Timer = Pointeur vers le timer configuré en mode PWM.
    valeur = Rapport cyclique en pourcentage (0 à 100).
    channel = Canal PWM à configurer (1, 2, 3 ou 4).
@Paramout : 
@Example : Set_PWM_Duty_Cycle(TIM2, 50.0, 1); // Définit un duty cycle de 50% sur le canal 1.
*/
void Set_PWM_Duty_Cycle(TIM_TypeDef * Timer,float valeur, char channel);

/*
@Brief : Gestionnaire d'interruption pour TIM2.
@Note : Doit être défini par l'utilisateur pour gérer les événements liés à TIM2.
@Paramin : 
@Paramout : 
@Example : void TIM2_IRQHandler(void) { // Code personnalisé ici }
*/
void TIM2_IRQHandler(void);

/*
@Brief : Gestionnaire d'interruption pour TIM3.
@Note : Doit être défini par l'utilisateur pour gérer les événements liés à TIM3.
@Paramin : 
@Paramout : 
@Example : void TIM3_IRQHandler(void) { // Code personnalisé ici }
*/
void TIM3_IRQHandler(void);

/*
@Brief : Gestionnaire d'interruption pour TIM4.
@Note : Doit être défini par l'utilisateur pour gérer les événements liés à TIM4.
@Paramin : 
@Paramout : 
@Example : void TIM4_IRQHandler(void) { // Code personnalisé ici }
*/
void TIM4_IRQHandler(void);




#define MyTimer_Base_Start(Timer) (Timer->CR1 |=0x1);
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &=~(0x1));


#endif