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
	menu->ttfTexteEchec = creerTexte(" ", "calibri.ttf", 20, 240, 240, 240);

	menu->zoneJoueurEnCours = creerZoneJoueurEnCours();
	menu->zoneChrono = creerZoneChrono();

	menu->couleurEnCours = BLANC;

	menu->tabBouton[0] = creerBouton(RETOUR, "retour.png");
	setPositionBouton(menu->tabBouton[0], LARGEUR_FENETRE - LARGEUR_MENU_DROITE + (LARGEUR_MENU_DROITE / 2 - 35 / 2), BOUTON_RETOUR_Y);
	setTailleBouton(menu->tabBouton[0], 35, 35);

	menu->timer[0] = init_timer();
	menu->timer[1] = init_timer();
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



void afficherMenuDroite(MenuDroite* m, Couleur couleurAJouer, SDL_Renderer* contexte){
	afficherFondMenuDroite(m, contexte);
	afficherDefausse(m->defausseB, contexte);
	afficherAllPiecesDefausse(m->defausseB, contexte);
	afficherDefausse(m->defausseN, contexte);
	afficherAllPiecesDefausse(m->defausseN, contexte);
	afficherZoneJoueurEnCours(m->zoneJoueurEnCours, contexte);
	afficherZoneChrono(m->zoneChrono, contexte);
	afficherBouton(m->tabBouton[0], contexte);
	afficherChrono(m->timer[couleurAJouer], contexte);
	afficherTexte(m->ttfTexteEchec, TEXTE_ECHEC_X, TEXTE_ECHEC_Y, contexte);

}



void mettreAJourTexteEchec(MenuDroite* m, Couleur couleurAJouer, SituationEchec s, SDL_Renderer* contexte){
	if (s == RIEN){
		//Dans le cas où la situation a changé (optimisation)
		if (*(m->texteEchec) != '\0'){
			m->texteEchec = "";
			m->ttfTexteEchec = creerTexte(" ", "calibri.ttf", 20, 240, 240, 240);
			afficherMenuDroite(m, couleurAJouer, contexte);
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


ZoneJoueurEnCours* creerZoneJoueurEnCours(){
	ZoneJoueurEnCours* z = (ZoneJoueurEnCours*)malloc(sizeof(ZoneJoueurEnCours));
	z->imageZoneJoueur = IMG_Load("joueur.png");
	if (z->imageZoneJoueur == NULL)
		logPrint(ERREUR, "Impossible de charger l'image de la zoneJoueurEnCours du menuDroite");
	z->ttfJoueur = creerTexte(" ", "calibri.ttf", 16, 220, 220, 220);
	z->dimension = (Dimension){ ZONE_JOUEUR_HAUTEUR, ZONE_JOUEUR_LARGEUR };
	z->position = (Position){ ZONE_JOUEUR_X, ZONE_JOUEUR_Y };	
	return z;
}


void afficherZoneJoueurEnCours(ZoneJoueurEnCours* z, SDL_Renderer* contexte){
	afficherImage(z->imageZoneJoueur, z->position, z->dimension, contexte);
	afficherTexte(z->ttfJoueur, z->position.x + 30, z->position.y + 5, contexte);
}


ZoneChrono* creerZoneChrono(){
	ZoneChrono* z = (ZoneChrono*)malloc(sizeof(ZoneChrono));
	z->imageZoneChrono = IMG_Load("zoneChrono.png");
	if (z->imageZoneChrono == NULL)
		logPrint(ERREUR, "Impossible de charger l'image de la zone Chrono");
	z->dimension = (Dimension){ ZONE_CHRONO_HAUTEUR, ZONE_CHRONO_LARGEUR };
	z->position = (Position){ ZONE_CHRONO_X, ZONE_CHRONO_Y };
	return z;
}


void afficherZoneChrono(ZoneChrono* z, SDL_Renderer* contexte){
	afficherImage(z->imageZoneChrono, z->position, z->dimension, contexte);
}
