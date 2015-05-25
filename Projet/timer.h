#ifndef TIMER_H
#define TIMER_H

#include "commun.h"
#include "texte.h"
#include <time.h>



#define CHRONO_TEXTE_MAX 20

#define TEMPS_COUP 20000 // 20s
#define POS_X_CHRONO (POSITION_MENU_DROITE.x+LARGEUR_MENU_DROITE/4)
#define POS_Y_CHRONO 320



//Tous les temps sont en ms 
typedef struct{
	uint32_t debut;
	uint32_t temps_actuel;
	uint32_t chrono;
	SDL_Surface* ttfchrono;
	char bufferTexte[CHRONO_TEXTE_MAX];
	Booleen reaffichageNecessaire;
}Timer;

Timer* init_timer();
void update_timer(Timer* t);
void afficherChrono(Timer* t, SDL_Renderer* contexte);
void remettreAZeroChrono(Timer* t);
void mettreEnPauseChrono(Timer* t);

int chrono();
#endif