#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280
#define MENU_PANTAILA ".\\media\\levels\\Menu.bmp"
#define LEHENENGO_PANTAILA ".\\media\\levels\\Nivel1.bmp"
#define LEHENENGO_MASKARA ".\\media\\levels\\maskarak\\Nivel1M.bmp"
#define BIGARREN_PANTAILA ".\\media\\levels\\Nivel2.bmp"
#define BIGARREN_MASKARA ".\\media\\levels\\maskarak\\Nivel2M.bmp"
#define HIRUGARREN_PANTAILA ".\\media\\levels\\Nivel3.bmp"
#define HIRUGARREN_MASKARA ".\\media\\levels\\maskarak\\Nivel3M.bmp"
#define LAUGARREN_PANTAILA ".\\media\\levels\\Nivel4.bmp"
#define LAUGARREN_MASKARA ".\\media\\levels\\maskarak\\Nivel4M.bmp"
#define BOSTGARREN_PANTAILA ".\\media\\levels\\Nivel5.bmp"
#define BOSTGARREN_MASKARA ".\\media\\levels\\maskarak\\Nivel5M.bmp"
#define GRABITATEA 18
#define ETSAI_KOPURUA 15
#define ETSAIA_ABIADURA 5

typedef enum {MENUA, KREDITUAK, KONTROLAK, LEHEN, BIGARREN, HIRUGARREN, LAUGARREN, BOSTGARREN, ATERA}PANTAILAK;
typedef enum {IDLE, KORRIKA, SALTO, ERORI, ERASO, HIL, KEA}SPRITE;
typedef enum {EZJOKATZEN, JOKATZEN}JOKOA;
typedef enum {EZKER, ERDIA, ESKUIN}SAGUA;
typedef enum {HILDA, BIZIRIK}EGOERA;
typedef enum {SAKATUGABE, SAKATUTA }TEKLAK;
typedef enum {ATZERA, AURRERA}ZENTZUA;
typedef enum {EZ, BAI}BOOLEANOA;
typedef enum {GORRIA = 249, BELTZA = 0, TXURIA = 255, BERDEA = 250, HORIA = 251, MOREA = 253, URDINA = 252}KOLOREAK;

int LeihoaEtaRenderHasi();		//Lehia eta rendera hasieratzen du, eta leihoari ikono bat ematen dio, errorerik baldin badaude 1 bueltatuko du 
int IrudiakKendu(int ZnbtUtzi);		//Irudien texturak ezabatzen ditu azkenetik hasten, nahi bada atzeko planoa ezabatu gabe utz daiteke, 1 parametroa pasatzen. Zenbat argazki geratu diren pasatzen du
void KargatuIrudiak(PANTAILAK Pantaila, int BizirikDaudenEtsaiak[], int* BizirikKopurua); //Pantailaren arabera argazki batzuk kargatzera deituko ditu, baina lehenengo garkatuta zeuden guztiak ezabatzen ditu
void ImgKargatu(char src[], int zabalera, int altuera, int x, int y);		//Argazki bat ordenagailutik igotzen du, eta beharrezkoak diren datuak emango di (zabalera, altuera, non kokatu...)
void KargatuMapa(char mapa[], void **pixels, int *pitch, Uint8 *bpp);
void RenderPrestatu(ZENTZUA begira, int BizirikDaudenEtsaiak[], int BizirikKopurua);		//Texturak renderizatzeko modu orokor batean, ere pertsonaia renderizatuko du "BIZIRIK" badago
void RenderMenu();		//MENUA pantailarako animazioak egiteko renderizatzen ditu testuaren argazkiak, eta saguaren arabera bata edo bestea erakusten du
void Irudikatu();		//Pantailan renderra erakusten du
void EbentuakKonprobatu(JOKOA *Jokoa, PANTAILAK *Pantaila, int* i, ZENTZUA *begira);		//Gertazten diren ebentu guztiak konprobatu eta behar bada ekintzak hasi
void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA* klika);		//Saguarekin klikatu denean zer botoi erabili den ikusten eta gordetzen du
void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika);		//Klika non egin den eta botoiaren arabera ekintzak hasten dira
void Animazioa();		//Jokatu sakatzen denean aniamzio labur bat egiten du
void PertsonaiaHasieratu();		//Jokatu sakatzean lehenengo aldiz pertsonaia kargatzera deitzen du
void JokalariaKargatu(char Irudia[], int i);		//Pertsonaiaren spriteak kargatzeko balio du, helbidea eta spritea zenbak irudi dituen hartzu eta gordetzen ditu
void EtsaiakHasieratu();
void EtsaiaKargatu(char Irudia[], int i);
void Ekintzak(int *i, ZENTZUA* begira, void* pixels, int pitch, Uint8 bpp, PANTAILAK* pantaila, int BizirikDaudenEtsaiak[], int BizirikKopurua);
void Amaitu(JOKOA *Jokoa, PANTAILAK *Pantaila);			//Jokoa amaitzen du
void MusikaJarri(char Fitxategia[]);
void EtsaiaKokatu(int znbk_etsaia, int x, int y, int BizirikDaudenEtsaiak[], int* BizirikKopurua);		//Etsaia nibel hasieran kokatu, etsaiaren zenbakia, x eta y posizioa emanez
Uint32 getpixel(void* pixels, int pitch, Uint8 bpp, int x, int y);
void KolisioakKonprobatu(void* pixels, int pitch, Uint8 bpp);
void AltueraZuzendu(void* pixels, int pitch, Uint8 bpp);
void GuztiakHil();
void EtsaienAdimena(int znbk_etsaia, void* pixels, int pitch, Uint8 bpp);// sigue lineas IA
#endif
