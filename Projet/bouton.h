/**
* \file bouton.h
* \brief Gestions des boutons
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Prototypes des fonctions de cr�ations, modifications et affichage des diff�rents boutons du jeu
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
#define NB_BOUTON_MREG 1 // Menu r�gles
#define NB_BOUTON_REGLES 2 //Fenetre r�gles

/**
* \enum idBouton
* \brief      Type du bouton cr��
*/
typedef enum { ENTRAINEMENT, DEUXJOUEURS, OPTION, REGLES, ACCUEIL, JOUER, PAUSE, REGLESUIVANTE, REGLEPRECEDENTE, RETOUR }idBouton;


/**
* \struct Bouton
* \brief  Contient l'ID du bouton, l'image correspondante, sa position initiale et actuelle, 
*		  ses dimensions et un bool�en pour savoir si le bouton est enfonc�
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
* \brief      Cr�e un bouton
* \param[in] cible : type de bouton � cr�er
* \param [in] nomImage: pointeur vers l'image � charger
* \return   Pointeur vers le bouton cr��
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
* \brief   Affiche le bouton pass� en param�tre
* \param[in] b : pointeur vers le bouton � afficher
* \param [in] contexte : contexte graphique
*/
void afficherBouton(Bouton* b, SDL_Renderer* contexte);

/**
* \fn enfoncerBouton(Bouton* b)
* \brief   Modifie la position du bouton de 3 pixels � droite et en bas
* \param[in] b : pointeur vers le bouton � envoyer
*/
void enfoncerBouton(Bouton* b);

/**
* \fn desenfoncerBouton(Bouton* b)
* \brief   Remet le bouton en position initiale
* \param[in] b : pointeur vers le bouton � relacher
*/
void desenfoncerBouton(Bouton* b);

#endif