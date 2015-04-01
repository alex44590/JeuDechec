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

	ListDeplacement *l = NULL;
	int posCurseur = 0;
	//Création ou réinitialisation du fichier de log "log.txt"
	logInit();
	createHistoryFile();

	printFileCurrentList(l, &posCurseur);
	logPrint(INFO, "salut");


	return 0;
}
