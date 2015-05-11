#ifndef ENTRAINEMENT_H
#define ENTRAINEMENT_H

#include "plateauDeJeu.h"


#define HAUTEUR_RESERVE 65
#define LARGEUR_RESERVE 245
#define TAILLE_RESERVE (Dimension){HAUTEUR_RESERVE, LARGEUR_RESERVE}
#define POSITION_RESERVE_NOIRE (Position){(LARGEUR_MENU-LARGEUR_RESERVE)/2, 335}
#define POSITION_RESERVE_BLANCHE (Position){(LARGEUR_MENU-LARGEUR_RESERVE)/2, 425}


#define LARGEUR_PIECE_RESERVE 33
#define HAUTEUR_PIECE_RESERVE 33
#define OFFSET_GAUCHE_PIECE_RESERVE 17
#define OFFSET_HAUT_PIECE_RESERVE 13
#define LARGEUR_ESPACE_PIECE_RESERVE 0
#define HAUTEUR_ESPACE_PIECE_RESERVE 2


typedef struct{
	Couleur couleur;
	Position position;
	Dimension dimension;
	SDL_Surface* imageReserve;
	Piece* tabPiecesReserve[2][8];
}Reserve;


Reserve* creerReserve(Couleur couleur);
void afficherReserve(Reserve* r, SDL_Renderer* contexte);

#endif