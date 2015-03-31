#ifndef PIECE_H
#define PIECE_H

#include "case.h"
#include "commun.h"
#define NB_PION_DEPART 8


typedef enum{ ROI, DAME, FOU, CAVALIER, TOUR, PION }TypePiece;

typedef struct{
	IDCase idPosition;
	IDPiece idPiece;
	Dimension dimension;
	Couleur couleur;
	TypePiece type;
	SDL_Surface* imagePiece;
	IDCase* deplacementPossibles;
	Booleen active;
	Booleen pieceSelectionne;
	Booleen surbrillance;
}Piece;

Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece);
void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee);
void afficherPiece(Piece* p, SDL_Renderer* contexte);
void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte);
void initAllPiece(Piece* tabPiece[8][8]);

#endif