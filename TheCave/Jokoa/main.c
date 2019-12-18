#include "Funtzioak.h"
#include <stdio.h>


int main(int argc, char* str[]) {
	char Atzekoplanoa[256] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	LeihoaHasi();
	
	SDL_Delay(2000);		//Txuriz 2 segundu

	AtzekoPlanoBerria(Atzekoplanoa);
	
	return 0;
}
