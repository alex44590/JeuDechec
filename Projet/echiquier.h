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

/**
* \struct Echiquier
* \brief  Contient un tableau deux dimensions représentant les cases de l'échiquier avec toutes les pièces
*		  ainsi que ses dimensions.
*/
typedef struct{
	Case* tabCases[8][8];
	Piece* tabPieces[8][8];
	Dimension dimension;
}Echiquier;

/**
* \fn Echiquier* creerEchiquier(ListDeplacement* l, Booleen ajouterPieces)
* \brief      Crée l'échiquier
* \param[in] l : pointeur vers la liste contenant les déplacements
* \param [in] ajouterPieces : permet de savoir s'il est nécessaire de rajouter les pièces sur l'échiquier
* \return   Pointeur vers l'échiquier
*/
Echiquier* creerEchiquier(ListDeplacement* l, Booleen ajouterPieces);

/**
* \fn void afficherEchiquier(Echiquier* echiquier, SDL_Renderer* contexte)
* \brief      Affiche l'échiquier
* \param[in] echiquier : pointeur vers l'échiquier
* \param [in] contexte : contexte graphique
*/
void afficherEchiquier(Echiquier* echiquier, SDL_Renderer* contexte);

/**
* \fn void enregisterEchiquier(Echiquier* e, char* nomFichierSortie);
* \brief      Exporte l'échiquier dans un fichier texte, Echiquier.txt
* \param[in] e : pointeur vers l'échiquier
* \param [in] nomFichierSortie : nom du fichier enregistré
*/
void enregisterEchiquier(Echiquier* e, char* nomFichierSortie);

#endif