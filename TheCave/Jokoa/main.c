#include "Funtzioak.h"
#include <stdio.h>
#include <SDL.h>

//Mikel

int main(int argc, char* str[])
{
	int irten = 0, ebentua = 0;
	char Atzekoplanoa[256] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	char Atzekoplanoa2[256] = ".\\img\\Nivel2.bmp";
	if (LeihoaHasi() == 1)
	{
		printf("Ezin izan da 1280x720- ko bideoa ezarri: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Delay(2000);		//Txuriz 2 segundu

	while (!irten)
	{
	if (AtzekoPlanoBerria(Atzekoplanoa) == 1)
	{
		fprintf(stderr, "Ezin izan da atzeko palnoa kargatu: %s\n", SDL_GetError());
		return 1;
	}
	};
	
	if (AtzekoPlanoBerria(Atzekoplanoa2) == 1)
	{
		fprintf(stderr, "Eziin izan da atzeko palnoa kargatu: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Delay(2000);		//Txuriz 2 segundu
	return 0;
}



