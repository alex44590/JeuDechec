/**
* \file bouton.h
* \brief Gestions des boutons
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Prototypes des fonctions de créations, modifications et affichage des différents boutons du jeu
* (Boutons de menu, retour, accueil...)
*
*/

#ifndef BOUTON_H
#define BOUTON_H

#include "commun.h"

#define NB_BOUTON_MP 4 // Menu principal
#define NB_BOUTON_M2J 3 // Menu 2 joueurs
#define NB_BOUTON_MENT 3 // Menu Entrainement
#define NB_BOUTON_MD 1 // Menu Droite
#define NB_BOUTON_MREG 1 // Menu règles
#define NB_BOUTON_REGLES 2 //Fenetre règles

/**
* \enum idBouton
* \brief      Type du bouton créé
*/
typedef enum { ENTRAINEMENT, DEUXJOUEURS, OPTION, REGLES, ACCUEIL, JOUER, PAUSE, REGLESUIVANTE, REGLEPRECEDENTE, RETOUR }idBouton;


/**
* \struct Bouton
* \brief  Contient l'ID du bouton, l'image correspondante, sa position initiale et actuelle, 
*		  ses dimensions et un booléen pour savoir si le bouton est enfoncé
*/
typedef struct{
	idBouton idBouton;
	SDL_Surface* image;
	Position positionInit;
	Position positionActuelle;
	Dimension dimension;
	Booleen enfonce;
}Bouton;


/**
* \fn Bouton* creerBouton(idBouton cible, char* nomImage) 
* \brief      Crée un bouton
* \param[in] cible : type de bouton à créer
* \param [in] nomImage: pointeur vers l'image à charger
* \return   Pointeur vers le bouton créé
*/
Bouton* creerBouton(idBouton cible, char* nomImage);

/**
* \fn void setPositionBouton(Bouton* b, int x, int y)
* \brief   Modifie la position du bouton
* \param[in] b : pointeur vers le bouton
* \param [in] x : position en x du bouton
* \param [in] y : position en y du bouton
*/
void setPositionBouton(Bouton* b, int x, int y);

/**
* \fn setTailleBouton(Bouton* b, int largeur, int hauteur)
* \brief   Modifie la taille du bouton
* \param[in] b : pointeur vers le bouton
* \param [in] largeur : largeur du bouton
* \param [in] longueur : longueur du bouton
*/
void setTailleBouton(Bouton* b, int largeur, int hauteur);

/**
* \fn afficherBouton(Bouton* b, SDL_Renderer* contexte)
* \brief   Affiche le bouton passé en paramètre
* \param[in] b : pointeur vers le bouton à afficher
* \param [in] contexte : contexte graphique
*/
void afficherBouton(Bouton* b, SDL_Renderer* contexte);

/**
* \fn enfoncerBouton(Bouton* b)
* \brief   Modifie la position du bouton de 3 pixels à droite et en bas
* \param[in] b : pointeur vers le bouton à envoyer
*/
void enfoncerBouton(Bouton* b);

/**
* \fn desenfoncerBouton(Bouton* b)
* \brief   Remet le bouton en position initiale
* \param[in] b : pointeur vers le bouton à relacher
*/
void desenfoncerBouton(Bouton* b);

#endif