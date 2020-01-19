#ifndef BASIC_H
#define BASIC_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280

typedef enum { FALSE, TRUE }BOOLEANOA;
typedef enum { MENUA, KREDITUAK, KONTROLAK, LEHEN, BIGARREN, HIRUGARREN, LAUGARREN, BOSTGARREN, FINALA, MINIJOKOA, AUKERATUMODUA, AUKERATUZERBITZUA, AUKERAZERBITZARIA, AUKERABEZEROA, ATERA }PANTAILAK;
typedef enum { IDLE, KORRIKA, SALTO, ERORI, ERASO, HIL, KEA }SPRITE;
typedef enum { MUSIKA_JOKUA, KEA_EFEKTUA, EZPATA_EFEKTUA, TIROA_EFEKTUA, MusikaBOSS, IRABAZI_EFEKTUA, GALDU_EFEKTUA, PONG_PARETA, PONG_PALA, PONG_IRABAZI }ABEZTIAK;




typedef struct S_PERTSONAIA		//Pertsonaiaren datuak////
{
	SDL_Rect SrcSprite, DestSprite;
	SPRITE sprite;
	BOOLEANOA bizirik;
	BOOLEANOA salto;
	BOOLEANOA erortzen;
	BOOLEANOA erasotzen;
}PERTSONAIA;

typedef struct S_ETSAIA		//Etsaien datuak
{
	SDL_Rect SrcSprite, DestSprite;
	BOOLEANOA bizirik;
	int abiadura;
	SDL_Texture* textura;
}ETSAIA;
typedef struct S_TIROAK		//Etsaien datuak
{
	SDL_Rect tiroa;
	BOOLEANOA pantailan;
	int angelua;
}TIROAK;


typedef struct S_PONG
{
	BOOLEANOA piztuta;
	SDL_Rect pilota, Player1, Player2;
	int angelua, abiadurax, abiaduray, P1puntuazioa, P2puntuazioa;
}PONG;


int LeihoaEtaRenderHasi();		//Lehia eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude 1 bueltatuko du 
void Amaitu(BOOLEANOA* Jokatzen, PANTAILAK* Pantaila);			//Jokoa amaitzen du
void PertsonaiaHasieratu();		//Jokatu sakatzean lehenengo aldiz pertsonaia kargatzera deitzen du
void EtsaiakHasieratu();
void GuztiakHil();
void PertsonaiaHil();
void EtsaiaKendu(int pos, int BizirikDaudenEtsaiak[], int BizirikKopurua);
void RectEraikitzailea(SDL_Rect* dest, int x, int y, int h, int w);
void BerrizJaurti();

#endif