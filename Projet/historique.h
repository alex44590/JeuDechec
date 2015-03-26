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