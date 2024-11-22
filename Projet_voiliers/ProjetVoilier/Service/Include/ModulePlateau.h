#ifndef MODULEPLATEAU_H
#define MODULEPLATEAU_H

#define Droite 0
#define Gauche 1

/*
	@Brief : Fonction qui configure les pins et les timers nécéssaire pour la rotation du plateau
	@Note : 	Pins utilisé :	
							- bit de sens = PC3
							- PWM moteur = PA0
						Périph utilisé :
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
	@Brief : Fonction qui controle le plateau par télécommande
	@Note : Fonction à appeler dans un while (en boucle)
	@Parr in : data (variable globale liée à l'USART utilisée)
	@Parr out : --
	@Exemple : ModulePlateau_tele(USART1data);
*/
void ModulePlateau_Tele(char data);

#endif
