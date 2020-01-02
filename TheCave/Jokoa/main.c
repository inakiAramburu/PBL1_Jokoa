#include "Funtzioak.h"
#include <stdio.h>
//itxaso

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";		//Argazkiaren helbidea
	char Irudia[128] = ".\\media\\player\\Run.bmp";	//foto Argazkiaren 
	int i = 0;
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	LeihoaHasi();

	//SDL_Delay(2000);		//Txuriz 2 segundu

	AtzekoPlanoBerria(Atzekoplanoa);
	//Argazkia_Sartu(Irudia, -10, 532, (128 * i), 0);
	teklatua();

	SDL_Delay(90);


	SDL_Delay(10000);
	return 0;
}
