#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include <SDL.h>

#define PANTAILA_ALTUERA 720
#define PANTAILA_ZABALERA 1280

int LeihoaHasi();
int AtzekoPlanoBerria(char AtzekoPlano[]);
int Argazkia_Sartu(char AtzekoPlanoa[], int Posx, int Posy);
void Sprite(char Argazkia[], char Atzekoplanoa[], int PosX, int PosY, int spritekopurua);
#endif
