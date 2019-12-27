#include "Funtzioak.h"
#include <SDL.h>

SDL_Renderer* render;
SDL_Window* leihoa;

typedef struct S_IMG
{
	SDL_Texture* textura;
	int x;
}IMG;

IMG Irudiak[100];		//Irudiak, dagozkien datuekin
int IrudiZnbk = 0;		//Irudi kopurua, hasieran 0

typedef struct S_PERTSONAIA
{
	int x;
	int y;
	EGOERA egoera;
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

	render = SDL_CreateRenderer(leihoa, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);		//Renderizatua hasi

	return 0;
}

void KargatuIrudiak(PANTAILAK Pantaila)
{
	switch (Pantaila)		
	{
		/*Jokolariak pantaila berri batera pasatzean behar izango diren irudi guztiak kargatzen dira. Horrela ez irudiak ez dira kargatuko
		jokalaria puntu horretara heltzen ez bada*/

		case MENUA:
			ImgKargatu(".\\img\\Menu.bmp");
			break;
		case LEHEN:
			ImgKargatu(".\\img\\Nivel2.bmp");
			break;
	}
}

void ImgKargatu(char src[])
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
	IrudiZnbk++;
}

void RenderPrestatu()
{
	int i;

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);

	for (i = 0; i < IrudiZnbk; i++)
	{
		SDL_RenderCopy(render, Irudiak[i].textura, NULL, NULL);
	}
}

void Irudikatu()
{
	SDL_RenderPresent(render);
}

void Amaitu()
{
	SDL_DestroyWindow(leihoa);
	SDL_DestroyRenderer(render);

	return;
}

void EbentuakKonprobatu()
{
	SDL_Event ebentua;
	while (SDL_PollEvent(&ebentua))
	{
		switch (ebentua.type)
		{
		case SDL_QUIT:
			Amaitu();
			break;
		}
	}
	
}
