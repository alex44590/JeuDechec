/**
* \file case.h
* \brief Gestions des cases
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Prototypes des fonctions de créations, modifications et affichage des cases de l'échiquier
*
*/


#ifndef CASE_H
#define CASE_H

#include "commun.h"



/**
* \struct Case
* \brief  Contient les dimensions de la case, son ID, sa position, sa couleur. Elle contient aussi trois booléens afin de savoir si 
*		  la case est sélectionnée, occupée et si elle est en surbrillance. Il y a aussi les différentes images qui correspondent
*		  aux différentes situations (actuelle, en surbrillance, occupée et en surbrillance, normale)
*/
typedef struct {
	Dimension dimension;
	IDCase identifiant;
	Position position;
	Couleur couleurCase;
	Booleen caseSelectionnee;
	Booleen enSurbrillance;
	SDL_Surface* imageCaseActuelle;
	SDL_Surface* imageCaseSurbrillance;
	SDL_Surface* imageCaseOccupeeSurbrillance;
	SDL_Surface* imageCaseNormale;
	Booleen occupee;
}Case;

/**
* \fn creerCaseBlanche(IDCase id)
* \brief   Crée une case blanche
* \param[in] id : ID de la case à créer
* \return Un pointeur vers la case créée
*/
Case* creerCaseBlanche(IDCase id);

/**
* \fn creerCaseNoire(IDCase id)
* \brief   Crée une case noire
* \param[in] id : ID de la case à créer
* \return Un pointeur vers la case créée
*/
Case* creerCaseNoire(IDCase id);

/**
* \fn afficherCase(Case* c, SDL_Renderer* contexte)
* \brief   Affiche la case passée en paramètre 
* \param[in] c : pointeur vers la case à afficher
* \param[in] contexte : contexte graphique
*/
void afficherCase(Case* c, SDL_Renderer* contexte);

/**
* \fn mettreEnSurbrillance(Case* c, SDL_Renderer* contexte)
* \brief   Met la case passée en paramètre en surbrillance
* \param[in] c : pointeur vers la case à mettre en surbrillance
* \param[in] contexte : contexte graphique
*/
void mettreEnSurbrillance(Case* c, SDL_Renderer* contexte);

/**
* \fn mettreEnSurbrillanceOccupee(Case* c, SDL_Renderer* contexte)
* \brief   Met une case occupée en surbrillance
* \param[in] c : pointeur vers la case à mettre en surbrillance
* \param[in] contexte : contexte graphique
*/
void mettreEnSurbrillanceOccupee(Case* c, SDL_Renderer* contexte);

/**
* \fn supprimerSurbrillance(Case* c, SDL_Renderer* contexte)
* \brief   Supprime la surbrillance de la case
* \param[in] c : pointeur vers la case 
* \param[in] contexte : contexte graphique
*/
void supprimerSurbrillance(Case* c, SDL_Renderer* contexte);
#endif