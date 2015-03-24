#ifndef MENU_H
#define MENU_H

#include "commun.h"
#include "bouton.h"

typedef struct{
	SDL_Surface* fondMenu;
	Bouton* tabBouton[NB_BOUTON];
}Menu;


Menu* creerMenu();
void afficherFondMenu(Menu* m, SDL_Renderer* contexte);
void afficherMenu(Menu* m, SDL_Renderer* contexte);


#endif