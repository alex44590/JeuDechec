/**
* \file piece
* \brief gestion des actions en interactions avec les pi�ces
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
* \brief   Cr�er et initialise une pi�ce du jeu 
* \param[in] TypePiece type
* \param[in] Couleur couleur
* \param[in] char numPiece
* \return un pointeur vers la pi�ce cr��e 
*/
Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece);

/**
* \fn void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee, ListDeplacement* l)
* \brief   D�place une pi�ce sur l'�chiquier
* \param[in] Piece* p
* \param[in] Piece* tabPiece[8][8]
* \param[in] Lettre colonneArrivee
* \param[in] LettreligneArrivee
* \param[in] ListDeplacement* l
*/
void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee, ListDeplacement* l);

/**
* \fn void afficherPiece(Piece* p, SDL_Renderer* contexte)
* \brief   Affiche une piece sur sa position sur l'�chiquier
* \param[in] Piece* p
* \param[in] SDL_Renderer* contexte
*/
void afficherPiece(Piece* p, SDL_Renderer* contexte);

/**
* \fn void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte)
* \brief   Affiche toutes les pieces sur l'�chiquier
* \param[in] Piece* tabPiece[8][8]
* \param[in] SDL_Renderer* contexte
*/
void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte);

/**
* \fn void initAllPiece(Piece* tabPiece[8][8], ListDeplacement* l)
* \brief   Cr�er toutes les pi�ces de d�part d'une partie d'�chec
* \param[in] Piece* tabPiece[8][8]
* \param[in] ListDeplacement* l
*/
void initAllPiece(Piece* tabPiece[8][8], ListDeplacement* l);

/**
* \fn void mettreEnSurbillancePiece(Piece* p, SDL_Renderer* contexte)
* \brief   Met en surbrillance la piece s�lectionn�e
* \param[in] Piece* p
* \param[in] SDL_Renderer* contexte
*/
void mettreEnSurbillancePiece(Piece* p, SDL_Renderer* contexte);

/**
* \fn void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte)
* \brief   Supprime la surbrillance de la pi�ce s'�lectionn�
* \param[out] Piece* p
* \param[in] SDL_Renderer* contexte
*/
void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte);

/**
* \fn void mangerPiece(Piece* p, Piece* tabPiece[8][8], ListDeplacement* l)
* \brief   mange une pi�ce adverse
* \param[out] Piece* p
* \param[in] Piece* tabPiece[8][8]
* \param[in] ListDeplacement* l
*/
void mangerPiece(Piece* p, Piece* tabPiece[8][8], ListDeplacement* l);

#endif
