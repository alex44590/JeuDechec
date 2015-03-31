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
#include "menuDroite.h"

#define MOUVEMENT_SOURIS_INTERIEUR_ECHIQUIER (event.motion.x > OFFSET_PLATEAU_GAUCHE && event.motion.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && event.motion.y > OFFSET_PLATEAU_HAUT && event.motion.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
#define MOUVEMENT_SOURIS_EXTERIEUR_ECHIQUIER (event.motion.x < OFFSET_PLATEAU_GAUCHE || event.motion.x > LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE || event.motion.y < OFFSET_PLATEAU_HAUT || event.motion.y > HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
#define CLIC_DOWN_SOURIS_SUR_BOUTON_MENU_GAUCHE (event.button.x > menu->tabBouton[i]->positionInit.x && event.button.x < menu->tabBouton[i]->positionInit.x + menu->tabBouton[i]->dimension.largeur && event.button.y > menu->tabBouton[i]->positionInit.y && event.button.y < menu->tabBouton[i]->positionInit.y + menu->tabBouton[i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER (event.button.x > OFFSET_PLATEAU_GAUCHE && event.button.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && event.button.y > OFFSET_PLATEAU_HAUT && event.button.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)


int main(int argc, char* argv[]){

	//Création ou réinitialisation du fichier de log "log.txt"
	logInit();


	//Démarrage de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		logPrint(ERREUR, "Erreur d'initialisation de la SDL");
		return EXIT_FAILURE; // On quitte le programme en cas d'erreur
	}
	logPrint(INFO, "Initialisation de la SDL");


	//Création de la fenetre
	SDL_Window* screen = SDL_CreateWindow("Jeu d'Echec Multijoueur",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		LARGEUR_FENETRE, HAUTEUR_FENETRE,
		0);


	//Chargement de l'icone
	SDL_Surface* icone = IMG_Load("Icone4.png");
	if (icone == NULL){
		logPrint(ERREUR, "Chargement de l'image pour l'icone échoué");
		return EXIT_FAILURE;
	}
	logPrint(INFO, "Chargement de l'icone");
	SDL_SetWindowIcon(screen, icone); //Insertion de l'icone dans la fenetre


	//Création du contexte qui apparaitra dans la fenetre
	SDL_Renderer* contexte = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	logPrint(INFO, "Création du contexte graphique");
	if (contexte == NULL)
		logPrint(ERREUR, "Création du contexte échoué");


	//Création de l'échiquier 
	Echiquier* echiquier = NULL;
	logPrint(INFO, "Création de l'échiquier");
	echiquier = creerEchiquier();
	if (echiquier == NULL)
		logPrint(ERREUR, "Echec de la création de l'échiquier");


	//Création des défausses
	logPrint(INFO, "Création de la défausse blanche");
	Defausse* defausseB = creerDefausse(BLANC);
	if (defausseB == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse blanche");

	logPrint(INFO, "Création de la défausse noire");
	Defausse* defausseN = creerDefausse(NOIR);
	if (defausseB == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse noire");


	//Création du plateau de jeu
	logPrint(INFO, "Création du plateau de jeu");
	PlateauDeJeu* plateau = creerPlateauDeJeu(echiquier, defausseB, defausseN);
	if (plateau == NULL)
		logPrint(ERREUR, "Echec de la création du plateau de jeu");
	afficherPlateauDeJeu(contexte, plateau);


	//Création du menu
	logPrint(INFO, "Création du menu");
	Menu* menu = creerMenu();
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la création du menu");
	afficherMenu(menu, contexte);

	//Création du menu de droite (contenant les défausses)
	logPrint(INFO, "Création du menu de droite");
	MenuDroite* menuDroite = creerMenuDroite(defausseB, defausseN);
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la création du menuDroite");
	afficherFondMenuDroite(menuDroite, contexte);


	//Affichage des défausses
	logPrint(INFO, "Affichage de la défausse blanche");
	afficherDefausse(defausseB, contexte);
	logPrint(INFO, "Affichage de la défausse noire");
	afficherDefausse(defausseN, contexte);


	SDL_RenderPresent(contexte);


	//BOUCLE PRINCIPALE 
	logPrint(INFO, "Lancement de la boucle principale du jeu");
	int continuer = 1;
	int i;
	SDL_Event event;
	Position oldPosSouris;
	oldPosSouris.x = 0;
	oldPosSouris.y = 0;

	Case* oldCasePointee = plateau->echiquier->tabCases[0][0];
	Case* casePointee = plateau->echiquier->tabCases[0][0];
	IDCase idCasePointee = casePointee->identifiant;
	IDCase idOldCasePointee = oldCasePointee->identifiant;

	Piece* pieceSelectionnee = NULL;

	Case* caseSelectionnee = NULL;
	IDCase idCaseSelectionnee;

	int j = 0;

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;


		case SDL_MOUSEMOTION:
			if (MOUVEMENT_SOURIS_INTERIEUR_ECHIQUIER){

				//Calcul de la case visée par la souris et de son id
				casePointee = plateau->echiquier->tabCases[(event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
				idCasePointee = casePointee->identifiant;

				if ((event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE != (oldPosSouris.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE ||
					(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE != (oldPosSouris.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE)
				{
					//Mise à jour de la couleur de la case puis réaffichage de la pièce
					mettreEnSurbrillance(casePointee, contexte);
					if (echiquier->tabPieces[idCasePointee.colonne][idCasePointee.ligne] != NULL)
						afficherPiece(echiquier->tabPieces[idCasePointee.colonne][idCasePointee.ligne], contexte);

					supprimerSurbrillance(oldCasePointee, contexte);
					if (echiquier->tabPieces[idOldCasePointee.colonne][idOldCasePointee.ligne] != NULL)
						afficherPiece(echiquier->tabPieces[idOldCasePointee.colonne][idOldCasePointee.ligne], contexte);

					oldCasePointee = casePointee;
					idOldCasePointee = oldCasePointee->identifiant;
				}
			}

			if (MOUVEMENT_SOURIS_EXTERIEUR_ECHIQUIER)
			{
				supprimerSurbrillance(oldCasePointee, contexte);
				if (echiquier->tabPieces[idOldCasePointee.colonne][idOldCasePointee.ligne] != NULL)
					afficherPiece(echiquier->tabPieces[idOldCasePointee.colonne][idOldCasePointee.ligne], contexte);

			}

			oldPosSouris.x = event.motion.x;
			oldPosSouris.y = event.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			//Traitement des boutons du menu
			for (i = 0; i < NB_BOUTON; i++){
				if (CLIC_DOWN_SOURIS_SUR_BOUTON_MENU_GAUCHE)
				{
					enfoncerBouton(menu->tabBouton[i]);
					afficherMenu(menu, contexte);
				}
			} //Fin du traitement des boutons
			break;

		case SDL_MOUSEBUTTONUP:
			//On vérifie que tous les boutons sont bien revenus à leur position initiale
			for (i = 0; i < NB_BOUTON; i++){
				if (menu->tabBouton[i]->enfonce == TRUE){
					desenfoncerBouton(menu->tabBouton[i]);
					afficherMenu(menu, contexte);
				}
			} // Fin de verif
			break;

		}

		SDL_RenderPresent(contexte);
		SDL_Delay(10);
	}
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return EXIT_SUCCESS;
}