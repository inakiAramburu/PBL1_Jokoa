#include "Funtzioak.h"
#include <stdio.h>
//Ekaitz, egitura

/*
https://assetstore.unity.com/packages/audio/music/orchestral/endless-cave-ambience-54032
https://downloads.khinsider.com/game-soundtracks/album/metal-gear-solid-portable-ops-psp-original-game-soundtrack/20%2520Null.mp3
https://downloads.khinsider.com/game-soundtracks/album/daxter-psp-rip/22%2520-%2520final%2520boss.mp3
https://downloads.khinsider.com/game-soundtracks/album/diablo-1
https://downloads.khinsider.com/game-soundtracks/album/diablo-1/03%2520Dungeon.mp3
*/


int main(int argc, char* str[]) {

	PANTAILAK Pantaila;		//Zein pantailan dagoen jokalaria
	JOKOA Jokoa = EZJOKATZEN;
	ZENTZUA begira = AURRERA;

	int KargaMenua = 0;		//Argazkiak bakarrik behin kargatzeko pantaila bakoitzean
	int KargaLehen = 0;		//""
	int KargaBigarren = 0;		//""
	int KargaKredituak = 0;		//""
	int KargaKontrolak = 0;		//""
	int animazioa;

	if (LeihoaEtaRenderHasi() == 1)		//Lehioa eta renderizatua hasieratzen du
	{
		printf("Ezin izan da 1280x720- ko bideoa ezarri: %s\n", SDL_GetError());		//Erroreak
		return 1;
	}

	Pantaila = MENUA;		//Hasieran Menu pantailan dago jokalaria
	Jokoa = JOKATZEN;

	while (Jokoa)
	{
		while (Pantaila == MENUA)
		{
			KargaKredituak = 0;
			KargaKontrolak = 0;
			if (!KargaMenua)
			{
				KargatuIrudiak(Pantaila);
				KargaMenua = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			RenderMenu();
			Irudikatu();
			SDL_Delay(50);
			
		}
		while (Pantaila == KREDITUAK)
		{
			KargaMenua = 0;
			if (!KargaKredituak)
			{
				KargatuIrudiak(Pantaila);
				KargaKredituak = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			RenderPrestatu(begira);
			Irudikatu();
			SDL_Delay(50);
		}
		while (Pantaila == KONTROLAK)
		{
			KargaMenua = 0;
			if (!KargaKontrolak)
			{
				KargatuIrudiak(Pantaila);
				KargaKontrolak = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			RenderPrestatu(begira);
			Irudikatu();
			SDL_Delay(50);
		}
		while (Pantaila == LEHEN)
		{
			int para_que_funcione;
			KargaMenua = 0;
			if (!KargaLehen)
			{
				KargatuIrudiak(Pantaila);
				KargaLehen = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			Ekintzak(&animazioa);
			RenderPrestatu(begira);
			Irudikatu();

			para_que_funcione =colisioa_detectatu();

			SDL_Delay(100);

		}
	}
	return 0;
}
