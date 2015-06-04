/**
* \file entrainement.h
* \brief Gestions du mode entrainement
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* D�finition des r�serves de pi�ces pour le mode entrainement
* Prototypes des fonctions de cr�ations, modifications et d'affichage des r�serves
*
*/

#ifndef ENTRAINEMENT_H
#define ENTRAINEMENT_H

#include "plateauDeJeu.h"
#include "commun.h"

/**
* \struct Reserve
* \brief  Contient la couleur, la position et les dimensions de la r�serve.On retrouve �galement le 
*		  le tableau des pi�ces en r�serve et l'image correspondante
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
* \brief      Cr�e la r�serve
* \param[in] couleur : couleur de la r�serve
* \return   Pointeur vers la r�serve cr��e
*/
Reserve* creerReserve(Couleur couleur);

/**
* \fn void afficherReserve(Reserve* r, SDL_Renderer* contexte)
* \brief      Affiche la r�serve
* \param[in] r : pointeur vers la r�serve
* \ param[in] contexte : contexte graphique
*/
void afficherReserve(Reserve* r, SDL_Renderer* contexte);

/**
* \fn void initAllPiecesReserve(Piece* tabPiece[2][8], Couleur c)
* \brief      Initialise toutes les pi�ces dans la r�serve
* \param[in] tabPiece[2][8] : tableau de pi�ces de la r�serve
* \ param[in] c : couleur de la pi�ce
*/
void initAllPiecesReserve(Piece* tabPiece[2][8], Couleur c);

/**
* \fn void afficherPieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte, int x, int y)
* \brief      Affiche une pi�ce en r�serve
* \param[in] r : pointeur vers la r�serve
* \ param[in] p : pointeur vers la pi�ce
* \param[in] contexte : contexte graphique
* \ param[in] x : position en x de la pi�ce 
* \ param[in] y : position en y de la pi�ce
*/
void afficherPieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte, int x, int y);

/**
* \fn void afficherAllPiecesReserve(Reserve* r, SDL_Renderer* contexte)
* \brief      Affiche toutes les pi�ces en r�serve
* \param[in] r : pointeur vers la r�serve
* \param[in] contexte : contexte graphique
*/
void afficherAllPiecesReserve(Reserve* r, SDL_Renderer* contexte);

/**
* \fn Piece* selectionnerPieceReserve(Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte)
* \brief      S�lectionne une pi�ce en r�serve
* \param[in] rb : pointeur vers la r�serve blanche
* \param[in] rn : pointeur vers la r�serve noire
* \param[in] x : position en x de la pi�ce
* \param[in] y : position en y de la pi�ce
* \param[in] contexte : contexte graphique
*/
Piece* selectionnerPieceReserve(Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte);

/**
* \fn void deselectionnerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, Couleur c, SDL_Renderer* contexte)
* \brief      S�lectionne une pi�ce en r�serve
* \param[in] rb: pointeur vers la r�serve noire
* \param[in] rn : pointeur vers la r�serve noire
* \param[in] p : pointeur vers la pi�ce
* \param[in] c : couleur de la pi�ce
* \param[in] contexte : contexte graphique 
*/
void deselectionnerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, Couleur c, SDL_Renderer* contexte);

/**
* \fn void mettreEnSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte)
* \brief      Met en surbrillance une pi�ce en r�serve lorsque celle-ci est s�lectionn�e
* \param[in] r : pointeur vers la r�serve
* \param[in] p : pointeur vers la pi�ce
* \param[in] contexte : contexte graphique
*/
void mettreEnSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte);

/**
* \fn void supprimerSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte)
* \brief  Supprime la surbrillance d'une pi�ce en r�serve
* \param[in]  r : pointeur vers la r�serve
* \param[in]  p : pointeur
* \param[in] contexte : contexte graphique
*/
void supprimerSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte);

/**
* \fn void supprimerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, SDL_Renderer* contexte)
* \brief  Supprime la surbrillance d'une pi�ce en r�serve
* \param[in]  rb : pointeur vers r�serve blanche
* \param[in]  rn : pointeur vers r�serve noire
* \param[in]  p : pointeur vers pi�ce s�lectionn�e
* \param[in] contexte : contexte graphique
*/
void supprimerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, SDL_Renderer* contexte);


/**
* \fn void remettrePieceReserve(Piece* p, PlateauDeJeu* pl, Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte)
* \brief Remet une pi�ce en r�serve
* \param[in] p : pointeur vers la pi�ce s�lectionn�e
* \param[in] pl : le plateau de jeu
* \param[in]  rb : r�serve noire
* \param[in]  rn : r�serve blanche
* \param[in]  x : position x dans la r�serve 
* \param[in]   y : position y dans la r�serve 
* \param[in]   contexte : contexte graphique
*/
void remettrePieceReserve(Piece* p, PlateauDeJeu* pl, Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte);
#endif