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
int Argazkia_Sartu(char Irudia[], int Posx, int Posy, int EPosx, int EPosy)
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

	DestNeurriak.x = Posx;
	DestNeurriak.y = Posy;
	DestNeurriak.w = 128;
	DestNeurriak.h = 60;

	SDL_Rect SrcNeurriak;

	SrcNeurriak.x = EPosx;
	SrcNeurriak.y = EPosy;
	SrcNeurriak.w = 128;
	SrcNeurriak.h = 60;

	SDL_FreeSurface(surface);		//Aurrekoa garbitzeko
	SDL_PollEvent(&event);
	SDL_RenderCopy(renderer, texture, &SrcNeurriak, &DestNeurriak);
	SDL_RenderPresent(renderer);


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
	char PertsonaiaDerecha[128] = ".\\media\\player\\Run.bmp";
	char PertsonaiaIzquierda[128] = ".\\media\\player\\Run2.bmp";
	char PertsonaiaAtaque [128]= ".\\media\\player\\Attack.bmp";
	char Atzekoplanoa[128] = ".\\media\\fondos\\Menu.bmp";	//Argazkiaren helbidea


	int Posx = -10;
	int Posy = 545;
	int D = 0, SPACE = 0, A = 0, X=0;
	int abiadura = 0;
	int abiaduray = 0;
	int i = 0;
	int EPosx = 0;
	int EPosy = 0;
	while (1) {

		SDL_Event evento;
		while (SDL_PollEvent(&evento) != 0) {

			if (evento.type == SDL_KEYDOWN)
			{
				switch (evento.key.keysym.scancode)
				{
					//derecha
				case SDL_SCANCODE_D:
					D = 1;
					abiadura = 7;
					break;
					//ataque
				case SDL_SCANCODE_X:
					X = 1;
					abiadura = 0;
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
			if (evento.type == SDL_KEYUP)
			{

				switch (evento.key.keysym.scancode)
				{
					//derecha
				case SDL_SCANCODE_D:
					D = 0;
					i = 0;
					EPosx=0;
					EPosy=0;
					abiadura = 0;
					break;
					//ataque
				case SDL_SCANCODE_X:
					X = 0;
					abiadura = 0;
					break;

					//izquierda

				case SDL_SCANCODE_A:
					A = 0;
					i = 0;
					EPosx = 0;
					EPosy = 0;
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
		printf("D %d SPACE %d A: %d X: %d\n", D, SPACE, A, X);
		Posx += abiadura;
		Posy -= abiaduray;

		EPosy = 0;
		
		if (D == 0) {
			if (A == 1) {
				Argazkia_Sartu(PertsonaiaIzquierda, Posx, Posy, EPosx, EPosy);
			}
			else if(D==1) {
				Argazkia_Sartu(PertsonaiaDerecha, Posx, Posy, EPosx, EPosy);
			}
		}
		 if (D == 1|| A==0) {
			 
				Argazkia_Sartu(PertsonaiaDerecha, Posx, Posy, EPosx, EPosy);
				if (i >= 10)
				{	i = 0;
					Argazkia_Sartu(PertsonaiaDerecha, Posx, Posy, EPosx, EPosy);
				}
				AtzekoPlanoBerria(Atzekoplanoa);		
				EPosx = (128 * i);
				i++;
				Argazkia_Sartu(PertsonaiaDerecha, Posx, Posy, EPosx, EPosy);
				SDL_Delay(50);
		}	
		else if (A== 1 || D == 0) {
			 Argazkia_Sartu(PertsonaiaIzquierda, Posx, Posy, EPosx, EPosy);
			 if (i > 10)
			 {
				 i = 0;
				 Argazkia_Sartu(PertsonaiaIzquierda, Posx, Posy, EPosx, EPosy);
			 }
			 AtzekoPlanoBerria(Atzekoplanoa);
			 //SDL_Delay(90);
			 EPosx = (128 * i);
			 i++;
			 Argazkia_Sartu(PertsonaiaIzquierda, Posx, Posy, EPosx, EPosy);
			 SDL_Delay(50);
		 }
		 if (X == 1) {
			 
			 Argazkia_Sartu(PertsonaiaAtaque, Posx, Posy, 128 * i, EPosy);
			 AtzekoPlanoBerria(Atzekoplanoa);
			 Argazkia_Sartu(PertsonaiaAtaque, Posx, Posy, 128 * i, EPosy);
			 SDL_Delay(50);
		 }
		
	}
}
