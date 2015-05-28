#include "echiquier.h"
#include "piece.h"

Echiquier* creerEchiquier(ListDeplacement* l, Booleen ajouterPieces){
	Echiquier* echiquier;
	echiquier = malloc(sizeof(Echiquier));
	if (echiquier == NULL)
		logPrint(ERREUR, "Erreur lors de l'allocation de l'échiquier");
	logPrint(INFO, "Initialisation des cases de l'échiquier");
	int i, j;
	for (i = 0; i < 7; i += 2){
		for (j = 0; j < 7; j += 2){
			echiquier->tabCases[i][j] = creerCaseBlanche((IDCase){ i, j });
			echiquier->tabCases[i][j + 1] = creerCaseNoire(((IDCase){ i, j + 1 }));
		}
	}
	for (i = 1; i < 8; i += 2){
		for (j = 0; j < 7; j += 2){
			echiquier->tabCases[i][j + 1] = creerCaseBlanche((IDCase){ i, j + 1 });
			echiquier->tabCases[i][j] = creerCaseNoire(((IDCase){ i, j }));
		}
	}


	if (ajouterPieces == TRUE){
		logPrint(INFO, "Initialisation des pièces de l'échiquier");
		initAllPiece(echiquier->tabPieces, l);

		//On tague les cases sur lesquelles on a déposé des pièces comme occupées
		for (i = 0; i < 8; ++i){
			echiquier->tabCases[i][0]->occupee = TRUE;
			echiquier->tabCases[i][1]->occupee = TRUE;
			echiquier->tabCases[i][6]->occupee = TRUE;
			echiquier->tabCases[i][7]->occupee = TRUE;
			for (j = 2; j < 6; ++j){
				echiquier->tabCases[i][j]->occupee = FALSE;
			}
		}
	}
	else {
		//Si on crée un échiquier vide, on initialise tout le tableau de pièce à NULL
		for (i = 0; i < 8; ++i){
			for (j = 0; j < 8; ++j){
				echiquier->tabPieces[i][j] = NULL;
			}
		}
	}
	return echiquier;
}


void afficherEchiquier(Echiquier* echiquier, SDL_Renderer* contexte){
	int i, j;
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			afficherCase(echiquier->tabCases[i][j], contexte);
		}
	}
	afficherAllPiece(echiquier->tabPieces, contexte);
}
	
//Fonction utile pendant le développement du logiciel nous permettant de visualiser la matrice deplacementPossible dans un fichier texte
void enregisterEchiquier(Echiquier* e, char* nomFichierSortie){
	FILE* fichier = NULL;
	int i, j;

	fichier = fopen(nomFichierSortie, "w");

	if (fichier == NULL)
		logPrint(ERREUR, "Erreur lors de l'ouverture du fichier pour l'enregistrement de la matrice déplacement possible");
	if (e == NULL)
		logPrint(ERREUR, "Impossible d'enregistrer la matrice des deplacements possible dans un fichier s'il s'agit de l'élément NULL");

	fprintf(fichier, "Pieces :\n\n");
	for (j = 0; j < 8; ++j){
		for (i = 0; i < 8; ++i){
			if (e->tabPieces[i][j] != NULL)
				fprintf(fichier, "%c%c%d|", e->tabPieces[i][j]->idPiece.type, e->tabPieces[i][j]->idPiece.couleur, e->tabPieces[i][j]->idPiece.numero);
			else
				fprintf(fichier, " * |");
		}
		fprintf(fichier, "\n--------------------------------\n");
	}

	fprintf(fichier, "\n\nCases :\n\n");
	for (j = 0; j < 8; ++j){
		for (i = 0; i < 8; ++i){
			fprintf(fichier, " %d |", e->tabCases[i][j]->occupee);
		}
		fprintf(fichier, "\n--------------------------------\n");
	}
	fclose(fichier);
}