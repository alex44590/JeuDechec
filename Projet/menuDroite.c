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

	menu->texteEchec = malloc(TEXTE_ECHEC_MAX * sizeof(char));
	*(menu->texteEchec) = '\0';

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



void afficherMenuDroite(MenuDroite* m, SDL_Renderer* contexte){
	afficherFondMenuDroite(m, contexte);
	afficherDefausse(m->defausseB, contexte);
	afficherAllPiecesDefausse(m->defausseB, contexte);
	afficherDefausse(m->defausseN, contexte);
	afficherAllPiecesDefausse(m->defausseN, contexte);
}



void afficherTexteEchec(MenuDroite* m, SituationEchec s, SDL_Renderer* contexte){
	if (s == RIEN){
		//Dans le cas où la situation a changé (optimisation)
		if (*(m->texteEchec) != '\0'){
			m->texteEchec = "";
			afficherFondMenuDroite(m, contexte);
			afficherDefausse(m->defausseB, contexte);
			afficherAllPiecesDefausse(m->defausseB, contexte);
			afficherDefausse(m->defausseN, contexte);
			afficherAllPiecesDefausse(m->defausseN, contexte);
		}
	}

	else if (s == ECHEC_BLANC){
		m->texteEchec = "Roi blanc en échec !";
		m->ttfTexteEchec = creerTexte(m->texteEchec, "calibri.ttf", 20, 240, 240, 240);
		afficherTexte(m->ttfTexteEchec, TEXTE_ECHEC_X, TEXTE_ECHEC_Y, contexte);
	}

	else if (s == ECHEC_NOIR){
		m->texteEchec = "Roi noir en échec !";
		m->ttfTexteEchec = creerTexte(m->texteEchec, "calibri.ttf", 20, 240, 240, 240);
		afficherTexte(m->ttfTexteEchec, TEXTE_ECHEC_X, TEXTE_ECHEC_Y, contexte);
	}

	else if (s == ECHEC_ET_MAT_BLANC){
		m->texteEchec = "Roi blanc en échec et mat !";
		m->ttfTexteEchec = creerTexte(m->texteEchec, "calibri.ttf", 20, 240, 240, 240);
		afficherTexte(m->ttfTexteEchec, TEXTE_ECHEC_X, TEXTE_ECHEC_Y, contexte);
	}

	else if (s == ECHEC_ET_MAT_NOIR){
		m->texteEchec = "Roi noir en échec et mat !";
		m->ttfTexteEchec = creerTexte(m->texteEchec, "calibri.ttf", 20, 240, 240, 240);
		afficherTexte(m->ttfTexteEchec, TEXTE_ECHEC_X, TEXTE_ECHEC_Y, contexte);
	}

	else if (s == PAT){
		m->texteEchec = "Egalité : Pat !";
		m->ttfTexteEchec = creerTexte(m->texteEchec, "calibri.ttf", 20, 240, 240, 240);
		afficherTexte(m->ttfTexteEchec, TEXTE_ECHEC_X, TEXTE_ECHEC_Y, contexte);
	}

	else{
		logPrint(AVERTISSEMENT, "Erreur de situation de jeu (fct afficher texte Echec). Aucun des cas recensés n'est validé");
	}
}
