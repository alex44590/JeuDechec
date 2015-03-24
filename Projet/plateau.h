#ifndef PLATEAU_H
#define PLATEAU_H
#include "case.h"
#include "commun.h"

/*typedef struct {
	Case*** tabCases;
}Plateau;*/

void afficherCadre(SDL_Renderer* contexte);
void creerPlateau(Case* Plateau[8][8]);
void afficherPlateau(Case* Plateau[8][8], SDL_Renderer* contexte);

#endif
