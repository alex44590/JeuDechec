#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include "case.h"
#include "piece.h"
#include "commun.h"

#define LARGEUR_PIECE_DEFAUSSE 33
#define HAUTEUR_PIECE_DEFAUSSE 33
#define OFFSET_GAUCHE_PIECE_DEFAUSSE 17
#define OFFSET_HAUT_PIECE_DEFAUSSE 13
#define LARGEUR_ESPACE_PIECE_DEFAUSSE 0
#define HAUTEUR_ESPACE_PIECE_DEFAUSSE 2

typedef struct{
	Couleur couleur;
	Position position;
	Dimension dimension;
	SDL_Surface* imageDefausse;
	Piece* tabPiecesDefaussees[2][8];
}Defausse;

Defausse* creerDefausse(Couleur couleur);
void afficherDefausse(Defausse* d, SDL_Renderer* contexte);
void afficherPieceDefausse(Defausse* d, Piece* p, SDL_Renderer* contexte, int x, int y);
void afficherAllPiecesDefausse(Defausse* d, SDL_Renderer* contexte);
void mettrePieceDefausse(Defausse* d, Piece* p, SDL_Renderer* contexte);
Piece* sortirPieceDefausse(Defausse* dBlanc, Defausse* dNoir, IDPiece id);
#endif