#include "Funtzioak.h"
#include <stdio.h>
//Mikel

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";
	char Atzekoplanoa2[128] = ".\\media\\fondos\\Nivel2.bmp";//Argazkiaren helbidea
	char pergamino[128] = ".\\media\\menu\\pergamino.bmp";	//foto Argazkiaren helbidea
	char Jolastu[128] = ".\\media\\menu\\Jolastu.bmp";
	char Kontrolak[128] = ".\\media\\menu\\Kontrolak.bmp";
	char Kredituak[128] = ".\\media\\menu\\Kredituak.bmp";
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu

	AtzekoPlanoBerria(Atzekoplanoa);
	//Argazkia_Sartu(pergamino, 380, 100, 480, 500);
	
	while (1)
	{
		int x, y;

		
		SDL_GetMouseState(&x, &y);

		if (!((x > 500 && x < 770) && (y > 210 && y < 275)) || ((x > 480 && x < 790) && (y > 300 && y < 382)) || ((x > 480 && x < 790) && (y > 400 && y < 482)) )
		{
			Argazkia_Sartu(pergamino, 380, 100, 480, 500);
			Argazkia_Sartu(Jolastu, 500, 210, 270, 65);
			Argazkia_Sartu(Kontrolak, 480, 300, 300, 72);
			Argazkia_Sartu(Kredituak, 480, 400, 300, 72);

			SDL_Delay(100);
			
			
		}

		if ((x > 500 && x < 770) && (y > 210 && y < 275))
		{
			Argazkia_Sartu(pergamino, 380, 100, 480, 500);
			Argazkia_Sartu(Jolastu, 500, 210, 280, 75);
			Argazkia_Sartu(Kontrolak, 480, 300, 300, 72);
			Argazkia_Sartu(Kredituak, 480, 400, 300, 72);
			SDL_Delay(100);
			AtzekoPlanoBerria2(Atzekoplanoa2);
		}

		if ((x > 480 && x < 790) && (y > 300 && y < 382))
			{
				Argazkia_Sartu(pergamino, 380, 100, 480, 500);
				Argazkia_Sartu(Jolastu, 500, 210, 270, 65);
				Argazkia_Sartu(Kontrolak, 480, 300, 310, 82);
				Argazkia_Sartu(Kredituak, 480, 400, 300, 72);
				SDL_Delay(100);
			}

			
		if ((x > 480 && x < 790) && (y > 400 && y < 482))
			{
				Argazkia_Sartu(pergamino, 380, 100, 480, 500);
				Argazkia_Sartu(Jolastu, 500, 210, 270, 65);
				Argazkia_Sartu(Kontrolak, 480, 300, 300, 72);
				Argazkia_Sartu(Kredituak, 480, 400, 310, 82);
				SDL_Delay(100);
			}
		
		
		SDL_Delay(100);
			
		
		
		
		
	}
	return 0;
}
