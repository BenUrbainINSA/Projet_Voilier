#include "stm32f10x.h"
#include "GestionVoile.h"
#include "GestionBatterie.h"
#include "ModuleChavirer.h"
#include "ModulePlateau.h"


/*
@Brief : Initialise tous les services
@Note
@Paramin 
@Paramout
@Example : App_Init();
*/

void App_Init();


/*
@Brief : Appelle et utilise tous les services
@Note
@Paramin 
@Paramout
@Example : App_Run();
*/

void App_Run();

/*
@Brief : Fonction appelé à chaque interruption du timer (soit toutes les 200ms)
@Note
@Paramin 
@Paramout
@Example : CallBack();
*/

void CallBack();