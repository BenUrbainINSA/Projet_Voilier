#ifndef MODULEPLATEAU_H
#define MODULEPLATEAU_H

#define Droite 0
#define Gauche 1

/*
	@Brief : Fonction qui configure les pins et les timers n�c�ssaire pour la rotation du plateau
	@Note : 	Pins utilis� :	
							- bit de sens = PC3
							- PWM moteur = PA0
						P�riph utilis� :
							- TIM2
	@Parr in : --
	@Parr out : --
	@Exemple : ModulePlateau_Init();
*/
void ModulePlateau_Init();

/*
	@Brief : Fonction qui commande la rotation du plateau
	@Note : Si on envoie 100 trop brusquement un mode de protection s'active
	@Parr in : Sens (Droite ou Gauche), Vitesse [0, 100]
	@Parr out : --
	@Exemple : ModulePlateau_Tourner(Droite, 55);
*/
void ModulePlateau_Tourner(int Sens, int Vitesse);

/*
	@Brief : Fonction qui stop le plateau
	@Parr in : --
	@Parr out : --
	@Exemple : ModulePlateau_Stopper();
*/
void ModulePlateau_Stopper();



/*
	@Brief : Fonction qui controle le plateau par t�l�commande
	@Note : Fonction � appeler dans un while (en boucle)
	@Parr in : data (variable globale li�e � l'USART utilis�e)
	@Parr out : --
	@Exemple : ModulePlateau_tele(USART1data);
*/
void ModulePlateau_Tele(char data);

#endif
