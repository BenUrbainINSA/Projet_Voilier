#ifndef MODULEPLATEAU_H
#define MODULEPLATEAU_H

#define Droite 0
#define Gauche 1

/*
	-Fonction qui commande la rotation du plateau
	-Pins utilisés :
		- bit de sens = PC3
		- PWM moteur = PA0
	-Arguments :
		- Sens = Droite ou Gauche
		- Vitesse = entier de 0 à 100
	-Périph utilisés :
		- TIM2
*/
void ModulePlateau_Tourner(int Sens, int Vitesse);

/*
	-Fonction qui stoppe le TIMER (donc la PWM)
*/
void ModulePlateau_Stopper();

#endif
