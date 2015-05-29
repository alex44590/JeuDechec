#ifndef REGLE_H
#define REGLE_H

#include "commun.h"
#include "texte.h"
#include "bouton.h"

#define NB_PAGES_REGLES 7
#define X_BOUTON_REGLE_PRECEDENT 320
#define Y_BOUTON_REGLE_PRECEDENT 570
#define X_BOUTON_REGLE_SUIVANT 1190
#define Y_BOUTON_REGLE_SUIVANT 570
#define LARGEUR_BOUTON_REGLE 50
#define HAUTEUR_BOUTON_REGLE 50



typedef struct{
	Bouton* boutons[2];
	SDL_Surface* imageRegle;
}PageRegle;

typedef struct{
	PageRegle* pagesRegles[NB_PAGES_REGLES];
	char numPageEnCours;
}FenetreRegle;

PageRegle* creerPageRegle(char numPage, Booleen boutonPrecedent, Booleen boutonSuivant);
void afficherPageRegle(PageRegle* p, SDL_Renderer* contexte);

FenetreRegle* creerFenetreRegle();
void afficherFenetreRegle(FenetreRegle* f, SDL_Renderer* contexte);
void pageRegleSuivante(FenetreRegle* f);
void pageReglePrecedente(FenetreRegle* f);

#endif