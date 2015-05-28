#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "menuDroite.h"
#include "listeDeplacement.h"
#include "plateauDeJeu.h"
#include "deplacementPossible.h"

void retourArriere(ListDeplacement *l, PlateauDeJeu *p, MenuDroite * m, SDL_Renderer* contexte, Couleur couleurAJouer, ContexteRoque* c);

#endif