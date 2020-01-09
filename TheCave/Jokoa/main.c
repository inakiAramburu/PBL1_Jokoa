#include "Funtzioak.h"
#include <stdio.h>
//dev, saltoa eta nivel aldaketa//

int main(int argc, char* argv[]) {

	PANTAILAK Pantaila;		//Zein pantailan dagoen jokalaria
	JOKOA Jokoa = EZJOKATZEN;
	void* pixels = NULL;
	int pitch;
	Uint8 bpp;

	if (LeihoaEtaRenderHasi() == 1)		//Lehioa eta renderizatua hasieratzen du
	{
		printf("Ezin izan da 1280x720- ko bideoa ezarri: %s\n", SDL_GetError());		//Erroreak
		return 1;
	}
	ZENTZUA begira = AURRERA;

	int KargaMenua = 0;		//Argazkiak bakarrik behin kargatzeko pantaila bakoitzean
	int KargaLehen = 0;		//""
	int KargaBigarren = 0;		//""
	int KargaHirugarren = 0;		//""
	int KargaLaugarren = 0;		//""
	int KargaBostgarren = 0;		//""
	int KargaKredituak = 0;		//""
	int KargaKontrolak = 0;		//""
	int animazioa;

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
			KargaMenua = 0;
			if (!KargaLehen)
			{
				KargatuIrudiak(Pantaila);
				KargatuMapa(LEHENENGO_MASKARA, &pixels, &pitch, &bpp);
				KargaLehen = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			Ekintzak(&animazioa, &begira, pixels, pitch, bpp, &Pantaila);
			RenderPrestatu(begira);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == BIGARREN)
		{
			KargaLehen = 0;
			if (!KargaBigarren)
			{
				KargatuIrudiak(Pantaila);
				KargatuMapa(BIGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaBigarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			Ekintzak(&animazioa, &begira, pixels, pitch, bpp, &Pantaila);
			RenderPrestatu(begira);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == HIRUGARREN)
		{
			KargaBigarren = 0;
			if (!KargaHirugarren)
			{
				KargatuIrudiak(Pantaila);
				KargatuMapa(HIRUGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaHirugarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			Ekintzak(&animazioa, &begira, pixels, pitch, bpp, &Pantaila);
			RenderPrestatu(begira);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == LAUGARREN)
		{
			KargaHirugarren = 0;
			if (!KargaLaugarren)
			{
				KargatuIrudiak(Pantaila);
				KargatuMapa(LAUGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaLaugarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			Ekintzak(&animazioa, &begira, pixels, pitch, bpp, &Pantaila);
			RenderPrestatu(begira);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == BOSTGARREN)
		{
			KargaLaugarren = 0;
			if (!KargaBostgarren)
			{
				KargatuIrudiak(Pantaila);
				KargatuMapa(BOSTGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaBostgarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &animazioa, &begira);
			Ekintzak(&animazioa, &begira, pixels, pitch, bpp, &Pantaila);
			RenderPrestatu(begira);
			Irudikatu();
			SDL_Delay(80);
		}
	}
	return 0;
}
