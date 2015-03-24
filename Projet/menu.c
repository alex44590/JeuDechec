#include "menu.h"

Bouton* creerBouton(idBouton cible, char* nomImage){
	Bouton* b = (Bouton*)malloc(sizeof(Bouton));
	b->cible = cible;
	b->enfonce = FALSE;

	SDL_Surface* imageBouton = IMG_Load(nomImage);
	b->image = imageBouton;

	b->dimension.largeur = 280;
	b->dimension.hauteur = 60;
	b->positionInit.x = b->positionActuelle.x = (LARGEUR_MENU - b->dimension.largeur) / 2;
	b->positionInit.y = b->positionActuelle.y = (HAUTEUR_MENU - NB_BOUTON * 1.3 * b->dimension.hauteur) / 2 + 1.3 * b->dimension.hauteur*cible;

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

Menu* creerMenu(){
	Menu* menu = (Menu*)malloc(sizeof(Menu));
	menu->fondMenu = IMG_Load("fondMenu2.png");

	menu->tabBouton[0] = creerBouton(JOUER, "Bouton0.png");
	menu->tabBouton[1] = creerBouton(OPTIONS, "Bouton1.png");
	menu->tabBouton[2] = creerBouton(REGLES, "Bouton2.png");
	menu->tabBouton[3] = creerBouton(STATISTIQUES, "Bouton3.png");
	
	return menu;
}

void afficherFondMenu(Menu* m, SDL_Renderer* contexte){
	SDL_Texture* textFond = SDL_CreateTextureFromSurface(contexte, m->fondMenu);
	SDL_Rect positionAffichage;
	positionAffichage.x = 0;
	positionAffichage.y = 0;
	positionAffichage.w = LARGEUR_MENU;
	positionAffichage.h = HAUTEUR_MENU;
	SDL_RenderCopy(contexte, textFond, NULL, &positionAffichage);
	SDL_DestroyTexture(textFond);
}

void afficherMenu(Menu* m, SDL_Renderer* contexte){
	afficherFondMenu(m,contexte);
	int i;
	for (i = 0; i < NB_BOUTON; ++i){
		afficherBouton(m->tabBouton[i], contexte);
	}
}

void enfoncerBouton(Bouton* b){
	if (b->enfonce==FALSE){
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