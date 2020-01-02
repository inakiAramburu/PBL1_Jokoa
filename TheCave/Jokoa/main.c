#include "Funtzioak.h"
#include <stdio.h>
//Gorka

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	char Irudia[128] = ".\\img\\sprites\\Run.bmp";	//foto Argazkiaren 
	char Eraso[128] = ".\\img\\sprites\\Attack.bmp";

	int i = 0;
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	LeihoaHasi();

	//SDL_Delay(2000);		//Txuriz 2 segundu

	AtzekoPlanoBerria(Atzekoplanoa);
	Sprite(Eraso, Atzekoplanoa, 0, 0, );
	//Argazkia_Sartu(Irudia, -10, 532, (128 * i), 0);
	teklatua();

	SDL_Delay(90);


	SDL_Delay(10000);
	return 0;
}