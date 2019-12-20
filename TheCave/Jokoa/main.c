#include "Funtzioak.h"
#include <stdio.h>
//mando

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";		//Argazkiaren helbidea
	char Pertsonaia[128] = ".\\media\\player\\Player\\run\\run1.bmp";
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	
	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu
	AtzekoPlanoBerria(Atzekoplanoa);

	Argazkia_Sartu(Pertsonaia, -10, 532, 150, 100);
	////////////////////////////////////MANDO//////////////////////////////////////////////
	SDL_Init(SDL_INIT_JOYSTICK);
	SDL_Joystick* joystick = SDL_JoystickOpen(0);
	printf("nombre del mando: %s\n", SDL_JoystickName(joystick));

	printf("ejes: %d\n", SDL_JoystickNumAxes(joystick));

	printf("Botones: %d\n", SDL_JoystickNumButtons(joystick));


	SDL_Event event;
	while (1)
	{
		while (SDL_PollEvent(&event) != 0)
		{

			if (event.type == SDL_JOYHATMOTION)
			{
				printf("evento\n");
				if (event.jhat.value & SDL_HAT_DOWN)
				{
					while (SDL_HAT_DOWN)
					{
						printf("baja\n");

					}
					//printf("baja\n");
				}

			}



		}

	}



	//////////////////////////////////////////////////////////////////////////////////
	SDL_Delay(10000);
	return 0;
}



