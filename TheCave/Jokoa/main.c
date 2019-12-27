#include "Funtzioak.h"
#include <stdio.h>
//dev

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";		//Argazkiaren helbidea
	
	char Pertsonaia[128] = ".\\media\\player\\Player\\run\\run1.bmp";
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	
	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu
	AtzekoPlanoBerria(Atzekoplanoa);
	while (1)
	{
		for (i = 0; i < 10; i++)
		{
			AtzekoPlanoBerria(Atzekoplanoa);
			Argazkia_Sartu(Irudia, (128 * i), 0);
			SDL_Delay(90);
		}
	}
	Argazkia_Sartu(Pertsonaia, -10, 532, 150, 100);
	teklatua();
	SDL_Delay(10000);
	return 0;
}
