#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280

typedef enum {MENUA, LEHEN, BIGARREN, KREDITUAK, KONTROLAK, ATERA}PANTAILAK;
typedef enum {IDLE, KORRIKA, SALTO, ERASO, HIL, KEA}SPRITE;
typedef enum {EZJOKATZEN, JOKATZEN}JOKOA;
typedef enum {EZKER, ERDIA, ESKUIN}SAGUA;

int LeihoaEtaRenderHasi();
void KargatuIrudiak(PANTAILAK Pantaila);
void ImgKargatu(char src[], int zabalera, int altuera, int x, int y);
void RenderPrestatu();
void RenderMenu();
void Irudikatu();
void EbentuakKonprobatu(JOKOA *Jokoa, PANTAILAK *Pantaila);
void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA* klika);
void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika);
void Animazioa();
void KargatuPertsonaia();
void JokalariaKargatu(char Irudia[], int i);
void Amaitu(JOKOA *Jokoa, PANTAILAK *Pantaila);
#endif
