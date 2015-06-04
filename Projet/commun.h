/**
* \file commun.h
* \brief Structures partagées et Macro-définitions communes
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* Fichier regroupant les structures et énumérations communes à plusieurs autres fichiers d'en tête
*
*/

#ifndef COMMUN_H
#define COMMUN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "log.h"


#define LARGEUR_BARRE 40
#define LONGUEUR_BARRE 640
#define HAUTEUR_CASE 70 
#define LARGEUR_CASE 70
#define HAUTEUR_PIECE 64
#define LARGEUR_PIECE 64
#define TAILLE_CASE (Dimension){HAUTEUR_CASE, LARGEUR_CASE}

#define LARGEUR_MENU 300
#define LARGEUR_MENU_DROITE 320
#define HAUTEUR_FENETRE (2*LARGEUR_BARRE + 8*LARGEUR_CASE)
#define LARGEUR_FENETRE (2*LARGEUR_BARRE + 8*LARGEUR_CASE + LARGEUR_MENU + LARGEUR_MENU_DROITE)
#define HAUTEUR_MENU HAUTEUR_FENETRE

#define OFFSET_PLATEAU_GAUCHE  (LARGEUR_BARRE + LARGEUR_MENU)
#define OFFSET_PLATEAU_DROITE  (LARGEUR_BARRE + LARGEUR_MENU_DROITE)
#define OFFSET_PLATEAU_HAUT  LARGEUR_BARRE
#define OFFSET_PLATEAU_BAS  LARGEUR_BARRE

#define OFFSET_BARRE_GAUCHE  (OFFSET_PLATEAU_GAUCHE - LARGEUR_BARRE)
#define OFFSET_BARRE_DROITE (OFFSET_PLATEAU_GAUCHE + 8 * LARGEUR_CASE)	
#define OFFSET_BARRE_HAUT  (OFFSET_PLATEAU_HAUT - LARGEUR_BARRE)
#define OFFSET_BARRE_BAS  (OFFSET_PLATEAU_HAUT + 8 * HAUTEUR_CASE)

#define POSITION_FROM_ID(colonne,ligne) (Position){OFFSET_PLATEAU_GAUCHE + colonne*LARGEUR_CASE, LARGEUR_BARRE + ligne*HAUTEUR_CASE}
#define POSITION_FROM_ID_PIECE(colonne,ligne) (Position){OFFSET_PLATEAU_GAUCHE + colonne*LARGEUR_CASE + (LARGEUR_CASE-LARGEUR_PIECE)/2, LARGEUR_BARRE + ligne*HAUTEUR_CASE + (HAUTEUR_CASE-HAUTEUR_PIECE)/2}

#define HAUTEUR_MENU_DROITE HAUTEUR_FENETRE
#define TAILLE_MENU_DROITE (Dimension){HAUTEUR_MENU_DROITE, LARGEUR_MENU_DROITE} 

#define POSITION_MENU_DROITE (Position){LARGEUR_MENU+2*LARGEUR_BARRE+8*LARGEUR_CASE, 0}

#define HAUTEUR_DEFAUSSE 92
#define LARGEUR_DEFAUSSE 300
#define TAILLE_DEFAUSSE (Dimension){HAUTEUR_DEFAUSSE, LARGEUR_DEFAUSSE}
#define POSITION_DEFAUSSE_NOIRE (Position){LARGEUR_MENU+2*LARGEUR_BARRE+8*LARGEUR_CASE+(LARGEUR_MENU_DROITE-LARGEUR_DEFAUSSE)/2, 14}
#define POSITION_DEFAUSSE_BLANCHE (Position){LARGEUR_MENU+2*LARGEUR_BARRE+8*LARGEUR_CASE+(LARGEUR_MENU_DROITE-LARGEUR_DEFAUSSE)/2, HAUTEUR_FENETRE-20-HAUTEUR_DEFAUSSE}

#define HAUTEUR_RESERVE 75
#define LARGEUR_RESERVE 280
#define X_RESERVE (LARGEUR_MENU-LARGEUR_RESERVE)/2
#define Y_RESERVE_NOIRE 335
#define Y_RESERVE_BLANCHE 425
#define TAILLE_RESERVE (Dimension){HAUTEUR_RESERVE, LARGEUR_RESERVE}
#define POSITION_RESERVE_NOIRE (Position){X_RESERVE, Y_RESERVE_NOIRE}
#define POSITION_RESERVE_BLANCHE (Position){X_RESERVE, Y_RESERVE_BLANCHE}

#define LARGEUR_PIECE_RESERVE 30
#define HAUTEUR_PIECE_RESERVE 30
#define OFFSET_GAUCHE_PIECE_RESERVE 24
#define OFFSET_HAUT_PIECE_RESERVE 6
#define LARGEUR_ESPACE_PIECE_RESERVE (-1)
#define HAUTEUR_ESPACE_PIECE_RESERVE 1

/**
* \enum Booléen
* \brief  Les valeurs possibles du booléen
*/
typedef enum { FALSE, TRUE }Booleen;

/**
* \enum Couleur
* \brief  Les couleurs possibles
*/
typedef enum{ BLANC, NOIR }Couleur;

/**
* \enum Lettre
* \brief  Les lettres correspondant aux colonnes de l'échiquier
*/
typedef enum{ A, B, C, D, E, F, G, H }Lettre;

/**
* \struct Dimension
* \brief  Contient la largeur et la hauteur
*/
typedef struct {
	short int hauteur;
	short int largeur;
}Dimension;

/**
* \struct Position
* \brief  Contient les coordonnées x et y 
*/
typedef struct {
	short int x;
	short int y;
}Position;

/**
* \struct IDPiece
* \brief  Contient le type et la couleur de la pièce ainsi que le numéro de la pièce
*			et une chaine de caractère qui regroupe les trois paramètres	
*/
typedef struct {
	char type;
	char couleur;
	char numero;
	char id[4]; //Id complet de la pièce sous la forme TN0 pour la 1ère Tour Noire, avec un \0 en 4ème caractère pour pouvoir utiliser les fct de string.h 
}IDPiece;

/**
* \struct IDCase
* \brief  Contient la ligne et la colonne auxquelles appartient la case 
*/
typedef struct {
	Lettre colonne;
	Lettre ligne;
}IDCase;

/**
* \fn afficherImage(SDL_Surface* image, Position p, Dimension d, SDL_Renderer* contexte)
* \brief     Méthode générique d'affichage d'image
* \param[in]  image : image à afficher
* \param [in] p : position de l'image 
* \param [in] d : dimension de l'image
* \param [in] contexte : contexte graphique
*/
void afficherImage(SDL_Surface* image, Position p, Dimension d, SDL_Renderer* contexte);


#endif // !COMMUN_H
