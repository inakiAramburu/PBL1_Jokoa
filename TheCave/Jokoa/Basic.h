#ifndef BASIC_H
#define BASIC_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280

typedef enum { FALSE, TRUE }BOOLEANOA;
typedef enum { MENUA, KREDITUAK, KONTROLAK, LEHEN, BIGARREN, HIRUGARREN, LAUGARREN, BOSTGARREN, ATERA }PANTAILAK;

typedef struct S_PERTSONAIA		//Pertsonaiaren datuak
{
	SDL_Rect SrcSprite, DestSprite;
	SPRITE sprite;
	BOOLEANOA bizirik;
	BOOLEANOA salto;
	BOOLEANOA erortzen;
	BOOLEANOA erasotzen;
}PERTSONAIA;

int LeihoaEtaRenderHasi();		//Lehia eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude 1 bueltatuko du 
void Amaitu(BOOLEANOA* Jokatzen, PANTAILAK* Pantaila);			//Jokoa amaitzen du
void PertsonaiaHasieratu();		//Jokatu sakatzean lehenengo aldiz pertsonaia kargatzera deitzen du
void EtsaiakHasieratu();
void GuztiakHil();
void PertsonaiaHil();
void EtsaiaKendu(int pos, int BizirikDaudenEtsaiak[], int BizirikKopurua);

#endif