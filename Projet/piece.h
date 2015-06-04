#ifndef PIECE_H
#define PIECE_H

#include "case.h"
#include "listeDeplacement.h"
#include "pieceCommun.h"
#define NB_PION_DEPART 8


extern int numeroDeplacement;

Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece);
void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee, ListDeplacement* l);
void afficherPiece(Piece* p, SDL_Renderer* contexte);
void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte);
void initAllPiece(Piece* tabPiece[8][8], ListDeplacement* l);
void mettreEnSurbillancePiece(Piece* p, SDL_Renderer* contexte);
void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte);
void mangerPiece(Piece* p, Piece* tabPiece[8][8], ListDeplacement* l);

#endif
