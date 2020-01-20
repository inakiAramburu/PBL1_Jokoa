#define _CRT_SECURE_NO_WARNINGS
#include "Basic.h"
#include "Motion.h"
#include "Event.h"
#include "Image.h"
#include <string.h>
#include <stdio.h>
#include "Sound.h"

HITBOX hitbox;

extern PERTSONAIA pertsonaia;
extern ETSAIA etsaia[ETSAI_KOPURUA + 1];
extern PONG easteregg;
extern TIROAK jaurtigai[100];


extern BOSSFIGHT faseak;

extern int IrudiZnbk;

int kont;

SDL_bool a = SDL_FALSE;
SDL_bool d = SDL_FALSE;
SDL_bool espacio = SDL_FALSE;
SDL_bool k = SDL_FALSE;
SDL_bool w = SDL_FALSE;
SDL_bool f3 = SDL_FALSE;
SDL_bool s = SDL_FALSE;
SDL_bool gora = SDL_FALSE;
SDL_bool behera = SDL_FALSE;

ROL Ordenagailua;

void EbentuakKonprobatu(SDL_bool* Jokatzen, PANTAILAK* Pantaila, int* pAnimazioa, ZENTZUA* begira, int BizirikDaudenEtsaiak[], int BizirikKopurua)
{	
	SDL_bool enter = SDL_FALSE;
	static char sekuentzia[16] = "";

	SAGUA klika;
	SDL_Event ebentua;
	do
	{
		while (SDL_PollEvent(&ebentua))
		{
			switch (ebentua.type)
			{
				*Pantaila += 1;
			case SDL_QUIT:
				Amaitu(Jokatzen, Pantaila);
				break;
			case SDL_MOUSEBUTTONUP:
				ZeinKlikatuDa(ebentua.button, &klika);
				KonprobatuKlika(Pantaila, klika, Jokatzen);
				break;
			case SDL_KEYDOWN:
				switch (ebentua.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
				{
				case SDL_SCANCODE_D:
					a = SDL_FALSE;
					if (!d && !pertsonaia.erortzen && !pertsonaia.salto && pertsonaia.sprite != HIL)
					{
						pertsonaia.sprite = KORRIKA;
						pertsonaia.erasotzen = SDL_FALSE;
						*pAnimazioa = 0;
					}
					d = SDL_TRUE;
					break;
				case SDL_SCANCODE_A:
					d = SDL_FALSE;
					if (!a && !pertsonaia.erortzen && !pertsonaia.salto && pertsonaia.sprite != HIL)
					{
						pertsonaia.sprite = KORRIKA;
						pertsonaia.erasotzen = SDL_FALSE;
						*pAnimazioa = 0;
					}
					a = SDL_TRUE;
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SDL_TRUE;
					break;
				case SDL_SCANCODE_K:
					if (!pertsonaia.erortzen && !pertsonaia.salto)
					{
						a = SDL_FALSE;
						d = SDL_FALSE;
					}

					if (!pertsonaia.erasotzen)
					{
						k = SDL_TRUE;
					}
					break;
				case SDL_SCANCODE_ESCAPE:
					Amaitu(Jokatzen, Pantaila);
					break;
				case SDL_SCANCODE_W:
					if (!a && !pertsonaia.erortzen && !pertsonaia.salto)
					{
						pertsonaia.erasotzen = SDL_FALSE;
					}
					w = SDL_TRUE;
					break;
				case SDL_SCANCODE_F3:
					f3 = !f3;
					break;
				case SDL_SCANCODE_S:
					s = SDL_TRUE;
					break;
				case SDL_SCANCODE_UP:
					gora = SDL_TRUE;
					break;
				case SDL_SCANCODE_DOWN:
					behera = SDL_TRUE;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (ebentua.key.keysym.scancode)
				{
				case SDL_SCANCODE_D:
					d = SDL_FALSE;
					break;
				case SDL_SCANCODE_A:
					a = SDL_FALSE;
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SDL_FALSE;
					break;
				case SDL_SCANCODE_K:
					k = SDL_FALSE;
					break;
				case SDL_SCANCODE_W:
					w = SDL_FALSE;
					break;
				case SDL_SCANCODE_S:
					s = SDL_FALSE;
					break;
				case SDL_SCANCODE_UP:
					gora = SDL_FALSE;
					break;
				case SDL_SCANCODE_DOWN:
					behera = SDL_FALSE;
					break;
				case SDL_SCANCODE_P:
					if (*Pantaila != MENUA)
					{
						strcpy(sekuentzia, "P");
						musica_Pong(PONG_PALA);
					}
					break;
				case SDL_SCANCODE_O:
					strcat(sekuentzia, "O");
					musica_Pong(PONG_PARETA);
					break;
				case SDL_SCANCODE_N:
					strcat(sekuentzia, "N");
					musica_Pong(PONG_PALA);
					break;
				case SDL_SCANCODE_G:
					strcat(sekuentzia, "G");
					musica_Pong(PONG_IRABAZI);
					break;
				case SDL_SCANCODE_RETURN:
					if (pertsonaia.bizirik)
					{
						if (!enter)
						{
							ImgKargatu(".\\media\\menu\\Pausa.bmp", 56, 67, 1200, 630);
							RenderPrestatu(*begira, BizirikDaudenEtsaiak, BizirikKopurua);
							Irudikatu();
						}
						else
						{
							IrudiZnbk = IrudiakKendu(IrudiZnbk - 1);
						}
						enter = !enter;
					}
				break;
			
				
				}
				break;
			}
			if (strcmp(sekuentzia, "PONG") == 0)
			{
				*Pantaila = AUKERATUMODUA;
				strcpy(sekuentzia, "");
			}
		}
		if (enter)
		{
			SDL_Delay(100);
		}
	}while (enter);
}

void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA* klika)
{
	switch (ebentua.button)
	{
	case SDL_BUTTON_LEFT:
		*klika = EZKER;
		break;

	case SDL_BUTTON_RIGHT:
		*klika = ESKUIN;
		break;

	case SDL_BUTTON_MIDDLE:
		*klika = ERDIA;
		break;
	}
}

void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika, SDL_bool *Jokatzen)
{
	int x, y;
	switch (*Pantaila)
	{
	case MENUA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 515 && y > 175) && (x < 765 && y < 275))
			{
				RenderPrestatu(AURRERA, 0, 0);
				Irudikatu();
				PertsonaiaHasieratu();
				EtsaiakHasieratu();
				Animazioa();
				*Pantaila = FINALA;
			}
			else if ((x > 510 && y > 300) && (x < 760 && y < 400))
			{
				*Pantaila = KONTROLAK;
			}
			else if ((x > 512 && y > 425) && (x < 762 && y < 525))
			{
				*Pantaila = KREDITUAK;
			}
		}
		break;

	case KREDITUAK:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1063 && y > 99) && (x < 1109 && y < 142))
			{
				*Pantaila = MENUA;
			}
		}
		break;

	case KONTROLAK:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1063 && y > 99) && (x < 1109 && y < 142))
			{
				*Pantaila = MENUA;
			}
		}
		break;
	case ATERA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 494 && y > 443) && (x < 800 && y < 533))
			{
				*Pantaila = LEHEN;
			}
			else if ((x > 587 && y > 547) && (x < 705 && y < 582))
			{
				*Jokatzen = SDL_FALSE;
			}
		}
		break;
	case AUKERATUMODUA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 381 && y > 454) && (x < 578 && y < 578)) //ONLINE
			{
				*Pantaila = AUKERATUZERBITZUA;
			}
			if ((x > 705 && y > 454) && (x < 895 && y < 578)) //LOCAL
			{
				*Pantaila = MINIJOKOA;
			}
		}
		break;
	case AUKERATUZERBITZUA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 381 && y > 454) && (x < 578 && y < 578)) //CREATE
			{
				*Pantaila = AUKERAZERBITZARIA;
			}
			if ((x > 705 && y > 454) && (x < 895 && y < 578)) //JOIN
			{
				*Pantaila = AUKERABEZEROA;
			}
		}
		break;
	case AUKERAZERBITZARIA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1159 && y > 639) && (x < 1236 && y < 677))
			{
				*Pantaila = MINIJOKOA;
			}
		}
		break;
	case AUKERABEZEROA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1159 && y > 639) && (x < 1236 && y < 677))
			{
				*Pantaila = MINIJOKOA;
			}
		}
		break;
	}
}



void KolisioakKonprobatu(void* pixels, int pitch, Uint8 bpp, int BizirikDaudenEtsaiak[], int* BizirikKopurua, ZENTZUA begira, int* pAnimazioa)
{

	int PertzonaiaEzkerMuga = pertsonaia.DestSprite.x + 46;
	int PertzonaiaEskuinMuga = pertsonaia.DestSprite.x + 82;
	int PertzonaiaYGoikoa = pertsonaia.DestSprite.y;
	int PertzonaiaYBekoa = pertsonaia.DestSprite.y + 59;
	int YBekoa = pertsonaia.DestSprite.y + 52;
	int altuera = 0;
	int etsaiaxEzker;
	int etsaiaxEskuin;
	int	etsaiayGoikoa;
	int	etsaiayBehekoa;
	int j;

	for (j = 0; j < *BizirikKopurua; j++)
	{
		//detecta el tipo de enemigo
		if (BizirikDaudenEtsaiak[j] >= 0 && BizirikDaudenEtsaiak[j] <= 4)
		{
			altuera = 0;
		}
		else if (BizirikDaudenEtsaiak[j] >= 5 && BizirikDaudenEtsaiak[j] <= 9)
		{
			altuera = 7;
		}
		//DETECTAR A QUE LADO MIRA EL PERSONAGE

		etsaiaxEzker = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.x + 9;
		etsaiaxEskuin = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.x + 29;
		etsaiayGoikoa = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.y + altuera;
		etsaiayBehekoa = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.y + 43;
		/*
				printf("etsaiaxEzker: %d\n", etsaiaxEzker);
				printf("etsaiaxEskuin: %d\n", etsaiaxEskuin);
				printf("etsaiayGoikoa: %d\n", etsaiayGoikoa);
				printf("etsaiayBehekoa: %d\n", etsaiayBehekoa);
				*/

		if (pertsonaia.sprite == ERASO && pertsonaia.erasotzen && *pAnimazioa > 4)
		{
			if (begira == AURRERA)
			{
				

				if ((etsaiaxEzker >= PertzonaiaEskuinMuga && etsaiaxEzker <= PertzonaiaEskuinMuga + 33) && ( PertzonaiaYGoikoa + 29 >= etsaiayGoikoa && PertzonaiaYGoikoa + 29  <= etsaiayBehekoa))
				{
					EtsaiaKendu(j, BizirikDaudenEtsaiak, *BizirikKopurua);
					--* BizirikKopurua;
				}
			}
			else
			{
				if ((etsaiaxEskuin >= PertzonaiaEzkerMuga - 33 && etsaiaxEskuin <= PertzonaiaEzkerMuga) && (PertzonaiaYGoikoa + 29 >= etsaiayGoikoa && PertzonaiaYGoikoa + 29 <= etsaiayBehekoa))
				{
					EtsaiaKendu(j, BizirikDaudenEtsaiak, *BizirikKopurua);
					--* BizirikKopurua;
				}
			}
		}
		if (((PertzonaiaEskuinMuga >= etsaiaxEzker && PertzonaiaEskuinMuga <= etsaiaxEskuin) || (PertzonaiaEzkerMuga <= etsaiaxEskuin && PertzonaiaEskuinMuga >= etsaiaxEzker)) && (PertzonaiaYBekoa >= etsaiayGoikoa && PertzonaiaYGoikoa <= etsaiayBehekoa))
		{
			if (pertsonaia.sprite != HIL)
			{
				*pAnimazioa = 0;
			}
			pertsonaia.sprite = HIL;
			
		}
	}

//////////////////////////////tetectar el color//////////////////////////////
hitbox.goikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 66, pertsonaia.DestSprite.y + 0);		//Burua
//Ezkerreko aldea
hitbox.ezker.goikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 46, pertsonaia.DestSprite.y + 11);

hitbox.ezker.erdikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 46, pertsonaia.DestSprite.y + 32);
hitbox.ezker.behekoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 46, pertsonaia.DestSprite.y + 52);
//Eskuineko aldea
hitbox.eskuin.goikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 82, pertsonaia.DestSprite.y + 11);
hitbox.eskuin.erdikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 82, pertsonaia.DestSprite.y + 32);
hitbox.eskuin.behekoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 82, pertsonaia.DestSprite.y + 52);
//Behekoa
hitbox.behekoa.ezker = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 54, pertsonaia.DestSprite.y + 59);
hitbox.behekoa.eskuin = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 75, pertsonaia.DestSprite.y + 59);
if (hitbox.behekoa.eskuin == GORRIA || hitbox.behekoa.ezker == GORRIA || hitbox.eskuin.behekoa == GORRIA || hitbox.ezker.behekoa == GORRIA)
{
	if (pertsonaia.sprite != HIL)
	{
		*pAnimazioa = 0;
	}
	pertsonaia.sprite = HIL;
	pertsonaia.erortzen = SDL_FALSE;
	pertsonaia.salto = SDL_FALSE;
}
}

void PongKolisioa()
{	//pelota y la primera pala

	if ((easteregg.pilota.x <= easteregg.Player1.x + easteregg.Player1.w) && ((easteregg.pilota.y + easteregg.pilota.h - 8 >= easteregg.Player1.y&& easteregg.pilota.y + easteregg.pilota.h <= easteregg.Player1.y + easteregg.Player1.h)|| (easteregg.pilota.y + 8 <= easteregg.Player1.y + easteregg.Player1.h && easteregg.pilota.y >= easteregg.Player1.y)))
	{
		musica_Pong(PONG_PALA);
		easteregg.abiadurax -= 1;
		if (easteregg.abiaduray < 0)
		{
			easteregg.abiaduray -= 1;
		}
		else
		{
			easteregg.abiaduray += 1;
		}
		easteregg.abiadurax *= -1;
		easteregg.pilota.x = easteregg.Player1.x + easteregg.Player1.w + 1;
	}
	//ganar
	else if( easteregg.pilota.x <= easteregg.Player1.x + easteregg.Player1.w / 2)
	{
		easteregg.P2puntuazioa++;
		printf("\n P1: %d	P2: %d", easteregg.P1puntuazioa, easteregg.P2puntuazioa);
		BerrizJaurti();
		musica_Pong(PONG_IRABAZI);

	}
	
	//pelota y la segunda pala
	if ((easteregg.pilota.x + easteregg.pilota.w >= easteregg.Player2.x) && ((easteregg.pilota.y + easteregg.pilota.h - 8 >= easteregg.Player2.y && easteregg.pilota.y + easteregg.pilota.h <= easteregg.Player2.y + easteregg.Player2.h) || (easteregg.pilota.y + 8 <= easteregg.Player2.y + easteregg.Player2.h && easteregg.pilota.y >= easteregg.Player2.y)))
	{
		musica_Pong(PONG_PALA);
		easteregg.abiadurax += 1;
		if (easteregg.abiaduray < 0)
		{
			easteregg.abiaduray -= 1;
		}
		else
		{
			easteregg.abiaduray += 1;
		}
		easteregg.abiadurax *= -1;
		easteregg.pilota.x = easteregg.Player2.x - (1 + easteregg.pilota.w);
	}
	//ganar

	else if (easteregg.pilota.x >= easteregg.Player2.x + easteregg.Player2.w/2)
	{
		easteregg.P1puntuazioa++;
		printf("\n P1: %d	P2: %d", easteregg.P1puntuazioa, easteregg.P2puntuazioa);
		BerrizJaurti();
		musica_Pong(PONG_IRABAZI);
	}
}

void KolisioakBoss(PANTAILAK* Pantaila, ZENTZUA begira, int* pAnimazioa, int* bAnimazioa, int BizirikDaudenEtsaiak[], int* BizirikKopurua)
{
	static Uint32 spawnrate = 0;
	static SDL_bool spawn = SDL_FALSE;
	int PertzonaiaEzkerMuga = pertsonaia.DestSprite.x + 46;
	int PertzonaiaEskuinMuga = pertsonaia.DestSprite.x + 82;
	int PertzonaiaYGoikoa = pertsonaia.DestSprite.y;
	int PertzonaiaYBekoa = pertsonaia.DestSprite.y + 59;
	int YBekoa = pertsonaia.DestSprite.y + 52;

	for (int j = 0; j < 40; j++)
	{
		if ((jaurtigai[j].tiroa.x <= PertzonaiaEskuinMuga && jaurtigai[j].tiroa.x + 10 >= PertzonaiaEzkerMuga) && (jaurtigai[j].tiroa.y + 10 >= PertzonaiaYGoikoa && jaurtigai[j].tiroa.y <= PertzonaiaYBekoa))
		{
			if (pertsonaia.sprite != HIL)
			{
				*pAnimazioa = 0;
			}
			pertsonaia.sprite = HIL;
		}
	}
	if (pertsonaia.sprite == ERASO && pertsonaia.erasotzen && *pAnimazioa > 4 && (PertzonaiaYGoikoa + 29 >= BOSS.DestSprite.y && PertzonaiaYGoikoa + 29 <= BOSS.DestSprite.y + 149))
	{
		if (begira == AURRERA)
		{
			if (BOSS.DestSprite.x + 16 >= PertzonaiaEskuinMuga && BOSS.DestSprite.x + 16 <= PertzonaiaEskuinMuga + 33)
			{

				if (faseak == SLEEP)
				{
					MusikaJOKUA(MusikaBOSS);

					faseak = TRANSFORM;
					*bAnimazioa = 0;
				}
				else if (SDL_TICKS_PASSED(SDL_GetTicks(), spawnrate) && faseak != TRANSFORM)
				{
					faseak = MUGITU;
					kont++;
					spawn = SDL_TRUE;
					spawnrate = SDL_GetTicks() + 2000;
					Efektuak(BOOS_KOLPE_EFEKTUA);

				}
			}
		}
		else
		{
			if (BOSS.DestSprite.x + 109 >= PertzonaiaEzkerMuga - 33 && BOSS.DestSprite.x + 109 <= PertzonaiaEzkerMuga)
			{
				if (faseak == SLEEP)
				{
					MusikaJOKUA(MusikaBOSS);

					faseak = TRANSFORM;
					*bAnimazioa = 0;
				}
				else if (SDL_TICKS_PASSED(SDL_GetTicks(), spawnrate) && faseak != TRANSFORM)
				{
					faseak = MUGITU;
					kont++;
					spawn = SDL_TRUE;
					spawnrate = SDL_GetTicks() + 2000;
					Efektuak(BOOS_KOLPE_EFEKTUA);
				}
				
			}
		}
	}
	if (faseak != SLEEP && (((PertzonaiaEskuinMuga >= BOSS.DestSprite.x + 16 && PertzonaiaEskuinMuga <= BOSS.DestSprite.x + 109) || (PertzonaiaEzkerMuga <= BOSS.DestSprite.x + 109 && PertzonaiaEskuinMuga >= BOSS.DestSprite.x + 16)) && (PertzonaiaYBekoa >= BOSS.DestSprite.y && PertzonaiaYGoikoa <= BOSS.DestSprite.y + 149)))
	{
		if (pertsonaia.sprite != HIL)
		{
			*pAnimazioa = 0;
		}
		pertsonaia.sprite = HIL;
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), spawnrate) && spawn)
	{
		for (int i = 0; i < 10; i++)
		{
			if (!etsaia[i].bizirik)
			{
				EtsaiaKokatu(i, etsaia[i].DestSprite.x, etsaia[i].DestSprite.y, BizirikDaudenEtsaiak, BizirikKopurua);
			}
		}
		spawn = SDL_FALSE;
	}
	if (kont == 3)
	{
		PertsonaiaHil(kont);
		*Pantaila = ATERA;
	}
}