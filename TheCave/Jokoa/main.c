#include "Funtzioak.h"
#include <stdio.h>
//Ekaitz, argazkien eta atzekoplanoen egitura (bukatu gabe, oraindik irudien posizioak falta eta nola irudiak kargatu eta deskargatuko diren)

int main(int argc, char* str[]) {

	PANTAILAK Pantaila;		//Zein pantailan dagoen jokalaria

	int KargaMenua = 0;		//Argazkiak bakarrik behin kargatzeko pantaila bakoitzean
	int KargaLehen = 0;		//""
	int KargaBigarren = 0;		//""

	Pantaila = MENUA;		//Hasieran Menu pantailan dago jokalaria

	if (LeihoaEtaRenderHasi() == 1)		//Lehioa eta renderizatua hasieratzen du
	{
		printf("Ezin izan da 1280x720- ko bideoa ezarri: %s\n", SDL_GetError());		//Erroreak
		return 1;
	}
	
	if (!KargaMenua)
	{
		KargatuIrudiak(Pantaila);
	}

	RenderPrestatu();
	Irudikatu();
	SDL_Delay(2000);		//Txuriz 2 segundu
	Amaitu();
	return 0;
}
