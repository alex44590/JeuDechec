#include "regle.h"

PageRegle* creerPageRegle(char numPage, Booleen boutonPrecedent, Booleen boutonSuivant){
	PageRegle* p = (PageRegle*)malloc(sizeof(PageRegle));
	if (p == NULL)
		logPrint(ERREUR, "Allocation de la page de règle échouée");

	char nomFichier[] = "Regles/ .png";
	nomFichier[7] = numPage;

	p->imageRegle = NULL;
	p->imageRegle = IMG_Load(nomFichier);
	if (p->imageRegle == NULL)
		logPrint(ERREUR, "Impossible de charger l'image de la page de règle");

	logPrint(INFO, "Nom de l'image de page regle chargée ci dessous :");
	logPrint(INFO, nomFichier);


	p->boutons[0] = NULL;
	p->boutons[1] = NULL;

	if (boutonPrecedent){
		p->boutons[0] = creerBouton(REGLEPRECEDENTE, "Regles/boutonPrecedent.png");
		setPositionBouton(p->boutons[0], X_BOUTON_REGLE_PRECEDENT, Y_BOUTON_REGLE_PRECEDENT);
		setTailleBouton(p->boutons[0], LARGEUR_BOUTON_REGLE, HAUTEUR_BOUTON_REGLE);
	}
	if (boutonSuivant){
		p->boutons[1] = creerBouton(REGLESUIVANTE, "Regles/boutonSuivant.png");
		setPositionBouton(p->boutons[1], X_BOUTON_REGLE_SUIVANT, Y_BOUTON_REGLE_SUIVANT);
		setTailleBouton(p->boutons[1], LARGEUR_BOUTON_REGLE, HAUTEUR_BOUTON_REGLE);
	}
	
	return p;
}


void afficherPageRegle(PageRegle* p, SDL_Renderer* contexte){
	SDL_Texture* textFond = SDL_CreateTextureFromSurface(contexte, p->imageRegle);
	SDL_Rect positionAffichage;
	positionAffichage.x = LARGEUR_MENU;
	positionAffichage.y = 0;
	positionAffichage.w = LARGEUR_FENETRE-LARGEUR_MENU;
	positionAffichage.h = HAUTEUR_FENETRE;
	SDL_RenderCopy(contexte, textFond, NULL, &positionAffichage);
	SDL_DestroyTexture(textFond);
	logPrint(INFO, "Affichage Page Regle");
	if (p->boutons[0] != NULL)
		afficherBouton(p->boutons[0], contexte);
	if (p->boutons[1] != NULL)
		afficherBouton(p->boutons[1], contexte);
}


FenetreRegle* creerFenetreRegle(){
	FenetreRegle* f = (FenetreRegle*)malloc(sizeof(FenetreRegle));
	if (f == NULL)
		logPrint(ERREUR, "Allocation de la fenetre de règles échouée");

	int i;
	f->numPageEnCours = 0;

	f->pagesRegles[0] = creerPageRegle('0', FALSE, TRUE);
	for (i = 1; i < NB_PAGES_REGLES - 1; i++){
		f->pagesRegles[i] = creerPageRegle(i+48, TRUE, TRUE);
	}
	f->pagesRegles[NB_PAGES_REGLES - 1] = creerPageRegle(NB_PAGES_REGLES + 47, TRUE, FALSE);

	return f;
}


void afficherFenetreRegle(FenetreRegle* f, SDL_Renderer* contexte){
	afficherPageRegle(f->pagesRegles[f->numPageEnCours], contexte);
}


void pageRegleSuivante(FenetreRegle* f){
	if (f->numPageEnCours < NB_PAGES_REGLES - 1)
		f->numPageEnCours++;
	else
		logPrint(AVERTISSEMENT, "Tentative d'accéder à la page de règle suivante alors qu'il n'en existe pas");
}


void pageReglePrecedente(FenetreRegle* f){
	if (f->numPageEnCours > 0)
		f->numPageEnCours--;
	else 
		logPrint(AVERTISSEMENT, "Tentative d'accéder à la page de règle précédente alors qu'il n'en existe pas");
}