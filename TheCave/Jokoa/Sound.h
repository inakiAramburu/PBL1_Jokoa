#ifndef SOUND_H
#define SOUND_H
#include "SDL_mixer.h"





Mix_Chunk* Soinuak[10];





void Musikaabiarazi();
void MusikaJarri(char Fitxategia[]);
void MusikaJOKUA();
void Efektuak(int zenbakia);

void musica_Pong(int numerodesonido);

void IrabaziGaldu(int zenbakia);

#endif