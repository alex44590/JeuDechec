#ifndef TEXTE_H
#define TEXTE_H

#include "commun.h"

SDL_Surface* creerTexte(char* texte, char* font, int taille, int r, int g, int b);
void afficherTexte(SDL_Surface* texte, int x, int y, SDL_Renderer* contexte);

#endif