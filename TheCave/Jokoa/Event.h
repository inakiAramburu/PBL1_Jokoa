#ifndef EVENT_H
#define EVENT_H

#include "Motion.h"

typedef enum { EZKER, ERDIA, ESKUIN }SAGUA;
typedef enum { GORRIA = 249, BELTZA = 0, TXURIA = 255, BERDEA = 250, HORIA = 251, MOREA = 253, URDINA = 252 }KOLOREAK;
typedef enum {LOKAL, ZERBITZARI, BEZEROA}ROL;

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

//lo cojer de event.c y asi los puedes usar donde quieras 
extern SDL_bool a;
extern SDL_bool d;
extern SDL_bool espacio;
extern SDL_bool k;
extern SDL_bool w;
extern SDL_bool f3;
extern SDL_bool s;
extern SDL_bool gora;
extern SDL_bool behera;

void EbentuakKonprobatu(SDL_bool* Jokatzen, PANTAILAK* Pantaila, int* pAnimazioa, ZENTZUA* begira, int BizirikDaudenEtsaiak[], int BizirikKopurua);	//Gertazten diren ebentu guztiak konprobatu eta behar bada ekintzak hasi
void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA* klika);		//Saguarekin klikatu denean zer botoi erabili den ikusten eta gordetzen du
void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika, SDL_bool* Jokatzen);		//Klika non egin den eta botoiaren arabera ekintzak hasten dira
void KolisioakKonprobatu(void* pixels, int pitch, Uint8 bpp, int BizirikDaudenEtsaiak[], int* BizirikKopurua, ZENTZUA begira, int* pAnimazioa);
void PongKolisioa();
void KolisioakBoss(PANTAILAK* Pantaila, ZENTZUA begira, int* pAnimazioa, int* bAnimazioa, int BizirikDaudenEtsaiak[], int* BizirikKopurua, Uint32* attackrate);



#endif

