#ifndef BOUTON_H
#define BOUTON_H

#include "commun.h"

typedef enum { JOUER, OPTIONS, REGLES, STATISTIQUES/*, APROPOS, QUITTER*/ }idBouton;

#define NB_BOUTON (STATISTIQUES+1)

typedef struct{
	idBouton cible;
	SDL_Surface* image;
	Position positionInit;
	Position positionActuelle;
	Dimension dimension;
	Booleen enfonce;
}Bouton;


Bouton* creerBouton(idBouton cible, char* nomImage);
void afficherBouton(Bouton* b, SDL_Renderer* contexte);

#endif