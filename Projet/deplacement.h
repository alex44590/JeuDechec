#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "timer.h"
#include "commun.h"


typedef struct Deplacement{
	IDPiece currentPiece;
	IDCase depart;
	IDCase arrivee;
	int numeroDeplacement;
	Timer heure;
	struct Deplacement* next;
	struct Deplacement* previous;
}Deplacement;

#endif