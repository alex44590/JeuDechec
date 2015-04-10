#ifndef PIECE_H
#define PIECE_H

#include "case.h"
#include "commun.h"
#include "listeDeplacement.h"
#define NB_PION_DEPART 8


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
	IDCase* deplacementPossibles;
	Booleen active;
	Booleen pieceSelectionne;
	Booleen surbrillance;
	int nbDeplacement;
}Piece;

Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece);
void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee, ListDeplacement* l);
void afficherPiece(Piece* p, SDL_Renderer* contexte);
void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte);
void initAllPiece(Piece* tabPiece[8][8], ListDeplacement* l);
void mettreEnSurbillancePiece(Piece* p, SDL_Renderer* contexte);
void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte);

#endif