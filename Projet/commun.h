#ifndef COMMUN_H
#define COMMUN_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

#define LARGEUR_BARRE 40
#define LONGUEUR_BARRE 640
#define HAUTEUR_CASE 70 
#define LARGEUR_CASE 70
#define HAUTEUR_PIECE 64
#define LARGEUR_PIECE 64
#define TAILLE_CASE (Dimension){HAUTEUR_CASE, LARGEUR_CASE}

#define LARGEUR_MENU 300
#define LARGEUR_FENETRE (2*LARGEUR_BARRE + 8*LARGEUR_CASE + LARGEUR_MENU)
#define HAUTEUR_FENETRE (2*LARGEUR_BARRE + 8*LARGEUR_CASE)
#define HAUTEUR_MENU HAUTEUR_FENETRE

#define OFFSET_PLATEAU_GAUCHE  (LARGEUR_BARRE + LARGEUR_MENU)
#define OFFSET_PLATEAU_DROITE  LARGEUR_BARRE
#define OFFSET_PLATEAU_HAUT  LARGEUR_BARRE
#define OFFSET_PLATEAU_BAS  LARGEUR_BARRE

#define OFFSET_BARRE_GAUCHE  (OFFSET_PLATEAU_GAUCHE - LARGEUR_BARRE)
#define OFFSET_BARRE_DROITE (OFFSET_PLATEAU_GAUCHE + 8 * LARGEUR_CASE)	
#define OFFSET_BARRE_HAUT  (OFFSET_PLATEAU_HAUT - LARGEUR_BARRE)
#define OFFSET_BARRE_BAS  (OFFSET_PLATEAU_HAUT + 8 * HAUTEUR_CASE)

#define POSITION_FROM_ID(colonne,ligne) (Position){OFFSET_PLATEAU_GAUCHE + colonne*LARGEUR_CASE, LARGEUR_BARRE + ligne*HAUTEUR_CASE}
#define POSITION_FROM_ID_PIECE(colonne,ligne) (Position){OFFSET_PLATEAU_GAUCHE + colonne*LARGEUR_CASE + (LARGEUR_CASE-LARGEUR_PIECE)/2, LARGEUR_BARRE + ligne*HAUTEUR_CASE + (HAUTEUR_CASE-HAUTEUR_PIECE)/2}

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
	Couleur couleur;
	int numero;
}IDPiece;

typedef struct {
	Lettre colonne;
	Lettre ligne;
}IDCase;

#endif // !COMMUN_H
