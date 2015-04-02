#ifndef DEPLACEMENTPOSSIBLE_H
#define DEPLACEMENTPOSSIBLE_H

#include "commun.h"
#include "echiquier.h"

//Taille de la matrice deplacement possible
#define LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE 8
#define HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE 8

/* Matrice qui repr�sente chaque case du tableau afin de savoir si le d�placement est possible
   0 = d�placement interdit
   1 = deplacement OK
*/

typedef struct {
	Piece* pieceConcernee; //Pi�ce dont on cherche � calculer les d�placements possibles
	int deplacementPossible[LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE][HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE];
	int deltaCavalier[2][8]; //Tableau 2 colonnes et 8 lignes contenant dans la colonne 0 les deltaX possibles du cavalier et dans la colonne 1 les deltaY associ�s
	int deltaRoi[2][8]; //Tableau 2 colonnes et 8 lignes contenant dans la colonne 0 les 8 deltaX possibles du roi et dans la colonne 1 les 8 deltaY associ�s
} DeplacementPossible;

DeplacementPossible* creerDeplacementPossible();
void calculerDeplacementPossible(Piece* p, Echiquier* e, DeplacementPossible* d, SDL_Renderer* contexte);
void enregisterMatriceDeplacementPossible(DeplacementPossible* d, char* nomFichierSortie);
void supprimerSurbrillanceDeplacementPossibles(DeplacementPossible* d, Echiquier* e, SDL_Renderer* contexte);
#endif