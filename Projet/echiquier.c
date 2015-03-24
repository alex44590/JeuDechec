#include "echiquier.h"

void initEchiquier(Echiquier* echiquier){
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
}


void afficherEchiquier(Echiquier echiquier, SDL_Renderer* contexte){
	int i, j;
	for (i = 0; i < 7; i += 2){
		for (j = 0; j < 7; j += 2){
			afficherCase(echiquier.tabCases[i][j], contexte);
			afficherCase(echiquier.tabCases[i][j + 1], contexte);
		}
	}
	for (i = 1; i < 8; i += 2){
		for (j = 0; j < 7; j += 2){
			afficherCase(echiquier.tabCases[i][j], contexte);
			afficherCase(echiquier.tabCases[i][j + 1], contexte);
		}
	}
}
	
