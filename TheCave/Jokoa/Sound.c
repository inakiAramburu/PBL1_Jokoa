#include "Basic.h"
#include "SDL_mixer.h"
#include "Sound.h"






void musica()
{

	Mix_Chunk* Sonidos[10];


	///iniciar audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) > 0) {
		printf("no se pudo cargar el asusbsistema audio  %s\n", SDL_GetError());
		exit(1);
	}
	/////////////////https://www.youtube.com/watch?v=yK0INWqpqSc///////////////////////

//cargar archivos
	Sonidos[0] = Mix_LoadWAV(".\\media\\sound\\querezeres.wav");
	if (Sonidos[0] == NULL) {
		printf("no se pudo cargar el sonido  %s\n", SDL_GetError());
		exit(1);
	}

	Sonidos[1] = Mix_LoadWAV(".\\media\\sound\\Kea.wav");
	if (Sonidos[1] == NULL) {
		printf("no se pudo cargar el sonido  %s\n", SDL_GetError());
		exit(1);
	}

	///////////////////////////////////////


	//iniciar canales
		//declaramos canales podemos usar asta 3 sonidos con esta fuuncion
	Mix_AllocateChannels(3);

	//esto es para iniciar audios el 1. numero es para elejir el canal. el 2. el sonido que quieres reproducir. 3. Las veces que quieres que se reproduzca. con -1 infinito y con 0 una vez
/////////////////	

//reproducir audio
	Mix_PlayChannel(1, Sonidos[0], -1);

	//esto se supone que es para cambiar el volumen del chunck 1. es la pista 2 el volumen
	//estaria bien poner unas teclas para subir bajar volumen y poner una variable donde esta el 1
	//Mix_Volume(sonido1, 1);

	//para de reproducir la pista 
	//Mix_Pause(1);

	//reanuda la pausa donde estaba antes
	//Mix_Resume(1);
	//Mix_PlayChannel(2, sonido2, 0);

}





void Musikaabiarazi()
{
	///	iniciar audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) > 0) {
		printf("no se pudo cargar el asusbsistema audio  %s\n", SDL_GetError());
		exit(1);
	}
	//iniciar canales
		//declaramos canales podemos usar asta 3 sonidos con esta fuuncion
	Mix_AllocateChannels(5);//0.Pong //1.Juego,MusikaBoss //2.IrabaziGaldu //3.Efectuak //4. Musica boos 
}


void MusikaJOKUA(int abeztia )
{

	if (Soinuak[abeztia]== NULL)
	{
		printf("no se pudo cargar el sonido %s\n", SDL_GetError());
		exit(1);
	}
	Mix_PlayChannel(1, Soinuak[abeztia], -1);

}

void IrabaziGaldu(int zenbakia)
{

	if (Soinuak[zenbakia] == NULL)
	{
		printf("no se pudo cargar el sonido %s\n", SDL_GetError());
		exit(1);
	}
	Mix_PlayChannel(2, Soinuak[zenbakia], 0);

}

void Efektuak(int zenbakia) 
{
		

	//cargar archivos
	

	if (Soinuak[zenbakia] == NULL)
	{
		printf("no se pudo cargar el sonido %s\n", SDL_GetError());
		exit(1);
	}
	Mix_PlayChannel(3, Soinuak[zenbakia], 0);
}








void musica_Pong(int numerodesonido)
{

	

	

//cargar archivos
	if (Soinuak[numerodesonido] == NULL) {
		printf("no se pudo cargar el sonido  %s\n", SDL_GetError());
		exit(1);
	}


	///////////////////////////////////////

	

	//esto es para iniciar audios el 1. numero es para elejir el canal. el 2. el sonido que quieres reproducir. 3. Las veces que quieres que se reproduzca. con -1 infinito y con 0 una vez
/////////////////	

//reproducir audio
	Mix_PlayChannel(0, Soinuak[numerodesonido], 0);


	//esto se supone que es para cambiar el volumen del chunck 1. es la pista 2 el volumen
	//estaria bien poner unas teclas para subir bajar volumen y poner una variable donde esta el 1
	//Mix_Volume(sonido1, 1);

	//para de reproducir la pista 
	//Mix_Pause(1);

	//reanuda la pausa donde estaba antes
	//Mix_Resume(1);
	//Mix_PlayChannel(2, sonido2, 0);

}