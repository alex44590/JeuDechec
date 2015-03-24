#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "timer.h"
#include "commun.h"


typedef struct Deplacement{
	IDPiece currentPiece;
	IDCase depart;
	IDCase arrivee;
	int numero;
	Timer heure;
	Deplacement next;
	Deplacement previous;
}Deplacement;

#endif

