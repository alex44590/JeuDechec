#include "case.h"

Case* creerCaseBlanche(IDCase id){
	Case* c = (Case*)malloc(sizeof(Case));
	c->couleurCase = BLANC;
	c->enSurbrillance = FALSE;
	c->identifiant = id;
	
	
	//c->imageCase = SDL_CreateRGBSurface(0, LARGEUR_CASE, HAUTEUR_CASE, 32, 0, 0, 0, 0); //(Si l'on veut une couleur unie)
	//SDL_FillRect(c->imageCase, NULL, SDL_MapRGB(c->imageCase->format, 255, 255, 255));

	c->imageCaseNormale = IMG_Load("IMBLt.jpg");
	c->imageCaseSurbrillance = IMG_Load("IMBLSt.jpg");
	c->imageCaseActuelle = c->imageCaseNormale;

	c->occupee = FALSE;
	//c->pieceOccupante = NULL;
	c->position = POSITION_FROM_ID(id.colonne, id.ligne);
	c->dimension = TAILLE_CASE;
	return c;
}

Case* creerCaseNoire(IDCase id){
	Case* c = (Case*)malloc(sizeof(Case));
	c->couleurCase = NOIR;
	c->enSurbrillance = FALSE;
	c->identifiant = id;

	//c->imageCase = SDL_CreateRGBSurface(0, LARGEUR_CASE, HAUTEUR_CASE, 32, 0, 0, 0, 0);
	//SDL_FillRect(c->imageCase, NULL, SDL_MapRGB(c->imageCase->format, 0, 0, 0));
	
	c->imageCaseNormale = IMG_Load("IMBFt.jpg");
	c->imageCaseSurbrillance = IMG_Load("IMBFSt.jpg");
	c->imageCaseActuelle = c->imageCaseNormale;

	c->occupee = FALSE;
	//c->pieceOccupante = NULL;
	c->position = POSITION_FROM_ID(id.colonne, id.ligne);
	c->dimension = TAILLE_CASE;
	return c;
}

void afficherCase(Case* c, SDL_Renderer* contexte){
	SDL_Texture* textureCase = SDL_CreateTextureFromSurface(contexte, c->imageCaseActuelle);
	SDL_Rect positionAffichage;
	positionAffichage.x = c->position.x;
	positionAffichage.y = c->position.y;
	positionAffichage.w = c->dimension.largeur;
	positionAffichage.h = c->dimension.hauteur;
	SDL_RenderCopy(contexte, textureCase, NULL, &positionAffichage);
	SDL_DestroyTexture(textureCase);
	SDL_free(&positionAffichage);
}

void mettreEnSurbrillance(Case* c, SDL_Renderer* contexte){
	if (c == NULL)
		logPrint(ERREUR, "Impossible de mettre en surbrillance l'élément nul !");
	c->enSurbrillance = TRUE;
	c->imageCaseActuelle = c->imageCaseSurbrillance;
	afficherCase(c, contexte);
}

void supprimerSurbrillance(Case* c, SDL_Renderer* contexte){
	if (c == NULL)
		logPrint(ERREUR, "Impossible de supprimer la surbrillance de l'élément nul !");
	c->enSurbrillance = FALSE;
	c->imageCaseActuelle = c->imageCaseNormale;
	afficherCase(c, contexte);
}
