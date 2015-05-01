#include "texte.h"

//***************************************
//*************PARTIE TEXTE**************
//***************************************

SDL_Surface* creerTexte(char* texte, char* font, int taille, int r, int g, int b){
	SDL_Surface* surfaceT = NULL; //Création de la surface qui contiendra le texte sous forme "d'image" 

	TTF_Font* police = NULL; //Chargement de la police d'écriture
	police = TTF_OpenFont(font, taille);
	if (police == NULL)
		logPrint(ERREUR, "la police n'a pas été chargé. Il se peut qu'elle n'existe pas dans le dossier du projet...");

	SDL_Color couleur = { r, g, b }; //Création de la couleur

	if (*texte == '\0') //Cas où le texte serait vide, on évite de renvoyer une surface null en créant un espace qui sera interprété par RenderText comme une lettre
		surfaceT = TTF_RenderText_Blended(police, " ", couleur);
	else
		surfaceT = TTF_RenderText_Blended(police, texte, couleur); //Chargement de l'image résultat dans la surface créée au début de la fonction.

	TTF_CloseFont(police); //Désallocation de la police

	return surfaceT;
}


void afficherTexte(SDL_Surface* texte, int x, int y, SDL_Renderer* contexte){
	SDL_Texture* textureTexte = NULL;
	textureTexte = SDL_CreateTextureFromSurface(contexte, texte);
	if (textureTexte == NULL)
		logPrint(ERREUR, "Création de la texture du texte à partir de la surface échouée (fonction afficherTexte)");
	else{
		SDL_Rect positionAffichage;
		positionAffichage.x = x;
		positionAffichage.y = y;
		positionAffichage.w = texte->w;
		positionAffichage.h = texte->h;
		SDL_RenderCopy(contexte, textureTexte, NULL, &positionAffichage);
		SDL_DestroyTexture(textureTexte);
	}
}


