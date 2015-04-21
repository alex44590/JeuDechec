#ifndef COMMUN_H
#define COMMUN_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "log.h"
#include <string.h>

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

typedef enum { FALSE, TRUE }Booleen;
typedef enum{ BLANC, NOIR }Couleur;
typedef enum{ A, B, C, D, E, F, G, H }Lettre;

typedef struct {
	short int hauteur;
	short int largeur;
}Dimension;

typedef struct {
	short int x;
	short int y;
}Position;

typedef struct {
	char type;
	char couleur;
	char numero;
	char id[4]; //Id complet de la pièce sous la forme TN0 pour la 1ère Tour Noire, avec un \0 en 4ème caractère pour pouvoir utiliser les fct de string.h 
}IDPiece;

typedef struct {
	Lettre colonne;
	Lettre ligne;
}IDCase;

#endif // !COMMUN_H
