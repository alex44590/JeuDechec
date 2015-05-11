#include "texte.h"

//***************************************
//*************PARTIE TEXTE**************
//***************************************

SDL_Surface* creerTexte(char* texte, char* font, int taille, int r, int g, int b){
	SDL_Surface* surfaceT = NULL; //Cr�ation de la surface qui contiendra le texte sous forme "d'image" 

	TTF_Font* police = NULL; //Chargement de la police d'�criture
	police = TTF_OpenFont(font, taille);
	if (police == NULL)
		logPrint(ERREUR, "la police n'a pas �t� charg�. Il se peut qu'elle n'existe pas dans le dossier du projet...");

	SDL_Color couleur = { r, g, b }; //Cr�ation de la couleur

	if (*texte == '\0') //Cas o� le texte serait vide, on �vite de renvoyer une surface null en cr�ant un espace qui sera interpr�t� par RenderText comme une lettre
		surfaceT = TTF_RenderText_Blended(police, " ", couleur);
	else
		surfaceT = TTF_RenderText_Blended(police, texte, couleur); //Chargement de l'image r�sultat dans la surface cr��e au d�but de la fonction.

	TTF_CloseFont(police); //D�sallocation de la police

	return surfaceT;
}


void afficherTexte(SDL_Surface* texte, int x, int y, SDL_Renderer* contexte){
	SDL_Texture* textureTexte = NULL;
	textureTexte = SDL_CreateTextureFromSurface(contexte, texte);
	if (textureTexte == NULL)
		logPrint(ERREUR, "Cr�ation de la texture du texte � partir de la surface �chou�e (fonction afficherTexte)");
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


