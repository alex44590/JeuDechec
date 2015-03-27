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


int main(int argc, char* argv[]){

	//Cr�ation ou r�initialisation du fichier de log "log.txt"
	logInit();


	//D�marrage de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		logPrint(ERREUR, "Erreur d'initialisation de la SDL");
		return EXIT_FAILURE; // On quitte le programme en cas d'erreur
	}
	logPrint(INFO, "Initialisation de la SDL");


	//Cr�ation de la fenetre
	SDL_Window* screen = SDL_CreateWindow("Jeu d'Echec Multijoueur",  
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		LARGEUR_FENETRE, HAUTEUR_FENETRE,
		0);


	//Chargement de l'icone
	SDL_Surface* icone = IMG_Load("Icone4.png"); 
	if (icone == NULL){
		logPrint(ERREUR, "Chargement de l'image pour l'icone �chou�");
		return EXIT_FAILURE;
	}
	logPrint(INFO, "Chargement de l'icone");
	SDL_SetWindowIcon(screen, icone); //Insertion de l'icone dans la fenetre


	//Cr�ation du contexte qui apparaitra dans la fenetre
	SDL_Renderer* contexte = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	logPrint(INFO, "Cr�ation du contexte graphique");
	if (contexte == NULL)
		logPrint(ERREUR, "Cr�ation du contexte �chou�");


	//Cr�ation de l'�chiquier 
	Echiquier* echiquier = NULL;
	logPrint(INFO, "Cr�ation de l'�chiquier");
	echiquier = creerEchiquier();
	if (echiquier == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de l'�chiquier");


	//Cr�ation des d�fausses
	logPrint(INFO, "Cr�ation de la d�fausse blanche");
	Defausse* defausseB = creerDefausse(BLANC);
	if (defausseB == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de la d�fausse blanche");

	logPrint(INFO, "Cr�ation de la d�fausse noire");
	Defausse* defausseN = creerDefausse(NOIR);
	if (defausseB == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de la d�fausse noire");


	//Cr�ation du plateau de jeu
	logPrint(INFO, "Cr�ation du plateau de jeu");
	PlateauDeJeu* plateau = creerPlateauDeJeu(echiquier, defausseB, defausseN);
	if (plateau == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du plateau de jeu");
	afficherPlateauDeJeu(contexte, plateau);


	//Cr�ation du menu
	logPrint(INFO, "Cr�ation du menu");
	Menu* menu = creerMenu();
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du menu");
	afficherMenu(menu, contexte);

	//Cr�ation du menu de droite (contenant les d�fausses)
	logPrint(INFO, "Cr�ation du menu de droite");
	MenuDroite* menuDroite = creerMenuDroite(defausseB, defausseN);
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du menuDroite");
	afficherFondMenuDroite(menuDroite, contexte);


	//Affichage des d�fausses
	logPrint(INFO, "Affichage de la d�fausse blanche");
	afficherDefausse(defausseB, contexte);
	logPrint(INFO, "Affichage de la d�fausse noire");
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
	

	Case* oldCase = plateau->echiquier->tabCases[0][0];
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;


		case SDL_MOUSEMOTION:
			if (event.motion.x > OFFSET_PLATEAU_GAUCHE &&
				event.motion.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE &&
				event.motion.y > OFFSET_PLATEAU_HAUT &&
				event.motion.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
			{
				if ((event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE != (oldPosSouris.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE ||
					(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE != (oldPosSouris.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE)
				{
					mettreEnSurbrillance(plateau->echiquier->tabCases[(event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE]);
					afficherCase(plateau->echiquier->tabCases[(event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE], contexte);
					supprimerSurbrillance(oldCase);
					afficherCase(oldCase, contexte);
					oldCase = plateau->echiquier->tabCases[(event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
					afficherAllPiece(echiquier->tabPieces, contexte);
				}
			}
			
			if (event.motion.x < OFFSET_PLATEAU_GAUCHE ||
				event.motion.x > LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE ||
				event.motion.y < OFFSET_PLATEAU_HAUT ||
				event.motion.y > HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
			{
				supprimerSurbrillance(oldCase);
				afficherCase(oldCase, contexte);
				afficherAllPiece(echiquier->tabPieces, contexte);

			}

			oldPosSouris.x = event.motion.x;
			oldPosSouris.y = event.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			//Traitement des boutons du menu
			for (i = 0; i<NB_BOUTON; i++){
				if (event.button.x > menu->tabBouton[i]->positionInit.x &&
					event.button.x < menu->tabBouton[i]->positionInit.x + menu->tabBouton[i]->dimension.largeur &&
					event.button.y > menu->tabBouton[i]->positionInit.y &&
					event.button.y < menu->tabBouton[i]->positionInit.y + menu->tabBouton[i]->dimension.hauteur)
				{
					enfoncerBouton(menu->tabBouton[i]);
					afficherMenu(menu, contexte);
				}
			} //Fin du traitement des boutons
			break;
		
		case SDL_MOUSEBUTTONUP:
			//On v�rifie que tous les boutons sont bien revenus � leur position initiale
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