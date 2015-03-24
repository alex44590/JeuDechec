#ifndef JOUEUR_H
#define JOUEUR_H

#include "commun.h"

typedef struct{
	char* pseudo;
	int nbVictoires;
	int nbCoupsJoues;
	Couleur couleurJoueur;
}Joueur;

#endif