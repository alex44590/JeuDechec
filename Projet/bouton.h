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
* \param[in] idBouton cible
* \param [in] char* nomImage
* \return   Pointeur vers le bouton créé
*/
Bouton* creerBouton(idBouton cible, char* nomImage);

/**
* \fn void setPositionBouton(Bouton* b, int x, int y)
* \brief   Modifie la position du bouton
* \param[in] Bouton* b
* \param [in] int x
* \param [in] int y
*/
void setPositionBouton(Bouton* b, int x, int y);

/**
* \fn setTailleBouton(Bouton* b, int largeur, int hauteur)
* \brief   Modifie la taille du bouton
* \param[in] Bouton* b
* \param [in] int largeur
* \param [in] int longueur
*/
void setTailleBouton(Bouton* b, int largeur, int hauteur);

/**
* \fn afficherBouton(Bouton* b, SDL_Renderer* contexte)
* \brief   Affiche le bouton passé en paramètre
* \param[in] Bouton* b
* \param [in] SDL_Renderer* contexte
*/
void afficherBouton(Bouton* b, SDL_Renderer* contexte);

/**
* \fn enfoncerBouton(Bouton* b)
* \brief   Modifie la position du bouton de 3 pixels à droite et en bas
* \param[in] Bouton* b
*/
void enfoncerBouton(Bouton* b);

/**
* \fn desenfoncerBouton(Bouton* b)
* \brief   Remet le bouton en position initiale
* \param[in] Bouton* b
*/
void desenfoncerBouton(Bouton* b);

#endif