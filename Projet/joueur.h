#ifndef JOUEUR_H
#define JOUEUR_H

#include "commun.h"

#define TAILLE_MAX_NOM_JOUEUR 10

typedef struct{
	char* pseudo;
	int nbVictoires;
	int nbCoupsJoues;
	Couleur couleur;
}Joueur;

#endif