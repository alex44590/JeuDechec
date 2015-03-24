#include "plateauDeJeu.h"

PlateauDeJeu* creerPlateauDeJeu(Echiquier* echiquier, Defausse* defausseB, Defausse* defausseN){
	PlateauDeJeu* plateau;
	plateau = malloc(sizeof(PlateauDeJeu));
	
	plateau->bordureG = IMG_Load("BarVG.png");
	plateau->bordureD = IMG_Load("BarVD.png");
	plateau->bordureH = IMG_Load("BarHH.png");
	plateau->bordureB = IMG_Load("BarHB.png");

	plateau->echiquier = echiquier;
	plateau->defausseBlanc = defausseB;
	plateau->defausseNoir = defausseN;

	return plateau;
}


void afficherBordures(SDL_Renderer* contexte, PlateauDeJeu* plateau){
	SDL_Texture* textBarVG = SDL_CreateTextureFromSurface(contexte, plateau->bordureG);
	SDL_Rect positionAffichage;
	positionAffichage.x = OFFSET_BARRE_GAUCHE;
	positionAffichage.y = OFFSET_BARRE_HAUT;
	positionAffichage.w = LARGEUR_BARRE;
	positionAffichage.h = LONGUEUR_BARRE;
	SDL_RenderCopy(contexte, textBarVG, NULL, &positionAffichage);
	SDL_DestroyTexture(textBarVG);

	SDL_Texture* textBarVD = SDL_CreateTextureFromSurface(contexte, plateau->bordureD);
	positionAffichage.x = OFFSET_BARRE_DROITE;
	SDL_RenderCopy(contexte, textBarVD, NULL, &positionAffichage);
	SDL_DestroyTexture(textBarVD);

	SDL_Texture* textBarHH = SDL_CreateTextureFromSurface(contexte, plateau->bordureH);
	positionAffichage.x = OFFSET_BARRE_GAUCHE;
	positionAffichage.w = LONGUEUR_BARRE;
	positionAffichage.h = LARGEUR_BARRE;
	SDL_RenderCopy(contexte, textBarHH, NULL, &positionAffichage);
	SDL_DestroyTexture(textBarHH);

	SDL_Texture* textBarHB = SDL_CreateTextureFromSurface(contexte, plateau->bordureB);
	positionAffichage.y = OFFSET_BARRE_BAS;
	SDL_RenderCopy(contexte, textBarHB, NULL, &positionAffichage);
	SDL_DestroyTexture(textBarHH);
}


void afficherPlateauDeJeu(SDL_Renderer* contexte, PlateauDeJeu* plateau){
	afficherBordures(contexte, plateau);
	afficherEchiquier(plateau->echiquier, contexte);
}
