#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include <time.h>
#include "commun.h"
#include "texte.h"

// initialisation d'un timer
Timer init_timer(){
	Timer t;
	t.chrono = 0;
	t.debut = SDL_GetTicks();
	t.temps_actuel = 0;
	return t;

	}
//mise à jour d'un timer
void update_timer(Timer t){
	t.temps_actuel = SDL_GetTicks();
	t.chrono = t.temps_actuel - t.debut; 

}

//retourne 1 quand le temps est dépassé

int chrono(SDL_Renderer* contexte){
	Timer chr = init_timer();
	int time_over = 0;
	char* buffer = malloc (sizeof (chr.chrono));
	SDL_Surface* ttfchrono;
	
	while (chr.chrono != TEMPS_COUP){
		update_timer(chr);
		sprintf(buffer,"Temps : ", chr.chrono/1000);
		ttfchrono=creerTexte(buffer,"calibri.ttf", 20, 240, 240, 240);
	    afficherTexte(ttfchrono, POS_X_CHRONO, POS_Y_CHRONO, contexte);
	}
	return time_over = 1;
}
