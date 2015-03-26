#ifndef MENUDROITE_H
#define MENUDROITE_H

#include "commun.h"
#include "bouton.h"
#include "option.h"
#include "defausse.h"

typedef struct{
	Dimension dimension;
	Position position;
	SDL_Surface* fondMenu;
	Defausse* defausseB;
	Defausse* defausseN;
}MenuDroite;

MenuDroite* creerMenuDroite(Defausse* defausseB, Defausse* defausseN);
void afficherFondMenuDroite(MenuDroite* m, SDL_Renderer* contexte);

#endif // !MENUDROITE_H
