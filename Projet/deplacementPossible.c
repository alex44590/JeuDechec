#include "deplacementPossible.h"

DeplacementPossible* creerDeplacementPossible(){
	DeplacementPossible* d = (DeplacementPossible *)malloc(sizeof(DeplacementPossible));
	if (d == NULL)
		logPrint(ERREUR, "Allocation de la m�moire pour la structure DeplacementPossible �chou�e...");
	int i;
	int j;
	//En th�orie pas besoin d'initialiser � 0 mais bon...
	for (i = 0; i < LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE; ++i){
		for (j = 0; j < HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE; ++j){
			d->deplacementPossible[i][j] = 0;
		}
	}
	//Cr�ation du delta cavalier (pas trouv� de m�thode plus simple qui marche...)
	//(d->deltaCavalier) = (int[2][8]){ { 2, 2, 1, -1, -2, -2, -1, 1 }, { 1, -1, -2, -2, -1, 1, 2, 2 } }; //Marche pas ...
	d->deltaCavalier[0][0] = 2;
	d->deltaCavalier[1][0] = -1;
	d->deltaCavalier[0][1] = 2;
	d->deltaCavalier[1][1] = 1;
	d->deltaCavalier[0][2] = 1;
	d->deltaCavalier[1][2] = 2;
	d->deltaCavalier[0][3] = -1;
	d->deltaCavalier[1][3] = 2;
	d->deltaCavalier[0][4] = -2;
	d->deltaCavalier[1][4] = 1;
	d->deltaCavalier[0][5] = -2;
	d->deltaCavalier[1][5] = -1;
	d->deltaCavalier[0][6] = -1;
	d->deltaCavalier[1][6] = -2;
	d->deltaCavalier[0][7] = 1;
	d->deltaCavalier[1][7] = -2;
	d->pieceConcernee = NULL;
	return d;

}

void calculerDeplacementPossible(Piece* p, Echiquier* e, DeplacementPossible* d){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de calculer les d�placements possible de l'�l�ment NULL");
	int x = p->idPosition.colonne;//idPosition pi�ce colonne
	int y = p->idPosition.ligne;//idPosition pi�ce ligne
	d->pieceConcernee = p;
	int newx;
	int newy;
	int i,j; //Variable de boucle

	switch (p->idPiece.type){
	case 'C':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet � 0 toute la matrice
		for (i = 0; i < 8; ++i){
			newx = x + d->deltaCavalier[0][i];
			newy = y + d->deltaCavalier[1][i];
			if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == FALSE){
				d->deplacementPossible[newx][newy] = 1;
			}
		}
		break;
		
	default:
		for (i = 0; i < 8; ++i){
			for (j = 0; j < 8; ++j){
				d->deplacementPossible[j][i] = 1;
			}
		}
		break;
	}//End switch
}

//Fonction utile pendant le d�veloppement du logiciel nous permettant de visualiser la matrice deplacementPossible dans un fichier texte
void enregisterMatriceDeplacementPossible(DeplacementPossible* d, char* nomFichierSortie){
	FILE* fichier = NULL;
	int i, j;

	fichier = fopen(nomFichierSortie, "w");

	if (fichier == NULL)
		logPrint(ERREUR, "Erreur lors de l'ouverture du fichier pour l'enregistrement de la matrice d�placement possible");
	if (d == NULL)
		logPrint(ERREUR, "Impossible d'enregistrer la matrice des deplacements possible dans un fichier s'il s'agit de l'�l�ment NULL");
	if (d->pieceConcernee == NULL)
		logPrint(ERREUR, "Impossible d'enregistrer la matrice des deplacements possible dans un fichier car la piece concernee dans le deplacement vaut NULL");

	fprintf(fichier, "Piece concernee : %s\n\n", d->pieceConcernee->idPiece.id);
	for (j = 0; j < 8; ++j){
		for (i = 0; i < 8; ++i){
			fprintf(fichier, "%d", d->deplacementPossible[i][j]);
		}
		fprintf(fichier, "\n");
	}
	fclose(fichier);
}