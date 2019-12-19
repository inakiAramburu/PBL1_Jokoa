#include "Funtzioak.h"
#include <stdio.h>
//dev

int main(int argc, char* str[]) {
	char Atzekoplanoa[256] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
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
	
	return 0;
}
