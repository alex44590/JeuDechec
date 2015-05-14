#ifndef ENTRAINEMENT_H
#define ENTRAINEMENT_H

#include "plateauDeJeu.h"
#include "commun.h"

typedef struct{
	Couleur couleur;
	Position position;
	Dimension dimension;
	SDL_Surface* imageReserve;
	Piece* tabPiecesReserve[2][8];
}Reserve;


Reserve* creerReserve(Couleur couleur);
void afficherReserve(Reserve* r, SDL_Renderer* contexte);
void initAllPiecesReserve(Piece* tabPiece[2][8], Couleur c);
void afficherPieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte, int x, int y);
void afficherAllPiecesReserve(Reserve* r, SDL_Renderer* contexte);
Piece* selectionnerPieceReserve(Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte);
void deselectionnerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, Couleur c, SDL_Renderer* contexte);
void mettreEnSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte);
void supprimerSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte);
void supprimerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, SDL_Renderer* contexte);

#endif