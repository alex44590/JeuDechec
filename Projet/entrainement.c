#include "entrainement.h"

Reserve* creerReserve(Couleur couleur){
	Reserve* reserve = (Reserve*)malloc(sizeof(Reserve));
	if (reserve == NULL){
		logPrint(ERREUR, "Allocation dynamique de la Reserve �chou�e");
	}

	reserve->couleur = couleur;
	reserve->dimension = TAILLE_RESERVE;

	if (couleur == NOIR)
		reserve->position = POSITION_RESERVE_NOIRE;
	else if (couleur == BLANC)
		reserve->position = POSITION_RESERVE_BLANCHE;
	else
		logPrint(ERREUR, "La couleur renseign�e lors de la cr�ation de la r�serve n'est pas valide");

	reserve->imageReserve = IMG_Load("Reserve.png");
	if (reserve->imageReserve == NULL)
		logPrint(AVERTISSEMENT, "Echec du chargement de l'image de la reserve");

	//Vidage du tableau de piece reservees
	int i;
	for (i = 0; i < 8; i++){
		reserve->tabPiecesReserve[0][i] = NULL;
		reserve->tabPiecesReserve[1][i] = NULL;
	}
	return reserve;
}


void afficherReserve(Reserve* r, SDL_Renderer* contexte){
	SDL_Texture* textureReserve = SDL_CreateTextureFromSurface(contexte, r->imageReserve);
	if (textureReserve == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de la texture de la r�serve depuis son image");
	SDL_Rect positionAffichage;
	positionAffichage.x = r->position.x;
	positionAffichage.y = r->position.y;
	positionAffichage.w = r->dimension.largeur;
	positionAffichage.h = r->dimension.hauteur;
	SDL_RenderCopy(contexte, textureReserve, NULL, &positionAffichage);
	SDL_DestroyTexture(textureReserve);
	SDL_free(&positionAffichage);
}