/**
* \file deplacementPossible
* \brief Gestions des d�placements des pi�ces
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
* D�finition des structures permettant le calcul des d�placements autoris�s d'une pi�ce
* Prototypes des fonctions de calcul de la matrice des d�placements possibles
* Gestion du Roque
* Calcul des situations d'�chec, d'�chec anticip� pour une pi�ce, du pat et de l'�chec et mat
*
*/

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
   2 = d�placement OK en mangeant la pi�ce
*/

typedef struct {
	Piece* pieceConcernee; //Pi�ce dont on cherche � calculer les d�placements possibles
	int deplacementPossible[LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE][HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE];
} DeplacementPossible;

typedef struct{
	int deltaCavalier[2][8]; //Tableau 2 colonnes et 8 lignes contenant dans la colonne 0 les deltaX possibles du cavalier et dans la colonne 1 les deltaY associ�s
	int deltaRoi[2][8]; //Tableau 2 colonnes et 8 lignes contenant dans la colonne 0 les 8 deltaX possibles du roi et dans la colonne 1 les 8 deltaY associ�s
	int deltaTour[2][28]; //Tableau 2 colonnes et 28 lignes contenant dans la colonne 0 les 8 deltaX possibles de la tour et dans la colonne 1 les 8 deltaY associ�s
	int deltaFou[2][28]; //Tableau 2 colonnes et 28 lignes contenant dans la colonne 0 les 8 deltaX possibles du fou et dans la colonne 1 les 8 deltaY associ�s
	int deltaPionNoir[2][2]; //2 colonnes et 2 lignes contenant en colonne 0 les deltaX possibles du pion et les deltaY associ�s en c1  (ligne 1 -> Uniquement pour le 1er tour)
	int deltaPionNoirPrise[2][2]; //2 colonnes et 2 lignes contenant en colonne 0 les deltaX possibles du pion pour manger et les deltaY associ�s en c1
	int deltaPionBlanc[2][2]; //2 colonnes et 2 lignes contenant en colonne 0 les deltaX possibles du pion et les deltaY associ�s en c1  (ligne 1 -> Uniquement pour le 1er tour)
	int deltaPionBlancPrise[2][2]; //2 colonnes et 2 lignes contenant en colonne 0 les deltaX possibles du pion pour manger et les deltaY associ�s en c1
}VecteurDeplacement;

typedef struct{
	Booleen roiDejaBouge[2];
	Booleen tourDejaBouge[2][2];
}ContexteRoque;

DeplacementPossible* creerDeplacementPossible();
VecteurDeplacement* creerVecteurDeplacement();
ContexteRoque* creerContexteRoque();
Booleen gererRoqueSiPossible(Piece* p1, Piece* p2, Echiquier* e, ContexteRoque* c, ListDeplacement* l);
int calculerDeplacementPossibleCaseParCase(Echiquier* e, DeplacementPossible* d, SDL_Renderer* contexte, int x, int y, int newx, int newy, Booleen surbrillance);
void calculerDeplacementPossible(Piece* p, Echiquier* e, DeplacementPossible* d, VecteurDeplacement* v, Booleen surbrillance, SDL_Renderer* contexte);
Booleen calculerEchec(Couleur c, Echiquier* e, DeplacementPossible* dEchec, VecteurDeplacement* v, IDCase* posRoi, SDL_Renderer* contexte);
Booleen calculerEchecAnticipe(Echiquier* e, Piece* p, Lettre colonneArrivee, Lettre ligneArrivee, DeplacementPossible* d, VecteurDeplacement* v, IDCase posRoi[], SDL_Renderer* contexte);
Booleen calculerEchecEtMatEtPat(Couleur c, Echiquier* e, DeplacementPossible* dEchecEtMat, DeplacementPossible* dEchecAnticipe, VecteurDeplacement* v, IDCase* posRoi, Booleen* pat, SDL_Renderer* contexte);
Booleen calculerPat(Couleur c, Echiquier* e, DeplacementPossible* dEchecEtMat, DeplacementPossible* dEchecAnticipe, VecteurDeplacement* v, IDCase* posRoi, Booleen* pat, SDL_Renderer* contexte);
void enregisterMatriceDeplacementPossible(DeplacementPossible* d, char* nomFichierSortie);
void supprimerSurbrillanceDeplacementPossibles(DeplacementPossible* d, Echiquier* e, SDL_Renderer* contexte);
void supprimerDeplacementPossibleEchecAnticipe(Echiquier* e, Piece* p, DeplacementPossible* d, DeplacementPossible* dEchecAnticipe, VecteurDeplacement* v, IDCase posRoi[], SDL_Renderer* contexte);
#endif