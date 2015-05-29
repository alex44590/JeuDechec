#include "option.h"

PageOptions* creerPageOptions(){
	PageOptions* p = (PageOptions*)malloc(sizeof(PageOptions));
	if (p == NULL)
		logPrint(ERREUR, "Allocation de la page de règle échouée");


	p->imageFondPage = NULL;
	p->imageFondPage = IMG_Load("pageOptions.png");
	if (p->imageFondPage == NULL)
		logPrint(ERREUR, "Impossible de charger l'image de la page d'options");

	int i, j;
	for (j = 0; j < 2; j++){
		for (i = 0; i < 6; i++){
			p->tabOptionTemps[i][j] = creerOption(i, OPTION_1_X + i * 50, OPTION_1_Y + j * 150);
		}
	}

	for (i = 0; i < 2; i++){
		for (j = 0; j < 2; j++){
			p->tabOptionTemps[i][j] = creerOption(i, OPTION_1_X + 6 * 50 + i*70, OPTION_1_Y + j * 150);
		}
	}

	return p;
}

void afficherPageOptions(PageOptions*p, SDL_Renderer* contexte){
	afficherImage(p->imageFondPage, (Position){ LARGEUR_MENU, HAUTEUR_MENU }, (Dimension){ LARGEUR_FENETRE - LARGEUR_MENU, HAUTEUR_MENU }, contexte);
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
	if (o->imageCochee || o->imagePasCochee == NULL)
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