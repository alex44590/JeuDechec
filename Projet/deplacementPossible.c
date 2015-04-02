#include "deplacementPossible.h"

DeplacementPossible* creerDeplacementPossible(){
	DeplacementPossible* d = (DeplacementPossible *)malloc(sizeof(DeplacementPossible));
	if (d == NULL)
		logPrint(ERREUR, "Allocation de la mémoire pour la structure DeplacementPossible échouée...");
	int i;
	int j;

	d->pieceConcernee = NULL;

	//En théorie pas besoin d'initialiser à 0 mais bon...
	for (i = 0; i < LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE; ++i){
		for (j = 0; j < HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE; ++j){
			d->deplacementPossible[i][j] = 0;
		}
	}

	//Création du delta cavalier (pas trouvé de méthode plus simple qui marche...)
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

	//Création du delta roi
	d->deltaRoi[0][0] = 1;
	d->deltaRoi[1][0] = -1;
	d->deltaRoi[0][1] = 1;
	d->deltaRoi[1][1] = 0;
	d->deltaRoi[0][2] = 1;
	d->deltaRoi[1][2] = 1;
	d->deltaRoi[0][3] = 0;
	d->deltaRoi[1][3] = 1;
	d->deltaRoi[0][4] = -1;
	d->deltaRoi[1][4] = 1;
	d->deltaRoi[0][5] = -1;
	d->deltaRoi[1][5] = 0;
	d->deltaRoi[0][6] = -1;
	d->deltaRoi[1][6] = -1;
	d->deltaRoi[0][7] = 0;
	d->deltaRoi[1][7] = -1;

	return d;

}

void calculerDeplacementPossible(Piece* p, Echiquier* e, DeplacementPossible* d, SDL_Renderer* contexte){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de calculer les déplacements possible de l'élément NULL");
	int x = p->idPosition.colonne;//idPosition pièce colonne
	int y = p->idPosition.ligne;//idPosition pièce ligne
	d->pieceConcernee = p;
	int newx;
	int newy;
	int i,j; //Variable de boucle

	switch (p->idPiece.type){
	case 'C':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice
		for (i = 0; i < 8; ++i){
			newx = x + d->deltaCavalier[0][i];
			newy = y + d->deltaCavalier[1][i];
			if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == FALSE){
				d->deplacementPossible[newx][newy] = 1;
				//On met en surbrillance les cases où l'on peut se déplacer
				mettreEnSurbrillance(e->tabCases[newx][newy], contexte);
				if (e->tabPieces[newx][newy] != NULL)
					afficherPiece(e->tabPieces[newx][newy], contexte);
			}
		}
		break;

	case 'R':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice
		for (i = 0; i < 8; ++i){
			newx = x + d->deltaRoi[0][i];
			newy = y + d->deltaRoi[1][i];
			if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == FALSE){
				d->deplacementPossible[newx][newy] = 1;
				//On met en surbrillance les cases où l'on peut se déplacer
				mettreEnSurbrillance(e->tabCases[newx][newy], contexte);
				if (e->tabPieces[newx][newy] != NULL)
					afficherPiece(e->tabPieces[newx][newy], contexte);
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

//Fonction utile pendant le développement du logiciel nous permettant de visualiser la matrice deplacementPossible dans un fichier texte
void enregisterMatriceDeplacementPossible(DeplacementPossible* d, char* nomFichierSortie){
	FILE* fichier = NULL;
	int i, j;

	fichier = fopen(nomFichierSortie, "w");

	if (fichier == NULL)
		logPrint(ERREUR, "Erreur lors de l'ouverture du fichier pour l'enregistrement de la matrice déplacement possible");
	if (d == NULL)
		logPrint(ERREUR, "Impossible d'enregistrer la matrice des deplacements possible dans un fichier s'il s'agit de l'élément NULL");
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


//supprime la surbrillance de toutes les cases de l'échiquier et réaffiche les pièces s'il y en a sur les cases dont on a supprimé la surbrillance
void supprimerSurbrillanceDeplacementPossibles(DeplacementPossible* d, Echiquier* e, SDL_Renderer* contexte){
	if (d == NULL)
		logPrint(AVERTISSEMENT, "Impossible de supprimer la surbrillances des cases où le déplacement est possible si l'objet DeplacementPossible est NULL");
	else{
		int i, j;
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				if (d->deplacementPossible[j][i] == 1){
					supprimerSurbrillance(e->tabCases[j][i], contexte);
					if (e->tabPieces[j][i] != NULL)
						afficherPiece(e->tabPieces[j][i], contexte);
				}
			}
		}
	}
}