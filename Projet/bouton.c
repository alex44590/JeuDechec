#include "bouton.h"

Bouton* creerBouton(idBouton cible, char* nomImage){
	Bouton* b = (Bouton*)malloc(sizeof(Bouton));
	b->idBouton = cible;
	b->enfonce = FALSE;

	SDL_Surface* imageBouton = IMG_Load(nomImage);
	b->image = imageBouton;

	b->dimension.largeur = 288;
	b->dimension.hauteur = 68;
	b->positionInit.x = b->positionActuelle.x = (LARGEUR_MENU - b->dimension.largeur) / 2;
	b->positionInit.y = b->positionActuelle.y = (HAUTEUR_MENU - NB_BOUTON_MP * 1.3 * b->dimension.hauteur) / 2 + 1.3 * b->dimension.hauteur*cible;

	return b;
}

void afficherBouton(Bouton* b, SDL_Renderer* contexte){
	SDL_Texture* textureBouton = SDL_CreateTextureFromSurface(contexte, b->image);
	SDL_Rect positionAffichage;
	positionAffichage.x = b->positionActuelle.x;
	positionAffichage.y = b->positionActuelle.y;
	positionAffichage.w = b->dimension.largeur;
	positionAffichage.h = b->dimension.hauteur;
	SDL_RenderCopy(contexte, textureBouton, NULL, &positionAffichage);
	SDL_DestroyTexture(textureBouton);
	SDL_free(&positionAffichage);
}


void enfoncerBouton(Bouton* b){
	if (b->enfonce == FALSE){
		b->positionActuelle.x += 3;
		b->positionActuelle.y += 3;
		b->enfonce = TRUE;
	}
}

void desenfoncerBouton(Bouton* b){
	b->enfonce = FALSE;
	b->positionActuelle.x = b->positionInit.x;
	b->positionActuelle.y = b->positionInit.y;
}
