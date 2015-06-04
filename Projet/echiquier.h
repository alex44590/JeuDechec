/**
* \file echiquier.h
* \brief Gestion de l'�chiquier
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Structure de l'�chiquier
* Fonctions de cr�ation, d'enregistrement et d'affichage de l'�chiquier
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