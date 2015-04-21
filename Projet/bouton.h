#ifndef BOUTON_H
#define BOUTON_H

#include "commun.h"

typedef enum { ENTRAINEMENT, DEUXJOUEURS, OPTION, APROPOS/*, QUITTER*/ }idBouton;

#define NB_BOUTON_MP (APROPOS+1) // Menu principal
#define NB_BOUTON_M2J 1 // Menu 2 joueurs

typedef struct{
	idBouton idBouton;
	SDL_Surface* image;
	Position positionInit;
	Position positionActuelle;
	Dimension dimension;
	Booleen enfonce;
}Bouton;


Bouton* creerBouton(idBouton cible, char* nomImage);
void afficherBouton(Bouton* b, SDL_Renderer* contexte);
void enfoncerBouton(Bouton* b);
void desenfoncerBouton(Bouton* b);

#endif