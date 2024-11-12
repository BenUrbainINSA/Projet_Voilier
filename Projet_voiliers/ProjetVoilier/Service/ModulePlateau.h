#ifndef MODULEPLATEAU_H
#define MODULEPLATEAU_H

#define Droite 0
#define Gauche 1

/*
	Utilise la pin PC3 (bit de sens) et PA0 (PWM)
	Sens = Droite ou Gauche
	Vitesse = entier de 0 à 100
*/
void TournerPlateau(int Sens, int Vitesse);

#endif
