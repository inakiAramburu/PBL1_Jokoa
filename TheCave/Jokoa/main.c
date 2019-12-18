#include "Funtzioak.h"
#include <stdio.h>
//inaki

int main(int argc, char* str[]) {
	char Atzekoplanoa[256] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	char Atzekoplanoa2[256] = ".\\img\\Menu.bmp";
	LeihoaHasi();
	
	SDL_Delay(2000);		//Txuriz 2 segundu

	AtzekoPlanoBerria(Atzekoplanoa);
	AtzekoPlanoBerria2(Atzekoplanoa2);
	
	
	variable();
	




	return 0;
}
