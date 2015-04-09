#ifndef DEPLACEMENTPOSSIBLE_H
#define DEPLACEMENTPOSSIBLE_H

#include "commun.h"
#include "echiquier.h"

//Taille de la matrice deplacement possible
#define LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE 8
#define HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE 8

/* Matrice qui représente chaque case du tableau afin de savoir si le déplacement est possible
   0 = déplacement interdit
   1 = deplacement OK
   2 = déplacement OK en mangeant la pièce
*/

typedef struct {
	Piece* pieceConcernee; //Pièce dont on cherche à calculer les déplacements possibles
	int deplacementPossible[LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE][HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE];
} DeplacementPossible;

typedef struct{
	int deltaCavalier[2][8]; //Tableau 2 colonnes et 8 lignes contenant dans la colonne 0 les deltaX possibles du cavalier et dans la colonne 1 les deltaY associés
	int deltaRoi[2][8]; //Tableau 2 colonnes et 8 lignes contenant dans la colonne 0 les 8 deltaX possibles du roi et dans la colonne 1 les 8 deltaY associés
	int deltaTour[2][28]; //Tableau 2 colonnes et 28 lignes contenant dans la colonne 0 les 8 deltaX possibles de la tour et dans la colonne 1 les 8 deltaY associés
	int deltaFou[2][28]; //Tableau 2 colonnes et 28 lignes contenant dans la colonne 0 les 8 deltaX possibles du fou et dans la colonne 1 les 8 deltaY associés
	int deltaPionNoir[2][2]; //2 colonnes et 2 lignes contenant en colonne 0 les deltaX possibles du pion et les deltaY associés en c1  (ligne 1 -> Uniquement pour le 1er tour)
	int deltaPionBlanc[2][2]; //2 colonnes et 2 lignes contenant en colonne 0 les deltaX possibles du pion et les deltaY associés en c1  (ligne 1 -> Uniquement pour le 1er tour)
}VecteurDeplacement;


DeplacementPossible* creerDeplacementPossible();
VecteurDeplacement* creerVecteurDeplacement();
void calculerDeplacementPossible(Piece* p, Echiquier* e, DeplacementPossible* d, VecteurDeplacement* v, SDL_Renderer* contexte);
int mettreEnSurbrillanceCasesSiDeplacementPossible(Echiquier* e, DeplacementPossible* d, SDL_Renderer* contexte, int x, int y, int newx, int newy);
void enregisterMatriceDeplacementPossible(DeplacementPossible* d, char* nomFichierSortie);
void supprimerSurbrillanceDeplacementPossibles(DeplacementPossible* d, Echiquier* e, SDL_Renderer* contexte);
#endif