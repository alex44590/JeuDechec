#include "menuDroite.h"

MenuDroite* creerMenuDroite(Defausse* defausseB, Defausse* defausseN){
	MenuDroite* menu = NULL;
	menu = (MenuDroite*)malloc(sizeof(MenuDroite));
	if (menu == NULL)
		logPrint(ERREUR, "Echec lors de l'allocation de MenuDroite");
	menu->defausseB = defausseB;
	menu->defausseN = defausseN;
	menu->fondMenu = IMG_Load("FondMenuD.jpg");
	if (menu->fondMenu == NULL)
		logPrint(AVERTISSEMENT, "Impossible de charger l'image de fond du menu de droite");
	menu->dimension = TAILLE_MENU_DROITE;
	menu->position = POSITION_MENU_DROITE;
	return menu;
}

void afficherFondMenuDroite(MenuDroite* m, SDL_Renderer* contexte){
	SDL_Texture* textFond = SDL_CreateTextureFromSurface(contexte, m->fondMenu);
	SDL_Rect positionAffichage;
	positionAffichage.x = m->position.x;
	positionAffichage.y = m->position.y;
	positionAffichage.w = m->dimension.largeur;
	positionAffichage.h = m->dimension.hauteur;
	SDL_RenderCopy(contexte, textFond, NULL, &positionAffichage);
	SDL_DestroyTexture(textFond);
}

