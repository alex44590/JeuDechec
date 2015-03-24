#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include "case.h"
#include "piece.h"
#include "commun.h"

typedef struct{
	Couleur couleur;
	Position position;
	Dimension dimension;
	Piece* tabPiecesDefaussees[16];
}Defausse;

Defausse* creerDefausse(Couleur couleur);

#endif