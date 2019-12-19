#include "Funtzioak.h"
#include <SDL.h>

SDL_Window* window;

void LeihoaHasi()
{
	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da SDL hasieratu: %s", SDL_GetError());
		return 1;
	}
	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"The Cave",                  			// Izenburua
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		PANTAILA_ZABALERA,                // Sortzeko lehioaren zabalera
		PANTAILA_ALTUERA,                 // Sortzeko leihoaren altuera
		SDL_WINDOW_OPENGL                 // Erabilitako teknologia grafikoa
	);
	// Leihoa komprobachen du.
	if (window == NULL) {

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da leihoa sortu: %s\n", SDL_GetError());
		return 1;
	}
}

//Fondoa jartzen du.
void AtzekoPlanoBerria(char AtzekoPlanoa[])
{

	SDL_Renderer* renderer;


	SDL_Surface* surface;
	SDL_Surface* surface2;
	SDL_Surface* surface3;

	SDL_Texture* texture;
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	SDL_Event event;


	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//irudia kargatu
	surface = SDL_LoadBMP(AtzekoPlanoa);
	surface2 = SDL_LoadBMP(".\\img\\pergamino.bmp");


	texture = SDL_CreateTextureFromSurface(renderer, surface);
	texture2 = SDL_CreateTextureFromSurface(renderer, surface2);




	SDL_FreeSurface(surface);		//Aurrekoa garbitzeko
	SDL_FreeSurface(surface2);


	SDL_Rect neurriak;

	neurriak.x = 354;
	neurriak.y = 112;
	neurriak.w = 600;
	neurriak.h = 460;



	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		SDL_RenderClear(renderer);


		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderCopy(renderer, texture2, NULL, &neurriak);
		SDL_RenderPresent(renderer);


	}

	return 0;

}