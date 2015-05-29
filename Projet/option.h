#ifndef OPTION_H
#define OPTION_H

#include "commun.h"
#include "bouton.h"
#include "menuDroite.h"

#define NB_OPTIONS_TEMPS 6

#define OPTION_LARGEUR 50
#define OPTION_HAUTEUR 50
#define OPTION_1_X 375
#define OPTION_1_Y 310

typedef enum { MIN_15, MIN_20, MIN_30, MIN_45, MIN_60, MIN_ILLIMITE, SURBRILLANCE_ACTIVEE, SURBRILLANCE_DESACTIVEE }IdOption;
typedef enum { MODE_ENTRAINEMENT, MODE_MULTIJOUEUR }IdMode;

typedef struct{
	IdOption idOption;
	SDL_Surface* imagePasCochee;
	SDL_Surface* imageCochee;
	SDL_Surface* imageActuelle;
	Position position;
	Dimension dimension;
	Booleen cochee;
}Option;

typedef struct
{
	SDL_Surface* imageFondPage;
	Option* tabOptionTemps[NB_OPTIONS_TEMPS][2];
	Option* tabOptionSurbrillance[2][2];
	Booleen surbrillance[2][2];
	int tempsJeuParJoueur[2];
}PageOptions;


PageOptions* creerPageOptions();
void afficherPageOptions(PageOptions* p, SDL_Renderer* contexte);

Option* creerOption(IdOption cible, int x, int y);
void afficherOption(Option* o, SDL_Renderer* contexte);
void cocherOption(Option* o);
void decocherOption(Option* o);
void gererOptionTemps(PageOptions* pageOptions, MenuDroite* menuDroiteEntrainement, MenuDroite* menuDroite2J, int i, int j, SDL_Renderer* contexte);
void gererOptionSurbrillance(PageOptions* pageOptions, Booleen* surbrillance2J, Booleen* surbrillanceEntrainement, int i, int j, SDL_Renderer* contexte);

#endif