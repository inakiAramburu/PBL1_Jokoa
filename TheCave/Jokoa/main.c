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
	printf("Controler name: %s\n", SDL_JoystickName(joystick));

	printf("Num Axes: %d\n", SDL_JoystickNumAxes(joystick));

	printf("Num Buttos: %d\n", SDL_JoystickNumButtons(joystick));


	SDL_Event event;
	while (1)
	{
		while (SDL_PollEvent(&event))
		{

			if (event.type == SDL_JOYAXISMOTION)
			{
				if (event.jaxis.axis == 0)
				{

					if (event.jaxis.value > 0)
					{
						printf("derecha\n");
					}

					if (event.jaxis.value < 0)
					{
						printf("izquierda\n");
					}
					printf("%d:\n", event.jaxis.value);
				}
			}

		}

	}



	//////////////////////////////////////////////////////////////////////////////////
	SDL_Delay(10000);
	return 0;
}
