/**
* \file historique.h
* \brief Gestions de l'historique
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Définition de la structure historique recensant les différents déplacements effectués
*
*/

#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include "timer.h"
#include "listeDeplacement.h"


typedef struct {
	char* joueur1;
	char* joueur2;
	ListDeplacement deplacementEffectues;
	Timer debut;
}Historique;

#endif