/**
* \file entrainement.h
* \brief Gestions du mode entrainement
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Définition des réserves de pièces pour le mode entrainement
* Prototypes des fonctions de créations, modifications et d'affichage des réserves
*
*/

#ifndef ENTRAINEMENT_H
#define ENTRAINEMENT_H

#include "plateauDeJeu.h"
#include "commun.h"

/**
* \struct Reserve
* \brief  Contient la couleur, la position et les dimensions de la réserve.On retrouve également le 
*		  le tableau des pièces en réserve et l'image correspondante
*/
typedef struct{
	Couleur couleur;
	Position position;
	Dimension dimension;
	SDL_Surface* imageReserve;
	Piece* tabPiecesReserve[2][8];
}Reserve;


/**
* \fn Reserve* creerReserve(Couleur couleur)
* \brief      Crée la réserve
* \param[in] couleur : couleur de la réserve
* \return   Pointeur vers la réserve créée
*/
Reserve* creerReserve(Couleur couleur);

/**
* \fn void afficherReserve(Reserve* r, SDL_Renderer* contexte)
* \brief      Affiche la réserve
* \param[in] r : pointeur vers la réserve
* \ param[in] contexte : contexte graphique
*/
void afficherReserve(Reserve* r, SDL_Renderer* contexte);

/**
* \fn void initAllPiecesReserve(Piece* tabPiece[2][8], Couleur c)
* \brief      Initialise toutes les pièces dans la réserve
* \param[in] tabPiece[2][8] : tableau de pièces de la réserve
* \ param[in] c : couleur de la pièce
*/
void initAllPiecesReserve(Piece* tabPiece[2][8], Couleur c);

/**
* \fn void afficherPieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte, int x, int y)
* \brief      Affiche une pièce en réserve
* \param[in] r : pointeur vers la réserve
* \ param[in] p : pointeur vers la pièce
* \param[in] contexte : contexte graphique
* \ param[in] x : position en x de la pièce 
* \ param[in] y : position en y de la pièce
*/
void afficherPieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte, int x, int y);

/**
* \fn void afficherAllPiecesReserve(Reserve* r, SDL_Renderer* contexte)
* \brief      Affiche toutes les pièces en réserve
* \param[in] r : pointeur vers la réserve
* \param[in] contexte : contexte graphique
*/
void afficherAllPiecesReserve(Reserve* r, SDL_Renderer* contexte);

/**
* \fn Piece* selectionnerPieceReserve(Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte)
* \brief      Sélectionne une pièce en réserve
* \param[in] rb : pointeur vers la réserve blanche
* \param[in] rn : pointeur vers la réserve noire
* \param[in] x : position en x de la pièce
* \param[in] y : position en y de la pièce
* \param[in] contexte : contexte graphique
*/
Piece* selectionnerPieceReserve(Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte);

/**
* \fn void deselectionnerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, Couleur c, SDL_Renderer* contexte)
* \brief      Sélectionne une pièce en réserve
* \param[in] rb: pointeur vers la réserve noire
* \param[in] rn : pointeur vers la réserve noire
* \param[in] p : pointeur vers la pièce
* \param[in] c : couleur de la pièce
* \param[in] contexte : contexte graphique 
*/
void deselectionnerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, Couleur c, SDL_Renderer* contexte);

/**
* \fn void mettreEnSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte)
* \brief      Met en surbrillance une pièce en réserve lorsque celle-ci est sélectionnée
* \param[in] r : pointeur vers la réserve
* \param[in] p : pointeur vers la pièce
* \param[in] contexte : contexte graphique
*/
void mettreEnSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte);

/**
* \fn void supprimerSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte)
* \brief  Supprime la surbrillance d'une pièce en réserve
* \param[in]  r : pointeur vers la réserve
* \param[in]  p : pointeur
* \param[in] contexte : contexte graphique
*/
void supprimerSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte);

/**
* \fn void supprimerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, SDL_Renderer* contexte)
* \brief  Supprime la surbrillance d'une pièce en réserve
* \param[in]  rb : pointeur vers réserve blanche
* \param[in]  rn : pointeur vers réserve noire
* \param[in]  p : pointeur vers pièce sélectionnée
* \param[in] contexte : contexte graphique
*/
void supprimerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, SDL_Renderer* contexte);


/**
* \fn void remettrePieceReserve(Piece* p, PlateauDeJeu* pl, Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte)
* \brief Remet une pièce en réserve
* \param[in] p : pointeur vers la pièce sélectionnée
* \param[in] pl : le plateau de jeu
* \param[in]  rb : réserve noire
* \param[in]  rn : réserve blanche
* \param[in]  x : position x dans la réserve 
* \param[in]   y : position y dans la réserve 
* \param[in]   contexte : contexte graphique
*/
void remettrePieceReserve(Piece* p, PlateauDeJeu* pl, Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte);
#endif