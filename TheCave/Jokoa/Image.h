#ifndef IMAGE_H
#define IMAGE_H

#include "Motion.h"

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

#define BOSS_PANTAILA ".\\media\\levels\\NivelBoss.bmp"
#define BOSS_MASKARA ".\\media\\levels\\maskarak\\NivelBossM.bmp"
typedef struct S_IMG		//Argazkiak eta pantailan irudikatzeko behar dutren datu guztiak
{
	SDL_Texture* textura;
	SDL_Rect Dimentsioak;
}IMG;

typedef struct S_IMGPERTSONAIA		//Pertsonaiaren irudiak banaturik, beti kargatuta egongo direlako Jokatu sakatzen denetik
{
	SDL_Texture* textura;
	int kop;
}IMGPERTSONAIA;


int IrudiakKendu(int ZnbtUtzi);		//Irudien texturak ezabatzen ditu azkenetik hasten, nahi bada atzeko planoa ezabatu gabe utz daiteke, 1 parametroa pasatzen. Zenbat argazki geratu diren pasatzen du
void KargatuIrudiak(PANTAILAK Pantaila, int BizirikDaudenEtsaiak[], int* BizirikKopurua); //Pantailaren arabera argazki batzuk kargatzera deituko ditu, baina lehenengo garkatuta zeuden guztiak ezabatzen ditu
void ImgKargatu(char src[], int zabalera, int altuera, int x, int y);		//Argazki bat ordenagailutik igotzen du, eta beharrezkoak diren datuak emango di (zabalera, altuera, non kokatu...)
void KargatuMapa(char mapa[], void** pixels, int* pitch, Uint8* bpp);
void RenderPrestatu(ZENTZUA begira, int BizirikDaudenEtsaiak[], int BizirikKopurua);		//Texturak renderizatzeko modu orokor batean, ere pertsonaia renderizatuko du "BIZIRIK" badago
void RenderMenu();		//MENUA pantailarako animazioak egiteko renderizatzen ditu testuaren argazkiak, eta saguaren arabera bata edo bestea erakusten du
void Irudikatu();		//Pantailan renderra erakusten du
void JokalariaKargatu(char Irudia[], int i);		//Pertsonaiaren spriteak kargatzeko balio du, helbidea eta spritea zenbak irudi dituen hartzu eta gordetzen ditu
void EtsaiaKargatu(char Irudia[], int i);
Uint32 getpixel(void* pixels, int pitch, Uint8 bpp, int x, int y);


#endif