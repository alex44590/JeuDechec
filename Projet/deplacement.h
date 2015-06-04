#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "menuDroite.h"
#include "listeDeplacement.h"
#include "plateauDeJeu.h"
#include "deplacementPossible.h"


/**
* \fn void retourArriere(ListDeplacement *l, PlateauDeJeu *p, MenuDroite * m, SDL_Renderer* contexte, Couleur* couleurAJouer, ContexteRoque* c)
* \brief     retourne au � l'�tat du d�placement pr�c�dent, met � jour le tableau de pi�ce 
* \param[in/out] ListeDeplacement
* \param[in/out] PlateauDeJeu 
* \param[in/out] MenuDroite
* \param[in/out] SDL_Renderer
* \param[in/out] CouleurAJouer
* \param[in/out] ContexteRoque
*/
void retourArriere(ListDeplacement *l, PlateauDeJeu *p, MenuDroite * m, SDL_Renderer* contexte, Couleur* couleurAJouer, ContexteRoque* c);

#endif