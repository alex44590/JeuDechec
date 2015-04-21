#ifndef OPTION_H
#define OPTION_H

#include "commun.h"
#include "bouton.h"


/*Création de la structure Option*/
typedef struct 
{
	Bouton* bouton;
}Option;

typedef struct{
	SDL_Surface* image;
	Booleen cochee;
	Dimension dimension;
	int idOption;
}OptionCochable;

typedef struct{
	int nbCoupsjoue;
	//int chrono;
	//Bouton Precredent;
}Indicateur;


#endif