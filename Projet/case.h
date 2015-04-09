#ifndef CASE_H
#define CASE_H

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
	SDL_Surface* imageCaseOccupeeSurbrillance;
	SDL_Surface* imageCaseNormale;
	Booleen occupee;
}Case;


Case* creerCaseBlanche(IDCase id);
Case* creerCaseNoire(IDCase id);
void afficherCase(Case* c, SDL_Renderer* contexte);
void mettreEnSurbrillance(Case* c, SDL_Renderer* contexte);
void mettreEnSurbrillanceOccupee(Case* c, SDL_Renderer* contexte);
void supprimerSurbrillance(Case* c, SDL_Renderer* contexte);
#endif