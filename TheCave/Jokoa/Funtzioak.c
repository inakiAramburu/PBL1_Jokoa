#include "Funtzioak.h"
#include <SDL.h>
#include <stdio.h>

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
	surface2 = SDL_LoadBMP(".\\img\\kiss.bmp");
	surface3 = SDL_LoadBMP(".\\img\\kiss2.bmp");

	
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	texture3 = SDL_CreateTextureFromSurface(renderer, surface3);




	SDL_FreeSurface(surface);		//Aurrekoa garbitzeko
	SDL_FreeSurface(surface2);
	SDL_FreeSurface(surface3);

	SDL_Rect neurriak;

	neurriak.x = 354; 
	neurriak.y = 112;
	neurriak.w = 600;
	neurriak.h = 460;


	int i=0;
	
		
		
		
		while (i != 99999) {
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT) {
				break;
			}
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderCopy(renderer, texture2, NULL, &neurriak);




			SDL_RenderPresent(renderer);

			i++;
		}
		while (1) {
		i = 0;
		while (i!=10) {
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT) {
				break;
			}
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderCopy(renderer, texture3, NULL, &neurriak);



			SDL_RenderPresent(renderer);
			i++;

		}
		i = 0;
		while (i != 10) {
			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT) {
				break;
			}
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderCopy(renderer, texture2, NULL, &neurriak);




			SDL_RenderPresent(renderer);

			i++;
		}
		i = 0;
		
	}

	return 0;

}


void Musika(char Fitxategia[])
{


	// explicacion
	//https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/

	//inicia la parte de audio
	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	/*  fichategia cargatu */
	if (SDL_LoadWAV("UnderTale.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
		fprintf(stderr, "no encuentra test.wav: %s\n", SDL_GetError());
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
	//SDL_Quit();
}

