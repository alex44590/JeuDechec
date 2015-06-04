/**
* \file casePseudo.h
* \brief Structure de la case permettant d'entrer un pseudo
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1*
*/

#ifndef CASEPSEUDO_H
#define CASEPSEUDO_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "commun.h"

#define TAILLEMAX_NOM_JOUEUR 12


/*Création de la structure CasePseudo*/
typedef struct
{
	Dimension dimension;
	Position position;
	char* texteJ1;
	char* texteJ2;
	Booleen selected;
}CasePseudo;

#endif