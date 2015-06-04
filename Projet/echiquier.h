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

/**
* \struct Echiquier
* \brief  Contient un tableau deux dimensions repr�sentant les cases de l'�chiquier avec toutes les pi�ces
*		  ainsi que ses dimensions.
*/
typedef struct{
	Case* tabCases[8][8];
	Piece* tabPieces[8][8];
	Dimension dimension;
}Echiquier;

/**
* \fn Echiquier* creerEchiquier(ListDeplacement* l, Booleen ajouterPieces)
* \brief      Cr�e l'�chiquier
* \param[in] l : pointeur vers la liste contenant les d�placements
* \param [in] ajouterPieces : permet de savoir s'il est n�cessaire de rajouter les pi�ces sur l'�chiquier
* \return   Pointeur vers l'�chiquier
*/
Echiquier* creerEchiquier(ListDeplacement* l, Booleen ajouterPieces);

/**
* \fn void afficherEchiquier(Echiquier* echiquier, SDL_Renderer* contexte)
* \brief      Affiche l'�chiquier
* \param[in] echiquier : pointeur vers l'�chiquier
* \param [in] contexte : contexte graphique
*/
void afficherEchiquier(Echiquier* echiquier, SDL_Renderer* contexte);

/**
* \fn void enregisterEchiquier(Echiquier* e, char* nomFichierSortie);
* \brief      Exporte l'�chiquier dans un fichier texte, Echiquier.txt
* \param[in] e : pointeur vers l'�chiquier
* \param [in] nomFichierSortie : nom du fichier enregistr�
*/
void enregisterEchiquier(Echiquier* e, char* nomFichierSortie);

#endif