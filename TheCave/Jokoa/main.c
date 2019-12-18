#include "Funtzioak.h"
#include <stdio.h>
//inaki

int main(int argc, char* str[]) {
	SDL_Init(SDL_INIT_AUDIO);
	char Atzekoplanoa[256] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu

	Musika("test.wav");


		AtzekoPlanoBerria(Atzekoplanoa);


	return 0;
}