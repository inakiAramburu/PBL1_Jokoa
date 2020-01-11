#include "Funtzioak.h"
#include <stdio.h>

#include <SDL_net.h>

//Fusion, saltoa eta nivel aldaketa//

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
	int pAnimazioa;

	int BizirikDaudenEtsaiak[ETSAI_KOPURUA];
	int BizirikKopurua;

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
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargaMenua = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			if (Pantaila != MENUA)
			{
				break;
			}
			RenderMenu();
			Irudikatu();
			SDL_Delay(50);
		}
		while (Pantaila == KREDITUAK)
		{
			KargaMenua = 0;
			if (!KargaKredituak)
			{
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargaKredituak = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			RenderPrestatu(begira, BizirikDaudenEtsaiak, BizirikKopurua);
			Irudikatu();


			//////////////////////////server///////////////////////////////////////
			SDL_Init(SDL_INIT_EVERYTHING);
			SDLNet_Init();
			IPaddress ip;

			SDLNet_ResolveHost(&ip, NULL, 1234);

			TCPsocket server = SDLNet_TCP_Open(&ip);
			TCPsocket client;
			char* enviado = "hola";

			while (1)
			{
				client = SDLNet_TCP_Accept(server);
				if (client)
				{
					//aqui se puede comunicar
					SDLNet_TCP_Send(client, enviado,100);
					SDLNet_TCP_Close(client);
					break;
				}
			}
			SDLNet_TCP_Close(server);



			////////////////////////////////////////////////////////////


			SDL_Delay(50);
		}
		while (Pantaila == KONTROLAK)
		{
			KargaMenua = 0;
			if (!KargaKontrolak)
			{
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargaKontrolak = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			RenderPrestatu(begira, BizirikDaudenEtsaiak, BizirikKopurua);
			Irudikatu();

			/////////////////////////cliente////////////////////////////////////////
			SDL_Init(SDL_INIT_EVERYTHING);
			SDLNet_Init();
			IPaddress ip;

			SDLNet_ResolveHost(&ip, "127.0.0.1", 1234);

			
			TCPsocket client=SDLNet_TCP_Open(&ip);
			char numerorecvido[100];
			SDLNet_TCP_Recv(client, numerorecvido, 100);
			

			printf("lrecivido: %s", numerorecvido);

			SDLNet_TCP_Close(client);



			////////////////////////////////////////////////////////////
			SDL_Delay(50);
		}
		while (Pantaila == LEHEN)
		{
			KargaMenua = 0;
			if (!KargaLehen)
			{
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargatuMapa(LEHENENGO_MASKARA, &pixels, &pitch, &bpp);
				KargaLehen = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			Ekintzak(&pAnimazioa, &begira, pixels, pitch, bpp, &Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
			RenderPrestatu(begira, BizirikDaudenEtsaiak, BizirikKopurua);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == BIGARREN)
		{
			KargaLehen = 0;
			if (!KargaBigarren)
			{
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargatuMapa(BIGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaBigarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			Ekintzak(&pAnimazioa, &begira, pixels, pitch, bpp, &Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
			RenderPrestatu(begira, BizirikDaudenEtsaiak, BizirikKopurua);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == HIRUGARREN)
		{
			KargaBigarren = 0;
			if (!KargaHirugarren)
			{
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargatuMapa(HIRUGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaHirugarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			Ekintzak(&pAnimazioa, &begira, pixels, pitch, bpp, &Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
			RenderPrestatu(begira, BizirikDaudenEtsaiak, BizirikKopurua);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == LAUGARREN)
		{
			KargaHirugarren = 0;
			if (!KargaLaugarren)
			{
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargatuMapa(LAUGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaLaugarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			Ekintzak(&pAnimazioa, &begira, pixels, pitch, bpp, &Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
			RenderPrestatu(begira, BizirikDaudenEtsaiak, BizirikKopurua);
			Irudikatu();
			SDL_Delay(80);
		}
		while (Pantaila == BOSTGARREN)
		{
			KargaLaugarren = 0;
			if (!KargaBostgarren)
			{
				KargatuIrudiak(Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
				KargatuMapa(BOSTGARREN_MASKARA, &pixels, &pitch, &bpp);
				KargaBostgarren = 1;
			}
			EbentuakKonprobatu(&Jokoa, &Pantaila, &pAnimazioa, &begira);
			Ekintzak(&pAnimazioa, &begira, pixels, pitch, bpp, &Pantaila, BizirikDaudenEtsaiak, &BizirikKopurua);
			RenderPrestatu(begira, BizirikDaudenEtsaiak, BizirikKopurua);
			Irudikatu();
			SDL_Delay(80);
		}
	}
	return 0;
}
