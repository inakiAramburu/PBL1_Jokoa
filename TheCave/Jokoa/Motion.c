#include "Basic.h"
#include "Image.h"
#include "Event.h"
#include "Motion.h"
#include "Sound.h"
#include <stdio.h>
#include <math.h>
#include <SDL_net.h>


extern HITBOX hitbox;

extern IMGPERTSONAIA spriteak[7];
extern int IrudiZnbk;

Uint32 time = 0;
Uint32 time2 = 0;
Uint32 time3 = 0;
Uint32 abiadura[8] = {150,60,80,80,10,100,80};

extern PERTSONAIA pertsonaia;
extern ETSAIA etsaia[ETSAI_KOPURUA];

extern PONG easteregg;
extern ROL Ordenagailua;
extern TCPsocket server, client;

void AltueraZuzendu(void* pixels, int pitch, Uint8 bpp)
{
	int i = 1;
	KOLOREAK tmp, tmp2;
	do
	{
		tmp = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 54, pertsonaia.DestSprite.y + 59 + i);
		tmp2 = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 75, pertsonaia.DestSprite.y + 59 + i);
		i++;
	} while (i < GRABITATEA && (tmp != BELTZA && tmp2 != BELTZA));
	if (i >= GRABITATEA)
	{
		return;
	}
	i--;
	pertsonaia.DestSprite.y += i;
}

void EtsaienAdimena(int znbk_etsaia, void* pixels, int pitch, Uint8 bpp)
{
	if ((getpixel(pixels, pitch, bpp, etsaia[znbk_etsaia].DestSprite.x + 32, etsaia[znbk_etsaia].DestSprite.y + 44) != BELTZA) || (getpixel(pixels, pitch, bpp, etsaia[znbk_etsaia].DestSprite.x, etsaia[znbk_etsaia].DestSprite.y + 44) != BELTZA))
	{
		etsaia[znbk_etsaia].abiadura *= -1;
	}
}

void Animazioa()
{
	//int i, j;

	SDL_Delay(500);
	IrudiZnbk = IrudiakKendu(1);
	pertsonaia.bizirik = FALSE;
	pertsonaia.sprite = KEA;
	pertsonaia.DestSprite.x = 10;
	pertsonaia.DestSprite.y = 555;
	pertsonaia.DestSprite.h = 60;
	pertsonaia.DestSprite.w = 128;
	pertsonaia.SrcSprite.h = 60;
	pertsonaia.SrcSprite.w = 128;
	pertsonaia.SrcSprite.y = 0;
	/*char Kea[128] = ".\\media\\sound\\Kea.wav";
	
		MusikaJarri(Kea);
		for (i = 0; i < spriteak[pertsonaia.sprite].kop; i++)
		{
			SDL_Delay(100);
			pertsonaia.SrcSprite.x = 128 * i;
			RenderPrestatu(AURRERA);
			Irudikatu();
		}
		pertsonaia.sprite = IDLE;
		for (j = 0; j < 2; j++)
		{
			for (i = 0; i < spriteak[pertsonaia.sprite].kop; i++)
			{
				pertsonaia.SrcSprite.x = 128 * i;
				RenderPrestatu(AURRERA);
				Irudikatu();
				SDL_Delay(150);
			}
		}
		pertsonaia.sprite = KORRIKA;
		for (j = 0; j < 12; j++)
		{
			for (i = 0; i < spriteak[pertsonaia.sprite].kop; i++)
			{
				pertsonaia.SrcSprite.x = 128 * i;
				pertsonaia.DestSprite.x += 9;
				RenderPrestatu(AURRERA);
				Irudikatu();
				SDL_Delay(80);
			}
		}
		pertsonaia.sprite = IDLE;
		RenderPrestatu(AURRERA);
		Irudikatu();
		SDL_Delay(300);
		IrudiZnbk = IrudiakKendu(0);
		pertsonaia.bizirik = FALSE;
		ImgKargatu(".\\media\\menu\\TheCaveW.bmp", 1000, 400, 140, 160);
		for (i = 0; i < 80; i++)
		{
			SDL_SetTextureAlphaMod(Irudiak[0].textura, 2 * i);
			RenderPrestatu(AURRERA);
			Irudikatu();
			SDL_Delay(100);
		}
		SDL_Delay(2000);*/
}

void Ekintzak(int* pAnimazioa, ZENTZUA* begira, void* pixels, int pitch, Uint8 bpp, PANTAILAK* pantaila, int BizirikDaudenEtsaiak[], int* BizirikKopurua)
{
	int abiadurax = 12;
	int abiaduray = 12;
	static int eAnimazioa;

	//	Debbug de pies
	if (f3)
	{
		printf("Pierna Izquierda: %d\n", hitbox.behekoa.ezker);
		printf("Izquierda x: %d  ", pertsonaia.DestSprite.x + 54);
		printf("y: %d \n\n", pertsonaia.DestSprite.y + 59);

		printf("Pierna derecha: %d\n", hitbox.behekoa.eskuin);
		printf("Derecha x: %d  ", pertsonaia.DestSprite.x + 75);
		printf("y: %d \n\n", pertsonaia.DestSprite.y);
	}
	KolisioakKonprobatu(pixels, pitch, bpp, BizirikDaudenEtsaiak, BizirikKopurua, *begira, pAnimazioa);

	if (hitbox.behekoa.eskuin == BELTZA || hitbox.behekoa.ezker == BELTZA)
	{
		if (pertsonaia.erortzen)
		{
			if (a || d)
			{
				pertsonaia.sprite = KORRIKA;
				*pAnimazioa = 0;
			}
			else
			{
				pertsonaia.sprite = IDLE;
				*pAnimazioa = 0;
			}
		}
		pertsonaia.erortzen = FALSE;
	}
	else if (hitbox.behekoa.eskuin == TXURIA && hitbox.behekoa.ezker == TXURIA)
	{
		if (!pertsonaia.salto)
		{
			pertsonaia.erortzen = TRUE;
			pertsonaia.sprite = ERORI;
			*pAnimazioa = 0;
		}
	}
	if (w)
	{
		if (hitbox.ezker.goikoa == HORIA)
		{
			*pantaila += 1;
			GuztiakHil();
			return;
		}
	}
	if (a)
	{
		*begira = ATZERA;
		if ((hitbox.ezker.behekoa != BERDEA && hitbox.ezker.erdikoa != BERDEA && hitbox.ezker.goikoa != BERDEA) && pertsonaia.DestSprite.x > -39 && pertsonaia.sprite != ERASO)
		{
			pertsonaia.DestSprite.x -= abiadurax;
		}
	}
	if (d)
	{
		*begira = AURRERA;
		if ((hitbox.eskuin.behekoa != BERDEA && hitbox.eskuin.erdikoa != BERDEA && hitbox.eskuin.goikoa != BERDEA) && pertsonaia.DestSprite.x < 1190 && pertsonaia.sprite != ERASO)
		{
			pertsonaia.DestSprite.x += abiadurax;
		}
	}
	if (!pertsonaia.erortzen && !pertsonaia.salto && !k && !espacio && !pertsonaia.erasotzen && !d && !a && pertsonaia.sprite != HIL)
	{
		if (pertsonaia.sprite != IDLE)
		{
			*pAnimazioa = 0;
		}
		pertsonaia.sprite = IDLE;

	}
	if (!pertsonaia.erortzen && !pertsonaia.salto && !k && espacio && pertsonaia.sprite != HIL)
	{
		pertsonaia.salto = TRUE;
		pertsonaia.sprite = SALTO;
		*pAnimazioa = 0;
	}
	if (!pertsonaia.erortzen && !pertsonaia.salto && k && !pertsonaia.erasotzen && !d && !a)
	{
		pertsonaia.erasotzen = TRUE;
		pertsonaia.sprite = ERASO;
		*pAnimazioa = 0;
	}
	if (pertsonaia.salto)
	{
		pertsonaia.DestSprite.y -= abiaduray;
		while (pertsonaia.DestSprite.y < 0)
		{
			pertsonaia.DestSprite.y++;
		}
	}
	if (pertsonaia.erortzen)
	{
		pertsonaia.DestSprite.y += GRABITATEA;
		AltueraZuzendu(pixels, pitch, bpp);
	}
	pertsonaia.SrcSprite.x = 128 * (*pAnimazioa);

	if (SDL_GetTicks() - time > abiadura[pertsonaia.sprite])
	{
		++* pAnimazioa;
		time = SDL_GetTicks();
	}

	if (*pAnimazioa >= spriteak[pertsonaia.sprite].kop)
	{
		if (pertsonaia.sprite == HIL)
		{
			PertsonaiaHil();
		}
		if (pertsonaia.salto)
		{
			pertsonaia.salto = FALSE;
			pertsonaia.erortzen = TRUE;
		}
		if (pertsonaia.erasotzen)
		{
			pertsonaia.erasotzen = FALSE;
			k = FALSE;

		}
		*pAnimazioa = 0;

	}
	for (int j = 0; j < *BizirikKopurua; j++)
	{
		if (etsaia[BizirikDaudenEtsaiak[j]].bizirik)
		{
			EtsaienAdimena(BizirikDaudenEtsaiak[j], pixels, pitch, bpp);
			etsaia[BizirikDaudenEtsaiak[j]].DestSprite.x += etsaia[BizirikDaudenEtsaiak[j]].abiadura;
			etsaia[BizirikDaudenEtsaiak[j]].SrcSprite.x = 32 * eAnimazioa;
		}
	}
	if (SDL_GetTicks() - time2 > 180)
	{
		eAnimazioa++;
		time2 = SDL_GetTicks();
	}
	if (eAnimazioa >= ETSAIA_SPRITE_KOPURUA)
	{
		eAnimazioa = 0;
	}
}

void EtsaiaKokatu(int znbk_etsaia, int x, int y, int BizirikDaudenEtsaiak[], int* BizirikKopurua)
{

	etsaia[znbk_etsaia].DestSprite.x = x;
	etsaia[znbk_etsaia].DestSprite.y = y;
	etsaia[znbk_etsaia].bizirik = TRUE;
	if (znbk_etsaia >= 0 && znbk_etsaia <= 4)
	{
		etsaia[znbk_etsaia].abiadura = ABIADURA_MAMUA;
	}
	else if (znbk_etsaia >= 5 && znbk_etsaia <= 9)
	{
		etsaia[znbk_etsaia].abiadura = ABIADURA_MUKITXUA;
	}
	BizirikDaudenEtsaiak[*BizirikKopurua] = znbk_etsaia;
	*BizirikKopurua += 1;
}

void PongExekutatu()
{
	int abiadura = 9;
	switch (Ordenagailua)
	{
		case ZERBITZARI:

			PongKolisioa();
			if (w && easteregg.Player1.y > 0)
			{
				easteregg.Player1.y -= abiadura;
			}
			else if (s && easteregg.Player1.y < 720 - easteregg.Player1.h)
			{
				easteregg.Player1.y += abiadura;
			}
			if (easteregg.pilota.y <= 0 || easteregg.pilota.y + 25 >= 720)
			{
				easteregg.abiaduray *= -1;
			}
			easteregg.pilota.x += easteregg.abiadurax * cos(easteregg.angelua * M_PI / 180);
			easteregg.pilota.y -= easteregg.abiaduray * sin(easteregg.angelua * M_PI / 180);

			int DatuakHost[4]={easteregg.Player1.x,easteregg.Player1.y,easteregg.pilota.x,easteregg.pilota.y};
			SDLNet_TCP_Send(client, DatuakHost, 4);

			int DatuakClient[2];
			SDLNet_TCP_Recv(client, DatuakClient, 2);
			easteregg.Player2.x = DatuakClient[0];
			easteregg.Player2.y = DatuakClient[1];

			break;
		case BEZEROA:
			if (gora && easteregg.Player2.y > 0)
			{
				easteregg.Player2.y -= abiadura;
			}
			else if (behera && easteregg.Player2.y < 720 - easteregg.Player2.h)
			{
				easteregg.Player2.y += abiadura;
			}
			int DatuakClient2[2] = { 1258, 90 };
			void* Datosbug = DatuakClient2;
			SDLNet_TCP_Send(client, Datosbug, 2);

			int DatuakHost2[2];
			void* Datosmuybug = DatuakHost2;
			SDLNet_TCP_Recv(client, Datosmuybug, 2);
			printf("%d %d", DatuakHost2[0], DatuakHost2[1]);
		/*	printf("%d", DatuakHost2[1]);
			printf("%d", DatuakHost2[2]);
			printf("%d", DatuakHost2[3]);
			easteregg.Player1.y = DatuakHost2[1];
			easteregg.pilota.x = DatuakHost2[2];
			easteregg.pilota.y = DatuakHost2[3];*/
			break;
	}
	
}
