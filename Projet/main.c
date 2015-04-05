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
	IDPiece P1 = { 'N', BLANC, 2 };
	IDCase D1 = { A, A };
	IDCase A1 = { B, B };
	ListDeplacement *l = malloc(sizeof(Deplacement));
	Deplacement Dep;
	if (l == NULL)
	{
		logPrint(ERREUR, "malloc pas bon");
	}
	Dep.currentPiece = P1;
	Dep.arrivee = A1;
	Dep.depart = D1;
	Dep.numeroDeplacement = 0;
	Dep.next = NULL;
	Dep.previous = NULL;

	l->current = &Dep;
	//l->current->currentPiece = P1;
	//l->current->arrivee = A1;
	//l->current->depart = D1;
	int posCurseur = 0;
	//Création ou réinitialisation du fichier de log "log.txt"
	logInit();
	createHistoryFile();

	printPiece(l,&posCurseur);
	printDepart(l,&posCurseur);
	//printFileCurrentList(l, &posCurseur);
	logPrint(INFO, "salut");


	return 0;
}
