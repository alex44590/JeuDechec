#ifndef HEADER_H
#define HEADER_H

//#include "piece.h"
//#include "deplacement.h"
#include "commun.h"

typedef enum{ ROI, DAME, FOU, CAVALIER, TOUR, PION }TypePiece;

typedef struct{
	IDCase idPosition;
	IDPiece idPiece;
	Dimension dimension;
	Couleur couleur;
	TypePiece type;
	SDL_Surface* imagePiece;
	SDL_Surface* imagePieceNormale;
	SDL_Surface* imagePieceSurbrillance;
	SDL_Surface* imagePieceDefausse;
	SDL_Surface* imagePieceReserve;
	SDL_Surface* imagePieceReserveNormale;
	SDL_Surface* imagePieceReserveSurbrillance;
	IDCase* deplacementPossibles;
	Booleen active;
	Booleen pieceSelectionne;
	Booleen surbrillance;
	Booleen surbrillanceReserve;
	int nbDeplacement;
}Piece;

#endif