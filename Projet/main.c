#include <stdio.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include "case.h"
#include "plateau.h"
#include "commun.h"
#include "menu.h"
#include "piece.h"
#include "echiquier.h"
#include "plateauDeJeu.h"
#include "listeDeplacement.h"


int main(int argc, char* argv[]){
	char id[4] ="TN1";

	IDPiece P1 = { 'T', 'N', '0', id};
	IDCase D1 = { A, A };
	IDCase A1 = { B, B };
	IDPiece P2 = { 'T', 'N', '1', id };
	IDCase D2 = { C, C };
	IDCase A2 = { D, D };
	IDPiece P3 = { 'T', 'N', '2', id };
	IDCase D3 = { E, E };
	IDCase A3 = { F, F };
	ListDeplacement *l = malloc(sizeof(Deplacement));


	Deplacement *Dep3= newDeplacement(P3, D3, A3, 2, NULL, NULL);
	Deplacement *Dep2= newDeplacement(P2, D2, A2, 1, NULL, NULL);
	Deplacement *Dep = newDeplacement(P1, D1, A1, 0, NULL, NULL);
	int posCurseur = 0;

	if (l == NULL)
	{
		logPrint(ERREUR, "malloc pas bon");
	}
	
	l->first = l->current=l->last=Dep;
	//insertFirst(l, P1, D1, A1, 0);
	//l->last = Dep3;
	createNewDeplacement(l, P2, D2, A2, 1);
	createNewDeplacement(l, P3, D3, A3, 2);
	setOnFirst(l);

	//Création ou réinitialisation du fichier de log "log.txt"
	logInit();
	createHistoryFile();


		printFileCurrentDeplacement(l, &posCurseur);
		next(l);
		//posCurseur -= 14;
		printFileCurrentDeplacement(l, &posCurseur);
		next(l);
		printFileCurrentDeplacement(l, &posCurseur);
	

	logPrint(INFO, id);



	return 0;
}
