#include "echiquier.h"
#include "piece.h"

Echiquier* creerEchiquier(){
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

	logPrint(INFO, "Initialisation des pièces de l'échiquier");
	initAllPiece(echiquier->tabPieces);
	
	//On tague les cases sur lesquelles on a déposé des pièces comme occupées
	for (i = 0; i < 8; ++i){
		echiquier->tabCases[0][i]->occupee = TRUE;
		echiquier->tabCases[1][i]->occupee = TRUE;
		echiquier->tabCases[6][i]->occupee = TRUE;
		echiquier->tabCases[7][i]->occupee = TRUE;
		for (j = 2; j < 6; ++j){
			echiquier->tabCases[j][i]->occupee = FALSE;
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
	
