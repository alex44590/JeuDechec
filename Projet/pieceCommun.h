#ifndef HEADER_H
#define HEADER_H

/**
* \file pieceCommun.h
* \brief Structure Piece
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Définition de la structure pièce dans un fichier dédié
* La pièce est partagée par plusieurs fichiers d'en tête qui sont doublement liés
*
*/
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