#include "Funtzioak.h"
#include <stdio.h>
//Mikel

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";		//Argazkiaren helbidea
	char pergamino[128] = ".\\media\\menu\\pergamino.bmp";	//foto Argazkiaren helbidea
	char Jolastu[128] = ".\\media\\menu\\Jolastu.bmp";
	char Kontrolak[128] = ".\\media\\menu\\Kontrolak.bmp";
	char Kredituak[128] = ".\\media\\menu\\Kredituak.bmp";
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu

	AtzekoPlanoBerria(Atzekoplanoa);
	Argazkia_Sartu(pergamino, 380, 100, 480, 500);
	
	while (1)
	{
		int x, y, buleano = 0;

		
		SDL_GetMouseState(&x, &y);

		if ((x > 500 && x < 770) && (y > 210 && y < 275))
		{
			
			Argazkia_Sartu(Jolastu, 510, 220, 280, 75);
		}
		else
		{
			Argazkia_Sartu(pergamino, 380, 100, 480, 500);
			buleano = 1;
			
				//Argazkia_Sartu(Jolastu, 500, 210, 270, 65);

		}
		
		
		
	}
	
	//Argazkia_Sartu(Kontrolak, 480, 300, 300, 72);
	//Argazkia_Sartu(Kredituak, 480, 400, 300, 72);



	
	






	return 0;
}
