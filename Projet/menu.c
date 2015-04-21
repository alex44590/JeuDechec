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


void selectionnerZonePseudo(Menu2J* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte){
	z->imageActuelle = z->imageZoneSelectionnee;

	if (reafficherMenu == TRUE)
		afficherMenu2J(m, contexte);
}


void deselectionnerZonePseudo(Menu2J* m, ZonePseudo* z, Booleen reafficherMenu, SDL_Renderer* contexte){
	z->imageActuelle = z->imageZone;

	if (reafficherMenu == TRUE)
		afficherMenu2J(m, contexte);
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

}


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


//Récupère une lettre ou un chiffre pressé sur le clavier (au travers d'une objet event) et l'ajoute en fin de chaine dest s'il reste de la place
void catSaisiePseudo(SDL_Event event, ZonePseudo* z, int* continuer, int* continuerBouclePrincipale){
	char src[2];
	src[1] = '\0';

	switch (event.type)
	{
	case SDL_QUIT:
		*continuer = 0;
		*continuerBouclePrincipale = 0;
		break;


	case SDL_MOUSEBUTTONDOWN:

		*continuer = 0;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE: /* Appui sur la touche Echap, on sort de la zone*/
			*continuer = 0;
			break;
		case SDLK_a:
			src[0] = 'a';
			break;
		case SDLK_b:
			src[0] = 'b';
			break;
		case SDLK_c:
			src[0] = 'c';
			break;
		case SDLK_d:
			src[0] = 'd';
			break;
		case SDLK_e:
			src[0] = 'e';
			break;
		case SDLK_f:
			src[0] = 'f';
			break;
		case SDLK_g:
			src[0] = 'g';
			break;
		case SDLK_h:
			src[0] = 'h';
			break;
		case SDLK_i:
			src[0] = 'i';
			break;
		case SDLK_j:
			src[0] = 'j';
			break;
		case SDLK_k:
			src[0] = 'k';
			break;
		case SDLK_l:
			src[0] = 'l';
			break;
		case SDLK_m:
			src[0] = 'm';
			break;
		case SDLK_n:
			src[0] = 'n';
			break;
		case SDLK_o:
			src[0] = 'o';
			break;
		case SDLK_p:
			src[0] = 'p';
			break;
		case SDLK_q:
			src[0] = 'q';
			break;
		case SDLK_r:
			src[0] = 'r';
			break;
		case SDLK_s:
			src[0] = 's';
			break;
		case SDLK_t:
			src[0] = 't';
			break;
		case SDLK_u:
			src[0] = 'u';
			break;
		case SDLK_v:
			src[0] = 'v';
			break;
		case SDLK_w:
			src[0] = 'w';
			break;
		case SDLK_x:
			src[0] = 'x';
			break;
		case SDLK_y:
			src[0] = 'y';
			break;
		case SDLK_z:
			src[0] = 'z';
			break;
		case SDLK_0:
			src[0] = '0';
			break;
		case SDLK_KP_0:
			src[0] = '0';
			break;
		case SDLK_1:
			src[0] = '1';
			break;
		case SDLK_KP_1:
			src[0] = '1';
			break;
		case SDLK_2:
			src[0] = '2';
			break;
		case SDLK_KP_2:
			src[0] = '2';
			break;
		case SDLK_3:
			src[0] = '3';
			break;
		case SDLK_KP_3:
			src[0] = '3';
			break;
		case SDLK_4:
			src[0] = '4';
			break;
		case SDLK_KP_4:
			src[0] = '4';
			break;
		case SDLK_5:
			src[0] = '5';
			break;
		case SDLK_KP_5:
			src[0] = '5';
			break;
		case SDLK_6:
			src[0] = '6';
			break;
		case SDLK_KP_6:
			src[0] = '6';
			break;
		case SDLK_7:
			src[0] = '7';
			break;
		case SDLK_KP_7:
			src[0] = '7';
			break;
		case SDLK_8:
			src[0] = '8';
			break;
		case SDLK_KP_8:
			src[0] = '8';
			break;
		case SDLK_9:
			src[0] = '9';
			break;
		case SDLK_KP_9:
			src[0] = '9';
			break;
		case SDLK_SPACE:
			src[0] = ' ';
			break;
		case SDLK_BACKSPACE:
			z->pseudo[strlen(z->pseudo) - 1] = '\0';
			break;
		case SDLK_TAB:
			*continuer = 0;
			break;
		case SDLK_RETURN:
			*continuer = 0;
			break;

		}
		if ((strlen(z->pseudo) + 1) < PSEUDO_LONGUEUR_MAX && src[0] != -52)
			strcat(z->pseudo, src);
	}//End switch


}