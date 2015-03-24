#include <stdio.h>
#include <stdlib.h>
#include <SDL2\SDL.h>
#include "case.h"
#include "plateau.h"
#include "commun.h"
#include "menu.h"
#include "piece.h"


void pause();

int main(int argc, char* argv[]){

	if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
		return EXIT_FAILURE; // On quitte le programme
	}

	SDL_Window* screen = SDL_CreateWindow("Jeu d'Echec Multijoueur", //Création de la fenetre 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		LARGEUR_FENETRE, HAUTEUR_FENETRE,
		0);

	SDL_Surface* icone = IMG_Load("Icone4.png"); //Chargement de l'icone
	SDL_SetWindowIcon(screen, icone); //Insertion de l'icone dans la fenetre
	SDL_Renderer* contexte = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Création du contexte qui apparaitra dans la fenetre

	Case* echiquier[8][8];
	creerPlateau(echiquier);
	afficherPlateau(echiquier, contexte);
	afficherCadre(contexte);

	Menu* menu = creerMenu();
	afficherMenu(menu, contexte);

	//Ajout de pieces
	Piece* tabPiece[32];
	initAllPiece(tabPiece);

	SDL_RenderPresent(contexte);


	//BOUCLE PRINCIPALE
	int continuer = 1;
	int i;
	SDL_Event event;
	Position oldPosSouris;
	oldPosSouris.x = 0;
	oldPosSouris.y = 0;
	


	Case* oldCase = echiquier[0][0];
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
					mettreEnSurbrillance(echiquier[(event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE]);
					afficherCase(echiquier[(event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE], contexte);
					supprimerSurbrillance(oldCase);
					afficherCase(oldCase, contexte);
					oldCase = echiquier[(event.motion.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.motion.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
				}
			}
			
			if (event.motion.x < OFFSET_PLATEAU_GAUCHE ||
				event.motion.x > LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE ||
				event.motion.y < OFFSET_PLATEAU_HAUT ||
				event.motion.y > HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
			{
				supprimerSurbrillance(oldCase);
				afficherCase(oldCase, contexte);

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
			//On vérifie que tous les boutons sont bien revenus à leur position initiale
			for (i = 0; i < NB_BOUTON; i++){
				if (menu->tabBouton[i]->enfonce == TRUE){
					desenfoncerBouton(menu->tabBouton[i]);
					afficherMenu(menu, contexte);
				}
			} // Fin de verif
			break;

		}
		
		afficherAllPiece(tabPiece, contexte);
		SDL_RenderPresent(contexte);
		SDL_Delay(10);
	}
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return EXIT_SUCCESS;
}