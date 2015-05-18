#ifndef BOUTON_H
#define BOUTON_H

#include "commun.h"

#define NB_BOUTON_MP 4 // Menu principal
#define NB_BOUTON_M2J 3 // Menu 2 joueurs
#define NB_BOUTON_MENT 3 // Menu Entrainement
#define NB_BOUTON_REGLES 2 //Fenetre règles

typedef enum { ENTRAINEMENT, DEUXJOUEURS, OPTION, REGLES, ACCUEIL, JOUER, PAUSE, REGLESUIVANTE, REGLEPRECEDENTE }idBouton;

typedef struct{
	idBouton idBouton;
	SDL_Surface* image;
	Position positionInit;
	Position positionActuelle;
	Dimension dimension;
	Booleen enfonce;
}Bouton;


Bouton* creerBouton(idBouton cible, char* nomImage);
void setPositionBouton(Bouton* b, int x, int y);
void setTailleBouton(Bouton* b, int largeur, int hauteur);
void afficherBouton(Bouton* b, SDL_Renderer* contexte);
void enfoncerBouton(Bouton* b);
void desenfoncerBouton(Bouton* b);

#endif