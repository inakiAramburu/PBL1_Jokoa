#include "Funtzioak.h"
#include <stdio.h>
//Gorka

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	char Atzekoplanoa2[128] = ".\\img\\Nivel2.bmp";
	if (LeihoaHasi() == 1)
	{
		printf("Ezin izan da 1280x720- ko bideoa ezarri: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(2000);		//Txuriz 2 segundu


	if (AtzekoPlanoBerria(Atzekoplanoa) == 1)
	{
		fprintf(stderr, "Ezin izan da atzeko palnoa kargatu: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Delay(2000);		//Txuriz 2 segundu
	if (AtzekoPlanoBerria(Atzekoplanoa2) == 1)
	{
		fprintf(stderr, "Ezin izan da atzeko palnoa kargatu: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Delay(2000);		//Txuriz 2 segundu
	return 0;
}
