#ifndef MENUDROITE_H
#define MENUDROITE_H

#define TEXTE_ECHEC_MAX 30
#define TEXTE_ECHEC_X 970
#define TEXTE_ECHEC_Y 310

#define ZONE_JOUEUR_X 970
#define ZONE_JOUEUR_Y 230
#define ZONE_JOUEUR_LARGEUR 260
#define ZONE_JOUEUR_HAUTEUR 25

#define BOUTON_RETOUR_X 1020 
#define BOUTON_RETOUR_Y 160

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
	SDL_Surface* imageZoneChrono;
}ZoneChrono;

typedef struct{
	Dimension dimension;
	Position position;
	SDL_Surface* fondMenu;
	Defausse* defausseB;
	Defausse* defausseN;
	Bouton* tabBouton[NB_BOUTON_MD];
	ZoneJoueurEnCours* zoneJoueurEnCours;
	ZoneChrono* zoneChrono;
	char* texteEchec;
	SDL_Surface* ttfTexteEchec;
	Timer* timer[2];
	Couleur couleurEnCours;
}MenuDroite;

typedef enum SituationEchec{ ECHEC_BLANC, ECHEC_NOIR, ECHEC_ET_MAT_BLANC, ECHEC_ET_MAT_NOIR, PAT, RIEN }SituationEchec;

MenuDroite* creerMenuDroite(Defausse* defausseB, Defausse* defausseN);
void afficherFondMenuDroite(MenuDroite* m, SDL_Renderer* contexte);
void afficherMenuDroite(MenuDroite* m, Couleur couleurAJouer, SDL_Renderer* contexte);

/*Fonction qui affiche un évènement notable en fonction de la situation de jeu (Echec, pat...) dans le menu de droite,
  ou qui supprime l'affichage précédent si la situation a été résolue*/
void mettreAJourTexteEchec(MenuDroite* m, Couleur couleurAJouer, SituationEchec s, SDL_Renderer* contexte);

ZoneJoueurEnCours* creerZoneJoueurEnCours();
void afficherZoneJoueurEnCours(ZoneJoueurEnCours* z, SDL_Renderer* contexte);

ZoneChrono* creerZoneChrono();
void afficherZoneChrono(ZoneChrono* z, SDL_Renderer* contexte);

#endif // !MENUDROITE_H
