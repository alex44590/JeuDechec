#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include <time.h>

// initialisation d'un timer
Timer init_timer(Timer t){
	t.chrono = 0;
	t.debut = SDL_GetTicks();
	t.temps_actuel = SDL_GetTicks();
	}
//mise à jour d'un timer
Timer update_timer(Timer t){
	t.temps_actuel = SDL_GetTicks();
	t.chrono = t.temps_actuel - t.debut; 

}