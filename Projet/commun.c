#include "commun.h"

void afficherImage(SDL_Surface* image, Position p, Dimension d, SDL_Renderer* contexte){
	SDL_Texture* texture = SDL_CreateTextureFromSurface(contexte, image);
	SDL_Rect positionAffichage;
	positionAffichage.x = p.x;
	positionAffichage.y = p.y;
	positionAffichage.w = d.largeur;
	positionAffichage.h = d.hauteur;
	SDL_RenderCopy(contexte, texture, NULL, &positionAffichage);
	SDL_DestroyTexture(texture);
}
