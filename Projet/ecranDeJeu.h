#ifndef ECRANDEJEU_H
#define ECRANDEJEU_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "commun.h"
#include "partie.h"
#include "menuPrincipal.h"
#include "option.h"


/*Création de la structure EcranDeJeu*/
union EcranDeJeu{
	MenuPrincipal menuPrincipal; 
	Partie partie;
	Option optionDeJeu;
};
/*edj = ecran de jeu*/

#endif