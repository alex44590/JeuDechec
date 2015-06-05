#ifndef TIMER_H
#define TIMER_H

#include "commun.h"
#include "texte.h"



#define CHRONO_TEXTE_MAX 20

#define ZONE_CHRONO_X 1020
#define ZONE_CHRONO_Y 280
#define ZONE_CHRONO_LARGEUR 170
#define ZONE_CHRONO_HAUTEUR 90

#define POS_X_CHRONO (ZONE_CHRONO_X+57)
#define POS_Y_CHRONO ZONE_CHRONO_Y+60

typedef struct{
	uint32_t heure;
	uint32_t min;
	uint32_t sec;
}Chrono;


//Tous les temps sont en ms 
typedef struct{
	uint32_t debut;
	uint32_t temps_actuel;
	uint32_t reserveTempsInitiale;
	uint32_t chrono;
	Chrono chronoLisible;
	SDL_Surface* ttfchrono;
	char bufferTexte[CHRONO_TEXTE_MAX];
	Booleen reaffichageNecessaire;
}Timer;



Timer* init_timer();


void update_timer(Timer* t, Booleen pause);


void afficherChrono(Timer* t, SDL_Renderer* contexte);

#endif