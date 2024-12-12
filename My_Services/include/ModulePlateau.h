#ifndef MODULEPLATEAU_H
#define MODULEPLATEAU_H

#define Droite 0
#define Gauche 1

/*
	@Brief : Fonction qui configure les pins, timers et l'usart n�c�ssaires pour la rotation du plateau
	@Note : 	Pins utilis�es :	
							- bit de sens = PC3
							- PWM moteur = PA6
						P�riphs utilis�es :
							- TIM3
							- USART 1
	@Parr in : --
	@Parr out : --
	@Exemple : ModulePlateau_Init();
*/
void ModulePlateau_Init();

/*
	@Brief : Fonction qui commande la rotation du plateau � l'aide de la t�l�commande
	@Note : Si on envoie 100 trop brusquement un mode de protection s'active
					Il faut appeler ModulePlateau_Init() avant d'appeler cette fonction
	@Parr in : -- (utilise les donn�es re�ues sur l'USART 1)
	@Parr out : --
	@Exemple : ModulePlateau_Tourner(Droite, 55);
*/
void ModulePlateau_Tourner();

#endif
