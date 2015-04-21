#include "joueur.h"

Joueur* creerJoueur(Couleur c){
	Joueur* j = NULL;
	j = (Joueur*)malloc(sizeof(Joueur));
	if (j == NULL)
		logPrint(ERREUR, "Allocation du joueur �chou�e");

	j->couleur = c;
	j->nbCoupsJoues = 0;
	j->nbVictoires = 0;

	j->pseudo = NULL;
	j->pseudo = (char*)malloc(TAILLE_MAX_NOM_JOUEUR*sizeof(char));
	if (j->pseudo == NULL)
		logPrint(ERREUR, "Allocation du pseudo du joueur �chou�e");

	return j;
}