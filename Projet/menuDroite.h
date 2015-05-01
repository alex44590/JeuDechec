#ifndef MENUDROITE_H
#define MENUDROITE_H

#define TEXTE_ECHEC_MAX 30
#define TEXTE_ECHEC_X 970
#define TEXTE_ECHEC_Y 290


#include "commun.h"
#include "texte.h"
#include "bouton.h"
#include "option.h"
#include "defausse.h"

typedef struct{
	Dimension dimension;
	Position position;
	SDL_Surface* fondMenu;
	Defausse* defausseB;
	Defausse* defausseN;
	char* texteEchec;
	SDL_Surface* ttfTexteEchec;
}MenuDroite;

typedef enum SituationEchec{ ECHEC_BLANC, ECHEC_NOIR, ECHEC_ET_MAT_BLANC, ECHEC_ET_MAT_NOIR, PAT, RIEN }SituationEchec;

MenuDroite* creerMenuDroite(Defausse* defausseB, Defausse* defausseN);
void afficherFondMenuDroite(MenuDroite* m, SDL_Renderer* contexte);

/*Fonction qui affiche un évènement notable en fonction de la situation de jeu (Echec, pat...) dans le menu de droite,
  ou qui supprime l'affichage précédent si la situation a été résolue*/
void afficherTexteEchec(MenuDroite* m, SituationEchec s, SDL_Renderer* contexte);
#endif // !MENUDROITE_H
