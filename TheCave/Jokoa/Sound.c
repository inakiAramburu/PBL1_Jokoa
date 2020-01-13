#include "Basic.h"
#include "SDL_mixer.h"
void MusikaJarri(char Fitxategia[])
{
	//explicacion
	//https://gigi.nullneuron.net/gigilabs/playing-a-wav-file-using-sdl2/

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

}

void musica()
{

	Mix_Chunk* sonido1;
	Mix_Chunk* sonido2;


	///iniciar audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096) >0) {
		printf("no se pudo cargar el asusbsistema audio  %s\n", SDL_GetError());
		exit(1);
	}
	/////////////////https://www.youtube.com/watch?v=yK0INWqpqSc///////////////////////

//cargar archivos
	sonido1 = Mix_LoadWAV(".\\media\\sound\\querezeres.wav");
	if (sonido1 == NULL) {
		printf("no se pudo cargar el sonido  %s\n", SDL_GetError());
		exit(1);
	}

	sonido2 = Mix_LoadWAV(".\\media\\sound\\Kea.wav");
	if (sonido2 == NULL) {
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
	Mix_PlayChannel(1, sonido1, -1);

	//esto se supone que es para cambiar el volumen del chunck 1. es la pista 2 el volumen
	//estaria bien poner unas teclas para subir bajar volumen y poner una variable donde esta el 1
	//Mix_Volume(sonido1, 1);

	//para de reproducir la pista 
	//Mix_Pause(1);

	//reanuda la pausa donde estaba antes
	//Mix_Resume(1);
	//Mix_PlayChannel(2, sonido2, 0);

}