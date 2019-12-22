#include "Funtzioak.h"
#include <SDL.h>

SDL_Renderer* render;
SDL_Window* leihoa;

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

	if (leihoa == NULL) { 		// Leihoa komprobatzen du.

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da leihoa sortu: %s\n", SDL_GetError());
		return 1;
	}
	render = SDL_CreateRenderer(leihoa, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	return 0;
}

//Fondoa jartzen du.
int AtzekoPlanoBerria(char AtzekoPlanoa[])
{
	
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Event event;

	//irudia kargatu
	surface = SDL_LoadBMP(AtzekoPlanoa);
	if (!surface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return 1;
	}
	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return 1;
	}

	SDL_FreeSurface(surface);		//Aurrekoa garbitzeko

	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, NULL);
	SDL_RenderPresent(render);
	
	return 0;

}

void Amaitu()
{
	SDL_DestroyWindow(leihoa);
	SDL_DestroyRenderer(render);

	return;
}
