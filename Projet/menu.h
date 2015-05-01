#ifndef MENU_H
#define MENU_H

#include "commun.h"
#include "texte.h"
#include "bouton.h"
#include "evenement.h"

#define LARGEUR_ZONE_PSEUDO 260
#define HAUTEUR_ZONE_PSEUDO 40
#define X_ZONE_PSEUDO_1 20
#define X_ZONE_PSEUDO_2 20
#define Y_ZONE_PSEUDO_1 150
#define Y_ZONE_PSEUDO_2 220
#define ESPACEMENT_NUMJ_ZONE -3 //Espacement vertical entre l'écriture "Joueur 1 (ou 2)" et la zone dans laquelle on écrit le pseudo correspondant

#define PSEUDO_LONGUEUR_MAX 20 //Caractère de fin de chaine compris

#define CLIC_SOURIS_INTERIEUR_PSEUDO_1 (in.clicSouris.x > X_ZONE_PSEUDO_1 && in.clicSouris.x < X_ZONE_PSEUDO_1 + LARGEUR_ZONE_PSEUDO && in.clicSouris.y > Y_ZONE_PSEUDO_1 && in.clicSouris.y < Y_ZONE_PSEUDO_1 + HAUTEUR_ZONE_PSEUDO)
#define CLIC_SOURIS_INTERIEUR_PSEUDO_2 (in.clicSouris.x > X_ZONE_PSEUDO_2 && in.clicSouris.x < X_ZONE_PSEUDO_2 + LARGEUR_ZONE_PSEUDO && in.clicSouris.y > Y_ZONE_PSEUDO_2 && in.clicSouris.y < Y_ZONE_PSEUDO_2 + HAUTEUR_ZONE_PSEUDO)


typedef struct{
	SDL_Surface* fondMenu;
	Bouton* tabBouton[NB_BOUTON_MP];
}Menu;

typedef struct{
	char pseudo[PSEUDO_LONGUEUR_MAX+1];
	int numZone;
	Dimension dimension;
	Position position;
	SDL_Surface* imageActuelle;
	SDL_Surface* imageZone;
	SDL_Surface* imageZoneSelectionnee;
	SDL_Surface* ttfPseudo; //Contient le pseudo sous forme d'une surface : Il est nécessaire de la recalculer à chaque changement d'une lettre dans pseudo
	SDL_Surface* ttfNumJ; //Affiche joueur 1 au dessus de la zone pseudo numero 1, ...
}ZonePseudo;

typedef struct{
	Dimension dimension;
	Position position;
	SDL_Surface* fondMenu;
	Bouton* tabBouton[NB_BOUTON_M2J];
	ZonePseudo* zone1;
	ZonePseudo* zone2;
}Menu2J;


//PARTIE MENU PRINCIPAL
Menu* creerMenu();
void afficherFondMenu(SDL_Surface* fondMenu, SDL_Renderer* contexte);
void afficherMenu(Menu* m, SDL_Renderer* contexte);

//PARTIE MENU 2 JOUEURS
Menu2J* creerMenuDeuxJoueurs();
void afficherMenu2J(Menu2J* m, SDL_Renderer* contexte);

//PARTIE ZONE PSEUDO
ZonePseudo* creerZonePseudo(int numZone);
void afficherAllZonesPseudo(ZonePseudo* zone1, ZonePseudo* zone2, SDL_Renderer* contexte);
void afficherZonePseudo(ZonePseudo* z, SDL_Renderer* contexte);
void selectionnerZonePseudo(Menu2J* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte);
void deselectionnerZonePseudo(Menu2J* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte);
void catSaisiePseudo(Input* in, ZonePseudo* z, int* continuerSaisiePseudo);

#endif