#include "Funtzioak.h"
#include <SDL.h>

SDL_Renderer* render;
SDL_Window* leihoa;

typedef struct S_IMG
{
	SDL_Texture* textura;
	SDL_Rect Dimentsioak;
}IMG;

IMG Irudiak[100];		//Irudiak, dagozkien datuekin
int IrudiZnbk;

typedef struct S_IMGPERTSONAIA
{
	SDL_Texture* textura;
	int kop;
}IMGPERTSONAIA;

IMGPERTSONAIA spriteak[6];

typedef struct S_PERTSONAIA
{
	SDL_Rect SrcSprite, DestSprite;
	SPRITE sprite;
}PERTSONAIA;

PERTSONAIA pertsonaia;

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

void KargatuIrudiak(PANTAILAK Pantaila)
{
	IrudiZnbk = 0;
	switch (Pantaila)		
	{
		/*Jokolariak pantaila berri batera pasatzean behar izango diren irudi guztiak kargatzen dira. Horrela ez irudiak ez dira kargatuko
		jokalaria puntu horretara heltzen ez bada*/

		case MENUA:
			ImgKargatu(".\\media\\fondos\\Menu.bmp", NULL, NULL, 0, 0);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\pergamino.bmp", 395, 560, 442, 80);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Jolastu.bmp", 250, 100, 515, 175);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Jolastu.bmp", 300, 120, 500, 165);		//Aniamzioa egiteko
			ImgKargatu(".\\media\\menu\\Kontrolak.bmp", 250, 100, 510, 300);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Kontrolak.bmp", 300, 120, 495, 290);		//Animazioa egiteko
			ImgKargatu(".\\media\\menu\\Kredituak.bmp", 250, 100, 512, 425);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Kredituak.bmp", 300, 120, 497, 415);		//Animazioa egiteko
			break;
		case KREDITUAK:
			ImgKargatu(".\\media\\fondos\\Menu.bmp", NULL, NULL, 0, 0);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\KredituakP.bmp", 950, 600, 208, 15);		//Zabalera, altuera, x, y
			break;
		case KONTROLAK:
			ImgKargatu(".\\media\\fondos\\Menu.bmp", NULL, NULL, 0, 0);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\KontrolakP.bmp", 950, 600, 208, 15);		//Zabalera, altuera, x, y
			break;
		case LEHEN:
			ImgKargatu(".\\media\\fondos\\Menu.bmp", NULL, NULL, 0, 0);
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

void RenderPrestatu()
{
	int i;

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	
	for (i = 0; i < IrudiZnbk; i++)
	{
		if (Irudiak[i].Dimentsioak.h == NULL)
		{
			SDL_RenderCopy(render, Irudiak[i].textura, NULL, NULL);
		}
		else
		{
			SDL_RenderCopy(render, Irudiak[i].textura, NULL, &Irudiak[i].Dimentsioak);
		}
	}
	SDL_RenderCopy(render, spriteak[pertsonaia.sprite].textura, &pertsonaia.SrcSprite, &pertsonaia.DestSprite);
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
		SDL_RenderCopy(render, Irudiak[3].textura, NULL, &Irudiak[3].Dimentsioak);
	}
	else
	{
		SDL_RenderCopy(render, Irudiak[2].textura, NULL, &Irudiak[2].Dimentsioak);
	}
	if ((x > 510 && y > 300) && (x < 760 && y < 400))
	{
		SDL_RenderCopy(render, Irudiak[5].textura, NULL, &Irudiak[5].Dimentsioak);
	}
	else
	{
		SDL_RenderCopy(render, Irudiak[4].textura, NULL, &Irudiak[4].Dimentsioak);
	}
	if ((x > 512 && y > 425) && (x < 762 && y < 525))
	{
		SDL_RenderCopy(render, Irudiak[7].textura, NULL, &Irudiak[7].Dimentsioak);
	}
	else
	{
		SDL_RenderCopy(render, Irudiak[6].textura, NULL, &Irudiak[6].Dimentsioak);
	}
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
	return;
}

void EbentuakKonprobatu(JOKOA *Jokoa, PANTAILAK *Pantaila)
{
	SAGUA klika;
	SDL_Event ebentua;
	while (SDL_PollEvent(&ebentua))
	{
		switch (ebentua.type)
		{
			case SDL_QUIT:
				Amaitu(&*Jokoa, &*Pantaila);
				break;
			case SDL_MOUSEBUTTONUP:
				ZeinKlikatuDa(ebentua.button, &klika);
				KonprobatuKlika(&*Pantaila, klika);
				break;
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
					IrudiZnbk = 1;
					RenderPrestatu();
					Irudikatu();
					KargatuPertsonaia();
					Animazioa();
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

void Animazioa()
{
	SDL_Delay(500);
	int i;
	IrudiZnbk = 1;
	pertsonaia.sprite = KEA;
	pertsonaia.DestSprite.x = 10;
	pertsonaia.DestSprite.y = 532;
	pertsonaia.DestSprite.h = 60;
	pertsonaia.DestSprite.w = 128;
	pertsonaia.SrcSprite.h = 60;
	pertsonaia.SrcSprite.w = 128;
	pertsonaia.SrcSprite.y = 0;
	for (i = 0; i < spriteak[pertsonaia.sprite].kop; i++)
	{
		pertsonaia.SrcSprite.x = 128 * i;
		RenderPrestatu();
		Irudikatu();
		SDL_Delay(100);
	}

}

void KargatuPertsonaia()
{
	
	JokalariaKargatu(".\\media\\player\\Idle.bmp", 0);
	spriteak[0].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Run.bmp", 1);
	spriteak[1].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Salto.bmp", 2);
	spriteak[2].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Attack.bmp", 3);
	spriteak[3].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Dead.bmp", 4);
	spriteak[4].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Humo.bmp", 5);
	spriteak[5].kop = 6;
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