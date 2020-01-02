#include "Funtzioak.h"
#include <stdio.h>
//Gorka

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	char Irudia[128] = ".\\img\\sprites\\Run.bmp";	//foto Argazkiaren 
	char Eraso[128] = ".\\img\\sprites\\Attack.bmp"; //8
	char Idle[128] = ".\\img\\sprites\\Idle.bmp"; //6
	char Kea[128] = ".\\img\\sprites\\Humo.bmp"; //4

	int i = 0;
	int abiadura = 0;
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	LeihoaHasi();

	AtzekoPlanoBerria(Atzekoplanoa);
	//Sprite(Eraso, Atzekoplanoa, 300, 300, 8);

	//////////////////////////////////////////////////////////////////

	Sprite(Kea, Atzekoplanoa, 100, 560, 4);

	

	while (1) {

		SDL_Event evento;
		while (SDL_PollEvent(&evento) != 0) {

			if (evento.type == SDL_KEYDOWN)
			{
				switch (evento.key.keysym.scancode)
				{

				case SDL_SCANCODE_X:
					printf("X\n");
					abiadura = 0;
					Sprite(Eraso, Atzekoplanoa, 100, 560, 8);

				}
			}
			if (evento.type == SDL_KEYUP)
			{

				switch (evento.key.keysym.scancode)
				{

				case SDL_SCANCODE_X:
					//Sprite(); DESTRUIR IMAGEN
					break;

				}
			}
		}
		Sprite(Idle, Atzekoplanoa, 100, 560, 6);

	}
	
	SDL_Delay(10000);
	return 0;
}