#ifndef EVENT_H
#define EVENT_H

#include "Motion.h"

typedef enum { EZKER, ERDIA, ESKUIN }SAGUA;
typedef enum { GORRIA = 249, BELTZA = 0, TXURIA = 255, BERDEA = 250, HORIA = 251, MOREA = 253, URDINA = 252 }KOLOREAK;
typedef enum {ZERBITZARI, BEZEROA}ROL;

typedef struct S_BEHEKOPIXEL
{
	KOLOREAK ezker;
	KOLOREAK eskuin;
}BEHEKOPIXEL;
typedef struct S_ALBOKOPIXEL
{
	KOLOREAK goikoa;
	KOLOREAK erdikoa;
	KOLOREAK behekoa;
}ALBOKOPIXEL;
typedef struct S_HITBOX
{
	ALBOKOPIXEL ezker;
	ALBOKOPIXEL eskuin;
	BEHEKOPIXEL behekoa;
	KOLOREAK goikoa;

}HITBOX;

extern BOOLEANOA a;
extern BOOLEANOA d;
extern BOOLEANOA espacio;
extern BOOLEANOA k;
extern BOOLEANOA w;
extern BOOLEANOA f3;
extern BOOLEANOA s;
extern BOOLEANOA gora;
extern BOOLEANOA behera;

void EbentuakKonprobatu(BOOLEANOA* Jokatzen, PANTAILAK* Pantaila, int* i, ZENTZUA* begira);		//Gertazten diren ebentu guztiak konprobatu eta behar bada ekintzak hasi
void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA* klika);		//Saguarekin klikatu denean zer botoi erabili den ikusten eta gordetzen du
void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika, BOOLEANOA* Jokatzen);		//Klika non egin den eta botoiaren arabera ekintzak hasten dira
void KolisioakKonprobatu(void* pixels, int pitch, Uint8 bpp, int BizirikDaudenEtsaiak[], int* BizirikKopurua, ZENTZUA begira, int* pAnimazioa, FASEAK *txokolate, int *bAnimazioa);
void PongKolisioa();

#endif

