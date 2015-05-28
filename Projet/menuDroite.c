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

	menu->zoneJoueurEnCours = creerZoneJoueurEnCours();
	menu->zoneChrono = creerZoneChrono();
	menu->zoneEchec = creerZoneEchec();

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
	afficherZonEchec(m->zoneEchec, contexte);
}



void mettreAJourTexteEchec(MenuDroite* m, Couleur couleurAJouer, SituationEchec s, SDL_Renderer* contexte){
	if (s == RIEN){
		//Dans le cas où la situation a changé (optimisation)
		if (*(m->zoneEchec->texteEchec) != '\0'){
			m->zoneEchec->texteEchec = "";
		}
	}

	else if (s == ECHEC_BLANC){
		m->zoneEchec->texteEchec = "Roi blanc en échec !";
		m->zoneEchec->ttfTexteEchec = creerTexte(m->zoneEchec->texteEchec, "calibri.ttf", 16, 255, 150, 150);
	}

	else if (s == ECHEC_NOIR){
		m->zoneEchec->texteEchec = "Roi noir en échec !";
		m->zoneEchec->ttfTexteEchec = creerTexte(m->zoneEchec->texteEchec, "calibri.ttf", 16, 255, 150, 150);
	}

	else if (s == ECHEC_ET_MAT_BLANC){
		m->zoneEchec->texteEchec = "Echec et Mat : les noirs gagnent !";
		m->zoneEchec->ttfTexteEchec = creerTexte(m->zoneEchec->texteEchec, "calibri.ttf", 16, 255, 150, 150);
	}

	else if (s == ECHEC_ET_MAT_NOIR){
		m->zoneEchec->texteEchec = "Echec et mat : les blancs gagnent !";
		m->zoneEchec->ttfTexteEchec = creerTexte(m->zoneEchec->texteEchec, "calibri.ttf", 16, 255, 150, 150);
	}

	else if (s == PAT){
		m->zoneEchec->texteEchec = "Egalité : Pat ! Partie terminée...";
		m->zoneEchec->ttfTexteEchec = creerTexte(m->zoneEchec->texteEchec, "calibri.ttf", 16, 255, 150, 150);
	}

	else{
		logPrint(AVERTISSEMENT, "Erreur de situation de jeu (fct afficher texte Echec). Aucun des cas recensés n'est validé");
	}

	afficherMenuDroite(m, couleurAJouer, contexte);
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

ZoneEchec* creerZoneEchec(){
	ZoneEchec* z = (ZoneEchec*)malloc(sizeof(ZoneEchec));
	z->texteEchec = malloc(TEXTE_ECHEC_MAX * sizeof(char));
	z->ttfTexteEchec = creerTexte(" ", "calibri.ttf", 16, 220, 220, 220);
	z->imageZoneEchec = IMG_Load("zoneEchec.png");
	if (z->imageZoneEchec == NULL)
		logPrint(ERREUR, "Impossible de charger l'image de la Zone Echec");
	z->dimension = (Dimension){ ZONE_ECHEC_HAUTEUR, ZONE_ECHEC_LARGEUR };
	z->position = (Position){ ZONE_ECHEC_X, ZONE_ECHEC_Y };
	return z;
}


void afficherZonEchec(ZoneEchec* z, SDL_Renderer* contexte){
	afficherImage(z->imageZoneEchec, z->position, z->dimension, contexte);
	if (z->texteEchec[0] != '\0');
	afficherTexte(z->ttfTexteEchec, z->position.x + 30, z->position.y + 7, contexte);
}
