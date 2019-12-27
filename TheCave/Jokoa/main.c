#include "Funtzioak.h"
#include <stdio.h>
//dev

int main(int argc, char* str[]) {
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";		//Argazkiaren helbidea
	
	char Pertsonaia[128] = ".\\media\\player\\Player\\run\\run1.bmp";
	//char Musika2[128] = ".\\media\\sound\\test.wav";
	//MusikaJarri(Musika2);
	
	LeihoaHasi();

	SDL_Delay(2000);		//Txuriz 2 segundu
	AtzekoPlanoBerria(Atzekoplanoa);
	
	Argazkia_Sartu(Pertsonaia, -10, 532, 150, 100);
	teklatua();
	SDL_Delay(10000);
	return 0;
}
