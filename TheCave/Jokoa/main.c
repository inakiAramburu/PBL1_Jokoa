#include "Funtzioak.h"
#include <stdio.h>
//Itxaso

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";		//Argazkiaren helbidea
	char pergamino[128] = ".\\media\\menu\\pergamino.bmp";	//foto Argazkiaren helbidea
	char Jolastu[128] = ".\\media\\menu\\Jolastu.bmp";
	char Kontrolak[128] = ".\\media\\menu\\Kontrolak.bmp";
	char Kredituak[128] = ".\\media\\menu\\Kredituak.bmp";
	char Pertsonaia[128] = ".\\media\\player\\Player\\run\\run1.bmp";
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	
	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu
	AtzekoPlanoBerria(Atzekoplanoa);
	Argazkia_Sartu(pergamino, 380, 100, 480, 500);
	Argazkia_Sartu(Jolastu, 500, 210, 270, 65);
	Argazkia_Sartu(Kontrolak, 480, 300, 300, 72);
	Argazkia_Sartu(Kredituak, 480, 400, 300, 72);
	Argazkia_Sartu(Pertsonaia, -10, 532, 150, 100);

	SDL_Delay(10000);
	return 0;
}
