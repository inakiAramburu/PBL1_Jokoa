#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280

typedef enum {MENUA, LEHEN, BIGARREN, ATERA}PANTAILAK;
typedef enum {IDLE, KORRIKA, SALTO, ERASO, HIL }SPRITE;
typedef enum{HILDA, BIZIRIK}EGOERA;
typedef enum{EZJOKATZEN, JOKATZEN}JOKOA;

int LeihoaEtaRenderHasi();
void KargatuIrudiak(PANTAILAK Pantaila);
void ImgKargatu(char src[], int zabalera, int altuera, int x, int y);
void RenderPrestatu();
void RenderMenu();
void Irudikatu();
void EbentuakKonprobatu(JOKOA *Jokoa, PANTAILAK *Pantaila);

void Amaitu(JOKOA *Jokoa, PANTAILAK *Pantaila);
#endif
