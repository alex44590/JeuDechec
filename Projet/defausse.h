#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include "case.h"
#include "piece.h"
#include "commun.h"

typedef struct{
	Couleur couleur;
	Position position;
	Dimension dimension;
	SDL_Surface* imageDefausse;
	Piece* tabPiecesDefaussees[16];
}Defausse;

Defausse* creerDefausse(Couleur couleur);
void afficherDefausse(Defausse* d, SDL_Renderer* contexte);

#endif