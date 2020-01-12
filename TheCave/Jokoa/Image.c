#include "Basic.h"
#include "Image.h"
#include <stdlib.h>
#include <stdio.h>

SDL_Renderer* render;
extern PERTSONAIA pertsonaia;
extern ETSAIA etsaia[ETSAI_KOPURUA];

extern PONG easteregg;

IMGPERTSONAIA spriteak[7];

IMG Irudiak[50];		//Irudiak, dagozkien datuekin
int IrudiZnbk;


int IrudiakKendu(int ZnbtUtzi)
{
	int i = IrudiZnbk - 1;

	while (i >= ZnbtUtzi)
	{
		SDL_DestroyTexture(Irudiak[i].textura);
		i--;
	}
	return i + 1;
}

void KargatuIrudiak(PANTAILAK Pantaila, int BizirikDaudenEtsaiak[], int* BizirikKopurua)
{
	IrudiZnbk = IrudiakKendu(0);
	*BizirikKopurua = 0;
	switch (Pantaila)
	{
		/*Jokolariak pantaila berri batera pasatzean behar izango diren irudi guztiak kargatzen dira. Horrela ez irudiak ez dira kargatuko
		jokalaria puntu horretara heltzen ez bada*/

	case MENUA:
		ImgKargatu(MENU_PANTAILA, 0, 0, 0, 0);		//Zabalera, altuera, x, y
		ImgKargatu(".\\media\\menu\\pergamino.bmp", 395, 560, 442, 80);		//Zabalera, altuera, x, y
		ImgKargatu(".\\media\\menu\\Jolastu.bmp", 250, 100, 515, 175);		//Zabalera, altuera, x, y
		ImgKargatu(".\\media\\menu\\Kontrolak.bmp", 250, 100, 510, 300);		//Zabalera, altuera, x, y
		ImgKargatu(".\\media\\menu\\Kredituak.bmp", 250, 100, 512, 425);		//Zabalera, altuera, x, y
		pertsonaia.bizirik = FALSE;
		break;
	case KREDITUAK:
		ImgKargatu(MENU_PANTAILA, 0, 0, 0, 0);		//Zabalera, altuera, x, y
		ImgKargatu(".\\media\\menu\\KredituakP.bmp", 950, 600, 208, 15);		//Zabalera, altuera, x, y
		break;
	case KONTROLAK:
		ImgKargatu(MENU_PANTAILA, 0, 0, 0, 0);		//Zabalera, altuera, x, y
		ImgKargatu(".\\media\\menu\\KontrolakP.bmp", 950, 600, 208, 15);		//Zabalera, altuera, x, y
		break;
	case LEHEN:
		ImgKargatu(LEHENENGO_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		pertsonaia.bizirik = TRUE;
		RectEraikitzailea(&pertsonaia.DestSprite, 0, 300, 60, 128);
		EtsaiaKokatu(1, 400, 469, BizirikDaudenEtsaiak, BizirikKopurua);		//REVISAR
		EtsaiaKokatu(0, 800, 469, BizirikDaudenEtsaiak, BizirikKopurua);		//REVISAR
		EtsaiaKokatu(5, 900, 469, BizirikDaudenEtsaiak, BizirikKopurua);		//REVISAR

		break;
	case BIGARREN:
		ImgKargatu(BIGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		RectEraikitzailea(&pertsonaia.DestSprite,  10,  510,  60,  128);
		break;
	case HIRUGARREN:
		ImgKargatu(HIRUGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		RectEraikitzailea(&pertsonaia.DestSprite, 10, 100, 60, 128);
		break;
	case LAUGARREN:
		ImgKargatu(LAUGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		RectEraikitzailea(&pertsonaia.DestSprite, 10, 100, 60, 128);
		break;
	case BOSTGARREN:
		ImgKargatu(BOSTGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		RectEraikitzailea(&pertsonaia.DestSprite, 10, 100, 60, 128);
		break;
	case MINIJOKOA:
		pertsonaia.bizirik = FALSE;
		GuztiakHil();
		easteregg.piztuta = TRUE;
		easteregg.P1puntuazioa = 0;
		easteregg.P2puntuazioa = 0;
		srand(SDL_GetTicks());
		do
		{
			easteregg.angelua = (rand() % 90) - 45;
		} while (easteregg.angelua < 15 && easteregg.angelua > -15);
		if (rand() % 2 == 0)
		{
			easteregg.abiadurax = -5;
		}
		else
		{
			easteregg.abiadurax = 5;
		}
		easteregg.abiaduray = 5;
		RectEraikitzailea(&easteregg.pilota, 628, 348, 25, 25);
		RectEraikitzailea(&easteregg.Player1, 50, 360, 150, 20);
		RectEraikitzailea(&easteregg.Player2, 1210, 360, 150, 20);
		break;
		
	}
}

void ImgKargatu(char src[], int zabalera, int altuera, int x, int y)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface = SDL_LoadBMP(src);
	if (!surface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}

	SDL_FreeSurface(surface);
	Irudiak[IrudiZnbk].textura = texture;
	RectEraikitzailea(&Irudiak[IrudiZnbk].Dimentsioak, x, y, altuera, zabalera);
	IrudiZnbk++;
}

void KargatuMapa(char mapa[], void** pixels, int* pitch, Uint8* bpp)
{
	SDL_Surface* surface = SDL_LoadBMP(mapa);
	*pixels = surface->pixels;

	*pitch = surface->pitch;
	*bpp = surface->format->BytesPerPixel;
}

void RenderPrestatu(ZENTZUA begira, int BizirikDaudenEtsaiak[], int BizirikKopurua)
{
	int i;

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);

	for (i = 0; i < IrudiZnbk; i++)
	{
		if (Irudiak[i].Dimentsioak.h == 0)
		{
			SDL_RenderCopy(render, Irudiak[i].textura, NULL, NULL);
		}
		else
		{
			SDL_RenderCopy(render, Irudiak[i].textura, NULL, &Irudiak[i].Dimentsioak);
		}
	}
	for (i = 0; i < BizirikKopurua; i++)
	{
		if (etsaia[BizirikDaudenEtsaiak[i]].bizirik)
		{
			if (etsaia[BizirikDaudenEtsaiak[i]].abiadura > 0)
			{
				SDL_RendererFlip flip = SDL_FLIP_VERTICAL;

				SDL_RenderCopyEx(render, etsaia[BizirikDaudenEtsaiak[i]].textura, &etsaia[BizirikDaudenEtsaiak[i]].SrcSprite, &etsaia[BizirikDaudenEtsaiak[i]].DestSprite, 180, NULL, flip);
			}
			else
			{
				SDL_RenderCopy(render, etsaia[BizirikDaudenEtsaiak[i]].textura, &etsaia[BizirikDaudenEtsaiak[i]].SrcSprite, &etsaia[BizirikDaudenEtsaiak[i]].DestSprite);
			}
		}
	}
	if (pertsonaia.bizirik)
	{
		if (begira == ATZERA)
		{
			SDL_RendererFlip flip = SDL_FLIP_VERTICAL;

			SDL_RenderCopyEx(render, spriteak[pertsonaia.sprite].textura, &pertsonaia.SrcSprite, &pertsonaia.DestSprite, 180, NULL, flip);
		}
		else
		{
			SDL_RenderCopy(render, spriteak[pertsonaia.sprite].textura, &pertsonaia.SrcSprite, &pertsonaia.DestSprite);
		}
	}
	if (easteregg.piztuta)
	{
		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderFillRect(render, &easteregg.pilota);
		SDL_RenderFillRect(render, &easteregg.Player1);
		SDL_RenderFillRect(render, &easteregg.Player2);
	}
}

void RenderMenu()
{
	int i = 0, x, y;

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	SDL_GetMouseState(&x, &y);

	SDL_RenderCopy(render, Irudiak[0].textura, NULL, NULL);
	SDL_RenderCopy(render, Irudiak[1].textura, NULL, &Irudiak[1].Dimentsioak);
	if ((x > 515 && y > 175) && (x < 765 && y < 275))
	{
		RectEraikitzailea(&Irudiak[2].Dimentsioak, 500, 165, 120, 300);
	}
	else
	{
		RectEraikitzailea(&Irudiak[2].Dimentsioak, 515, 175, 100, 250);
	}
	if ((x > 510 && y > 300) && (x < 760 && y < 400))
	{
		RectEraikitzailea(&Irudiak[3].Dimentsioak, 495, 290, 120, 300);
	}
	else
	{
		RectEraikitzailea(&Irudiak[3].Dimentsioak, 510, 300, 100, 250);
	}
	if ((x > 512 && y > 425) && (x < 762 && y < 525))
	{
		RectEraikitzailea(&Irudiak[4].Dimentsioak, 497, 415, 120, 300);
	}
	else
	{
		RectEraikitzailea(&Irudiak[4].Dimentsioak, 512, 425, 100, 250);
	}
	SDL_RenderCopy(render, Irudiak[2].textura, NULL, &Irudiak[2].Dimentsioak);
	SDL_RenderCopy(render, Irudiak[3].textura, NULL, &Irudiak[3].Dimentsioak);
	SDL_RenderCopy(render, Irudiak[4].textura, NULL, &Irudiak[4].Dimentsioak);
}

void Irudikatu()
{
	SDL_RenderPresent(render);
}

void JokalariaKargatu(char Irudia[], int i)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface = SDL_LoadBMP(Irudia);

	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}
	SDL_FreeSurface(surface);
	spriteak[i].textura = texture;
}

void EtsaiaKargatu(char Irudia[], int i)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface = SDL_LoadBMP(Irudia);

	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}
	SDL_FreeSurface(surface);
	etsaia[i].textura = texture;
}

Uint32 getpixel(void* pixels, int pitch, Uint8 bpp, int x, int y)
{


	Uint8* p = (Uint8*)pixels + ((Uint64)(y)*pitch + x) * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;
	}
}
