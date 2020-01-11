#include "Funtzioak.h"
#include <SDL.h>
#include <stdio.h>

Uint32 time=0;
Uint32 time2 = 0;
Uint32 abiadura[8] = {150,60,80,80,10,100,80};
int numero = 0;
//IDLE, KORRIKA, SALTO, ERORI, ERASO, HIL, KEA
/*
extern int pitch; //el numero de pixels por fila
extern Uint32 bpp; //el numero de Byte por pixel
extern void* pixels;*/









typedef struct S_IMGPERTSONAIA		//Pertsonaiaren irudiak banaturik, beti kargatuta egongo direlako Jokatu sakatzen denetik
{
	SDL_Texture* textura;
	int kop;
}IMGPERTSONAIA;

IMGPERTSONAIA spriteak[7];		




typedef struct S_ETSAIA		//Etsaien datuak
{
	SDL_Rect SrcSprite, DestSprite;
	BOOLEANOA bizirik;
	int abiadura;
	SDL_Texture* textura;
}ETSAIA;

ETSAIA etsaia[ETSAI_KOPURUA];