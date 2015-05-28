#include "commun.h"
#include "case.h"
#include "menu.h"
#include "piece.h"
#include "echiquier.h"
#include "plateauDeJeu.h"
#include "menuDroite.h"
#include "deplacementPossible.h"
#include "listeDeplacement.h"
#include "evenement.h"
#include "entrainement.h"
#include "timer.h"
#include "regle.h"
#include "deplacement.h"


int main(int argc, char* argv[]){

	/******************************************/
	/*********     CONTEXTE SDL      **********/
	/******************************************/

	//Démarrage de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		logPrint(ERREUR, "Erreur d'initialisation de la SDL");
		return EXIT_FAILURE; // On quitte le programme en cas d'erreur
	}
	logPrint(INFO, "Initialisation de la SDL");


	//Démarrage de la SDL_ttf (texte)
	if (TTF_Init() == -1) {
		logPrint(ERREUR, "Erreur d'initialisation de la SDL_ttf");
		return EXIT_FAILURE;
	}
	logPrint(INFO, "Initialisation de la SDL_ttf");


	//Création de la fenetre
	SDL_Window* screen = SDL_CreateWindow("Jeu d'Echec Multijoueur",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		LARGEUR_FENETRE, HAUTEUR_FENETRE,
		0);


	//Chargement de l'icone
	SDL_Surface* icone = IMG_Load("Icone4.png");
	if (icone == NULL){
		logPrint(ERREUR, "Chargement de l'image pour l'icone échoué");
		return EXIT_FAILURE;
	}
	logPrint(INFO, "Chargement de l'icone");
	SDL_SetWindowIcon(screen, icone); //Insertion de l'icone dans la fenetre


	//Création du contexte qui apparaitra dans la fenetre
	SDL_Renderer* contexte = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	logPrint(INFO, "Création du contexte graphique");
	if (contexte == NULL)
		logPrint(ERREUR, "Création du contexte échouée");



	/******************************************/
	/*******   OUTILS DE SUIVI DU JEU     *****/
	/******************************************/

	//Création ou réinitialisation du fichier de log "log.txt"
	logInit();

	//Création ou réinitialisation du fichier d'historique "Historique.txt"
	createHistoryFile();
	logPrint(INFO, "Création du fichier historique");

	//Création de la Liste chaînée des déplacements
	ListDeplacement* l = initListDeplacement();

	//Création des situation de jeu qui indiquera s'il y a échec, pat ...
	logPrint(INFO, "Création de la situation de jeu 2 joueurs");
	SituationEchec situationEchec2J;
	situationEchec2J = RIEN;

	logPrint(INFO, "Création de la situation de jeu entrainement");
	SituationEchec situationEchecEntrainement;
	situationEchecEntrainement = RIEN;

	SituationEchec* situationEchec = &situationEchecEntrainement;

	//Création du contexte de Roque
	logPrint(INFO, "Création de la structure ContexteRoque recensant les différents éléments permettant de valider ou non les conditions du roque");
	ContexteRoque* contexteRoqueEntrainement = creerContexteRoque();
	ContexteRoque* contexteRoque2J = creerContexteRoque();
	ContexteRoque* contexteRoque = contexteRoque2J;


	/******************************************/
	/*******   COMPOSANTS DU PLATEAU     ******/
	/******************************************/

	//Création des échiquiers
	Echiquier* echiquier2J = NULL;
	logPrint(INFO, "Création de l'échiquier 2 joueurs");
	echiquier2J = creerEchiquier(l, TRUE);
	if (echiquier2J == NULL)
		logPrint(ERREUR, "Echec de la création de l'échiquier 2 joueurs");

	Echiquier* echiquierEntrainement = NULL;
	logPrint(INFO, "Création de l'échiquier entrainement");
	echiquierEntrainement = creerEchiquier(l, FALSE);
	if (echiquierEntrainement == NULL)
		logPrint(ERREUR, "Echec de la création de l'échiquier entrainement");


	//Création des défausses
	logPrint(INFO, "Création de la défausse blanche 2 joueurs");
	Defausse* defausseB2J = creerDefausse(BLANC);
	if (defausseB2J == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse blanche 2 joueurs");

	logPrint(INFO, "Création de la défausse blanche entrainement");
	Defausse* defausseBEntrainement = creerDefausse(BLANC);
	if (defausseBEntrainement == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse blanche");

	logPrint(INFO, "Création de la défausse noire 2 joueurs");
	Defausse* defausseN2J = creerDefausse(NOIR);
	if (defausseN2J == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse noire 2 joueurs");

	logPrint(INFO, "Création de la défausse noire entrainement");
	Defausse* defausseNEntrainement = creerDefausse(NOIR);
	if (defausseNEntrainement == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse noire entrainement");


	//Création des plateaux de jeu
	logPrint(INFO, "Création du plateau de jeu 2 joueurs");
	PlateauDeJeu* plateau2J = creerPlateauDeJeu(echiquier2J, defausseB2J, defausseN2J);
	if (plateau2J == NULL)
		logPrint(ERREUR, "Echec de la création du plateau de jeu 2 joueurs");

	logPrint(INFO, "Création du plateau de jeu entrainement");
	PlateauDeJeu* plateauEntrainement = creerPlateauDeJeu(echiquierEntrainement, defausseBEntrainement, defausseNEntrainement);
	if (plateauEntrainement == NULL)
		logPrint(ERREUR, "Echec de la création du plateau de jeu entrainement");

	PlateauDeJeu* plateau = plateauEntrainement;


	//Créations des réserves pour le mode entrainement
	logPrint(INFO, "Création des réserves de pièces à placer pour l'entrainement");
	Reserve* reserveB = creerReserve(BLANC);
	Reserve* reserveN = creerReserve(NOIR);
	if (reserveB == NULL || reserveN == NULL)
		logPrint(ERREUR, "Echec de la création d'une réserve");



	/******************************************/
	/*******        MENUS DU JEU         ******/
	/******************************************/

	//Création du menu principal
	logPrint(INFO, "Création du menu");
	Menu* menu = creerMenu();
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la création du menu");
	afficherMenu(menu, contexte);

	//Affichage de l'image d'accueil
	logPrint(INFO, "Affichage de l'image d'accueil");
	afficherImageAccueil(menu->imageAccueil, contexte);

	//Création du menu 2 joueurs 
	logPrint(INFO, "Création du menu 2 joueurs");
	Menu2J* menu2J = creerMenuDeuxJoueurs();

	//Création du menu entrainement
	logPrint(INFO, "Création du menu entrainement");
	MenuEntrainement* menuEntrainement = creerMenuEntrainement(reserveB, reserveN);

	//Création du menu règles
	logPrint(INFO, "Création du menu règles");
	MenuRegles* menuRegles = creerMenuRegles();

	//Création d'un menu générique prenant soit la valeur menu2J soit menuEntrainement
	MenuGenerique menuEnCours;
	menuEnCours.menuAccueil = menu;

	//Création des menus de droite (contenant les défausses)
	logPrint(INFO, "Création du menu de droite 2 joueurs");
	MenuDroite* menuDroite2J = creerMenuDroite(defausseB2J, defausseN2J);
	if (menuDroite2J == NULL)
		logPrint(ERREUR, "Echec de la création du menuDroite 2 joueurs");

	logPrint(INFO, "Création du menu de droite entrainement");
	MenuDroite* menuDroiteEntrainement = creerMenuDroite(defausseBEntrainement, defausseNEntrainement);
	if (menuDroiteEntrainement == NULL)
		logPrint(ERREUR, "Echec de la création du menuDroite entrainement");

	MenuDroite* menuDroite = menuDroiteEntrainement;


	/******************************************/
	/***  OUTILS DE DEPLACEMENT DES PIECES  ***/
	/******************************************/

	//Création de l'objet Déplacement Possible
	logPrint(INFO, "Création de l'objet Déplacement Possible");
	DeplacementPossible* deplacementPossible = creerDeplacementPossible();

	//Création de l'objet Déplacement Possible pour le calcul des positions d'échec
	logPrint(INFO, "Création de l'objet Déplacement Possible pour les positions d'échec");
	DeplacementPossible* deplacementPossibleEchec = creerDeplacementPossible();

	//Création de l'objet Déplacement Possible pour le calcul des positions d'échec anticipé (avant de jouer une pièce)
	logPrint(INFO, "Création de l'objet Déplacement Possible pour les positions d'échec anticipée");
	DeplacementPossible* deplacementPossibleEchecAnticipe = creerDeplacementPossible();

	//Création du vecteur de déplacements
	logPrint(INFO, "Création de l'objet Vecteur Deplacement");
	VecteurDeplacement* vecteurDeplacement = creerVecteurDeplacement();


	/******************************************/
	/*******  REGLES ET OPTIONS DE JEU  *******/
	/******************************************/

	//Création de la fenetre de règles
	logPrint(INFO, "Création de la fenêtre contenenant les règles du jeu");
	FenetreRegle* fenetreRegle = creerFenetreRegle();
	

	/******************************************/
	/***  OUTILS DE GESTION DES EVENEMENTS  ***/
	/******************************************/

	//Création de la structure input permettant la gestion des évènements
	logPrint(INFO, "Création de la Structure input permettant la gestion des évènements");
	Input in;
	memset(&in, 0, sizeof(in)); //Mise à 0 de toute la structure



	/*******************************************************/
	/*******  VARIABLES UTILES AU DEROULEMENT DE JEU  ******/
	/*******************************************************/
	logPrint(INFO, "Lancement de la boucle principale du jeu");

	TYPE_MENU typeMenuSelectionne = MENU_ACCUEIL;
	TYPE_MENU typeMenuEnCours = MENU_ACCUEIL;

	int continuer = 1;
	int continuerSaisiePseudo = 0;
	int i, j = 0;

	Position oldPosSouris;

	oldPosSouris.x = 0;
	oldPosSouris.y = 0;

	Case* oldCasePointee = NULL;// plateau->echiquier->tabCases[0][0];
	Case* casePointee = NULL;//  plateau->echiquier->tabCases[0][0];

	Piece* pieceSelectionnee = NULL;
	Case* caseSelectionnee = NULL;
	IDCase idCaseSelectionnee;

	Piece* pieceReserveSelectionnee = NULL;
	Booleen pieceReserveDejaSelectionnee = FALSE;
	Piece* pieceSelectionneeEntrainement = NULL;
	Case* caseSelectionneeEntrainement = NULL;
	IDCase idCaseSelectionneeEntrainement;

	IDCase positionRoi2J[2];
	positionRoi2J[BLANC].colonne = E;
	positionRoi2J[BLANC].ligne = 7;
	positionRoi2J[NOIR].colonne = E;
	positionRoi2J[NOIR].ligne = 0;

	IDCase positionRoiEntrainement[2];
	positionRoiEntrainement[BLANC].colonne = -1;
	positionRoiEntrainement[BLANC].ligne = -1;
	positionRoiEntrainement[NOIR].colonne = -1;
	positionRoiEntrainement[NOIR].ligne = -1;

	IDCase* positionRoi[2];
	positionRoi[0] = &positionRoi2J[0];
	positionRoi[1] = &positionRoi2J[1];

	Booleen jeuLance = FALSE;
	Booleen jeuEntrainementLance = FALSE;

	Couleur couleurAJouerEntrainement = BLANC;
	Couleur couleurAJouer2J = BLANC;
	Couleur* couleurAJouer = &couleurAJouer2J;

	Booleen echec;


	/*******************************************************/
	/*******  VARIABLES UTILES AU DEROULEMENT DE JEU  ******/
	/*******************************************************/
	logPrint(INFO, "Lancement de la boucle principale du jeu");
	while (!in.quit)
	{
		mettreAJourEvent(&in);

		/******************************************/
		/*********   GESTION DES TIMERS  **********/
		/******************************************/
		//update_timer(menuDroiteEntrainement->timer[0], !jeuEntrainementLance || *couleurAJouer);
		//update_timer(menuDroiteEntrainement->timer[1], !jeuEntrainementLance || !*couleurAJouer);
		//update_timer(menuDroite2J->timer[0], !jeuLance || *couleurAJouer);
		//update_timer(menuDroite2J->timer[1], !jeuLance || !*couleurAJouer);


		//On rafraichit l'affichage du chrono si besoin est
		if (typeMenuEnCours == MENU_2J){
			if (menuDroite2J->timer[*couleurAJouer]->reaffichageNecessaire)
				afficherMenuDroite(menuDroite2J, *couleurAJouer, contexte);
		}

		else if (typeMenuEnCours == MENU_ENTRAINEMENT){
			if (menuDroiteEntrainement->timer[*couleurAJouer]->reaffichageNecessaire)
				afficherMenuDroite(menuDroiteEntrainement, *couleurAJouer, contexte);
		}


		/******************************************/
		/*********   GESTION DES MENUS   **********/
		/******************************************/

		//Cas du Menu princpal
		if (typeMenuEnCours == MENU_ACCUEIL){
			if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE && in.sourisEnfoncee){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_MP; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_PRINCIPAL)
					{
						switch (menu->tabBouton[i]->idBouton){
						case DEUXJOUEURS:
							typeMenuSelectionne = MENU_2J;
							break;
						case ENTRAINEMENT:
							typeMenuSelectionne = MENU_ENTRAINEMENT;
							break;
						case REGLES:
							typeMenuSelectionne = MENU_REGLES;
							break;
						}
						enfoncerBouton(menu->tabBouton[i]);
						afficherMenu(menu, contexte);
					}
				}
			}
		}


		//Cas du Menu 2 joueurs
		if (typeMenuEnCours == MENU_2J){
			if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE && in.sourisEnfoncee){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_M2J; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_2JOUEURS)
					{
						switch (menu2J->tabBouton[i]->idBouton){
						case ACCUEIL:
							typeMenuSelectionne = MENU_ACCUEIL;
							jeuLance = FALSE;
							desenfoncerBouton(menu2J->tabBouton[1]); //On désenfonce le bouton jouer
							enfoncerBouton(menu2J->tabBouton[2]); //On enfonce le bouton pause
							enfoncerBouton(menu2J->tabBouton[i]); // //On enfonce le bouton pressé
							break;
						case JOUER:
							if (PSEUDO_MENU_2J_CORRECT){
								jeuLance = TRUE;
								enfoncerBouton(menu2J->tabBouton[i]); //On enfonce le bouton pressé
								desenfoncerBouton(menu2J->tabBouton[2]); //On désenfonce le bouton pause
								afficherMenu2J(menu2J, contexte);
								//On affiche le joueur qui doit jouer
								if (couleurAJouer2J == BLANC)
									menuDroite2J->zoneJoueurEnCours->ttfJoueur = menu2J->zone1->ttfPseudo;
								else
									menuDroite2J->zoneJoueurEnCours->ttfJoueur = menu2J->zone2->ttfPseudo;
								afficherMenuDroite(menuDroite2J, *couleurAJouer, contexte);
							}
							else{
								menuDroite2J->zoneJoueurEnCours->ttfJoueur = creerTexte("Entrez le nom des joueurs !", "calibri.ttf", 16, 255, 100, 100);
								afficherMenuDroite(menuDroite2J, *couleurAJouer, contexte);
							}
							break;
						case PAUSE:
							jeuLance = FALSE;
							enfoncerBouton(menu2J->tabBouton[i]); // //On enfonce le bouton pressé
							desenfoncerBouton(menu2J->tabBouton[1]); //On désenfonce le bouton jouer
							afficherMenu2J(menu2J, contexte);
							break;
						}
					}
				}
			}

			//Si clic sur bouton du menu droite (retour par exemple)
			else if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_DROITE){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_MD; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_DROITE)
					{
						switch (menuDroite->tabBouton[i]->idBouton){
						case RETOUR:
							enfoncerBouton(menuDroite->tabBouton[i]); // //On enfonce le bouton pressé
							afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
							break;
						}
					}
				}
			}
		}


		//Cas du Menu Entrainement
		if (typeMenuEnCours == MENU_ENTRAINEMENT){
			if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE && in.sourisEnfoncee){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_MENT; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_ENTRAINEMENT)
					{
						switch (menuEntrainement->tabBouton[i]->idBouton){
						case ACCUEIL:
							typeMenuSelectionne = MENU_ACCUEIL;
							jeuEntrainementLance = FALSE;
							desenfoncerBouton(menuEntrainement->tabBouton[1]); //On désenfonce le bouton jouer
							enfoncerBouton(menuEntrainement->tabBouton[2]); //On enfonce le bouton pause
							enfoncerBouton(menuEntrainement->tabBouton[i]); //On enfonce le bouton pressé
							break;
						case JOUER:
							if (PSEUDO_MENU_ENTRAINEMENT_CORRECT){
								//Si les rois ont bien été positionnées sur l'échiquier
								if (positionRoiEntrainement[BLANC].colonne != -1 && positionRoiEntrainement[NOIR].colonne != -1){
									jeuEntrainementLance = TRUE;
									enfoncerBouton(menuEntrainement->tabBouton[i]); //On enfonce le bouton pressé
									desenfoncerBouton(menuEntrainement->tabBouton[2]); //On désenfonce le bouton pause
									afficherMenuEntrainement(menuEntrainement, contexte);
									//On affiche le joueur qui doit jouer
									if (couleurAJouerEntrainement == BLANC)
										menuDroiteEntrainement->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone1->ttfPseudo;

									else
										menuDroiteEntrainement->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone2->ttfPseudo;
									afficherMenuDroite(menuDroiteEntrainement, *couleurAJouer, contexte);
								}
								//Si ce n'est pas le cas, on affiche un message d'erreur
								else{
									menuDroiteEntrainement->zoneJoueurEnCours->ttfJoueur = creerTexte("Positionnez les rois sur l'échiquier!", "calibri.ttf", 16, 255, 100, 100);
									afficherMenuDroite(menuDroiteEntrainement, *couleurAJouer, contexte);
								}
							}

							else{
								menuDroiteEntrainement->zoneJoueurEnCours->ttfJoueur = creerTexte("Entrez le nom des joueurs !", "calibri.ttf", 16, 255, 100, 100);
								afficherMenuDroite(menuDroiteEntrainement, *couleurAJouer, contexte);
							}
							break;
						case PAUSE:
							jeuEntrainementLance = FALSE;
							enfoncerBouton(menuEntrainement->tabBouton[i]); //On enfonce le bouton pressé
							desenfoncerBouton(menuEntrainement->tabBouton[1]); //On désenfonce le bouton jouer
							afficherMenuEntrainement(menuEntrainement, contexte);
							break;
						}
						afficherMenuEntrainement(menuEntrainement, contexte);
					}
				}
			}

			//Si clic sur bouton du menu droite (retour par exemple)
			else if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_DROITE){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_MD; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_DROITE)
					{
						switch (menuDroite->tabBouton[i]->idBouton){
						case RETOUR:
							enfoncerBouton(menuDroite->tabBouton[i]); // //On enfonce le bouton pressé
							break;
						}
					}
				}
			}
		}



		//Cas du menu règle
		if (typeMenuEnCours == MENU_REGLES){
			if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE && in.sourisEnfoncee){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_MREG; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_REGLES)
					{
						switch (menuRegles->tabBouton[i]->idBouton){
						case ACCUEIL:
							typeMenuSelectionne = MENU_ACCUEIL;
							break;
						}
						enfoncerBouton(menuRegles->tabBouton[i]);
						afficherMenuRegles(menuRegles, contexte);
					}
				}
			}

			else if (CLIC_DOWN_SOURIS_BOUTON_REGLE_PRECEDENTE){
				if (fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[0] != NULL){
					enfoncerBouton(fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[0]);
					afficherFenetreRegle(fenetreRegle, contexte);
				}
			}

			else if (CLIC_DOWN_SOURIS_BOUTON_REGLE_SUIVANTE){
				if (fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[1] != NULL){
					enfoncerBouton(fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[1]);
					afficherFenetreRegle(fenetreRegle, contexte);
				}
			}
		}



		//Relachement des boutons
		if (in.sourisRelachee){
			//Si on était dans le menu accueil
			if (typeMenuEnCours == MENU_ACCUEIL){
				//On vérifie que tous les boutons sont bien revenus à leur position initiale
				for (i = 0; i < NB_BOUTON_MP; i++){
					if (menu->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menu->tabBouton[i]);
						afficherMenu(menu, contexte);
					}
				}

				//Si un changement de menu a été demandé, on l'effectue
				if (typeMenuSelectionne != typeMenuEnCours){
					if (typeMenuSelectionne == MENU_2J){
						afficherMenu2J(menu2J, contexte);
						//Changement du plateau de jeu
						plateau = plateau2J;
						menuEnCours.menu2J = menu2J;
						menuDroite = menuDroite2J;
						couleurAJouer = &couleurAJouer2J;
						situationEchec = &situationEchec2J;
						contexteRoque = contexteRoque2J;
						positionRoi[0] = &positionRoi2J[0];
						positionRoi[1] = &positionRoi2J[1];
						afficherPlateauDeJeu(contexte, plateau);
						afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
						mettreAJourTexteEchec(menuDroite, *couleurAJouer, *situationEchec, contexte);
						typeMenuEnCours = MENU_2J;
					}

					else if (typeMenuSelectionne == MENU_ENTRAINEMENT){
						afficherMenuEntrainement(menuEntrainement, contexte);
						//Changement du plateau de jeu
						plateau = plateauEntrainement;
						menuEnCours.menuEntrainement = menuEntrainement;
						menuDroite = menuDroiteEntrainement;
						couleurAJouer = &couleurAJouerEntrainement;
						situationEchec = &situationEchecEntrainement;
						contexteRoque = contexteRoqueEntrainement;
						positionRoi[0] = &positionRoiEntrainement[0];
						positionRoi[1] = &positionRoiEntrainement[1];
						afficherPlateauDeJeu(contexte, plateau);
						afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
						mettreAJourTexteEchec(menuDroite, *couleurAJouer, *situationEchec, contexte);
						typeMenuEnCours = MENU_ENTRAINEMENT;
					}

					else if (typeMenuSelectionne == MENU_REGLES){
						afficherMenuRegles(menuRegles, contexte);
						afficherFenetreRegle(fenetreRegle, contexte);
						typeMenuEnCours = MENU_REGLES;
					}
				}
			}


			//Si on était dans le menu 2 joueurs
			else if (typeMenuEnCours == MENU_2J){
				//On vérifie que tous les boutons sont bien revenus à leur position initiale
				for (i = 0; i < NB_BOUTON_M2J; i++){
					if (menu2J->tabBouton[i]->enfonce == TRUE && menu2J->tabBouton[i]->idBouton != PAUSE && menu2J->tabBouton[i]->idBouton != JOUER){
						desenfoncerBouton(menu2J->tabBouton[i]);
						afficherMenu2J(menu2J, contexte);
					}
				}

				//On vérifie qu'on a cliqué sur le bouton retour
				for (i = 0; i < NB_BOUTON_MD; i++){
					if (menuDroite->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menuDroite->tabBouton[i]);
						afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
						retourArriere(l, plateau, menuDroite, contexte, *couleurAJouer, contexteRoque);
						enregisterEchiquier(plateau->echiquier, "Echiquier.txt");
						
					}
				}

				//Si un changement de menu a été demandé, on l'effectue
				if (typeMenuSelectionne != typeMenuEnCours){
					if (typeMenuSelectionne == MENU_ACCUEIL){
						afficherMenu(menu, contexte);
						menuEnCours.menuAccueil = menu;
						typeMenuEnCours = MENU_ACCUEIL;
					}
				}
			}


			//Si on était dans le menu entrainement
			else if (typeMenuEnCours == MENU_ENTRAINEMENT){
				//On vérifie que tous les boutons sont bien revenus à leur position initiale
				for (i = 0; i < NB_BOUTON_MENT; i++){
					if (menuEntrainement->tabBouton[i]->enfonce == TRUE && menuEntrainement->tabBouton[i]->idBouton != PAUSE && menuEntrainement->tabBouton[i]->idBouton != JOUER){
						desenfoncerBouton(menuEntrainement->tabBouton[i]);
						afficherMenuEntrainement(menuEntrainement, contexte);
						afficherMenuDroite(menuDroiteEntrainement, *couleurAJouer, contexte);
					}
				}

				//Si un changement de menu a été demandé, on l'effectue
				if (typeMenuSelectionne != typeMenuEnCours){
					if (typeMenuSelectionne == MENU_ACCUEIL){
						afficherMenu(menu, contexte);
						menuEnCours.menuAccueil = menu;
						typeMenuEnCours = MENU_ACCUEIL;
					}
				}

				//On vérifie qu'on a cliqué sur le bouton retour
				for (i = 0; i < NB_BOUTON_MD; i++){
					if (menuDroite->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menuDroite->tabBouton[i]);
						afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
						retourArriere(l, plateau, menuDroite, contexte, *couleurAJouer, contexteRoque);
						enregisterEchiquier(plateau->echiquier, "Echiquier.txt");

					}
				}
			}


			//Si on était dans le menu règles
			else if (typeMenuEnCours == MENU_REGLES){
				//On vérifie que tous les boutons du menu sont bien revenus à leur position initiale
				for (i = 0; i < NB_BOUTON_MREG; i++){
					if (menuRegles->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menuRegles->tabBouton[i]);
						afficherMenuRegles(menuRegles, contexte);
					}
				}

				//On vérifie que les boutons suivant et précédent sont revenus à leur position initiale
				if (fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[0] != NULL){
					if (fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[0]->enfonce){
						desenfoncerBouton(fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[0]);
						pageReglePrecedente(fenetreRegle);
						afficherFenetreRegle(fenetreRegle, contexte);
					}
				}

				if (fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[1] != NULL){
					if (fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[1]->enfonce){
						desenfoncerBouton(fenetreRegle->pagesRegles[fenetreRegle->numPageEnCours]->boutons[1]);
						pageRegleSuivante(fenetreRegle);
						afficherFenetreRegle(fenetreRegle, contexte);
					}
				}

				//Si un changement de menu a été demandé, on l'effectue
				if (typeMenuSelectionne != typeMenuEnCours){
					if (typeMenuSelectionne == MENU_ACCUEIL){
						afficherMenu(menu, contexte);
						menuEnCours.menuAccueil = menu;
						typeMenuEnCours = MENU_ACCUEIL;
					}
				}
			}
		}



		/*****************************************/
		/********   GESTION DES PSEUDOS  *********/
		/*****************************************/

		/****     Dans le menu 2 joueurs     ****/
		if (typeMenuEnCours == MENU_2J){
			if (in.sourisEnfoncee && (CLIC_SOURIS_INTERIEUR_PSEUDO_1 || CLIC_SOURIS_INTERIEUR_PSEUDO_2))
				continuerSaisiePseudo = 1;

			if (CLIC_SOURIS_INTERIEUR_PSEUDO_1 && continuerSaisiePseudo){
				deselectionnerZonePseudo2J(menu2J, menu2J->zone2, FALSE, contexte);
				selectionnerZonePseudo2J(menu2J, menu2J->zone1, TRUE, contexte);
				catSaisiePseudo(&in, menu2J->zone1, &continuerSaisiePseudo);
				menu2J->zone1->ttfPseudo = creerTexte(menu2J->zone1->pseudo, "calibri.ttf", 16, 240, 240, 240);
				afficherMenu2J(menu2J, contexte);
			}

			else if (CLIC_SOURIS_INTERIEUR_PSEUDO_2 && continuerSaisiePseudo){
				deselectionnerZonePseudo2J(menu2J, menu2J->zone1, FALSE, contexte);
				selectionnerZonePseudo2J(menu2J, menu2J->zone2, TRUE, contexte);
				catSaisiePseudo(&in, menu2J->zone2, &continuerSaisiePseudo);
				menu2J->zone2->ttfPseudo = creerTexte(menu2J->zone2->pseudo, "calibri.ttf", 16, 240, 240, 240);
				afficherMenu2J(menu2J, contexte);
			}

			else if (in.sourisEnfoncee && !CLIC_SOURIS_INTERIEUR_PSEUDO_1 && !CLIC_SOURIS_INTERIEUR_PSEUDO_2 && CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE || !continuerSaisiePseudo){
				deselectionnerZonePseudo2J(menu2J, menu2J->zone1, FALSE, contexte);
				deselectionnerZonePseudo2J(menu2J, menu2J->zone2, TRUE, contexte);
			}

			else if (in.sourisEnfoncee && !CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE){
				deselectionnerZonePseudo2J(menu2J, menu2J->zone1, FALSE, contexte);
				deselectionnerZonePseudo2J(menu2J, menu2J->zone2, TRUE, contexte);
			}
		}


		/****     Dans le menu entrainement     ****/
		else if (typeMenuEnCours == MENU_ENTRAINEMENT){
			if (in.sourisEnfoncee && (CLIC_SOURIS_INTERIEUR_PSEUDO_1 || CLIC_SOURIS_INTERIEUR_PSEUDO_2)){
				continuerSaisiePseudo = 1;
			}

			if (CLIC_SOURIS_INTERIEUR_PSEUDO_1 && continuerSaisiePseudo){
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone2, FALSE, contexte);
				selectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone1, TRUE, contexte);
				catSaisiePseudo(&in, menuEntrainement->zone1, &continuerSaisiePseudo);
				menuEntrainement->zone1->ttfPseudo = creerTexte(menuEntrainement->zone1->pseudo, "calibri.ttf", 16, 240, 240, 240);
				afficherMenuEntrainement(menuEntrainement, contexte);
			}

			else if (CLIC_SOURIS_INTERIEUR_PSEUDO_2 && continuerSaisiePseudo){
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone1, FALSE, contexte);
				selectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone2, TRUE, contexte);
				catSaisiePseudo(&in, menuEntrainement->zone2, &continuerSaisiePseudo);
				menuEntrainement->zone2->ttfPseudo = creerTexte(menuEntrainement->zone2->pseudo, "calibri.ttf", 16, 240, 240, 240);
				afficherMenuEntrainement(menuEntrainement, contexte);
			}

			else if (in.sourisEnfoncee && !CLIC_SOURIS_INTERIEUR_PSEUDO_1 && !CLIC_SOURIS_INTERIEUR_PSEUDO_2 && CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE || !continuerSaisiePseudo){
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone1, FALSE, contexte);
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone2, TRUE, contexte);
			}

			else if (in.sourisEnfoncee && !CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE){
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone1, FALSE, contexte);
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone2, TRUE, contexte);
			}
		}


		/**************************************************************/
		/*******  DISPOSITION DES PIECES - MODE ENTRAINEMENT   ********/
		/**************************************************************/
		if (typeMenuEnCours == MENU_ENTRAINEMENT){

			/*************************************************************/
			/***  Entrainement : Selection des pièces dans la réserve  ***/
			/*************************************************************/
			if (in.sourisEnfoncee && CLIC_DOWN_SOURIS_INTERIEUR_RESERVE && !pieceReserveDejaSelectionnee && !jeuEntrainementLance){

				if (pieceReserveSelectionnee == NULL){
					pieceReserveSelectionnee = selectionnerPieceReserve(reserveB, reserveN, in.clicSouris.x, in.clicSouris.y, contexte);
					pieceReserveDejaSelectionnee = TRUE;

				}

				else if (pieceReserveSelectionnee == selectionnerPieceReserve(reserveB, reserveN, in.clicSouris.x, in.clicSouris.y, contexte)){
					deselectionnerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, pieceReserveSelectionnee->couleur, contexte);
					pieceReserveSelectionnee = NULL;
					pieceReserveDejaSelectionnee = TRUE;
				}

				else{
					deselectionnerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, pieceReserveSelectionnee->couleur, contexte);
					pieceReserveSelectionnee = selectionnerPieceReserve(reserveB, reserveN, in.clicSouris.x, in.clicSouris.y, contexte);
					pieceReserveDejaSelectionnee = TRUE;
				}

				//Dans tous les cas, si on clique dans la réserve, on déselectionne la pièce sélectionnée dans l'échiquier
				if (pieceSelectionneeEntrainement != NULL){
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);
					afficherEchiquier(plateau->echiquier, contexte);
					pieceSelectionneeEntrainement = NULL;
				}

				afficherMenuEntrainement(menuEntrainement, contexte);
			}

			//Si clic ailleurs dans le menu entrainement, on déselectionne la pièce
			else if (in.sourisEnfoncee && !CLIC_DOWN_SOURIS_INTERIEUR_RESERVE && CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE && !pieceReserveDejaSelectionnee && pieceReserveSelectionnee != NULL){
				deselectionnerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, pieceReserveSelectionnee->couleur, contexte);
				pieceReserveSelectionnee = NULL;
				pieceReserveDejaSelectionnee = TRUE;
			}

			else if (in.sourisRelachee)
				pieceReserveDejaSelectionnee = FALSE;


			/******************************************************************/
			/***  Entrainement : Positionnement des pièces sur l'échiquier  ***/
			/******************************************************************/

			if (!jeuEntrainementLance && CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER && in.sourisEnfoncee){
				//Pour éviter la répétition du code si l'on garde le clic enfoncé 
				in.sourisEnfoncee = FALSE;

				caseSelectionneeEntrainement = plateau->echiquier->tabCases[(in.clicSouris.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(in.clicSouris.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
				idCaseSelectionneeEntrainement = caseSelectionneeEntrainement->identifiant;

				//Si on clique sur une pièce dans l'échiquier et qu'on avait déjà sélectionné une pièce dans la réserve
				if (plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] != NULL && pieceReserveSelectionnee != NULL && pieceSelectionneeEntrainement == NULL){
					//On déselectionne la pièce de la réserve et on sélectionne celle de l'échiquier
					deselectionnerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, pieceReserveSelectionnee->couleur, contexte);
					pieceReserveSelectionnee = NULL;
					pieceSelectionneeEntrainement = plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne];
					mettreEnSurbillancePiece(pieceSelectionneeEntrainement, contexte);
				}

				//Si on clique sur une pièce dans l'échiquier et qu'aucune pièce de la réserve n'est sélectionnée ni aucune pièce de l'échiquier
				else if (plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] != NULL && pieceSelectionneeEntrainement == NULL && pieceReserveSelectionnee == NULL){
					pieceSelectionneeEntrainement = plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne];
					mettreEnSurbillancePiece(pieceSelectionneeEntrainement, contexte);
				}

				//Si on clique sur une pièce dans l'échiquier et qu'une pièce de l'échiquier différente est déjà sélectionnée 
				else if (plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] != NULL && pieceSelectionneeEntrainement != NULL && pieceReserveSelectionnee == NULL){
					//On supprime la surbrillance de la pièce précédente
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);

					//S'il ne s'agit pas de la même pièce, on sélectionne la nouvelle pièce
					if (pieceSelectionneeEntrainement != plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne]){
						pieceSelectionneeEntrainement = plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne];
						mettreEnSurbillancePiece(pieceSelectionneeEntrainement, contexte);
					}
					else
						pieceSelectionneeEntrainement = NULL;
				}


				//Si une pièce est sélectionnée dans la réserve et que la case n'en contient pas
				else if (pieceReserveSelectionnee != NULL && plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] == NULL){
					//On supprime la pièce de la réserve
					supprimerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, contexte);
					afficherMenuEntrainement(menuEntrainement, contexte);

					//On déplace la pièce sur l'échiquier
					bougerPiece(pieceReserveSelectionnee, plateau->echiquier->tabPieces, caseSelectionneeEntrainement->identifiant.colonne, caseSelectionneeEntrainement->identifiant.ligne, l);
					plateau->echiquier->tabCases[pieceReserveSelectionnee->idPosition.colonne][pieceReserveSelectionnee->idPosition.ligne]->occupee = TRUE;
					supprimerSurbillancePiece(pieceReserveSelectionnee, contexte);

					//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'échec par la suite)
					if (pieceReserveSelectionnee->type == ROI && pieceReserveSelectionnee->couleur == BLANC){
						positionRoiEntrainement[BLANC].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[BLANC].ligne = caseSelectionneeEntrainement->identifiant.ligne;					
					}
					else if (pieceReserveSelectionnee->type == ROI && pieceReserveSelectionnee->couleur == NOIR){
						positionRoiEntrainement[NOIR].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[NOIR].ligne = caseSelectionneeEntrainement->identifiant.ligne;
					}

					//On déselectionne la pièce
					pieceReserveSelectionnee = NULL;
				}


				//Si une pièce est sélectionnée sur l'échiquier et que la case n'en contient pas
				else if (pieceSelectionneeEntrainement != NULL && plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] == NULL){
					//On déplace la pièce sur l'échiquier
					bougerPiece(pieceSelectionneeEntrainement, plateau->echiquier->tabPieces, caseSelectionneeEntrainement->identifiant.colonne, caseSelectionneeEntrainement->identifiant.ligne, l);
					plateau->echiquier->tabCases[pieceSelectionneeEntrainement->idPosition.colonne][pieceSelectionneeEntrainement->idPosition.ligne]->occupee = TRUE;
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);

					//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'échec par la suite)
					if (pieceSelectionneeEntrainement->type == ROI && pieceSelectionneeEntrainement->couleur == BLANC){
						positionRoiEntrainement[BLANC].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[BLANC].ligne = caseSelectionneeEntrainement->identifiant.ligne;
					}
					else if (pieceSelectionneeEntrainement->type == ROI && pieceSelectionneeEntrainement->couleur == NOIR){
						positionRoiEntrainement[NOIR].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[NOIR].ligne = caseSelectionneeEntrainement->identifiant.ligne;
					}
					//Ensuite on déselectionne la pièce de la réserve
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);
					pieceSelectionneeEntrainement = NULL;
				}
				afficherEchiquier(plateau->echiquier, contexte);
			}


			//Si on clique en dehors de l'échiquier, on déselectionne la possible pièce sélectionnée
			else if (!jeuEntrainementLance && in.sourisEnfoncee && !CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER){
				if (pieceSelectionneeEntrainement != NULL){
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);
					pieceSelectionneeEntrainement = NULL;
					afficherEchiquier(plateau->echiquier, contexte);
				}
			}
		}


		/******************************************/
		/*******  GESTION DE L'ECHIQUIER   ********/
		/******************************************/

		if (CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER && in.sourisEnfoncee && ((typeMenuEnCours == MENU_ENTRAINEMENT && jeuEntrainementLance) || (typeMenuEnCours == MENU_2J && jeuLance))){
			//Pour éviter la répétition du code si l'on garde le clic enfoncé 
			in.sourisEnfoncee = FALSE;

			//On calcule la case correspondant à la position du clic souris effectué
			caseSelectionnee = plateau->echiquier->tabCases[(in.clicSouris.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(in.clicSouris.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
			idCaseSelectionnee = caseSelectionnee->identifiant;

			//Si aucune pièce sélectionnée et que la case en contient une
			if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee == NULL){
				//S'il s'agit bien de la couleur à jouer
				if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->couleur == (*couleurAJouer)){
					pieceSelectionnee = plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne];
					mettreEnSurbillancePiece(pieceSelectionnee, contexte);
					//Calcul des déplacements autorisés pour la pièce nouvellement sélectionnée
					calculerDeplacementPossible(plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier, deplacementPossible, vecteurDeplacement, TRUE, contexte);
					
					/**********************TEST ECHEC ANTICIPE*********************/
					//On supprime de la matrice des déplacements possibles les cases où la pièce mettrait le roi en échec si elle s'y rendait
					supprimerDeplacementPossibleEchecAnticipe(plateau->echiquier, pieceSelectionnee, deplacementPossible, deplacementPossibleEchecAnticipe, vecteurDeplacement, *positionRoi, contexte);
					/******************** FIN TEST ECHEC ANTICIPE*********************/

					enregisterMatriceDeplacementPossible(deplacementPossible, "matDepPoss.txt");
				}
			}

			//Si pièce sélectionnée et que la case en contient une
			else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee != NULL){
				
				//S'il y a possibilité de roque
				if (gererRoqueSiPossible(pieceSelectionnee, plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier, contexteRoque, l)){
					
					/********** TEST ECHEC ANTICIPE ! **************/
					Booleen echecAnticipe = calculerEchecAnticipe(plateau->echiquier, pieceSelectionnee, idCaseSelectionnee.colonne, idCaseSelectionnee.ligne, deplacementPossibleEchecAnticipe, vecteurDeplacement, *positionRoi, contexte);
					if (echecAnticipe)
						logPrint(INFO, "** ATTENTION ! ******** POSITION D'ECHEC ANTICIPEE DETECTEE ! **********");
					/********** FIN TEST ECHEC ANTICIPE ! **************/


					//On vérifie une éventuelle position d'échec du côté adverse
					echec = calculerEchec(!pieceSelectionnee->couleur, plateau->echiquier, deplacementPossibleEchec, vecteurDeplacement, *positionRoi, contexte);
					enregisterMatriceDeplacementPossible(deplacementPossibleEchec, "MatDechec.txt");
					if (echec){
						logPrint(INFO, "********** POSITION D'ECHEC DETECTEE ! **********");
						if (pieceSelectionnee->couleur == NOIR)
							*situationEchec = ECHEC_BLANC;
						else
							*situationEchec = ECHEC_NOIR;
					}
					else
						*situationEchec = RIEN;

					//On déselectionne la pièce
					supprimerSurbillancePiece(pieceSelectionnee, contexte);
					pieceSelectionnee = NULL;
					supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);

					//Au tour de l'autre couleur de jouer.
					*couleurAJouer = !(*couleurAJouer);
					if (*couleurAJouer == BLANC){
						if (typeMenuEnCours == MENU_ENTRAINEMENT)
							menuDroite->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone1->ttfPseudo;
						else
							menuDroite->zoneJoueurEnCours->ttfJoueur = menu2J->zone1->ttfPseudo;
					}
					else{
						if (typeMenuEnCours == MENU_ENTRAINEMENT)
							menuDroite->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone2->ttfPseudo;
						else
							menuDroite->zoneJoueurEnCours->ttfJoueur = menu2J->zone2->ttfPseudo;
					}
					afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
				}



				//Si le déplacement n'est pas possible
				else if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 0){
					supprimerSurbillancePiece(pieceSelectionnee, contexte);
					pieceSelectionnee = NULL;
					supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);
				}


				//S'il y a possibilité de manger une pièce
				else if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 2){


					/********** TEST ECHEC ANTICIPE ! **************/
					Booleen echecAnticipe = calculerEchecAnticipe(plateau->echiquier, pieceSelectionnee, idCaseSelectionnee.colonne, idCaseSelectionnee.ligne, deplacementPossibleEchecAnticipe, vecteurDeplacement, *positionRoi, contexte);
					if (echecAnticipe)
						logPrint(INFO, "** ATTENTION ! ******** POSITION D'ECHEC ANTICIPEE DETECTEE ! **********");
					/********** FIN TEST ECHEC ANTICIPE ! **************/

					//On met la pièce en défausse

					IDPiece idPieceASortir = plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->idPiece;
					l->current->IDPieceManger = idPieceASortir;
					if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->couleur == BLANC)
						mettrePieceDefausse(plateau->defausseBlanc, plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], contexte);
					else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->couleur == NOIR)
						mettrePieceDefausse(plateau->defausseNoir, plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], contexte);

					//On mange la pièce 
					mangerPiece(plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier->tabPieces, l);
					plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = FALSE;
					

					//Ensuite on bouge la pièce sélectionnée sur la case nouvellement libre
					bougerPiece(pieceSelectionnee, plateau->echiquier->tabPieces, caseSelectionnee->identifiant.colonne, caseSelectionnee->identifiant.ligne, l);
					plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = TRUE;
					supprimerSurbillancePiece(pieceSelectionnee, contexte);

					//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'échec par la suite)
					if (pieceSelectionnee->type == ROI){
						(*positionRoi[pieceSelectionnee->couleur]).colonne = caseSelectionnee->identifiant.colonne;
						(*positionRoi[pieceSelectionnee->couleur]).ligne = caseSelectionnee->identifiant.ligne;
						contexteRoque->roiDejaBouge[pieceSelectionnee->couleur] = TRUE;
					}
					//Si on vient de bouger une tour, on l'indique pour le roque
					if (pieceSelectionnee->type == TOUR){
						contexteRoque->tourDejaBouge[pieceSelectionnee->couleur][pieceSelectionnee->idPiece.numero] = TRUE;
					}

					//On vérifie une éventuelle position d'échec du côté adverse
					echec = calculerEchec(!pieceSelectionnee->couleur, plateau->echiquier, deplacementPossibleEchec, vecteurDeplacement, *positionRoi, contexte);
					enregisterMatriceDeplacementPossible(deplacementPossibleEchec, "MatDechec.txt");
					if (echec){
						logPrint(INFO, "********** POSITION D'ECHEC DETECTEE ! **********");
						if (pieceSelectionnee->couleur == NOIR)
							*situationEchec = ECHEC_BLANC;
						else
							*situationEchec = ECHEC_NOIR;
					}
					else
						*situationEchec = RIEN;


					//On déselectionne la pièce
					pieceSelectionnee = NULL;
					supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);

					//Au tour de l'autre couleur de jouer.
					*couleurAJouer = !(*couleurAJouer);
					if (*couleurAJouer == BLANC){
						if (typeMenuEnCours == MENU_ENTRAINEMENT)
							menuDroite->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone1->ttfPseudo;
						else
							menuDroite->zoneJoueurEnCours->ttfJoueur = menu2J->zone1->ttfPseudo;}
					else{
						if (typeMenuEnCours == MENU_ENTRAINEMENT)
							menuDroite->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone2->ttfPseudo;
						else
							menuDroite->zoneJoueurEnCours->ttfJoueur = menu2J->zone2->ttfPseudo;}
					afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
				}
			}


			//Si pièce sélectionnée et que la case n'en contient pas
			else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == NULL){
				if (pieceSelectionnee != NULL){
					//Si déplacement autorisé, on l'effectue
					if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 1){

						/********** TEST ECHEC ANTICIPE ! **************/
						Booleen echecAnticipe = calculerEchecAnticipe(plateau->echiquier, pieceSelectionnee, idCaseSelectionnee.colonne, idCaseSelectionnee.ligne, deplacementPossibleEchecAnticipe, vecteurDeplacement, *positionRoi, contexte);
						if (echecAnticipe)
							logPrint(INFO, "** ATTENTION ! ******** POSITION D'ECHEC ANTICIPEE DETECTEE ! **********");
						/********** FIN TEST ECHEC ANTICIPE ! **************/

						plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = FALSE;
						bougerPiece(pieceSelectionnee, plateau->echiquier->tabPieces, caseSelectionnee->identifiant.colonne, caseSelectionnee->identifiant.ligne, l);
						plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = TRUE;
						echec = calculerEchec(pieceSelectionnee->couleur, plateau->echiquier, deplacementPossibleEchec, vecteurDeplacement, *positionRoi, contexte);
						supprimerSurbillancePiece(pieceSelectionnee, contexte);
						l->current->IDPieceManger = pieceSelectionnee->idPiece; //Piece mangé = pièce sélectionner pour fonction retour arrière

						//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'échec par la suite)
						if (pieceSelectionnee->type == ROI){
							(*positionRoi[pieceSelectionnee->couleur]).colonne = caseSelectionnee->identifiant.colonne;
							(*positionRoi[pieceSelectionnee->couleur]).ligne = caseSelectionnee->identifiant.ligne;
							contexteRoque->roiDejaBouge[pieceSelectionnee->couleur] = TRUE;
						}
						//Si on vient de bouger une tour, on l'indique pour le roque
						if (pieceSelectionnee->type == TOUR){
							contexteRoque->tourDejaBouge[pieceSelectionnee->couleur][pieceSelectionnee->idPiece.numero] = TRUE;
						}

						//On vérifie une éventuelle position d'échec du côté adverse
						Booleen echec = calculerEchec(!pieceSelectionnee->couleur, plateau->echiquier, deplacementPossibleEchec, vecteurDeplacement, *positionRoi, contexte);
						enregisterMatriceDeplacementPossible(deplacementPossibleEchec, "MatDechec.txt");
						if (echec){
							logPrint(INFO, "********** POSITION D'ECHEC DETECTEE ! **********");
							if (pieceSelectionnee->couleur == NOIR)
								*situationEchec = ECHEC_BLANC;
							else
								*situationEchec = ECHEC_NOIR;
						}
						else
							*situationEchec = RIEN;

						//Ensuite on déselectionne la pièce
						pieceSelectionnee = NULL;
						supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);

						//Au tour de l'autre couleur de jouer, et on remet à 0 le chrono
						*couleurAJouer = !(*couleurAJouer);
						menuDroite->couleurEnCours = *couleurAJouer;
						if (*couleurAJouer == BLANC){
							if (typeMenuEnCours == MENU_ENTRAINEMENT)
								menuDroite->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone1->ttfPseudo;
							else
								menuDroite->zoneJoueurEnCours->ttfJoueur = menu2J->zone1->ttfPseudo;
						}
						else{
							if (typeMenuEnCours == MENU_ENTRAINEMENT)
								menuDroite->zoneJoueurEnCours->ttfJoueur = menuEntrainement->zone2->ttfPseudo;
							else
								menuDroite->zoneJoueurEnCours->ttfJoueur = menu2J->zone2->ttfPseudo;
						}
						afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
					}

					//Sinon, on déselectionne la pièce
					else{
						supprimerSurbillancePiece(pieceSelectionnee, contexte);
						pieceSelectionnee = NULL;
						supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);
					}
				}
			}
			afficherEchiquier(plateau->echiquier, contexte);
			enregisterEchiquier(plateau->echiquier, "Echiquier.txt");
			mettreAJourTexteEchec(menuDroite, *couleurAJouer, *situationEchec, contexte);
		}


		
		SDL_RenderPresent(contexte);


	}

	SDL_DestroyWindow(screen);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}