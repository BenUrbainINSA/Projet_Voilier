#include "stm32f10x.h"
#include "GestionVoile.h"


int Encoder_value;
int gpio;
float angle =0.0;
float angle_prev=0.0;

int main ( void )
{
	GestionVoile_Init();
	
	
	while (1)
	{
	Encoder_value=Get_MyEncoder_In_Deg(TIM2);
	GestionVoile_Direction(Encoder_value);
		
		}

	}
