#ifndef MENUDROITE_H
#define MENUDROITE_H

#define TEXTE_ECHEC_MAX 30
#define TEXTE_ECHEC_X 970
#define TEXTE_ECHEC_Y 310

#define ZONE_JOUEUR_X 970
#define ZONE_JOUEUR_Y 230
#define ZONE_JOUEUR_LARGEUR 260
#define ZONE_JOUEUR_HAUTEUR 25

#include "commun.h"
#include "texte.h"
#include "bouton.h"
#include "option.h"
#include "defausse.h"
#include "timer.h"


typedef struct{
	Dimension dimension;
	Position position;
	SDL_Surface* imageZoneJoueur;
	SDL_Surface* ttfJoueur;
}ZoneJoueurEnCours;

typedef struct{
	Dimension dimension;
	Position position;
	SDL_Surface* fondMenu;
	Defausse* defausseB;
	Defausse* defausseN;
	ZoneJoueurEnCours* zoneJoueurEnCours;
	char* texteEchec;
	SDL_Surface* ttfTexteEchec;
	Timer* timer;
}MenuDroite;

typedef enum SituationEchec{ ECHEC_BLANC, ECHEC_NOIR, ECHEC_ET_MAT_BLANC, ECHEC_ET_MAT_NOIR, PAT, RIEN }SituationEchec;

MenuDroite* creerMenuDroite(Defausse* defausseB, Defausse* defausseN);
void afficherFondMenuDroite(MenuDroite* m, SDL_Renderer* contexte);
void afficherMenuDroite(MenuDroite* m, SDL_Renderer* contexte);

/*Fonction qui affiche un �v�nement notable en fonction de la situation de jeu (Echec, pat...) dans le menu de droite,
  ou qui supprime l'affichage pr�c�dent si la situation a �t� r�solue*/
void mettreAJourTexteEchec(MenuDroite* m, SituationEchec s, SDL_Renderer* contexte);

ZoneJoueurEnCours* creerZoneJoueurEnCours();
void afficherZoneJoueurEnCours(ZoneJoueurEnCours* z, SDL_Renderer* contexte);
#endif // !MENUDROITE_H
