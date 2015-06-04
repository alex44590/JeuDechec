/**
* \file evenement.h
* \brief Gestions des évènements SDL
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Définition de la structure Input recensant l'état à instant t des évènement SDL
* Fonction de mise à jour de la structure Input
* Macro-Définition des évènements courants (Clic souris un bouton du menu, sur une case de l'échiquier, ...)
*
*/

#ifndef EVENEMENT_H
#define EVENEMENT_H

#include "commun.h"

#define MOUVEMENT_SOURIS_INTERIEUR_ECHIQUIER (in.posSouris.x > OFFSET_PLATEAU_GAUCHE && in.posSouris.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && in.posSouris.y > OFFSET_PLATEAU_HAUT && in.posSouris.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)

#define CLIC_DOWN_SOURIS_BOUTON_MENU_PRINCIPAL in.sourisEnfoncee && (in.clicSouris.x > menu->tabBouton[i]->positionInit.x && in.clicSouris.x < menu->tabBouton[i]->positionInit.x + menu->tabBouton[i]->dimension.largeur && in.clicSouris.y > menu->tabBouton[i]->positionInit.y && in.clicSouris.y < menu->tabBouton[i]->positionInit.y + menu->tabBouton[i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_BOUTON_MENU_2JOUEURS in.sourisEnfoncee && (in.clicSouris.x > menu2J->tabBouton[i]->positionInit.x && in.clicSouris.x < menu2J->tabBouton[i]->positionInit.x + menu2J->tabBouton[i]->dimension.largeur && in.clicSouris.y > menu2J->tabBouton[i]->positionInit.y && in.clicSouris.y < menu2J->tabBouton[i]->positionInit.y + menu2J->tabBouton[i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_BOUTON_MENU_ENTRAINEMENT in.sourisEnfoncee && (in.clicSouris.x > menuEntrainement->tabBouton[i]->positionInit.x && in.clicSouris.x < menuEntrainement->tabBouton[i]->positionInit.x + menuEntrainement->tabBouton[i]->dimension.largeur && in.clicSouris.y > menuEntrainement->tabBouton[i]->positionInit.y && in.clicSouris.y < menuEntrainement->tabBouton[i]->positionInit.y + menuEntrainement->tabBouton[i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_BOUTON_MENU_REGLES in.sourisEnfoncee && (in.clicSouris.x > menuRegles->tabBouton[i]->positionInit.x && in.clicSouris.x < menuRegles->tabBouton[i]->positionInit.x + menuRegles->tabBouton[i]->dimension.largeur && in.clicSouris.y > menuRegles->tabBouton[i]->positionInit.y && in.clicSouris.y < menuRegles->tabBouton[i]->positionInit.y + menuRegles->tabBouton[i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_BOUTON_MENU_DROITE in.sourisEnfoncee && (in.clicSouris.x > menuDroite->tabBouton[i]->positionInit.x && in.clicSouris.x < menuDroite->tabBouton[i]->positionInit.x + menuDroite->tabBouton[i]->dimension.largeur && in.clicSouris.y > menuDroite->tabBouton[i]->positionInit.y && in.clicSouris.y < menuDroite->tabBouton[i]->positionInit.y + menuDroite->tabBouton[i]->dimension.hauteur)


#define CLIC_DOWN_SOURIS_BOUTON_REGLE_SUIVANTE in.sourisEnfoncee && (in.clicSouris.x > X_BOUTON_REGLE_SUIVANT && in.clicSouris.x < (X_BOUTON_REGLE_SUIVANT + LARGEUR_BOUTON_REGLE) && in.clicSouris.y > Y_BOUTON_REGLE_SUIVANT && in.clicSouris.y < (Y_BOUTON_REGLE_SUIVANT + HAUTEUR_BOUTON_REGLE))
#define CLIC_DOWN_SOURIS_BOUTON_REGLE_PRECEDENTE in.sourisEnfoncee && (in.clicSouris.x > X_BOUTON_REGLE_PRECEDENT && in.clicSouris.x < (X_BOUTON_REGLE_PRECEDENT + LARGEUR_BOUTON_REGLE) && in.clicSouris.y > Y_BOUTON_REGLE_PRECEDENT && in.clicSouris.y < (Y_BOUTON_REGLE_PRECEDENT + HAUTEUR_BOUTON_REGLE))
#define CLIC_DOWN_SOURIS_OPTION_TEMPS_PAGE_OPTIONS in.sourisEnfoncee && (in.clicSouris.x > pageOptions->tabOptionTemps[j][i]->position.x && in.clicSouris.x < pageOptions->tabOptionTemps[j][i]->position.x + pageOptions->tabOptionTemps[j][i]->dimension.largeur && in.clicSouris.y > pageOptions->tabOptionTemps[j][i]->position.y && in.clicSouris.y < pageOptions->tabOptionTemps[j][i]->position.y + pageOptions->tabOptionTemps[j][i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_OPTION_SURBRILLANCE_PAGE_OPTIONS in.sourisEnfoncee && (in.clicSouris.x > pageOptions->tabOptionSurbrillance[j][i]->position.x && in.clicSouris.x < pageOptions->tabOptionSurbrillance[j][i]->position.x + pageOptions->tabOptionSurbrillance[j][i]->dimension.largeur && in.clicSouris.y > pageOptions->tabOptionSurbrillance[j][i]->position.y && in.clicSouris.y < pageOptions->tabOptionSurbrillance[j][i]->position.y + pageOptions->tabOptionSurbrillance[j][i]->dimension.hauteur)


#define CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE (in.clicSouris.x > 0 && in.clicSouris.x < OFFSET_PLATEAU_GAUCHE)
#define CLIC_DOWN_SOURIS_INTERIEUR_MENU_DROITE (in.clicSouris.x > OFFSET_PLATEAU_DROITE && in.clicSouris.x < LARGEUR_FENETRE)
#define CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER (in.clicSouris.x > OFFSET_PLATEAU_GAUCHE && in.clicSouris.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && in.clicSouris.y > OFFSET_PLATEAU_HAUT && in.clicSouris.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)

#define CLIC_DOWN_SOURIS_INTERIEUR_RESERVE (in.clicSouris.x >= X_RESERVE && in.clicSouris.x <= (X_RESERVE + LARGEUR_RESERVE) && ((in.clicSouris.y >= Y_RESERVE_NOIRE && in.clicSouris.y <= Y_RESERVE_NOIRE + HAUTEUR_RESERVE) ||  (in.clicSouris.y >= Y_RESERVE_BLANCHE && in.clicSouris.y <= Y_RESERVE_BLANCHE + HAUTEUR_RESERVE)))

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
	Dimension tailleFenetre;
}Input;

void mettreAJourEvent(Input* in);

#endif