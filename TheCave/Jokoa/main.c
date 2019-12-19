#include "Funtzioak.h"
#include <stdio.h>
//inaki

int main(int argc, char* str[]) {
	char Atzekoplanoa[256] = ".\\img\\Menu.bmp";		//Argazkiaren helbidea
	char pergamino[256] = ".\\img\\pergamino.bmp";	//foto Argazkiaren helbidea
	char Jolastu[256] = ".\\img\\Jolastu.bmp";
	char Kontrolak[256] = ".\\img\\Kontrolak.bmp";
	char Kredituak[256] = ".\\img\\Kredituak.bmp";

	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu
	AtzekoPlanoBerria(Atzekoplanoa);
	Argazkia_Sartu(pergamino, 380, 100, 480, 500);
	Argazkia_Sartu(Jolastu, 500, 210, 270, 65);
	Argazkia_Sartu(Kontrolak, 480, 300, 300, 72);
	Argazkia_Sartu(Kredituak, 480, 400, 300, 72);
	SDL_Delay(10000);






	return 0;
}
