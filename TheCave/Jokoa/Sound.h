#ifndef SOUND_H
#define SOUND_H

#define MUSIKA_MENU ".\\media\\sound\\MusikaGeneral\\MusikaMenua.wav"


#define KEA_EFEKTUA  ".\\media\\sound\\effect\\Pertsonaia\\Kea.wav"
#define EZPADA_EFEKTUA ".\\media\\sound\\effect\\Pertsonaia\\Ezpata.wav"

#define MusikaBOSS ".\\media\\sound\\boss\\MusikaBoss.wav"

#define IRABAZI_EFEKTUA ".\\media\\sound\\IrabaziGaldu\\Irabazi.wav"
#define GALDU_GALDU ".\\media\\sound\\IrabaziGaldu\\GameOver.wav"



void Musikaabiarazi();
void MusikaJarri(char Fitxategia[]);
void MusikaJOKUA();
void Efektuak(int zenbakia);

void musica_Pong(int numerodesonido);

void IrabaziGaldu(int zenbakia);

#endif