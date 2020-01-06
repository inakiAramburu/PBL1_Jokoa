#include "Funtzioak.h"
#include <SDL.h>

SDL_Renderer* render;
SDL_Window* leihoa;

typedef struct S_IMG		//Argazkiak eta pantailan irudikatzeko behar dutren datu guztiak
{
	SDL_Texture* textura;
	SDL_Rect Dimentsioak;
}IMG;

IMG Irudiak[50];		//Irudiak, dagozkien datuekin
int IrudiZnbk;

typedef struct S_IMGPERTSONAIA		//Pertsonaiaren irudiak banaturik, beti kargatuta egongo direlako Jokatu sakatzen denetik
{
	SDL_Texture* textura;
	int kop;
}IMGPERTSONAIA;

IMGPERTSONAIA spriteak[6];		

typedef struct S_PERTSONAIA		//Pertsonaiaren datuak
{
	SDL_Rect SrcSprite, DestSprite;
	SPRITE sprite;
	EGOERA egoera;
}PERTSONAIA;

PERTSONAIA pertsonaia;

TEKLAK a = SAKATUGABE;
TEKLAK d = SAKATUGABE;
TEKLAK espacio = SAKATUGABE;
TEKLAK k = SAKATUGABE;

int LeihoaEtaRenderHasi()
{
            // Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da SDL hasieratu: %s", SDL_GetError());
		return 1;
	}
	// Create an application window with the following settings:
	leihoa = SDL_CreateWindow(
		"The Cave",                  			// Izenburua
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		SDL_WINDOWPOS_CENTERED,           // Leihoa erdian jarri
		PANTAILA_ZABALERA,                // Sortzeko lehioaren zabalera
		PANTAILA_ALTUERA,                 // Sortzeko leihoaren altuera
		SDL_WINDOW_OPENGL                 // Erabilitako teknologia grafikoa
	);

	if (leihoa == NULL) { 		// Leihoa sortu dela konprobatzen du

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin izan da leihoa sortu: %s\n", SDL_GetError());		//Errorea
		return 1;
	}

	SDL_Surface* ikonoa = SDL_LoadBMP(".\\media\\Ikonoa.bmp");
	SDL_SetWindowIcon(leihoa, ikonoa);
	SDL_FreeSurface(ikonoa);

	render = SDL_CreateRenderer(leihoa, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);		//Renderizatua hasi

	return 0;
}

int IrudiakKendu(int ZnbtUtzi)
{
	int i = IrudiZnbk - 1;

	while (i >= ZnbtUtzi)
	{
		SDL_DestroyTexture(Irudiak[i].textura);
		i--;
	}
	return i + 1;
}

void KargatuIrudiak(PANTAILAK Pantaila)
{
	IrudiZnbk = IrudiakKendu(0);
	switch (Pantaila)		
	{
		/*Jokolariak pantaila berri batera pasatzean behar izango diren irudi guztiak kargatzen dira. Horrela ez irudiak ez dira kargatuko
		jokalaria puntu horretara heltzen ez bada*/

		case MENUA:
			ImgKargatu(".\\media\\fondos\\Menu.bmp", NULL, NULL, 0, 0);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\pergamino.bmp", 395, 560, 442, 80);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Jolastu.bmp", 250, 100, 515, 175);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Jolastu.bmp", 300, 120, 500, 165);		//Aniamzioa egiteko
			ImgKargatu(".\\media\\menu\\Kontrolak.bmp", 250, 100, 510, 300);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Kontrolak.bmp", 300, 120, 495, 290);		//Animazioa egiteko
			ImgKargatu(".\\media\\menu\\Kredituak.bmp", 250, 100, 512, 425);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\Kredituak.bmp", 300, 120, 497, 415);		//Animazioa egiteko
			pertsonaia.egoera = HILDA;
			break;
		case KREDITUAK:
			ImgKargatu(".\\media\\fondos\\Menu.bmp", NULL, NULL, 0, 0);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\KredituakP.bmp", 950, 600, 208, 15);		//Zabalera, altuera, x, y
			break;
		case KONTROLAK:
			ImgKargatu(".\\media\\fondos\\Menu.bmp", NULL, NULL, 0, 0);		//Zabalera, altuera, x, y
			ImgKargatu(".\\media\\menu\\KontrolakP.bmp", 950, 600, 208, 15);		//Zabalera, altuera, x, y
			break;
		case LEHEN:
			ImgKargatu(".\\media\\fondos\\Nivel2.bmp", NULL, NULL, 0, 0);
			pertsonaia.DestSprite.x = 10;
			pertsonaia.DestSprite.y = 450;
			break;
	}
}

void ImgKargatu(char src[], int zabalera, int altuera, int x, int y)
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	
	surface = SDL_LoadBMP(src);
	if (!surface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}

	SDL_FreeSurface(surface);
	Irudiak[IrudiZnbk].textura = texture;
	Irudiak[IrudiZnbk].Dimentsioak.h = altuera;
	Irudiak[IrudiZnbk].Dimentsioak.w = zabalera;
	Irudiak[IrudiZnbk].Dimentsioak.x = x;
	Irudiak[IrudiZnbk].Dimentsioak.y = y;
	IrudiZnbk++;
}

void RenderPrestatu(ZENTZUA begira)
{
	int i;

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	
	for (i = 0; i < IrudiZnbk; i++)
	{
		if (Irudiak[i].Dimentsioak.h == NULL)
		{
			SDL_RenderCopy(render, Irudiak[i].textura, NULL, NULL);
		}
		else
		{
			SDL_RenderCopy(render, Irudiak[i].textura, NULL, &Irudiak[i].Dimentsioak);
		}
	}
	if (pertsonaia.egoera == BIZIRIK)
	{
		if (begira == ATZERA)
		{
			SDL_RendererFlip flip = SDL_FLIP_VERTICAL;

			SDL_RenderCopyEx(render, spriteak[pertsonaia.sprite].textura, &pertsonaia.SrcSprite, &pertsonaia.DestSprite, 180, NULL, flip);
		}
		else
		{
			SDL_RenderCopy(render, spriteak[pertsonaia.sprite].textura, &pertsonaia.SrcSprite, &pertsonaia.DestSprite);
		}
	}
	
}

void RenderMenu()
{
	int i = 0, x, y;

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	SDL_GetMouseState(&x, &y);

	SDL_RenderCopy(render, Irudiak[0].textura, NULL, NULL);
	SDL_RenderCopy(render, Irudiak[1].textura, NULL, &Irudiak[1].Dimentsioak);
	if ((x > 515 && y > 175) && (x < 765 && y < 275))
	{
		SDL_RenderCopy(render, Irudiak[3].textura, NULL, &Irudiak[3].Dimentsioak);
	}
	else
	{
		SDL_RenderCopy(render, Irudiak[2].textura, NULL, &Irudiak[2].Dimentsioak);
	}
	if ((x > 510 && y > 300) && (x < 760 && y < 400))
	{
		SDL_RenderCopy(render, Irudiak[5].textura, NULL, &Irudiak[5].Dimentsioak);
	}
	else
	{
		SDL_RenderCopy(render, Irudiak[4].textura, NULL, &Irudiak[4].Dimentsioak);
	}
	if ((x > 512 && y > 425) && (x < 762 && y < 525))
	{
		SDL_RenderCopy(render, Irudiak[7].textura, NULL, &Irudiak[7].Dimentsioak);
	}
	else
	{
		SDL_RenderCopy(render, Irudiak[6].textura, NULL, &Irudiak[6].Dimentsioak);
	}
	
}

void Irudikatu()
{
	SDL_RenderPresent(render);
}

void Amaitu(JOKOA *Jokoa, PANTAILAK *Pantaila)
{
	SDL_DestroyWindow(leihoa);
	SDL_DestroyRenderer(render);
	*Jokoa = EZJOKATZEN;
	*Pantaila = ATERA;
	return;
}

void EbentuakKonprobatu(JOKOA *Jokoa, PANTAILAK *Pantaila, int* i, ZENTZUA *begira)
{
	SAGUA klika;
	SDL_Event ebentua;
	while (SDL_PollEvent(&ebentua))
	{
		switch (ebentua.type)
		{
			case SDL_QUIT:
				Amaitu(&*Jokoa, &*Pantaila);
				break;
			case SDL_MOUSEBUTTONUP:
				ZeinKlikatuDa(ebentua.button, &klika);
				KonprobatuKlika(&*Pantaila, klika);
				break;
			case SDL_KEYDOWN:
				switch (ebentua.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
				{
				case SDL_SCANCODE_D:
					a = SAKATUGABE;
					if (!d)
					{
						*begira = AURRERA;
						pertsonaia.sprite = KORRIKA;
						*i = 0;
					}
					d = SAKATUTA;
					break;
				case SDL_SCANCODE_A:
					d = SAKATUGABE;
					if (!a)
					{
						*begira = ATZERA;
						pertsonaia.sprite = KORRIKA;
						*i = 0;
					}
					a = SAKATUTA;
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SAKATUTA;
					break;
				case SDL_SCANCODE_K:
					k = SAKATUTA;
					break;
				case SDL_SCANCODE_ESCAPE:
					Amaitu(&*Jokoa, &*Pantaila);
					break;
				}
				break;
			case SDL_KEYUP:
				switch (ebentua.key.keysym.scancode)
				{
				case SDL_SCANCODE_D:
					d = SAKATUGABE;
					if (!a)
					{
						pertsonaia.sprite = IDLE;
						*i = 0;
					}
					break;
				case SDL_SCANCODE_A:
					a = SAKATUGABE;
					if (!d)
					{
						pertsonaia.sprite = IDLE;
						*i = 0;
					}
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SAKATUGABE;
					break;
				case SDL_SCANCODE_K:
					k = SAKATUGABE;
					break;
				}
				break;
		}

		}
	}

void Ekintzak(int *i)
{
	if (a)
	{	
		pertsonaia.DestSprite.x -= 8;
	}
	if (d) 
	{
		pertsonaia.DestSprite.x += 8;
	}
	if (espacio) 
	{
		
	}
	pertsonaia.SrcSprite.x = 128 * (*i);
	*i += 1;
	if (*i >= spriteak[pertsonaia.sprite].kop)
	{
		*i = 0;
	}
}


void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA *klika)
{
	switch (ebentua.button)
	{
		case SDL_BUTTON_LEFT:
			*klika = EZKER;
			break;

		case SDL_BUTTON_RIGHT:
			*klika = ESKUIN;
			break;

		case SDL_BUTTON_MIDDLE:
			*klika = ERDIA;
			break;
	}
}

void KonprobatuKlika(PANTAILAK *Pantaila, SAGUA klika)
{
	int x, y;
	switch (*Pantaila)
	{
		case MENUA:
			if (klika == EZKER)
			{
				SDL_GetMouseState(&x, &y);
				if ((x > 515 && y > 175) && (x < 765 && y < 275))
				{
					IrudiZnbk = 1;
					RenderPrestatu(AURRERA);
					Irudikatu();
					KargatuPertsonaia();
					Animazioa();
					*Pantaila = LEHEN;
				}
				else if ((x > 510 && y > 300) && (x < 760 && y < 400))
				{
					*Pantaila = KONTROLAK;
				}
				else if ((x > 512 && y > 425) && (x < 762 && y < 525))
				{
					*Pantaila = KREDITUAK;
				}
			}
			break;

		case KREDITUAK:
			if (klika == EZKER)
			{
				SDL_GetMouseState(&x, &y);
				if ((x > 1055 && y > 89) && (x < 1120 && y < 151))
				{
					*Pantaila = MENUA;
				}
			}
			break;

		case KONTROLAK:
			if (klika == EZKER)
			{
				SDL_GetMouseState(&x, &y);
				if ((x > 1055 && y > 89) && (x < 1120 && y < 151))
				{
					*Pantaila = MENUA;
				}
			}
			break;
	}
}

void KargatuPertsonaia()
{
	
	JokalariaKargatu(".\\media\\player\\Idle.bmp", 0);
	spriteak[0].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Run.bmp", 1);
	spriteak[1].kop = 10;
	
	JokalariaKargatu(".\\media\\player\\Salto.bmp", 2);
	spriteak[2].kop = 14;
	
	JokalariaKargatu(".\\media\\player\\Attack.bmp", 3);
	spriteak[3].kop = 8;
	
	JokalariaKargatu(".\\media\\player\\Dead.bmp", 4);
	spriteak[4].kop = 6;
	
	JokalariaKargatu(".\\media\\player\\Humo.bmp", 5);
	spriteak[5].kop = 4;
}

void JokalariaKargatu(char Irudia[], int i)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface = SDL_LoadBMP(Irudia);

	if (!surface)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da argazkitik azalera sortu: %s\n", SDL_GetError());
		return;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ezin da azaleratik textura sortu: %s\n", SDL_GetError());
		return;
	}
	SDL_FreeSurface(surface);
	spriteak[i].textura = texture;
}

void MusikaJarri(char Fitxategia[])
{
	// explicacion
	//https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/

	//inicia la parte de audio
	SDL_Init(SDL_INIT_AUDIO);

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	/*  fichategia cargatu */
	if (SDL_LoadWAV(Fitxategia, &wavSpec, &wavBuffer, &wavLength) == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "no encuentra test.wav: %s\n", SDL_GetError());
		exit(-1);
	}
	// abrir dependencias de audio

	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	// iniciar el sonido

	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);




	// dena itxi

	//SDL_CloseAudioDevice(deviceId);
	//SDL_FreeWAV(wavBuffer);
	//SDL_Quit();
}

void Animazioa()
{
	int i, j;

	SDL_Delay(500);
	IrudiZnbk = IrudiakKendu(1);
	pertsonaia.egoera = BIZIRIK;
	pertsonaia.sprite = KEA;
	pertsonaia.DestSprite.x = 10;
	pertsonaia.DestSprite.y = 555;
	pertsonaia.DestSprite.h = 60;
	pertsonaia.DestSprite.w = 128;
	pertsonaia.SrcSprite.h = 60;
	pertsonaia.SrcSprite.w = 128;
	pertsonaia.SrcSprite.y = 0;
	char Kea[128] = ".\\media\\sound\\Kea.wav";
	/*MusikaJarri(Kea);
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
	for (j = 0; j < 20; j++)
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

	IrudiZnbk = IrudiakKendu(0);
	pertsonaia.egoera = HILDA;
	ImgKargatu(".\\media\\menu\\pergamino.bmp", 395, 560, 442, 80);
	for (i = 0; i < 100; i++)
	{
		SDL_SetTextureAlphaMod(Irudiak[0].textura, 2 * i);
		RenderPrestatu(AURRERA);
		Irudikatu();
		SDL_Delay(100);
	}*/
	pertsonaia.egoera = BIZIRIK;
}

Uint32 getpixel(void* pixels, int pitch, Uint32 bpp, Uint32 x, Uint32 y)
{


	Uint8* p = (Uint8*)pixels + (y * (Uint32)(pitch)+x) * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;
	}
}

void* CargarMascara(char* nombre, int* pitch, Uint32* bpp) {

	SDL_Surface* surface = SDL_LoadBMP(nombre);
	void* pixels = surface->pixels;

	*pitch = surface->pitch;
	*bpp = surface->format->BytesPerPixel;

	return pixels;
}
