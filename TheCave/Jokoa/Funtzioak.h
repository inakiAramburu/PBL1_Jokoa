#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280
#define MENU_PANTAILA ".\\media\\fondos\\Menu.bmp"
#define LEHENENGO_PANTAILA ".\\media\\fondos\\Nivel2.bmp"
#define BIGARREN_PANTAILA ".\\media\\fondos\\Nivel3.bmp"
#define MUSIKA_MENU ".\\media\\sound\\test.wav"
#define EFEKTUA_KEA ".\\media\\sound\\Kea.wav"
#define EFEKTUA_KORRIKA ".\\media\\sound\\Korrika.wav"

typedef enum {MENUA, KREDITUAK, KONTROLAK, LEHEN, BIGARREN, HIRUGARREN, LAUGARREN, ATERA}PANTAILAK;
typedef enum {IDLE, KORRIKA, SALTO, ERORI, ERASO, HIL, KEA}SPRITE;
typedef enum {EZJOKATZEN, JOKATZEN}JOKOA;
typedef enum {EZKER, ERDIA, ESKUIN}SAGUA;
typedef enum {HILDA, BIZIRIK}EGOERA;
typedef enum {SAKATUGABE, SAKATUTA }TEKLAK;
typedef enum {ATZERA, AURRERA}ZENTZUA;
typedef enum {EZ, BAI}BOOLEANOA;


int LeihoaEtaRenderHasi();		//Lehia eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude 1 bueltatuko du 
int IrudiakKendu(int ZnbtUtzi);		//Irudien texturak ezabatzen ditu azkenetik hasten, nahi bada atzeko planoa ezabatu gabe utz daiteke, 1 parametroa pasatzen. Zenbat argazki geratu diren pasatzen du
void KargatuIrudiak(PANTAILAK Pantaila); //Pantailaren arabera argazki batzuk kargatzera deituko ditu, baina lehenengo garkatuta zeuden guztiak ezabatzen ditu
void ImgKargatu(char src[], int zabalera, int altuera, int x, int y);		//Argazki bat ordenagailutik igotzen du, eta beharrezkoak diren datuak emango di (zabalera, altuera, non kokatu...)
void KargatuMapa(char mapa[], void **pixels, int *pitch, Uint8 *bpp);
void RenderPrestatu(ZENTZUA begira);		//Texturak renderizatzeko modu orokor batean, ere pertsonaia renderizatuko du "BIZIRIK" badago
void RenderMenu();		//MENUA pantailarako animazioak egiteko renderizatzen ditu testuaren argazkiak, eta saguaren arabera bata edo bestea erakusten du
void Irudikatu();		//Pantailan renderra erakusten du
void EbentuakKonprobatu(JOKOA *Jokoa, PANTAILAK *Pantaila, int* i, ZENTZUA *begira);		//Gertazten diren ebentu guztiak konprobatu eta behar bada ekintzak hasi
void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA* klika);		//Saguarekin klikatu denean zer botoi erabili den ikusten eta gordetzen du
void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika);		//Klika non egin den eta botoiaren arabera ekintzak hasten dira
void Animazioa();		//Jokatu sakatzen denean aniamzio labur bat egiten du
void KargatuPertsonaia();		//Jokatu sakatzean lehenengo aldiz pertsonaia kargatzera deitzen du
void JokalariaKargatu(char Irudia[], int i);		//Pertsonaiaren spriteak kargatzeko balio du, helbidea eta spritea zenbak irudi dituen hartzu eta gordetzen ditu
void Ekintzak(int *i, void* pixels, int pitch, Uint8 bpp, ZENTZUA* begira);
void Amaitu(JOKOA *Jokoa, PANTAILAK *Pantaila);			//Jokoa amaitzen du
void MusikaJarri(char Fitxategia[]);
void MusikaKendu(char Fitxategia[]);
Uint32 getpixel(void* pixels, int pitch, Uint8 bpp, Uint32 x, Uint32 y);
int KolisioakKonprobatu(void* pixels, int pitch, Uint8 bpp);

#endif
