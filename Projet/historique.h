/**
* \file historique.h
* \brief Gestions de l'historique
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* D�finition de la structure historique recensant les diff�rents d�placements effectu�s
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