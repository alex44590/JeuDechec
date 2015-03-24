#ifndef PLATEAUDEJEU_H
#define PLATEAUDEJEU_H

#include "case.h"
#include "piece.h"
#include "commun.h"
#include "echiquier.h"
#include "defausse.h"

typedef struct{
	Position position;
	Dimension dimension;
	Echiquier* echiquier;
	Defausse* defausseBlanc;
	Defausse* defausseNoir;
	SDL_Surface* bordureG;
	SDL_Surface* bordureD;
	SDL_Surface* bordureH;
	SDL_Surface* bordureB;
}PlateauDeJeu;


void afficherBordures(SDL_Renderer* contexte, PlateauDeJeu* plateau);
PlateauDeJeu* creerPlateauDeJeu(Echiquier* echiquier, Defausse* defausseB, Defausse* defausseN);
void afficherPlateauDeJeu(SDL_Renderer* contexte, PlateauDeJeu* plateau);


#endif