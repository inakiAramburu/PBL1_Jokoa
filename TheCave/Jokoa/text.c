/*#include "SDL_ttf.h"
#include "SDL.h"
#include "text.h"
#include <stdio.h>

TTF_Font* font = 0;


void textuaSortu(void) {
	font = TTF_OpenFontIndex("C:\\WINDOWS\\Fonts\\Arial.TTF", 16, 0);
	if (!font)
	{
		printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
		// handle error
	}
}
void textuaIdatzi(int x, int y, char* str)
{
	SDL_Surface* surface;
	SDL_Texture* mTexture;
	SDL_Color textColor = { 0XFF, 0XFF, 0XFF };
	SDL_Rect src, dst;
	extern SDL_Renderer* render;


	if (font == 0) return;
	
	src.x = 0; dst.x = x;
	src.y = 0; dst.y = y;
	surface = TTF_RenderText_Solid(font, str, textColor);
	mTexture = SDL_CreateTextureFromSurface(render, surface);
	SDL_RenderCopy(render, mTexture, &src, &dst);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(mTexture);
}*/