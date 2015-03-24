#ifndef CASE_H
#define CASE_H

#define _CRT_SECURE_NO_DEPRECATE//Autorise l'utilisation de fopen plutot que fopen_s

#include "commun.h"


typedef struct {
	Dimension dimension;
	IDCase identifiant;
	Position position;
	Couleur couleurCase;
	Booleen caseSelectionnee;
	Booleen enSurbrillance;
	SDL_Surface* imageCaseActuelle;
	SDL_Surface* imageCaseSurbrillance;
	SDL_Surface* imageCaseNormale;
	Booleen occupee;
	//Piece* pieceOccupante;
}Case;


Case* creerCaseBlanche(IDCase id);
Case* creerCaseNoire(IDCase id);
void afficherCase(Case* c, SDL_Renderer* contexte);
void mettreEnSurbrillance(Case* c);
void supprimerSurbrillance(Case* c);
#endif