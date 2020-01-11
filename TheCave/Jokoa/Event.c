#include "Basic.h"
#include "Image.h"
#include "Event.h"
#include "Motion.h"
#include "Sound.h"

HITBOX hitbox;

extern PERTSONAIA pertsonaia;

BOOLEANOA a = FALSE;
BOOLEANOA d = FALSE;
BOOLEANOA espacio = FALSE;
BOOLEANOA k = FALSE;
BOOLEANOA w = FALSE;
BOOLEANOA f3 = FALSE;

void EbentuakKonprobatu(BOOLEANOA* Jokatzen, PANTAILAK* Pantaila, int* pAnimazioa, ZENTZUA* begira)
{
	SAGUA klika;
	SDL_Event ebentua;
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
			KonprobatuKlika(Pantaila, klika);
			break;
		case SDL_KEYDOWN:
			switch (ebentua.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
			{
			case SDL_SCANCODE_D:
				a = FALSE;
				if (!d && !pertsonaia.erortzen && !pertsonaia.salto)
				{
					pertsonaia.sprite = KORRIKA;
					pertsonaia.erasotzen = FALSE;
					*pAnimazioa = 0;
				}
				d = TRUE;
				break;
			case SDL_SCANCODE_A:
				d = FALSE;
				if (!a && !pertsonaia.erortzen && !pertsonaia.salto)
				{
					pertsonaia.sprite = KORRIKA;
					pertsonaia.erasotzen = FALSE;
					*pAnimazioa = 0;
				}
				a = TRUE;
				break;
			case SDL_SCANCODE_SPACE:
				espacio = TRUE;
				break;
			case SDL_SCANCODE_K:
				if (!pertsonaia.erortzen && !pertsonaia.salto)
				{
					a = FALSE;
					d = FALSE;
				}

				if (!pertsonaia.erasotzen)
				{
					k = TRUE;
				}
				break;
			case SDL_SCANCODE_ESCAPE:
				Amaitu(Jokatzen, Pantaila);
				break;
			case SDL_SCANCODE_W:
				if (!a && !pertsonaia.erortzen && !pertsonaia.salto)
				{
					pertsonaia.erasotzen = FALSE;
				}
				w = TRUE;
				break;
			case SDL_SCANCODE_F3:
				f3 = !f3;
				break;
			case SDL_SCANCODE_9:

				break;
			}
			break;
		case SDL_KEYUP:
			switch (ebentua.key.keysym.scancode)
			{
			case SDL_SCANCODE_D:
				d = FALSE;
				break;
			case SDL_SCANCODE_A:
				a = FALSE;
				break;
			case SDL_SCANCODE_SPACE:
				espacio = FALSE;
				break;
			case SDL_SCANCODE_K:
				k = FALSE;
				break;
			case SDL_SCANCODE_W:
				w = FALSE;
				break;
			case SDL_SCANCODE_F3:

				break;
			}
			break;
		}

	}
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

void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika)
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
				int relleno[1];
				int rellenodim = 0;
				IrudiZnbk = 1;
				RenderPrestatu(AURRERA, relleno, rellenodim);
				Irudikatu();
				PertsonaiaHasieratu();
				EtsaiakHasieratu();
				Animazioa();
				*Pantaila = LEHEN;
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
			if ((x > 1055 && y > 89) && (x < 1120 && y < 151))
			{
				*Pantaila = MENUA;
			}
		}
		break;

	case KONTROLAK:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1055 && y > 89) && (x < 1120 && y < 151))
			{
				*Pantaila = MENUA;
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



	for (int j = 0; j < *BizirikKopurua; j++)
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

		etsaiaxEzker = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.x + 5;
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
				if (etsaiaxEzker >= PertzonaiaEskuinMuga && etsaiaxEzker <= PertzonaiaEskuinMuga + 33)
				{
					numero++;
					printf("VIVO %d\n", numero);
					EtsaiaKendu(j, BizirikDaudenEtsaiak, *BizirikKopurua);
					--* BizirikKopurua;
				}
			}
			else
			{
				if (etsaiaxEskuin >= PertzonaiaEzkerMuga - 33 && etsaiaxEskuin <= PertzonaiaEzkerMuga)
				{
					numero++;
					printf("VIVO %d\n", numero);
					EtsaiaKendu(j, BizirikDaudenEtsaiak, *BizirikKopurua);
					--* BizirikKopurua;
				}
			}
		}
		if (((PertzonaiaEskuinMuga >= etsaiaxEzker && PertzonaiaEskuinMuga <= etsaiaxEskuin) || (PertzonaiaEzkerMuga <= etsaiaxEskuin && PertzonaiaEskuinMuga >= etsaiaxEzker)) && (PertzonaiaYBekoa >= etsaiayGoikoa && PertzonaiaYGoikoa <= etsaiayBehekoa))
		{
			pertsonaia.sprite = HIL;
			*pAnimazioa = 0;
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
		pertsonaia.erortzen = FALSE;
		pertsonaia.salto = FALSE;
	}
}
