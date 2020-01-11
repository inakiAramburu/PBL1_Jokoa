#include "Funtzioak.h"
#include <SDL.h>
#include <stdio.h>

SDL_Renderer* render;
SDL_Window* leihoa;
Uint32 time=0;
Uint32 time2 = 0;
Uint32 abiadura[8] = {150,60,80,80,10,100,80};
int numero = 0;
//IDLE, KORRIKA, SALTO, ERORI, ERASO, HIL, KEA
/*
extern int pitch; //el numero de pixels por fila
extern Uint32 bpp; //el numero de Byte por pixel
extern void* pixels;*/

typedef struct S_BEHEKOPIXEL
{
	KOLOREAK ezker;
	KOLOREAK eskuin;
}BEHEKOPIXEL;

typedef struct S_ALBOKOPIXEL
{
	KOLOREAK goikoa;
	KOLOREAK erdikoa;
	KOLOREAK behekoa;
}ALBOKOPIXEL;

typedef struct S_HITBOX
{
	ALBOKOPIXEL ezker;
	ALBOKOPIXEL eskuin;
	BEHEKOPIXEL behekoa;
	KOLOREAK goikoa;

}HITBOX;

HITBOX hitbox;

typedef struct S_IMG		//Argazkiak eta pantailan irudikatzeko behar dutren datu guztiak
{
	SDL_Texture* textura;
	SDL_Rect Dimentsioak;
}IMG;

IMG Irudiak[50];		//Irudiak, dagozkien datuekin
int IrudiZnbk;

typedef struct S_IMGPERTSONAIA		//Pertsonaiaren irudiak banaturik, beti kargatuta egongo direlako Jokatu sakatzen denetik
{
	SDL_Texture* textura;
	int kop;
}IMGPERTSONAIA;

IMGPERTSONAIA spriteak[7];		

typedef struct S_PERTSONAIA		//Pertsonaiaren datuak
{
	SDL_Rect SrcSprite, DestSprite;
	SPRITE sprite;
	EGOERA egoera;
	BOOLEANOA salto;
	BOOLEANOA erortzen;
	BOOLEANOA erasotzen;
}PERTSONAIA;

PERTSONAIA pertsonaia;

typedef struct S_ETSAIA		//Etsaien datuak
{
	SDL_Rect SrcSprite, DestSprite;
	EGOERA egoera;
	int abiadura;
	SDL_Texture* textura;
}ETSAIA;

ETSAIA etsaia[ETSAI_KOPURUA];

typedef struct S_PONG
{
	BOOLEANOA piztuta;
	SDL_Rect pilota, Player1, Player2;
}PONG;

PONG easteregg;

TEKLAK a = SAKATUGABE;
TEKLAK d = SAKATUGABE;
TEKLAK espacio = SAKATUGABE;
TEKLAK k = SAKATUGABE;
TEKLAK w = SAKATUGABE;
TEKLAK s = SAKATUGABE;
TEKLAK f3 = SAKATUGABE;

int LeihoaEtaRenderHasi()
{
            // Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da SDL hasieratu: %s", SDL_GetError());
		return 1;
	}
	// Create an application window with the following settings:
	leihoa = SDL_CreateWindow(
		"The Cave",                  			// Izenburua
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		PANTAILA_ZABALERA,                // Sortzeko lehioaren zabalera
		PANTAILA_ALTUERA,                 // Sortzeko leihoaren altuera
		SDL_WINDOW_OPENGL                 // Erabilitako teknologia grafikoa
	);

	if (leihoa == NULL) { 		// Leihoa sortu dela konprobatzen du

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da leihoa sortu: %s\n", SDL_GetError());		//Errorea
		return 1;
	}

	SDL_Surface* ikonoa = SDL_LoadBMP(".\\media\\Ikonoa.bmp");
	SDL_SetWindowIcon(leihoa, ikonoa);
	SDL_FreeSurface(ikonoa);

	render = SDL_CreateRenderer(leihoa, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);		//Renderizatua hasi

	return 0;
}

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

void KargatuIrudiak(PANTAILAK Pantaila, int BizirikDaudenEtsaiak[], int *BizirikKopurua)
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
		pertsonaia.egoera = HILDA;
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
		Eraikitzaile(&pertsonaia.DestSprite, 0, 300, 60, 128);

		EtsaiaKokatu(1, 400, 469, BizirikDaudenEtsaiak, BizirikKopurua);		//REVISAR
		EtsaiaKokatu(0, 800, 469, BizirikDaudenEtsaiak, BizirikKopurua);		//REVISAR
		EtsaiaKokatu(5, 900, 469, BizirikDaudenEtsaiak, BizirikKopurua);		//REVISAR

		break;
	case BIGARREN:
		ImgKargatu(BIGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		Eraikitzaile(&pertsonaia.DestSprite, 10, 510, 60, 128);
		break;
	case HIRUGARREN:
		ImgKargatu(HIRUGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		Eraikitzaile(&pertsonaia.DestSprite, 10, 100, 60, 128);
		break;
	case LAUGARREN:
		ImgKargatu(LAUGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		Eraikitzaile(&pertsonaia.DestSprite, 10, 100, 60, 128);
		break;
	case BOSTGARREN:
		ImgKargatu(BOSTGARREN_PANTAILA, 0, 0, 0, 0);
		pertsonaia.SrcSprite.x = 0;
		Eraikitzaile(&pertsonaia.DestSprite, 10, 100, 60, 128);
		break;
	case MINIJOKOA:
		easteregg.piztuta = BAI;
		Eraikitzaile(&easteregg.pilota, 360, 640, 25, 25);
		Eraikitzaile(&easteregg.Player1, 50, 640, 200, 20);
		Eraikitzaile(&easteregg.Player2, 620, 640, 200, 20);
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
	Irudiak[IrudiZnbk].Dimentsioak.h = altuera;
	Irudiak[IrudiZnbk].Dimentsioak.w = zabalera;
	Irudiak[IrudiZnbk].Dimentsioak.x = x;
	Irudiak[IrudiZnbk].Dimentsioak.y = y;
	IrudiZnbk++;
}

void KargatuMapa(char mapa[], void **pixels, int *pitch, Uint8 *bpp)
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
	if (easteregg.piztuta)
	{

		SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
		SDL_RenderFillRect(render, &easteregg.pilota);
		SDL_RenderFillRect(render, &easteregg.Player1);
		SDL_RenderFillRect(render, &easteregg.Player2);
	}
	for (i = 0; i < BizirikKopurua; i++)
	{
		if (etsaia[BizirikDaudenEtsaiak[i]].egoera == BIZIRIK)
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
	if (pertsonaia.egoera == BIZIRIK)
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
		Irudiak[2].Dimentsioak.w = 300;
		Irudiak[2].Dimentsioak.h = 120;
		Irudiak[2].Dimentsioak.x = 500;
		Irudiak[2].Dimentsioak.y = 165;
	}
	else
	{
		Irudiak[2].Dimentsioak.w = 250;
		Irudiak[2].Dimentsioak.h = 100;
		Irudiak[2].Dimentsioak.x = 515;
		Irudiak[2].Dimentsioak.y = 175;
	}
	if ((x > 510 && y > 300) && (x < 760 && y < 400))
	{
		Irudiak[3].Dimentsioak.x = 495;
		Irudiak[3].Dimentsioak.y = 290;
		Irudiak[3].Dimentsioak.w = 300;
		Irudiak[3].Dimentsioak.h = 120;
	}
	else
	{
		Irudiak[3].Dimentsioak.x = 510;
		Irudiak[3].Dimentsioak.y = 300;
		Irudiak[3].Dimentsioak.w = 250;
		Irudiak[3].Dimentsioak.h = 100;
	}
	if ((x > 512 && y > 425) && (x < 762 && y < 525))
	{
		Irudiak[4].Dimentsioak.x = 497;
		Irudiak[4].Dimentsioak.y = 415;
		Irudiak[4].Dimentsioak.w = 300;
		Irudiak[4].Dimentsioak.h = 120;
	}
	else
	{
		Irudiak[4].Dimentsioak.x = 512;
		Irudiak[4].Dimentsioak.y = 425;
		Irudiak[4].Dimentsioak.w = 250;
		Irudiak[4].Dimentsioak.h = 100;
	}
	SDL_RenderCopy(render, Irudiak[2].textura, NULL, &Irudiak[2].Dimentsioak);
	SDL_RenderCopy(render, Irudiak[3].textura, NULL, &Irudiak[3].Dimentsioak);
	SDL_RenderCopy(render, Irudiak[4].textura, NULL, &Irudiak[4].Dimentsioak);
}

void Irudikatu()
{
	SDL_RenderPresent(render);
}

void Amaitu(JOKOA *Jokoa, PANTAILAK *Pantaila)
{
	SDL_DestroyWindow(leihoa);
	SDL_DestroyRenderer(render);
	*Jokoa = EZJOKATZEN;
	*Pantaila = ATERA;
}

void EbentuakKonprobatu(JOKOA *Jokoa, PANTAILAK *Pantaila, int* pAnimazioa, ZENTZUA *begira)
{
	SAGUA klika;
	SDL_Event ebentua;
	while (SDL_PollEvent(&ebentua))
	{
		switch (ebentua.type)
		{
			*Pantaila += 1;
			case SDL_QUIT:
				Amaitu(Jokoa, Pantaila);
				break;
			case SDL_MOUSEBUTTONUP:
				ZeinKlikatuDa(ebentua.button, &klika);
				KonprobatuKlika(Pantaila, klika);
				break;
			case SDL_KEYDOWN:
				switch (ebentua.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
				{
				case SDL_SCANCODE_D:
					a = SAKATUGABE;
					if (!d && !pertsonaia.erortzen && !pertsonaia.salto)
					{
						pertsonaia.sprite = KORRIKA;
						pertsonaia.erasotzen = EZ;
						*pAnimazioa = 0;
					}
					d = SAKATUTA;
					break;
				case SDL_SCANCODE_A:
					d = SAKATUGABE;
					if (!a && !pertsonaia.erortzen && !pertsonaia.salto)
					{
						pertsonaia.sprite = KORRIKA;
						pertsonaia.erasotzen = EZ;
						*pAnimazioa = 0;
					}
					a = SAKATUTA;
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SAKATUTA;
					break;
				case SDL_SCANCODE_K:
					if (!pertsonaia.erortzen && !pertsonaia.salto)
					{
						a = SAKATUGABE;
						d = SAKATUGABE;
					}
				
					if (!pertsonaia.erasotzen)
					{
						k = SAKATUTA;
					}
					break;
				case SDL_SCANCODE_ESCAPE:
					Amaitu(Jokoa, Pantaila);
					break;
				case SDL_SCANCODE_W:
					if (!a && !pertsonaia.erortzen && !pertsonaia.salto)
					{
						pertsonaia.erasotzen = EZ;
					}
					w = SAKATUTA;
					break;
				case SDL_SCANCODE_S:
					s = SAKATUTA;
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
					d = SAKATUGABE;
					break;
				case SDL_SCANCODE_A:
					a = SAKATUGABE;
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SAKATUGABE;
					break;
				case SDL_SCANCODE_K:
					k = SAKATUGABE;
					break;
				case SDL_SCANCODE_W:
					w = SAKATUGABE;
					break;
				case SDL_SCANCODE_S:
					s = SAKATUGABE;
					break;
				case SDL_SCANCODE_F3:
					
					break;
				}
				break;
		}

	}
}

void Ekintzak(int* pAnimazioa, ZENTZUA* begira, void* pixels, int pitch, Uint8 bpp, PANTAILAK* pantaila, int BizirikDaudenEtsaiak[], int *BizirikKopurua)
{
	if (!easteregg.piztuta)
	{
		int abiadurax = 12;
		int abiaduray = 12;
		static int eAnimazioa;

		//	Debbug de pies
		if (f3)
		{
			printf("Pierna Izquierda: %d\n", hitbox.behekoa.ezker);
			printf("Izquierda x: %d  ", pertsonaia.DestSprite.x + 54);
			printf("y: %d \n\n", pertsonaia.DestSprite.y + 59);

			printf("Pierna derecha: %d\n", hitbox.behekoa.eskuin);
			printf("Derecha x: %d  ", pertsonaia.DestSprite.x + 75);
			printf("y: %d \n\n", pertsonaia.DestSprite.y);
		}
		KolisioakKonprobatu(pixels, pitch, bpp, BizirikDaudenEtsaiak, BizirikKopurua, *begira, pAnimazioa);

		if (hitbox.behekoa.eskuin == BELTZA || hitbox.behekoa.ezker == BELTZA)
		{
			if (pertsonaia.erortzen)
			{
				if (a || d)
				{
					pertsonaia.sprite = KORRIKA;
					*pAnimazioa = 0;
				}
				else
				{
					pertsonaia.sprite = IDLE;
					*pAnimazioa = 0;
				}
			}
			pertsonaia.erortzen = EZ;
		}
		else if (hitbox.behekoa.eskuin == TXURIA && hitbox.behekoa.ezker == TXURIA)
		{
			if (!pertsonaia.salto)
			{
				pertsonaia.erortzen = BAI;
				pertsonaia.sprite = ERORI;
				*pAnimazioa = 0;
			}
		}
		if (w)
		{
			if (hitbox.ezker.goikoa == HORIA)
			{
				*pantaila += 1;
				GuztiakHil();
				return;
			}
		}
		if (a)
		{
			*begira = ATZERA;
			if ((hitbox.ezker.behekoa != BERDEA && hitbox.ezker.erdikoa != BERDEA && hitbox.ezker.goikoa != BERDEA) && pertsonaia.DestSprite.x > -39 && pertsonaia.sprite != ERASO)
			{
				pertsonaia.DestSprite.x -= abiadurax;
			}
		}
		if (d)
		{
			*begira = AURRERA;
			if ((hitbox.eskuin.behekoa != BERDEA && hitbox.eskuin.erdikoa != BERDEA && hitbox.eskuin.goikoa != BERDEA) && pertsonaia.DestSprite.x < 1190 && pertsonaia.sprite != ERASO)
			{
				pertsonaia.DestSprite.x += abiadurax;
			}
		}
		if (!pertsonaia.erortzen && !pertsonaia.salto && !k && !espacio && !pertsonaia.erasotzen && !d && !a && pertsonaia.sprite != HIL)
		{
			if (pertsonaia.sprite != IDLE)
			{
				*pAnimazioa = 0;
			}
			pertsonaia.sprite = IDLE;

		}
		if (!pertsonaia.erortzen && !pertsonaia.salto && !k && espacio && pertsonaia.sprite != HIL)
		{
			pertsonaia.salto = BAI;
			pertsonaia.sprite = SALTO;
			*pAnimazioa = 0;
		}
		if (!pertsonaia.erortzen && !pertsonaia.salto && k && !pertsonaia.erasotzen && !d && !a)
		{
			pertsonaia.erasotzen = BAI;
			pertsonaia.sprite = ERASO;
			*pAnimazioa = 0;
		}
		if (pertsonaia.salto)
		{
			pertsonaia.DestSprite.y -= abiaduray;
		}
		if (pertsonaia.erortzen)
		{
			pertsonaia.DestSprite.y += GRABITATEA;
			AltueraZuzendu(pixels, pitch, bpp);
		}
		pertsonaia.SrcSprite.x = 128 * (*pAnimazioa);

		if (SDL_GetTicks() - time > abiadura[pertsonaia.sprite])
		{
			++* pAnimazioa;
			time = SDL_GetTicks();
		}

		if (*pAnimazioa >= spriteak[pertsonaia.sprite].kop)
		{
			if (pertsonaia.sprite == HIL)
			{
				PertsonaiaHil();
			}
			if (pertsonaia.salto)
			{
				pertsonaia.salto = EZ;
				pertsonaia.erortzen = BAI;
			}
			if (pertsonaia.erasotzen)
			{
				pertsonaia.erasotzen = EZ;
				k = SAKATUGABE;

			}
			*pAnimazioa = 0;

		}
		for (int j = 0; j < *BizirikKopurua; j++)
		{
			if (etsaia[BizirikDaudenEtsaiak[j]].egoera == BIZIRIK)
			{
				EtsaienAdimena(BizirikDaudenEtsaiak[j], pixels, pitch, bpp);
				etsaia[BizirikDaudenEtsaiak[j]].DestSprite.x += etsaia[BizirikDaudenEtsaiak[j]].abiadura;
				etsaia[BizirikDaudenEtsaiak[j]].SrcSprite.x = 32 * eAnimazioa;
			}
		}
		if (SDL_GetTicks() - time2 > 180)
		{
			eAnimazioa++;
			time2 = SDL_GetTicks();
		}
		if (eAnimazioa >= ETSAIA_SPRITE_KOPURUA)
		{
			eAnimazioa = 0;
		}
	}
	else
	{
		if (w && easteregg.Player1.y > 0)
		{
			easteregg.Player1.y -= 9;
		}
		else if (s)
		{
			easteregg.Player1.y += 9;
		}
	}
	
}

void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA *klika)
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

void KonprobatuKlika(PANTAILAK *Pantaila, SAGUA klika)
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
				if ((x > 1063 && y > 99) && (x < 1109 && y < 142))
				{
					*Pantaila = MENUA;
				}
				else if ((x > 961 && y > 521) && (x < 1034 && y < 576))
				{
					*Pantaila = MINIJOKOA;
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
	}
}

void PertsonaiaHasieratu()
{	
	JokalariaKargatu(".\\media\\player\\Idle.bmp", 0);
	spriteak[0].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Run.bmp", 1);
	spriteak[1].kop = 10;
	
	JokalariaKargatu(".\\media\\player\\Salto.bmp", 2);
	spriteak[2].kop = 8;
	
	JokalariaKargatu(".\\media\\player\\Caida.bmp", 3);
	spriteak[3].kop = 6;

	JokalariaKargatu(".\\media\\player\\Attack.bmp", 4);
	spriteak[4].kop = 8;
	
	JokalariaKargatu(".\\media\\player\\Dead.bmp", 5);
	spriteak[5].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Humo.bmp", 6);
	spriteak[6].kop = 4;
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

void EtsaiakHasieratu()
{
	int j, tmp = 0, kopurua=5;
	for (j = 0; j < kopurua; j++)
	{
		EtsaiaKargatu(".\\media\\enemies\\Mamua.bmp", j);
		etsaia[j].SrcSprite.h = 44;
		etsaia[j].SrcSprite.w = 33;
		etsaia[j].SrcSprite.x = 0;
		etsaia[j].SrcSprite.y = 0;
		etsaia[j].DestSprite.w = 33;
		etsaia[j].DestSprite.h = 44;
	}
	tmp = j;
	for (j = tmp; j < tmp + kopurua; j++)
	{
		EtsaiaKargatu(".\\media\\enemies\\Mukitxua.bmp", j);
		etsaia[j].SrcSprite.h = 44;
		etsaia[j].SrcSprite.w = 33;
		etsaia[j].SrcSprite.x = 0;
		etsaia[j].SrcSprite.y = 0;
		etsaia[j].DestSprite.w = 33;
		etsaia[j].DestSprite.h = 44;
	}
	tmp = j;
	/*
	for (j = tmp; j < tmp + kopurua; j++)
	{
		EtsaiaKargatu(".\\media\\enemies\\MOKOS.bmp", j);
		etsaia[j].kop = 4;
	}
	ARAÑA*/
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

void MusikaJarri(char Fitxategia[])
{
	//explicacion
	//https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	/*  fichategia cargatu */
	if (SDL_LoadWAV(Fitxategia, &wavSpec, &wavBuffer, &wavLength) == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "no encuentra test.wav: %s\n", SDL_GetError());
		exit(-1);
	}
	// abrir dependencias de audio

	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	// iniciar el sonido

	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);

	// dena itxi

	//SDL_CloseAudioDevice(deviceId);
	//SDL_FreeWAV(wavBuffer);
}

void EtsaiaKokatu(int znbk_etsaia, int x, int y, int BizirikDaudenEtsaiak[], int *BizirikKopurua)
{

	etsaia[znbk_etsaia].DestSprite.x = x;
	etsaia[znbk_etsaia].DestSprite.y = y;
	etsaia[znbk_etsaia].egoera = BIZIRIK;
	if (znbk_etsaia >= 0 && znbk_etsaia <= 4)
	{
		etsaia[znbk_etsaia].abiadura = ABIADURA_MAMUA;
	}
	else if (znbk_etsaia >= 5 && znbk_etsaia <= 9)
	{
		etsaia[znbk_etsaia].abiadura = ABIADURA_MUKITXUA;
	}
	BizirikDaudenEtsaiak[*BizirikKopurua] = znbk_etsaia;
	*BizirikKopurua += 1;
}

void Animazioa()
{
	//int i, j;

	SDL_Delay(500);
	IrudiZnbk = IrudiakKendu(1);
	pertsonaia.egoera = BIZIRIK;
	pertsonaia.sprite = KEA;
	pertsonaia.DestSprite.x = 10;
	pertsonaia.DestSprite.y = 555;
	pertsonaia.DestSprite.h = 60;
	pertsonaia.DestSprite.w = 128;
	pertsonaia.SrcSprite.h = 60;
	pertsonaia.SrcSprite.w = 128;
	pertsonaia.SrcSprite.y = 0;
	char Kea[128] = ".\\media\\sound\\Kea.wav";
/*
	MusikaJarri(Kea);
	for (i = 0; i < spriteak[pertsonaia.sprite].kop; i++)
	{
		SDL_Delay(100);
		pertsonaia.SrcSprite.x = 128 * i;
		RenderPrestatu(AURRERA);
		Irudikatu();
	}
	pertsonaia.sprite = IDLE;
	for (j = 0; j < 2; j++)
	{
		for (i = 0; i < spriteak[pertsonaia.sprite].kop; i++)
		{
			pertsonaia.SrcSprite.x = 128 * i;
			RenderPrestatu(AURRERA);
			Irudikatu();
			SDL_Delay(150);
		}
	}
	pertsonaia.sprite = KORRIKA;
	for (j = 0; j < 12; j++)
	{
		for (i = 0; i < spriteak[pertsonaia.sprite].kop; i++)
		{
			pertsonaia.SrcSprite.x = 128 * i;
			pertsonaia.DestSprite.x += 9;
			RenderPrestatu(AURRERA);
			Irudikatu();
			SDL_Delay(80);
		}
	}
	pertsonaia.sprite = IDLE;
	RenderPrestatu(AURRERA);
	Irudikatu();
	SDL_Delay(300);
	IrudiZnbk = IrudiakKendu(0);
	pertsonaia.egoera = HILDA;
	ImgKargatu(".\\media\\menu\\TheCaveW.bmp", 1000, 400, 140, 160);
	for (i = 0; i < 80; i++)
	{
		SDL_SetTextureAlphaMod(Irudiak[0].textura, 2 * i);
		RenderPrestatu(AURRERA);
		Irudikatu();
		SDL_Delay(100);
	}
	SDL_Delay(2000);*/
}

Uint32 getpixel(void* pixels, int pitch, Uint8 bpp, int x, int y )
{


	Uint8* p = (Uint8*)pixels + ((Uint64)(y)* pitch+x) * bpp;

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

void KolisioakKonprobatu(void* pixels, int pitch, Uint8 bpp, int BizirikDaudenEtsaiak[] ,int *BizirikKopurua, ZENTZUA begira, int *pAnimazioa)
{
	
	int PertzonaiaEzkerMuga = pertsonaia.DestSprite.x + 46;
	int PertzonaiaEskuinMuga = pertsonaia.DestSprite.x + 82;

	int PertzonaiaYGoikoa = pertsonaia.DestSprite.y;
	int PertzonaiaYBekoa = pertsonaia.DestSprite.y + 59;



	int YBekoa = pertsonaia.DestSprite.y + 52;
	int altuera=0;

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

		if (pertsonaia.sprite == ERASO && pertsonaia.erasotzen == BAI && *pAnimazioa > 4)
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
				if (etsaiaxEskuin >= PertzonaiaEzkerMuga -33 && etsaiaxEskuin <= PertzonaiaEzkerMuga)
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
		pertsonaia.erortzen = EZ;
		pertsonaia.salto = EZ;
	}
}

void AltueraZuzendu(void *pixels, int pitch, Uint8 bpp)
{
	int i = 1;
	KOLOREAK tmp, tmp2;
	do
	{
		tmp = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 54, pertsonaia.DestSprite.y + 59 + i);
		tmp2 = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 75, pertsonaia.DestSprite.y + 59 + i);
		i ++;
	} while (i < GRABITATEA && (tmp != BELTZA && tmp2 != BELTZA));
	if (i >= GRABITATEA)
	{
		return;
	}
	i--;
	pertsonaia.DestSprite.y += i;
}

void GuztiakHil()
{
	for (int i = 0; i < ETSAI_KOPURUA; i++)
	{
		etsaia[i].egoera = HILDA;
	}
}
void EtsaienAdimena(int znbk_etsaia, void* pixels, int pitch, Uint8 bpp)
{
	if ((getpixel(pixels, pitch, bpp, etsaia[znbk_etsaia].DestSprite.x + 32, etsaia[znbk_etsaia].DestSprite.y + 44) != BELTZA)|| (getpixel(pixels, pitch, bpp, etsaia[znbk_etsaia].DestSprite.x, etsaia[znbk_etsaia].DestSprite.y + 44) != BELTZA))
	{
		etsaia[znbk_etsaia].abiadura *= -1;
	}
}

void PertsonaiaHil()
{
	pertsonaia.egoera = HILDA;
}

void EtsaiaKendu(int pos, int BizirikDaudenEtsaiak[], int BizirikKopurua)
{
	etsaia[BizirikDaudenEtsaiak[pos]].egoera = HILDA;
	for (int j = pos; j < BizirikKopurua - 1; j++)
	{
		BizirikDaudenEtsaiak[j] = BizirikDaudenEtsaiak[j + 1];
	}
}

void Eraikitzaile(SDL_Rect *dest, int x, int y, int h, int w)
{
	dest->w = w;
	dest->h = h;
	dest->x = x;
	dest->y = y;
}
