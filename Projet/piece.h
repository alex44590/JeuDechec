/**
* \file piece
* \brief gestion des actions en interactions avec les pièces
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
*/

#ifndef PIECE_H
#define PIECE_H

#include "case.h"
#include "listeDeplacement.h"
#include "pieceCommun.h"
#define NB_PION_DEPART 8


extern int numeroDeplacement;

/**
* \fn Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece)
* \brief   Créer et initialise une pièce du jeu 
* \param[in] TypePiece type
* \param[in] Couleur couleur
* \param[in] char numPiece
* \return un pointeur vers la pièce créée 
*/
Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece);

/**
* \fn void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee, ListDeplacement* l)
* \brief   Déplace une pièce sur l'échiquier
* \param[in] Piece* p
* \param[in] Piece* tabPiece[8][8]
* \param[in] Lettre colonneArrivee
* \param[in] LettreligneArrivee
* \param[in] ListDeplacement* l
*/
void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee, ListDeplacement* l);

/**
* \fn void afficherPiece(Piece* p, SDL_Renderer* contexte)
* \brief   Affiche une piece sur sa position sur l'échiquier
* \param[in] Piece* p
* \param[in] SDL_Renderer* contexte
*/
void afficherPiece(Piece* p, SDL_Renderer* contexte);

/**
* \fn void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte)
* \brief   Affiche toutes les pieces sur l'échiquier
* \param[in] Piece* tabPiece[8][8]
* \param[in] SDL_Renderer* contexte
*/
void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte);

/**
* \fn void initAllPiece(Piece* tabPiece[8][8], ListDeplacement* l)
* \brief   Créer toutes les pièces de départ d'une partie d'échec
* \param[in] Piece* tabPiece[8][8]
* \param[in] ListDeplacement* l
*/
void initAllPiece(Piece* tabPiece[8][8], ListDeplacement* l);

/**
* \fn void mettreEnSurbillancePiece(Piece* p, SDL_Renderer* contexte)
* \brief   Met en surbrillance la piece sélectionnée
* \param[in] Piece* p
* \param[in] SDL_Renderer* contexte
*/
void mettreEnSurbillancePiece(Piece* p, SDL_Renderer* contexte);

/**
* \fn void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte)
* \brief   Supprime la surbrillance de la pièce s'électionné
* \param[out] Piece* p
* \param[in] SDL_Renderer* contexte
*/
void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte);

/**
* \fn void mangerPiece(Piece* p, Piece* tabPiece[8][8], ListDeplacement* l)
* \brief   mange une pièce adverse
* \param[out] Piece* p
* \param[in] Piece* tabPiece[8][8]
* \param[in] ListDeplacement* l
*/
void mangerPiece(Piece* p, Piece* tabPiece[8][8], ListDeplacement* l);

#endif
