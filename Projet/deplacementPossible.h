#ifndef DEPLACEMENTPOSSIBLE_H
#define DEPLACEMENTPOSSIBLE_H

#define LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE 8
#define HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE 8

/* Matrice qui représente chaque case du tableau afin de savoir si le déplacement est possible
   0 = déplacement interdit
   1 = deplacement Blanc OK
   2 = deplacement Noir OK */

typedef struct {
	short int deplacementPossible[LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE][HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE];
} DeplacementPossible;

#endif