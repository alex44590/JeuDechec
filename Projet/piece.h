#ifndef PIECE_H
#define PIECE_H

#include "case.h"
#include "commun.h"
#define NB_PION_DEPART 8


typedef enum{ ROI, DAME, FOU, CAVALIER, TOUR, PION }TypePiece;

typedef struct {
	Lettre colonne;
	Lettre ligne;
}Id;

typedef struct {
	char type;
	char couleur;
	int numero;
}IdPiece;

typedef struct{
	Id idPosition;
	IdPiece idPiece;
	Dimension dimension;
	Couleur couleur;
	TypePiece type;
	SDL_Surface* imagePiece;
	Id* deplacementPossibles;
	Booleen active;
	Booleen pieceSelectionne;
	Booleen surbrillance;
}Piece;

Piece* newPiece(Id position, int numero, TypePiece t, Couleur c, char* cheminImage);
void initAllPiece(Piece* tabPiece[32]);
void afficherPiece(Piece* p, SDL_Renderer* contexte);
void afficherAllPiece(Piece* tabPiece[32], SDL_Renderer* contexte);

#endif