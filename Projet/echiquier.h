/**
* \file echiquier.h
* \brief Gestion de l'échiquier
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Structure de l'échiquier
* Fonctions de création, d'enregistrement et d'affichage de l'échiquier
*
*/

#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include "case.h"
#include "piece.h"
#include "commun.h"

typedef struct{
	Case* tabCases[8][8];
	Piece* tabPieces[8][8];
	Dimension dimension;
}Echiquier;

Echiquier* creerEchiquier(ListDeplacement* l, Booleen ajouterPieces);
void afficherEchiquier(Echiquier* echiquier, SDL_Renderer* contexte);
void enregisterEchiquier(Echiquier* e, char* nomFichierSortie);

#endif