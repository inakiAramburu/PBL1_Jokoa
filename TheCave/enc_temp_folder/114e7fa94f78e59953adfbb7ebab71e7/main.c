/*#include "SDL.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
	SDL_Window* win = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* bitmapTex = NULL;
	SDL_Surface* bitmapSurface = NULL;
	SDL_Surface* pergamino = NULL;
	

	SDL_Init(SDL_INIT_VIDEO);

	//SDL_CreateWindow(Nombre de la pnatalla , Centrar la posicion x , centrar la posicion y , pixeles en x, pixeles en y, 0);

	win = SDL_CreateWindow("The Cave", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	bitmapSurface = SDL_LoadBMP("fondo.bmp");
	bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
	SDL_FreeSurface(bitmapSurface);
	
	

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	

	SDL_DestroyTexture(bitmapTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);

	

	SDL_Quit();

	pergamino = SDL_LoadBMP("pergamino.bmp");

	SDL_BlitSurface(pergamino, NULL, win, 100, 100);


	return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#define MASK 255, 255, 255

int main()
{
	SDL_Window* screen;
	SDL_Surface* fondo;
	SDL_Surface* jugador;
	SDL_Event event;
	int terminar = 0;
	SDL_Rect posicion;
	int i, j;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("No se pudo inicializar SDL: %s\n",
			SDL_GetError());
		exit(1);
	}

	fondo = SDL_LoadBMP("fondo.bmp");
	jugador = SDL_LoadBMP("pergamino.bmp");
	

	screen = SDL_CreateWindow("The Cave", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

	if (screen == NULL)
	{
		printf("Error al entrar a modo grafico: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}


	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
		{
			posicion.x = 64 * i;
			posicion.y = 48 * j;
			SDL_BlitSurface(fondo, NULL, screen, &posicion);
		}

	posicion.x = 320;
	posicion.y = 400;
	SDL_BlitSurface(jugador, NULL, screen, &posicion);



	while (terminar == 0)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYUP)
				terminar = 1;
		}
	}

	SDL_Quit();
	return 0;
}
	
