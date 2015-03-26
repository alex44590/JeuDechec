#include "defausse.h"


Defausse* creerDefausse(Couleur couleur){
	Defausse* defausse = (Defausse*)malloc(sizeof(Defausse));
	if (defausse == NULL){
		logPrint(ERREUR, "Allocation dynamique de la Defausse échouée");
	}

	defausse->couleur = couleur;
	defausse->dimension = TAILLE_DEFAUSSE;

	return defausse;
}


