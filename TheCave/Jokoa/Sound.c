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
	Mix_Chunk* effect1;
	Mix_Music* music;
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	music=Mix_LoadMUS(".\\media\\soud\\mus_battle2.wav");
	effect1 = Mix_LoadWAV(".\\media\\soud\\videoplayback.wav");

	Mix_FreeChunk(effect1);
	Mix_FreeMusic(music);
	Mix_CloseAudio;

	Mix_PlayingMusic(music, -1);
}
