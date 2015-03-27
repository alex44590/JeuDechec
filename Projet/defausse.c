#include "defausse.h"


Defausse* creerDefausse(Couleur couleur){
	Defausse* defausse = (Defausse*)malloc(sizeof(Defausse));
	if (defausse == NULL){
		logPrint(ERREUR, "Allocation dynamique de la Defausse échouée");
	}

	defausse->couleur = couleur;
	defausse->dimension = TAILLE_DEFAUSSE;

	if (couleur == NOIR)
		defausse->position = POSITION_DEFAUSSE_NOIRE;
	else if (couleur == BLANC)
		defausse->position = POSITION_DEFAUSSE_BLANCHE;
	else
		logPrint(ERREUR, "La couleur renseignée lors de la création de la défausse n'est pas valide");	

	defausse->imageDefausse = IMG_Load("defausse2.png");
	if (defausse->imageDefausse == NULL)
		logPrint(AVERTISSEMENT, "Echec du chargement de l'image de la defausse");
	
	return defausse;
}


void afficherDefausse(Defausse* d, SDL_Renderer* contexte){
	SDL_Texture* textureDefausse = SDL_CreateTextureFromSurface(contexte, d->imageDefausse);
	if (textureDefausse == NULL)
		logPrint(ERREUR, "Echec de la création de la texture de la défausse depuis son image");
	SDL_Rect positionAffichage;
	positionAffichage.x = d->position.x;
	positionAffichage.y = d->position.y;
	positionAffichage.w = d->dimension.largeur;
	positionAffichage.h = d->dimension.hauteur;
	SDL_RenderCopy(contexte, textureDefausse, NULL, &positionAffichage);
	SDL_DestroyTexture(textureDefausse);
	SDL_free(&positionAffichage);
}


