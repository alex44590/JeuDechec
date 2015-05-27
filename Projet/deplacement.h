#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "menuDroite.h"
#include "listeDeplacement.h"

void retourArriere(ListDeplacement *l, Piece* tabPiece[8][8], Defausse* dBlanc, Defausse* dNoir, MenuDroite * m, SDL_Renderer* contexte);

#endif