#include "Funtzioak.h"
#include <SDL.h>
#include <stdio.h>

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
int Argazkia_Sartu(char Irudia[], int Posx, int Posy, int luzeera, int altuera)
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
	SDL_Rect neurriak;
	int i = 0;

	
		neurriak.x = Posx;
		neurriak.y = Posy;
		neurriak.w = luzeera;
		neurriak.h = altuera;

		SDL_FreeSurface(surface);		//Aurrekoa garbitzeko
		SDL_PollEvent(&event);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, texture, NULL, &neurriak);
		SDL_RenderPresent(renderer);
		SDL_Delay(1);
	

	//neurriak.x = Posx;


	return 0;

}

//musika funtzioa
/*a medias*/
void MusikaJarri(char Fitxategia[])
{
	// explicacion
	//https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/

	//inicia la parte de audio
	SDL_Init(SDL_INIT_AUDIO);

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
	//SDL_Quit();
}

void teklatua()
{
	char Pertsonaia[128] = ".\\media\\player\\Player\\run\\run1.bmp";

	
	int Posx = -10;
	int Posy = 532;
	int D = 0, SPACE = 0,A=0;
	int abiadura = 0;
	int abiaduray = 0;
	while (1) {

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.scancode)
				{
					//derecha
				case SDL_SCANCODE_D:
					D = 1;
					abiadura = 7;


					break;

					//izquierda

				case SDL_SCANCODE_A:
					A = 1;
					abiadura = -7;

					break;

					//abajo

				case SDL_SCANCODE_S:
					printf("S\n");
					break;

					//arriba

				case SDL_SCANCODE_W:
					printf("W\n");
					break;

					//saltar

				case SDL_SCANCODE_SPACE:
					SPACE = 1;
					abiaduray = 7;
					break;

				}
			}
			if (e.type == SDL_KEYUP)
			{

				switch (e.key.keysym.scancode)
				{
					//derecha
				case SDL_SCANCODE_D:
					D = 0;
					abiadura = 0;
					break;

					//izquierda

				case SDL_SCANCODE_A:
					A = 0;
					abiadura = 0;

					break;

					//abajo

				case SDL_SCANCODE_S:
					printf("S\n");
					break;

					//arriba

				case SDL_SCANCODE_W:
					printf("W\n");
					break;

					//saltar

				case SDL_SCANCODE_SPACE:
					SPACE = 0;
					abiaduray = 0;
					break;

				}
			}
		}
		printf("D %d SPACE %d A: %d\n", D, SPACE, A);
		Posx += abiadura;
		Posy -= abiaduray;
		Argazkia_Sartu(Pertsonaia, Posx, Posy, 150, 100);
		SDL_Delay(50);
	}
}

