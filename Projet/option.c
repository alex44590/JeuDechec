#include "option.h"

PageOptions* creerPageOptions(){
	PageOptions* p = (PageOptions*)malloc(sizeof(PageOptions));
	if (p == NULL)
		logPrint(ERREUR, "Allocation de la page de règle échouée");


	p->imageFondPage = IMG_Load("pageOptions.png");

	if (p->imageFondPage == NULL)
		logPrint(ERREUR, "Impossible de charger l'image de la page d'options");

	int i, j;
	for (j = 0; j < 2; j++){
		for (i = 0; i < 6; i++){
			p->tabOptionTemps[i][j] = creerOption(i, OPTION_1_X + i * 90, OPTION_1_Y + j * 200);
		}
	}

	cocherOption(p->tabOptionTemps[MIN_45][0]);
	cocherOption(p->tabOptionTemps[MIN_45][1]);

	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			p->tabOptionSurbrillance[i][j] = creerOption(i+NB_OPTIONS_TEMPS, OPTION_1_X + 605 + i * 120, OPTION_1_Y + j * 200);
		}
	}

	cocherOption(p->tabOptionSurbrillance[SURBRILLANCE_ACTIVEE-NB_OPTIONS_TEMPS][0]);
	cocherOption(p->tabOptionSurbrillance[SURBRILLANCE_ACTIVEE-NB_OPTIONS_TEMPS][1]);

	return p;
}

void afficherPageOptions(PageOptions* p, SDL_Renderer* contexte){
	afficherImage(p->imageFondPage, (Position){ LARGEUR_MENU, 0}, (Dimension){HAUTEUR_MENU , LARGEUR_FENETRE - LARGEUR_MENU}, contexte);
	int i, j;
	for (i = 0; i < 6; i++){
		for (j = 0; j < 2; j++){
			afficherOption(p->tabOptionTemps[i][j], contexte);
		}
	}

	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			afficherOption(p->tabOptionSurbrillance[i][j], contexte);
		}
	}
}


Option* creerOption(IdOption id, int x, int y){
	Option* o = (Option*)malloc(sizeof(Option));
	if (o == NULL)
		logPrint(ERREUR, "Allocation de la page de règle échouée");

	o->cochee = FALSE;

	o->dimension = (Dimension){ OPTION_LARGEUR, OPTION_HAUTEUR };
	o->position = (Position){ x, y};
	o->idOption = id;

	o->imageCochee = IMG_Load("ON.png");
	o->imagePasCochee = IMG_Load("OFF.png");
	o->imageActuelle = o->imagePasCochee;
	if (o->imageCochee == NULL || o->imagePasCochee == NULL)
		logPrint(ERREUR, "Impossible de charger l'image de case cochable du menu options");

	return o;
}

void cocherOption(Option* o){
	o->cochee = TRUE;
	o->imageActuelle = o->imageCochee;
}

void decocherOption(Option* o){
	o->cochee = FALSE;
	o->imageActuelle = o->imagePasCochee;
}

void afficherOption(Option* o, SDL_Renderer* contexte){
	afficherImage(o->imageActuelle, o->position, o->dimension, contexte);
}


void gererOptionTemps(PageOptions* pageOptions, MenuDroite* menuDroiteEntrainement, MenuDroite* menuDroite2J, int i, int j, SDL_Renderer* contexte){
	if (i == MODE_ENTRAINEMENT){
		switch (pageOptions->tabOptionTemps[j][i]->idOption){
		case MIN_15:
			menuDroiteEntrainement->timer[0]->reserveTempsInitiale = menuDroiteEntrainement->timer[1]->reserveTempsInitiale = 900000;
			update_timer(menuDroiteEntrainement->timer[0], FALSE);
			update_timer(menuDroiteEntrainement->timer[1], FALSE);
			break;
		case MIN_20:
			menuDroiteEntrainement->timer[0]->reserveTempsInitiale = menuDroiteEntrainement->timer[1]->reserveTempsInitiale = 1200000;
			update_timer(menuDroiteEntrainement->timer[0], FALSE);
			update_timer(menuDroiteEntrainement->timer[1], FALSE);
			break;
		case MIN_30:
			menuDroiteEntrainement->timer[0]->reserveTempsInitiale = menuDroiteEntrainement->timer[1]->reserveTempsInitiale = 1800000;
			update_timer(menuDroiteEntrainement->timer[0], FALSE);
			update_timer(menuDroiteEntrainement->timer[1], FALSE);
			break;
		case MIN_45:
			menuDroiteEntrainement->timer[0]->reserveTempsInitiale = menuDroiteEntrainement->timer[1]->reserveTempsInitiale = 2700000;
			update_timer(menuDroiteEntrainement->timer[0], FALSE);
			update_timer(menuDroiteEntrainement->timer[1], FALSE);
			break;
		case MIN_60:
			menuDroiteEntrainement->timer[0]->reserveTempsInitiale = menuDroiteEntrainement->timer[1]->reserveTempsInitiale = 3599000;
			update_timer(menuDroiteEntrainement->timer[0], FALSE);
			update_timer(menuDroiteEntrainement->timer[1], FALSE);
			break;
		case MIN_ILLIMITE:
			//A voir...
			break;
		}
	}

	else if (i == MODE_MULTIJOUEUR){
		switch (pageOptions->tabOptionTemps[j][i]->idOption){
		case MIN_15:
			menuDroite2J->timer[0]->reserveTempsInitiale = menuDroite2J->timer[1]->reserveTempsInitiale = 900000;
			update_timer(menuDroite2J->timer[0], FALSE);
			update_timer(menuDroite2J->timer[1], FALSE);
			break;
		case MIN_20:
			menuDroite2J->timer[0]->reserveTempsInitiale = menuDroite2J->timer[1]->reserveTempsInitiale = 1200000;
			update_timer(menuDroite2J->timer[0], FALSE);
			update_timer(menuDroite2J->timer[1], FALSE);
			break;
		case MIN_30:
			menuDroite2J->timer[0]->reserveTempsInitiale = menuDroite2J->timer[1]->reserveTempsInitiale = 1800000;
			update_timer(menuDroite2J->timer[0], FALSE);
			update_timer(menuDroite2J->timer[1], FALSE);
			break;
		case MIN_45:
			menuDroite2J->timer[0]->reserveTempsInitiale = menuDroite2J->timer[1]->reserveTempsInitiale = 2700000;
			update_timer(menuDroite2J->timer[0], FALSE);
			update_timer(menuDroite2J->timer[1], FALSE);
			break;
		case MIN_60:
			menuDroite2J->timer[0]->reserveTempsInitiale = menuDroite2J->timer[1]->reserveTempsInitiale = 3599000;
			update_timer(menuDroite2J->timer[0], FALSE);
			update_timer(menuDroite2J->timer[1], FALSE);
			break;
		case MIN_ILLIMITE:
			//A voir...
			break;
		}
	}

	int k;
	for (k = 0; k < NB_OPTIONS_TEMPS; k++){
		if (k != j && pageOptions->tabOptionTemps[k][i]->cochee)
			decocherOption(pageOptions->tabOptionTemps[k][i]);
	}
	cocherOption(pageOptions->tabOptionTemps[j][i]);
	afficherPageOptions(pageOptions, contexte);
}


void gererOptionSurbrillance(PageOptions* pageOptions, Booleen* surbrillance2J, Booleen* surbrillanceEntrainement, int i, int j, SDL_Renderer* contexte){
	if (i == MODE_ENTRAINEMENT){
		switch (pageOptions->tabOptionSurbrillance[j][i]->idOption){
		case SURBRILLANCE_ACTIVEE:
			*surbrillanceEntrainement = TRUE;
			break;
		case SURBRILLANCE_DESACTIVEE:
			*surbrillanceEntrainement = FALSE;
			break;
		}
	}

	else if (i == MODE_MULTIJOUEUR){
		switch (pageOptions->tabOptionSurbrillance[j][i]->idOption){
		case SURBRILLANCE_ACTIVEE:
			*surbrillance2J = TRUE;
			break;
		case SURBRILLANCE_DESACTIVEE:
			*surbrillance2J = FALSE;
			break;
		}
	}

	int k;
	for (k = 0; k < 2; k++){
		if (k != j && pageOptions->tabOptionSurbrillance[k][i]->cochee)
			decocherOption(pageOptions->tabOptionSurbrillance[k][i]);
	}
	cocherOption(pageOptions->tabOptionSurbrillance[j][i]);
	afficherPageOptions(pageOptions, contexte);
}