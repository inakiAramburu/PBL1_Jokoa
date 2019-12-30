#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280
//
int LeihoaHasi();
int Argazkia_Sartu(char Irudia[], int Posx, int Posy, int EPosx, int EPosy);
int AtzekoPlanoBerria(char AtzekoPlanoa[]);
void MusikaJarri(char Fitxategia[]);

void teklatua();
#endif
