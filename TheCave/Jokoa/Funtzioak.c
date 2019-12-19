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
	int prueba = 0, prueba2 = 0;

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
	//surface3 = SDL_LoadBMP(".\\img\\pergamino2.bmp");


	texture = SDL_CreateTextureFromSurface(renderer, surface);
	texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	//texture3 = SDL_CreateTextureFromSurface(renderer, surface3);




	SDL_FreeSurface(surface);		//Aurrekoa garbitzeko
	SDL_FreeSurface(surface2);
	//SDL_FreeSurface(surface3);


	SDL_Rect neurriak;
	SDL_Rect neurriak2;
	
	

	neurriak.x = 400;
	neurriak.y = 100;
	neurriak.w = 480;
	neurriak.h = 500;

	neurriak2.x = 390;
	neurriak2.y = 90;
	neurriak2.w = 500;
	neurriak2.h = 520;



	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		SDL_RenderClear(renderer);
		 
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderCopy(renderer, texture2, NULL, &neurriak2);
		SDL_RenderPresent(renderer);

		if (prueba2 == 0)
		{
			
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderCopy(renderer, texture2, NULL, &neurriak);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000);
			prueba2 = 1;

		}
		


	}

	return 0;

}