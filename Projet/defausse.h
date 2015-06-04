/**
* \file defausse.h
* \brief Gestions des d�fausses
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* D�finition de la structure d�fausse
* Prototypes des fonctions de cr�ations, modifications et affichage des d�fausses de pi�ces
*
*/

#ifndef DEFAUSSE_H
#define DEFAUSSE_H

#include "case.h"
#include "piece.h"
#include "commun.h"

#define LARGEUR_PIECE_DEFAUSSE 33
#define HAUTEUR_PIECE_DEFAUSSE 33
#define OFFSET_GAUCHE_PIECE_DEFAUSSE 17
#define OFFSET_HAUT_PIECE_DEFAUSSE 13
#define LARGEUR_ESPACE_PIECE_DEFAUSSE 0
#define HAUTEUR_ESPACE_PIECE_DEFAUSSE 2


typedef struct{
	Couleur couleur;
	Position position;
	Dimension dimension;
	SDL_Surface* imageDefausse;
	Piece* tabPiecesDefaussees[2][8];
}Defausse;

/**
* \fn creerDefausse(Couleur couleur)
* \brief   Cr�e une d�fause
* \param[in] Couleur couleur
* \return Un pointeur vers la d�fausse cr�ee
*/
Defausse* creerDefausse(Couleur couleur);

/**
* \fn afficherDefausse(Defausse* d, SDL_Renderer* contexte)
* \brief   Affiche une d�fausse
* \param[in] Defause* d
* \param[in] SDL_Renderer* contexte
*/
void afficherDefausse(Defausse* d, SDL_Renderer* contexte);

/**
* \fn afficherPieceDefausse(Defausse* d,Piece* p, SDL_Renderer* contexte, int x, int y)
* \brief   Affiche une pi�ce dans une d�fausse
* \param[in] Defause* d
* \param[in] Piece* p
* \param[in] SDL_Renderer* contexte
* \param[in] int x
* \param[in] int y
*/
void afficherPieceDefausse(Defausse* d, Piece* p, SDL_Renderer* contexte, int x, int y);

/**
* \fn afficherAllPiecesDefausse(Defausse* d, SDL_Renderer* contexte)
* \brief   Affiche toutes les pi�ces dans la d�fausse
* \param[in] Defause* d
* \param[in] SDL_Renderer* contexte
*/
void afficherAllPiecesDefausse(Defausse* d, SDL_Renderer* contexte);

/**
* \fn mettrePieceDefausse(Defausse* d, Piece* p, SDL_Renderer* contexte)
* \brief   Mise d'une pi�ce dans la d�fausse
* \param[in] Defause* d
* \param[in] Piece* p
* \param[in] SDL_Renderer* contexte
*/
void mettrePieceDefausse(Defausse* d, Piece* p, SDL_Renderer* contexte);

/**
* \fn sortirPieceDefausse(Defausse* dBlanc, Defausse* dNoir, IDPiece id)
* \brief   Cr�e une d�fause
* \param[in] Defausse* dBlanc
* \param[in] Defausse* dNoir
* \param[in] IDPiece id
* \return Un pointeur vers la piece sortie de la defausse
*/
Piece* sortirPieceDefausse(Defausse* dBlanc, Defausse* dNoir, IDPiece id);
#endif