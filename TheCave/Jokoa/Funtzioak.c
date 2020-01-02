#include "Funtzioak.h"
#include <SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

int LeihoaHasi()
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
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return 1;
	}

	SDL_FreeSurface(surface);		//Aurrekoa garbitzeko
	SDL_PollEvent(&event);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	return 0;
}

//Argazkia jartzen du.
int Argazkia_Sartu(char Irudia[], int Posx, int Posy)
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Event event;


	//irudia kargatu
	surface = SDL_LoadBMP(Irudia);
	if (!surface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return 1;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return 1;
	}
	//irudiaren pozizioa jarri

	SDL_Rect DestNeurriak;

	DestNeurriak.x = 640;
	DestNeurriak.y = 360;
	DestNeurriak.w = 128;
	DestNeurriak.h = 60;

	SDL_Rect SrcNeurriak;

	SrcNeurriak.x = Posx;
	SrcNeurriak.y = Posy;
	SrcNeurriak.w = 128;
	SrcNeurriak.h = 60;

	SDL_FreeSurface(surface); //Aurrekoa garbitzeko
	SDL_PollEvent(&event);
	SDL_RenderCopy(renderer, texture, &SrcNeurriak, &DestNeurriak);
	SDL_RenderPresent(renderer);

	return 0;

}

void Sprite(char Argazkia[], char Atzekoplanoa[], int PosX, int PosY, int spritekopurua) {
	
	int i;

	for (i = 0; i < spritekopurua; i++)
	{
		AtzekoPlanoBerria(Atzekoplanoa);
		Argazkia_Sartu(Argazkia, (128 * i), 0);
		SDL_Delay(100);
	}
}