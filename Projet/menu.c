#include "menu.h"


//***************************************
//*********PARTIE MENU PRINCIPAL*********
//***************************************

Menu* creerMenu(){
	Menu* menu = (Menu*)malloc(sizeof(Menu));
	menu->fondMenu = IMG_Load("fondMenu3.png");

	menu->tabBouton[0] = creerBouton(ENTRAINEMENT, "Bouton0.png");
	menu->tabBouton[1] = creerBouton(DEUXJOUEURS, "Bouton1.png");
	menu->tabBouton[2] = creerBouton(OPTION, "Bouton2.png");
	menu->tabBouton[3] = creerBouton(APROPOS, "Bouton3.png");

	menu->imageAccueil = IMG_Load("imageAccueil.png");

	return menu;
}

void afficherFondMenu(SDL_Surface* fondMenu, SDL_Renderer* contexte){
	SDL_Texture* textFond = SDL_CreateTextureFromSurface(contexte, fondMenu);
	SDL_Rect positionAffichage;
	positionAffichage.x = 0;
	positionAffichage.y = 0;
	positionAffichage.w = LARGEUR_MENU;
	positionAffichage.h = HAUTEUR_MENU;
	SDL_RenderCopy(contexte, textFond, NULL, &positionAffichage);
	SDL_DestroyTexture(textFond);
}

void afficherMenu(Menu* m, SDL_Renderer* contexte){
	afficherFondMenu(m->fondMenu, contexte);
	int i;
	for (i = 0; i < NB_BOUTON_MP; ++i){
		afficherBouton(m->tabBouton[i], contexte);
	}
}

void afficherImageAccueil(SDL_Surface* imageAccueil, SDL_Renderer* contexte){
	SDL_Texture* textImg = SDL_CreateTextureFromSurface(contexte, imageAccueil);
	SDL_Rect positionAffichage;
	positionAffichage.x = LARGEUR_MENU;
	positionAffichage.y = 0;
	positionAffichage.w = LARGEUR_FENETRE-LARGEUR_MENU;
	positionAffichage.h = HAUTEUR_MENU;
	SDL_RenderCopy(contexte, textImg, NULL, &positionAffichage);
	SDL_DestroyTexture(textImg);
}

//***************************************
//********* PARTIE ZONE PSEUDO **********
//***************************************

ZonePseudo* creerZonePseudo(int numZone){
	ZonePseudo* z = (ZonePseudo*)malloc(sizeof(ZonePseudo));

	z->pseudo[0] = '\0';
	z->numZone = numZone;

	z->dimension.hauteur = HAUTEUR_ZONE_PSEUDO;
	z->dimension.largeur = LARGEUR_ZONE_PSEUDO;
	if (numZone == 1){
		z->position.x = X_ZONE_PSEUDO_1;
		z->position.y = Y_ZONE_PSEUDO_1;
		z->ttfNumJ = creerTexte("Joueur 1", "evanescent.ttf", 32, 220, 220, 220);
	}
	else if (numZone == 2){
		z->position.x = X_ZONE_PSEUDO_2;
		z->position.y = Y_ZONE_PSEUDO_2;
		z->ttfNumJ = creerTexte("Joueur 2", "evanescent.ttf", 32, 220, 220, 220);
	}

	z->imageZone = IMG_Load("ZP.png");
	if (z->imageZone == NULL)
		logPrint(ERREUR, "Chargement de l'image Zone Pseudo échoué");

	z->imageZoneSelectionnee = IMG_Load("ZPS.png");
	if (z->imageZoneSelectionnee == NULL)
		logPrint(ERREUR, "Chargement de l'image Zone Pseudo Selectionnee échoué");

	z->imageActuelle = z->imageZone;

	z->ttfPseudo = NULL;

	return z;
}


void afficherAllZonesPseudo(ZonePseudo* zone1, ZonePseudo* zone2, SDL_Renderer* contexte){
	afficherZonePseudo(zone1, contexte);
	//On affiche le texte "joueur 1 (ou 2)" au dessus de la zone de pseudo correspondante, en prenant soin de centrer ll'affichage
	afficherTexte(zone1->ttfNumJ, zone1->position.x + (zone1->dimension.largeur - zone1->ttfNumJ->w) / 2, zone1->position.y - ESPACEMENT_NUMJ_ZONE - zone1->ttfNumJ->h, contexte);

	afficherZonePseudo(zone2, contexte);
	afficherTexte(zone2->ttfNumJ, zone2->position.x + (zone2->dimension.largeur - zone2->ttfNumJ->w) / 2, zone2->position.y - ESPACEMENT_NUMJ_ZONE - zone2->ttfNumJ->h, contexte);
}


void afficherZonePseudo(ZonePseudo* z, SDL_Renderer* contexte){
	SDL_Texture* textureZone = NULL;
	textureZone = SDL_CreateTextureFromSurface(contexte, z->imageActuelle);
	if (textureZone == NULL)
		logPrint(ERREUR, "Création de la texture de la zone de pseudo échouée");
	SDL_Rect positionAffichage;
	positionAffichage.x = z->position.x;
	positionAffichage.y = z->position.y;
	positionAffichage.w = z->dimension.largeur;
	positionAffichage.h = z->dimension.hauteur;
	SDL_RenderCopy(contexte, textureZone, NULL, &positionAffichage);
	SDL_DestroyTexture(textureZone);
}


void selectionnerZonePseudo2J(Menu2J* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte){
	z->imageActuelle = z->imageZoneSelectionnee;

	if (reafficherMenu == TRUE)
		afficherMenu2J(m, contexte);

}

void deselectionnerZonePseudo2J(Menu2J* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte){
	z->imageActuelle = z->imageZone;

	if (reafficherMenu == TRUE)
		afficherMenu2J(m, contexte);
}

void selectionnerZonePseudoEntrainement(MenuEntrainement* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte){
	z->imageActuelle = z->imageZoneSelectionnee;

	if (reafficherMenu == TRUE)
		afficherMenuEntrainement(m, contexte);

}

void deselectionnerZonePseudoEntrainement(MenuEntrainement* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte){
	z->imageActuelle = z->imageZone;

	if (reafficherMenu == TRUE)
		afficherMenuEntrainement(m, contexte);
}


//Récupère une lettre ou un chiffre pressé sur le clavier (au travers d'une objet event) et l'ajoute en fin de chaine dest s'il reste de la place
void catSaisiePseudo(Input* in, ZonePseudo* z, int* continuerSaisiePseudo){
	int i;
	int j;
	char src[2];
	src[1] = '\0';

	//Cas ou l'on a appuyé sur un chiffre (pas du Numpad) et que la majuscule est activée
	for (i = SDLK_0; i <= SDLK_9; i++){
		if (in->clavier[i] && (in->clavier[KEYCODE_REDUIT(SDLK_LSHIFT)] || in->clavier[KEYCODE_REDUIT(SDLK_RSHIFT)] || in->clavier[KEYCODE_REDUIT(SDLK_CAPSLOCK)])){
			src[0] = i;
			in->clavier[i] = 0;
		}
	}

	//Cas des touches numériques du pavé numérique sauf le 0 plus galère...
	for (i = KEYCODE_REDUIT(SDLK_KP_1); i <= KEYCODE_REDUIT(SDLK_KP_9); i++){
		if (in->clavier[i]){
			src[0] = i-111;
			in->clavier[i] = 0;
		}
	}

	//Cas du 0 du numpad
	if (in->clavier[KEYCODE_REDUIT(SDLK_KP_0)]){
		src[0] = '0';
		in->clavier[KEYCODE_REDUIT(SDLK_KP_0)] = 0;
	}

	//Cas des chiffres (pas du numpad) si la majuscule n'est pas active et qu'on apuuie pas sur alt-gr
	j = 0;
	for (i = SDLK_0; i <= SDLK_9; i++){
		if (in->clavier[i] && !(in->clavier[KEYCODE_REDUIT(SDLK_LSHIFT)] || in->clavier[KEYCODE_REDUIT(SDLK_RSHIFT)] || in->clavier[KEYCODE_REDUIT(SDLK_CAPSLOCK)])){
			char caracSpec[10] = {'à', '&', 'é', '"', '\'', '(', '-', 'è', '_', 'ç'};
			src[0] = caracSpec[j];
			in->clavier[i] = 0;
		}
		++j;
	}

	if (in->clavier[SDLK_ESCAPE]) /* Appui sur la touche Echap, on sort de la zone*/
		*continuerSaisiePseudo = 0;

	for (i = SDLK_a; i <= SDLK_z; i++){
		if (in->clavier[i] && (in->clavier[KEYCODE_REDUIT(SDLK_LSHIFT)] || in->clavier[KEYCODE_REDUIT(SDLK_RSHIFT)] || in->clavier[KEYCODE_REDUIT(SDLK_CAPSLOCK)])){
			src[0] = i-32;
			in->clavier[i] = 0;
		}
		else if (in->clavier[i]){
			src[0] = i;
			in->clavier[i] = 0;
		}
	}

	if (in->clavier[SDLK_SPACE]){
		src[0] = ' ';
		in->clavier[SDLK_SPACE] = 0;
	}

	if (in->clavier[SDLK_BACKSPACE]){
		z->pseudo[strlen(z->pseudo) - 1] = '\0';
		in->clavier[SDLK_BACKSPACE] = 0;
	}

	if (in->clavier[SDLK_TAB]){
		*continuerSaisiePseudo = 0;
		in->clavier[SDLK_TAB] = 0;
	}

	if (in->clavier[SDLK_RETURN]){
		*continuerSaisiePseudo = 0;
		in->clavier[SDLK_RETURN] = 0;
	}

	if ((strlen(z->pseudo) + 1) < PSEUDO_LONGUEUR_MAX && src[0] != -52)
		strcat(z->pseudo, src);


}

//***************************************
//*********PARTIE MENU 2 JOUEURS*********
//***************************************

Menu2J* creerMenuDeuxJoueurs(){
	Menu2J* m = (Menu2J*)malloc(sizeof(Menu2J));

	m->fondMenu = NULL;
	m->fondMenu = IMG_Load("fondMenu3.png");
	if (m->fondMenu == NULL)
		logPrint(ERREUR, "Erreur lors du chargement de l'image du fond de menu 2 joueurs");

	m->position.x = 0;
	m->position.y = 0;
	m->dimension.hauteur = HAUTEUR_MENU;
	m->dimension.largeur = LARGEUR_MENU;

	m->tabBouton[0] = creerBouton(ACCUEIL, "BoutonHome.png");
	setTailleBouton(m->tabBouton[0], 45, 45);
	setPositionBouton(m->tabBouton[0], LARGEUR_MENU / 2 - m->tabBouton[0]->dimension.largeur / 2, 110);

	m->zone1 = NULL;
	m->zone2 = NULL;
	m->zone1 = creerZonePseudo(1);
	m->zone2 = creerZonePseudo(2);
	if (m->zone1 == NULL || m->zone2 == NULL)
		logPrint(ERREUR, "Erreur lors de l'assignation des zones pseudo dans le menu 2 joueurs");

	return m;
}


void afficherMenu2J(Menu2J* m, SDL_Renderer* contexte){
	afficherFondMenu(m->fondMenu, contexte);
	afficherAllZonesPseudo(m->zone1, m->zone2, contexte);
	if (m->zone1->ttfPseudo != NULL)
		afficherTexte(m->zone1->ttfPseudo, m->zone1->position.x + 15, m->zone1->position.y + 11, contexte);
	if (m->zone2->ttfPseudo != NULL)
		afficherTexte(m->zone2->ttfPseudo, m->zone2->position.x + 15, m->zone2->position.y + 11, contexte);
	afficherBouton(m->tabBouton[0], contexte);

}



//*****************************************
//******  PARTIE MENU ENTRAINEMENT  *******
//*****************************************

MenuEntrainement* creerMenuEntrainement(Reserve* reserveB, Reserve* reserveN){
	MenuEntrainement* m = (MenuEntrainement*)malloc(sizeof(MenuEntrainement));

	m->fondMenu = NULL;
	m->fondMenu = IMG_Load("fondMenu3.png");
	if (m->fondMenu == NULL)
		logPrint(ERREUR, "Erreur lors du chargement de l'image du fond de menu entrainement");

	m->position.x = 0;
	m->position.y = 0;
	m->dimension.hauteur = HAUTEUR_MENU;
	m->dimension.largeur = LARGEUR_MENU;

	m->tabBouton[0] = creerBouton(ACCUEIL, "BoutonHome.png");
	setTailleBouton(m->tabBouton[0], 45, 45);
	setPositionBouton(m->tabBouton[0], LARGEUR_MENU / 2 - m->tabBouton[0]->dimension.largeur / 2, 110);

	m->zone1 = NULL;
	m->zone2 = NULL;
	m->zone1 = creerZonePseudo(1);
	m->zone2 = creerZonePseudo(2);

	m->reserveB = reserveB;
	m->reserveN = reserveN;

	if (m->zone1 == NULL || m->zone2 == NULL)
		logPrint(ERREUR, "Erreur lors de l'assignation des zones pseudo dans le menu entrainement");

	return m;
}


void afficherMenuEntrainement(MenuEntrainement* m, SDL_Renderer* contexte){
	afficherFondMenu(m->fondMenu, contexte);
	afficherAllZonesPseudo(m->zone1, m->zone2, contexte);
	if (m->zone1->ttfPseudo != NULL)
		afficherTexte(m->zone1->ttfPseudo, m->zone1->position.x + 15, m->zone1->position.y + 11, contexte);
	if (m->zone2->ttfPseudo != NULL)
		afficherTexte(m->zone2->ttfPseudo, m->zone2->position.x + 15, m->zone2->position.y + 11, contexte);
	afficherBouton(m->tabBouton[0], contexte);
	afficherReserve(m->reserveB, contexte);
	afficherReserve(m->reserveN, contexte);
}