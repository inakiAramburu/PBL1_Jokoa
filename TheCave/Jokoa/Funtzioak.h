#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280

typedef enum {MENUA, LEHEN, BIGARREN}PANTAILAK;

int LeihoaEtaRenderHasi();
void KargatuIrudiak(PANTAILAK Pantaila);
void ImgKargatu(char src[]);
void RenderPrestatu();
void Irudikatu();

void Amaitu();
#endif
