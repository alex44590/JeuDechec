#ifndef EVENEMENT_H
#define EVENEMENT_H

#include "commun.h"

#define MOUVEMENT_SOURIS_INTERIEUR_ECHIQUIER (in.posSouris.x > OFFSET_PLATEAU_GAUCHE && in.posSouris.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && in.posSouris.y > OFFSET_PLATEAU_HAUT && in.posSouris.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
#define CLIC_DOWN_SOURIS_SUR_BOUTON_MENU_GAUCHE in.sourisEnfoncee && (in.clicSouris.x > menu->tabBouton[i]->positionInit.x && in.clicSouris.x < menu->tabBouton[i]->positionInit.x + menu->tabBouton[i]->dimension.largeur && in.clicSouris.y > menu->tabBouton[i]->positionInit.y && in.clicSouris.y < menu->tabBouton[i]->positionInit.y + menu->tabBouton[i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE in.sourisEnfoncee && (in.clicSouris.x > 0 && in.clicSouris.x < OFFSET_PLATEAU_GAUCHE)
#define CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER in.sourisEnfoncee && (in.clicSouris.x > OFFSET_PLATEAU_GAUCHE && in.clicSouris.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && in.clicSouris.y > OFFSET_PLATEAU_HAUT && in.clicSouris.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)

#define KEYCODE_REDUIT(x) (x - 1073741753) //Permet de réduire les SDLK_... dont le nombre n'est pas entre 0 et 127 en un nombre entre 128 et 353

/* Les fonctions et structures définies dans ce header vont permettre de simplifier la gestion 
   des évènements de la SDL (pressage de plusieurs touches en meme temps, eviter le double switch...*/

typedef struct{
	Booleen clavier[354];
	Position posSouris;
	Position clicSouris;
	Booleen sourisEnfoncee;
	Booleen sourisRelachee;
	Booleen quit;
}Input;

void mettreAJourEvent(Input* in);

#endif