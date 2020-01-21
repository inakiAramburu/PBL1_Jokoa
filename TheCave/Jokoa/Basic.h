#ifndef BASIC_H
#define BASIC_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280

typedef enum { MENUA, KREDITUAK, KONTROLAK, LEHEN, BIGARREN, HIRUGARREN, LAUGARREN, BOSTGARREN, FINALA, AUKERATUMODUA, AUKERATUZERBITZUA, AUKERAZERBITZARIA, AUKERABEZEROA, MINIJOKOA, ATERA }PANTAILAK;
typedef enum { IDLE, KORRIKA, SALTO, ERORI, ERASO, HIL, KEA }SPRITE;
typedef enum { MUSIKA_JOKUA, KEA_EFEKTUA, EZPATA_EFEKTUA, TIROA_EFEKTUA, MusikaBOSS, BOOS_KOLPE_EFEKTUA, IRABAZI_EFEKTUA, GALDU_EFEKTUA, PONG_PARETA, PONG_PALA, PONG_IRABAZI }ABEZTIAK;


typedef struct S_PERTSONAIA		//Pertsonaiaren datuak////
{
	SDL_Rect SrcSprite, DestSprite;//1.de donde lo pillas 2. donde lo pones
	SPRITE sprite;
	SDL_bool bizirik;
	SDL_bool salto;
	SDL_bool erortzen;
	SDL_bool erasotzen;
}PERTSONAIA;

typedef struct S_ETSAIA		//Etsaien datuak
{
	SDL_Rect SrcSprite, DestSprite; //1.de donde lo pillas 2. donde lo pones
	SDL_bool bizirik;
	int abiadura;
	SDL_Texture* textura;
}ETSAIA;
typedef struct S_TIROAK		//Etsaien datuak
{
	SDL_Rect tiroa;
	SDL_bool pantailan;
	int angelua;
}TIROAK;


typedef struct S_PONG
{
	SDL_bool piztuta;
	SDL_Rect pilota, Player1, Player2;
	int angelua, abiadurax, abiaduray, P1puntuazioa, P2puntuazioa;
}PONG;


int LeihoaEtaRenderHasi();		//Lehia eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude 1 bueltatuko du 
void Amaitu(SDL_bool* Jokatzen, PANTAILAK* Pantaila);			//Jokoa amaitzen du
void PertsonaiaHasieratu();		//Jokatu sakatzean lehenengo aldiz pertsonaia kargatzera deitzen du
void EtsaiakHasieratu();
void GuztiakHil();
void PertsonaiaHil();
void EtsaiaKendu(int pos, int BizirikDaudenEtsaiak[], int BizirikKopurua);
void RectEraikitzailea(SDL_Rect* dest, int x, int y, int h, int w);
void BerrizJaurti();

#endif