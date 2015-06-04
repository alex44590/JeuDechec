#include "timer.h"

// initialisation d'un timer
Timer* init_timer(){
	Timer* t = malloc(sizeof(Timer));
	t->debut = SDL_GetTicks();
	t->temps_actuel = SDL_GetTicks();
	t->reserveTempsInitiale = 2700000; //45min
	t->chrono = 2700000;
	t->chronoLisible.heure = (int)(t->reserveTempsInitiale / 3600000);
	t->chronoLisible.min = (int)(t->reserveTempsInitiale / 60000.0 - t->chronoLisible.heure * 60);
	t->chronoLisible.sec = (int)(t->reserveTempsInitiale / 1000 - t->chronoLisible.heure * 3600 - t->chronoLisible.min * 60);
	return t;
}


/*//Mise à jour d'un timer : Met à jour le temps actuel
//Recalcule la valeur de chrono toutes les secondes et met le booleen du timer reaffichageNecessaire à 1 si la mise à jour de l'affichage est nécessaire
void update_timer(Timer* t){
t->temps_actuel = SDL_GetTicks();
if ((Uint32)((t->temps_actuel - t->debut) / 1000) != (Uint32)(t->chrono / 1000)){
t->chrono = t->temps_actuel - t->debut;
t->reaffichageNecessaire = TRUE;
logPrint(AVERTISSEMENT, "Reaffichage timer nécessaire");
}
}*/

//Mise à jour d'un timer : Met à jour le temps actuel
//Recalcule la valeur de chrono toutes les secondes et met le booleen du timer reaffichageNecessaire à 1 si la mise à jour de l'affichage est nécessaire
void update_timer(Timer* t, Booleen pause){
	t->temps_actuel = SDL_GetTicks();
	if ((Uint32)((t->temps_actuel - t->debut) / 1000) != (Uint32)(t->chrono / 1000)){
		if (pause){
			t->debut = t->chrono - t->reserveTempsInitiale + t->temps_actuel;
			t->reaffichageNecessaire = TRUE;
		}
		else{
			t->chrono = t->reserveTempsInitiale - (t->temps_actuel - t->debut);
			t->reaffichageNecessaire = TRUE;
			t->chronoLisible.heure = (int)(t->chrono / 3600000);
			t->chronoLisible.min = (int)(t->chrono / 60000.0 - t->chronoLisible.heure * 60);
			t->chronoLisible.sec = (int)(t->chrono / 1000 - t->chronoLisible.heure * 3600 - t->chronoLisible.min * 60);
		}
	}
}


//Affiche le chrono dans le menu de droite si le raffraichissement est nécessaire
//Remet à Faux le booléen du timer reaffichageNecessaire si tel est le cas...
void afficherChrono(Timer* t, SDL_Renderer* contexte){
	sprintf(t->bufferTexte, "%2.2d:%2.2d", t->chronoLisible.min, t->chronoLisible.sec);
	t->ttfchrono = creerTexte(t->bufferTexte, "calibri.ttf", 20, 240, 240, 240);
	afficherTexte(t->ttfchrono, POS_X_CHRONO, POS_Y_CHRONO, contexte);
	t->reaffichageNecessaire = FALSE;
	//logPrint(INFO, t->bufferTexte);
}
