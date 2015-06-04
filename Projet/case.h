/**
* \file case.h
* \brief Gestions des cases
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Prototypes des fonctions de cr�ations, modifications et affichage des cases de l'�chiquier
*
*/


#ifndef CASE_H
#define CASE_H

#include "commun.h"



/**
* \struct Case
* \brief  Contient les dimensions de la case, son ID, sa position, sa couleur. Elle contient aussi trois bool�ens afin de savoir si 
*		  la case est s�lectionn�e, occup�e et si elle est en surbrillance. Il y a aussi les diff�rentes images qui correspondent
*		  aux diff�rentes situations (actuelle, en surbrillance, occup�e et en surbrillance, normale)
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
* \brief   Cr�e une case blanche
* \param[in] id : ID de la case � cr�er
* \return Un pointeur vers la case cr��e
*/
Case* creerCaseBlanche(IDCase id);

/**
* \fn creerCaseNoire(IDCase id)
* \brief   Cr�e une case noire
* \param[in] id : ID de la case � cr�er
* \return Un pointeur vers la case cr��e
*/
Case* creerCaseNoire(IDCase id);

/**
* \fn afficherCase(Case* c, SDL_Renderer* contexte)
* \brief   Affiche la case pass�e en param�tre 
* \param[in] c : pointeur vers la case � afficher
* \param[in] contexte : contexte graphique
*/
void afficherCase(Case* c, SDL_Renderer* contexte);

/**
* \fn mettreEnSurbrillance(Case* c, SDL_Renderer* contexte)
* \brief   Met la case pass�e en param�tre en surbrillance
* \param[in] c : pointeur vers la case � mettre en surbrillance
* \param[in] contexte : contexte graphique
*/
void mettreEnSurbrillance(Case* c, SDL_Renderer* contexte);

/**
* \fn mettreEnSurbrillanceOccupee(Case* c, SDL_Renderer* contexte)
* \brief   Met une case occup�e en surbrillance
* \param[in] c : pointeur vers la case � mettre en surbrillance
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