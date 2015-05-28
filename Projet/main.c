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

	//D�marrage de la SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		logPrint(ERREUR, "Erreur d'initialisation de la SDL");
		return EXIT_FAILURE; // On quitte le programme en cas d'erreur
	}
	logPrint(INFO, "Initialisation de la SDL");


	//D�marrage de la SDL_ttf (texte)
	if (TTF_Init() == -1) {
		logPrint(ERREUR, "Erreur d'initialisation de la SDL_ttf");
		return EXIT_FAILURE;
	}
	logPrint(INFO, "Initialisation de la SDL_ttf");


	//Cr�ation de la fenetre
	SDL_Window* screen = SDL_CreateWindow("Jeu d'Echec Multijoueur",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		LARGEUR_FENETRE, HAUTEUR_FENETRE,
		0);


	//Chargement de l'icone
	SDL_Surface* icone = IMG_Load("Icone4.png");
	if (icone == NULL){
		logPrint(ERREUR, "Chargement de l'image pour l'icone �chou�");
		return EXIT_FAILURE;
	}
	logPrint(INFO, "Chargement de l'icone");
	SDL_SetWindowIcon(screen, icone); //Insertion de l'icone dans la fenetre


	//Cr�ation du contexte qui apparaitra dans la fenetre
	SDL_Renderer* contexte = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	logPrint(INFO, "Cr�ation du contexte graphique");
	if (contexte == NULL)
		logPrint(ERREUR, "Cr�ation du contexte �chou�e");



	/******************************************/
	/*******   OUTILS DE SUIVI DU JEU     *****/
	/******************************************/

	//Cr�ation ou r�initialisation du fichier de log "log.txt"
	logInit();

	//Cr�ation ou r�initialisation du fichier d'historique "Historique.txt"
	createHistoryFile();
	logPrint(INFO, "Cr�ation du fichier historique");

	//Cr�ation de la Liste cha�n�e des d�placements
	ListDeplacement* l = initListDeplacement();

	//Cr�ation des situation de jeu qui indiquera s'il y a �chec, pat ...
	logPrint(INFO, "Cr�ation de la situation de jeu 2 joueurs");
	SituationEchec situationEchec2J;
	situationEchec2J = RIEN;

	logPrint(INFO, "Cr�ation de la situation de jeu entrainement");
	SituationEchec situationEchecEntrainement;
	situationEchecEntrainement = RIEN;

	SituationEchec* situationEchec = &situationEchecEntrainement;

	//Cr�ation du contexte de Roque
	logPrint(INFO, "Cr�ation de la structure ContexteRoque recensant les diff�rents �l�ments permettant de valider ou non les conditions du roque");
	ContexteRoque* contexteRoqueEntrainement = creerContexteRoque();
	ContexteRoque* contexteRoque2J = creerContexteRoque();
	ContexteRoque* contexteRoque = contexteRoque2J;


	/******************************************/
	/*******   COMPOSANTS DU PLATEAU     ******/
	/******************************************/

	//Cr�ation des �chiquiers
	Echiquier* echiquier2J = NULL;
	logPrint(INFO, "Cr�ation de l'�chiquier 2 joueurs");
	echiquier2J = creerEchiquier(l, TRUE);
	if (echiquier2J == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de l'�chiquier 2 joueurs");

	Echiquier* echiquierEntrainement = NULL;
	logPrint(INFO, "Cr�ation de l'�chiquier entrainement");
	echiquierEntrainement = creerEchiquier(l, FALSE);
	if (echiquierEntrainement == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de l'�chiquier entrainement");


	//Cr�ation des d�fausses
	logPrint(INFO, "Cr�ation de la d�fausse blanche 2 joueurs");
	Defausse* defausseB2J = creerDefausse(BLANC);
	if (defausseB2J == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de la d�fausse blanche 2 joueurs");

	logPrint(INFO, "Cr�ation de la d�fausse blanche entrainement");
	Defausse* defausseBEntrainement = creerDefausse(BLANC);
	if (defausseBEntrainement == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de la d�fausse blanche");

	logPrint(INFO, "Cr�ation de la d�fausse noire 2 joueurs");
	Defausse* defausseN2J = creerDefausse(NOIR);
	if (defausseN2J == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de la d�fausse noire 2 joueurs");

	logPrint(INFO, "Cr�ation de la d�fausse noire entrainement");
	Defausse* defausseNEntrainement = creerDefausse(NOIR);
	if (defausseNEntrainement == NULL)
		logPrint(ERREUR, "Echec de la cr�ation de la d�fausse noire entrainement");


	//Cr�ation des plateaux de jeu
	logPrint(INFO, "Cr�ation du plateau de jeu 2 joueurs");
	PlateauDeJeu* plateau2J = creerPlateauDeJeu(echiquier2J, defausseB2J, defausseN2J);
	if (plateau2J == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du plateau de jeu 2 joueurs");

	logPrint(INFO, "Cr�ation du plateau de jeu entrainement");
	PlateauDeJeu* plateauEntrainement = creerPlateauDeJeu(echiquierEntrainement, defausseBEntrainement, defausseNEntrainement);
	if (plateauEntrainement == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du plateau de jeu entrainement");

	PlateauDeJeu* plateau = plateauEntrainement;


	//Cr�ations des r�serves pour le mode entrainement
	logPrint(INFO, "Cr�ation des r�serves de pi�ces � placer pour l'entrainement");
	Reserve* reserveB = creerReserve(BLANC);
	Reserve* reserveN = creerReserve(NOIR);
	if (reserveB == NULL || reserveN == NULL)
		logPrint(ERREUR, "Echec de la cr�ation d'une r�serve");



	/******************************************/
	/*******        MENUS DU JEU         ******/
	/******************************************/

	//Cr�ation du menu principal
	logPrint(INFO, "Cr�ation du menu");
	Menu* menu = creerMenu();
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du menu");
	afficherMenu(menu, contexte);

	//Affichage de l'image d'accueil
	logPrint(INFO, "Affichage de l'image d'accueil");
	afficherImageAccueil(menu->imageAccueil, contexte);

	//Cr�ation du menu 2 joueurs 
	logPrint(INFO, "Cr�ation du menu 2 joueurs");
	Menu2J* menu2J = creerMenuDeuxJoueurs();

	//Cr�ation du menu entrainement
	logPrint(INFO, "Cr�ation du menu entrainement");
	MenuEntrainement* menuEntrainement = creerMenuEntrainement(reserveB, reserveN);

	//Cr�ation du menu r�gles
	logPrint(INFO, "Cr�ation du menu r�gles");
	MenuRegles* menuRegles = creerMenuRegles();

	//Cr�ation d'un menu g�n�rique prenant soit la valeur menu2J soit menuEntrainement
	MenuGenerique menuEnCours;
	menuEnCours.menuAccueil = menu;

	//Cr�ation des menus de droite (contenant les d�fausses)
	logPrint(INFO, "Cr�ation du menu de droite 2 joueurs");
	MenuDroite* menuDroite2J = creerMenuDroite(defausseB2J, defausseN2J);
	if (menuDroite2J == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du menuDroite 2 joueurs");

	logPrint(INFO, "Cr�ation du menu de droite entrainement");
	MenuDroite* menuDroiteEntrainement = creerMenuDroite(defausseBEntrainement, defausseNEntrainement);
	if (menuDroiteEntrainement == NULL)
		logPrint(ERREUR, "Echec de la cr�ation du menuDroite entrainement");

	MenuDroite* menuDroite = menuDroiteEntrainement;


	/******************************************/
	/***  OUTILS DE DEPLACEMENT DES PIECES  ***/
	/******************************************/

	//Cr�ation de l'objet D�placement Possible
	logPrint(INFO, "Cr�ation de l'objet D�placement Possible");
	DeplacementPossible* deplacementPossible = creerDeplacementPossible();

	//Cr�ation de l'objet D�placement Possible pour le calcul des positions d'�chec
	logPrint(INFO, "Cr�ation de l'objet D�placement Possible pour les positions d'�chec");
	DeplacementPossible* deplacementPossibleEchec = creerDeplacementPossible();

	//Cr�ation de l'objet D�placement Possible pour le calcul des positions d'�chec anticip� (avant de jouer une pi�ce)
	logPrint(INFO, "Cr�ation de l'objet D�placement Possible pour les positions d'�chec anticip�e");
	DeplacementPossible* deplacementPossibleEchecAnticipe = creerDeplacementPossible();

	//Cr�ation du vecteur de d�placements
	logPrint(INFO, "Cr�ation de l'objet Vecteur Deplacement");
	VecteurDeplacement* vecteurDeplacement = creerVecteurDeplacement();


	/******************************************/
	/*******  REGLES ET OPTIONS DE JEU  *******/
	/******************************************/

	//Cr�ation de la fenetre de r�gles
	logPrint(INFO, "Cr�ation de la fen�tre contenenant les r�gles du jeu");
	FenetreRegle* fenetreRegle = creerFenetreRegle();
	

	/******************************************/
	/***  OUTILS DE GESTION DES EVENEMENTS  ***/
	/******************************************/

	//Cr�ation de la structure input permettant la gestion des �v�nements
	logPrint(INFO, "Cr�ation de la Structure input permettant la gestion des �v�nements");
	Input in;
	memset(&in, 0, sizeof(in)); //Mise � 0 de toute la structure



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
							desenfoncerBouton(menu2J->tabBouton[1]); //On d�senfonce le bouton jouer
							enfoncerBouton(menu2J->tabBouton[2]); //On enfonce le bouton pause
							enfoncerBouton(menu2J->tabBouton[i]); // //On enfonce le bouton press�
							break;
						case JOUER:
							if (PSEUDO_MENU_2J_CORRECT){
								jeuLance = TRUE;
								enfoncerBouton(menu2J->tabBouton[i]); //On enfonce le bouton press�
								desenfoncerBouton(menu2J->tabBouton[2]); //On d�senfonce le bouton pause
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
							enfoncerBouton(menu2J->tabBouton[i]); // //On enfonce le bouton press�
							desenfoncerBouton(menu2J->tabBouton[1]); //On d�senfonce le bouton jouer
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
							enfoncerBouton(menuDroite->tabBouton[i]); // //On enfonce le bouton press�
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
							desenfoncerBouton(menuEntrainement->tabBouton[1]); //On d�senfonce le bouton jouer
							enfoncerBouton(menuEntrainement->tabBouton[2]); //On enfonce le bouton pause
							enfoncerBouton(menuEntrainement->tabBouton[i]); //On enfonce le bouton press�
							break;
						case JOUER:
							if (PSEUDO_MENU_ENTRAINEMENT_CORRECT){
								//Si les rois ont bien �t� positionn�es sur l'�chiquier
								if (positionRoiEntrainement[BLANC].colonne != -1 && positionRoiEntrainement[NOIR].colonne != -1){
									jeuEntrainementLance = TRUE;
									enfoncerBouton(menuEntrainement->tabBouton[i]); //On enfonce le bouton press�
									desenfoncerBouton(menuEntrainement->tabBouton[2]); //On d�senfonce le bouton pause
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
									menuDroiteEntrainement->zoneJoueurEnCours->ttfJoueur = creerTexte("Positionnez les rois sur l'�chiquier!", "calibri.ttf", 16, 255, 100, 100);
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
							enfoncerBouton(menuEntrainement->tabBouton[i]); //On enfonce le bouton press�
							desenfoncerBouton(menuEntrainement->tabBouton[1]); //On d�senfonce le bouton jouer
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
							enfoncerBouton(menuDroite->tabBouton[i]); // //On enfonce le bouton press�
							break;
						}
					}
				}
			}
		}



		//Cas du menu r�gle
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
			//Si on �tait dans le menu accueil
			if (typeMenuEnCours == MENU_ACCUEIL){
				//On v�rifie que tous les boutons sont bien revenus � leur position initiale
				for (i = 0; i < NB_BOUTON_MP; i++){
					if (menu->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menu->tabBouton[i]);
						afficherMenu(menu, contexte);
					}
				}

				//Si un changement de menu a �t� demand�, on l'effectue
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


			//Si on �tait dans le menu 2 joueurs
			else if (typeMenuEnCours == MENU_2J){
				//On v�rifie que tous les boutons sont bien revenus � leur position initiale
				for (i = 0; i < NB_BOUTON_M2J; i++){
					if (menu2J->tabBouton[i]->enfonce == TRUE && menu2J->tabBouton[i]->idBouton != PAUSE && menu2J->tabBouton[i]->idBouton != JOUER){
						desenfoncerBouton(menu2J->tabBouton[i]);
						afficherMenu2J(menu2J, contexte);
					}
				}

				//On v�rifie qu'on a cliqu� sur le bouton retour
				for (i = 0; i < NB_BOUTON_MD; i++){
					if (menuDroite->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menuDroite->tabBouton[i]);
						afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
						retourArriere(l, plateau, menuDroite, contexte, *couleurAJouer, contexteRoque);
						enregisterEchiquier(plateau->echiquier, "Echiquier.txt");
						
					}
				}

				//Si un changement de menu a �t� demand�, on l'effectue
				if (typeMenuSelectionne != typeMenuEnCours){
					if (typeMenuSelectionne == MENU_ACCUEIL){
						afficherMenu(menu, contexte);
						menuEnCours.menuAccueil = menu;
						typeMenuEnCours = MENU_ACCUEIL;
					}
				}
			}


			//Si on �tait dans le menu entrainement
			else if (typeMenuEnCours == MENU_ENTRAINEMENT){
				//On v�rifie que tous les boutons sont bien revenus � leur position initiale
				for (i = 0; i < NB_BOUTON_MENT; i++){
					if (menuEntrainement->tabBouton[i]->enfonce == TRUE && menuEntrainement->tabBouton[i]->idBouton != PAUSE && menuEntrainement->tabBouton[i]->idBouton != JOUER){
						desenfoncerBouton(menuEntrainement->tabBouton[i]);
						afficherMenuEntrainement(menuEntrainement, contexte);
						afficherMenuDroite(menuDroiteEntrainement, *couleurAJouer, contexte);
					}
				}

				//Si un changement de menu a �t� demand�, on l'effectue
				if (typeMenuSelectionne != typeMenuEnCours){
					if (typeMenuSelectionne == MENU_ACCUEIL){
						afficherMenu(menu, contexte);
						menuEnCours.menuAccueil = menu;
						typeMenuEnCours = MENU_ACCUEIL;
					}
				}

				//On v�rifie qu'on a cliqu� sur le bouton retour
				for (i = 0; i < NB_BOUTON_MD; i++){
					if (menuDroite->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menuDroite->tabBouton[i]);
						afficherMenuDroite(menuDroite, *couleurAJouer, contexte);
						retourArriere(l, plateau, menuDroite, contexte, *couleurAJouer, contexteRoque);
						enregisterEchiquier(plateau->echiquier, "Echiquier.txt");

					}
				}
			}


			//Si on �tait dans le menu r�gles
			else if (typeMenuEnCours == MENU_REGLES){
				//On v�rifie que tous les boutons du menu sont bien revenus � leur position initiale
				for (i = 0; i < NB_BOUTON_MREG; i++){
					if (menuRegles->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menuRegles->tabBouton[i]);
						afficherMenuRegles(menuRegles, contexte);
					}
				}

				//On v�rifie que les boutons suivant et pr�c�dent sont revenus � leur position initiale
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

				//Si un changement de menu a �t� demand�, on l'effectue
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
			/***  Entrainement : Selection des pi�ces dans la r�serve  ***/
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

				//Dans tous les cas, si on clique dans la r�serve, on d�selectionne la pi�ce s�lectionn�e dans l'�chiquier
				if (pieceSelectionneeEntrainement != NULL){
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);
					afficherEchiquier(plateau->echiquier, contexte);
					pieceSelectionneeEntrainement = NULL;
				}

				afficherMenuEntrainement(menuEntrainement, contexte);
			}

			//Si clic ailleurs dans le menu entrainement, on d�selectionne la pi�ce
			else if (in.sourisEnfoncee && !CLIC_DOWN_SOURIS_INTERIEUR_RESERVE && CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE && !pieceReserveDejaSelectionnee && pieceReserveSelectionnee != NULL){
				deselectionnerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, pieceReserveSelectionnee->couleur, contexte);
				pieceReserveSelectionnee = NULL;
				pieceReserveDejaSelectionnee = TRUE;
			}

			else if (in.sourisRelachee)
				pieceReserveDejaSelectionnee = FALSE;


			/******************************************************************/
			/***  Entrainement : Positionnement des pi�ces sur l'�chiquier  ***/
			/******************************************************************/

			if (!jeuEntrainementLance && CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER && in.sourisEnfoncee){
				//Pour �viter la r�p�tition du code si l'on garde le clic enfonc� 
				in.sourisEnfoncee = FALSE;

				caseSelectionneeEntrainement = plateau->echiquier->tabCases[(in.clicSouris.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(in.clicSouris.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
				idCaseSelectionneeEntrainement = caseSelectionneeEntrainement->identifiant;

				//Si on clique sur une pi�ce dans l'�chiquier et qu'on avait d�j� s�lectionn� une pi�ce dans la r�serve
				if (plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] != NULL && pieceReserveSelectionnee != NULL && pieceSelectionneeEntrainement == NULL){
					//On d�selectionne la pi�ce de la r�serve et on s�lectionne celle de l'�chiquier
					deselectionnerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, pieceReserveSelectionnee->couleur, contexte);
					pieceReserveSelectionnee = NULL;
					pieceSelectionneeEntrainement = plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne];
					mettreEnSurbillancePiece(pieceSelectionneeEntrainement, contexte);
				}

				//Si on clique sur une pi�ce dans l'�chiquier et qu'aucune pi�ce de la r�serve n'est s�lectionn�e ni aucune pi�ce de l'�chiquier
				else if (plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] != NULL && pieceSelectionneeEntrainement == NULL && pieceReserveSelectionnee == NULL){
					pieceSelectionneeEntrainement = plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne];
					mettreEnSurbillancePiece(pieceSelectionneeEntrainement, contexte);
				}

				//Si on clique sur une pi�ce dans l'�chiquier et qu'une pi�ce de l'�chiquier diff�rente est d�j� s�lectionn�e 
				else if (plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] != NULL && pieceSelectionneeEntrainement != NULL && pieceReserveSelectionnee == NULL){
					//On supprime la surbrillance de la pi�ce pr�c�dente
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);

					//S'il ne s'agit pas de la m�me pi�ce, on s�lectionne la nouvelle pi�ce
					if (pieceSelectionneeEntrainement != plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne]){
						pieceSelectionneeEntrainement = plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne];
						mettreEnSurbillancePiece(pieceSelectionneeEntrainement, contexte);
					}
					else
						pieceSelectionneeEntrainement = NULL;
				}


				//Si une pi�ce est s�lectionn�e dans la r�serve et que la case n'en contient pas
				else if (pieceReserveSelectionnee != NULL && plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] == NULL){
					//On supprime la pi�ce de la r�serve
					supprimerPieceReserve(reserveB, reserveN, pieceReserveSelectionnee, contexte);
					afficherMenuEntrainement(menuEntrainement, contexte);

					//On d�place la pi�ce sur l'�chiquier
					bougerPiece(pieceReserveSelectionnee, plateau->echiquier->tabPieces, caseSelectionneeEntrainement->identifiant.colonne, caseSelectionneeEntrainement->identifiant.ligne, l);
					plateau->echiquier->tabCases[pieceReserveSelectionnee->idPosition.colonne][pieceReserveSelectionnee->idPosition.ligne]->occupee = TRUE;
					supprimerSurbillancePiece(pieceReserveSelectionnee, contexte);

					//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'�chec par la suite)
					if (pieceReserveSelectionnee->type == ROI && pieceReserveSelectionnee->couleur == BLANC){
						positionRoiEntrainement[BLANC].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[BLANC].ligne = caseSelectionneeEntrainement->identifiant.ligne;					
					}
					else if (pieceReserveSelectionnee->type == ROI && pieceReserveSelectionnee->couleur == NOIR){
						positionRoiEntrainement[NOIR].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[NOIR].ligne = caseSelectionneeEntrainement->identifiant.ligne;
					}

					//On d�selectionne la pi�ce
					pieceReserveSelectionnee = NULL;
				}


				//Si une pi�ce est s�lectionn�e sur l'�chiquier et que la case n'en contient pas
				else if (pieceSelectionneeEntrainement != NULL && plateau->echiquier->tabPieces[idCaseSelectionneeEntrainement.colonne][idCaseSelectionneeEntrainement.ligne] == NULL){
					//On d�place la pi�ce sur l'�chiquier
					bougerPiece(pieceSelectionneeEntrainement, plateau->echiquier->tabPieces, caseSelectionneeEntrainement->identifiant.colonne, caseSelectionneeEntrainement->identifiant.ligne, l);
					plateau->echiquier->tabCases[pieceSelectionneeEntrainement->idPosition.colonne][pieceSelectionneeEntrainement->idPosition.ligne]->occupee = TRUE;
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);

					//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'�chec par la suite)
					if (pieceSelectionneeEntrainement->type == ROI && pieceSelectionneeEntrainement->couleur == BLANC){
						positionRoiEntrainement[BLANC].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[BLANC].ligne = caseSelectionneeEntrainement->identifiant.ligne;
					}
					else if (pieceSelectionneeEntrainement->type == ROI && pieceSelectionneeEntrainement->couleur == NOIR){
						positionRoiEntrainement[NOIR].colonne = caseSelectionneeEntrainement->identifiant.colonne;
						positionRoiEntrainement[NOIR].ligne = caseSelectionneeEntrainement->identifiant.ligne;
					}
					//Ensuite on d�selectionne la pi�ce de la r�serve
					supprimerSurbillancePiece(pieceSelectionneeEntrainement, contexte);
					pieceSelectionneeEntrainement = NULL;
				}
				afficherEchiquier(plateau->echiquier, contexte);
			}


			//Si on clique en dehors de l'�chiquier, on d�selectionne la possible pi�ce s�lectionn�e
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
			//Pour �viter la r�p�tition du code si l'on garde le clic enfonc� 
			in.sourisEnfoncee = FALSE;

			//On calcule la case correspondant � la position du clic souris effectu�
			caseSelectionnee = plateau->echiquier->tabCases[(in.clicSouris.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(in.clicSouris.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
			idCaseSelectionnee = caseSelectionnee->identifiant;

			//Si aucune pi�ce s�lectionn�e et que la case en contient une
			if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee == NULL){
				//S'il s'agit bien de la couleur � jouer
				if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->couleur == (*couleurAJouer)){
					pieceSelectionnee = plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne];
					mettreEnSurbillancePiece(pieceSelectionnee, contexte);
					//Calcul des d�placements autoris�s pour la pi�ce nouvellement s�lectionn�e
					calculerDeplacementPossible(plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier, deplacementPossible, vecteurDeplacement, TRUE, contexte);
					
					/**********************TEST ECHEC ANTICIPE*********************/
					//On supprime de la matrice des d�placements possibles les cases o� la pi�ce mettrait le roi en �chec si elle s'y rendait
					supprimerDeplacementPossibleEchecAnticipe(plateau->echiquier, pieceSelectionnee, deplacementPossible, deplacementPossibleEchecAnticipe, vecteurDeplacement, *positionRoi, contexte);
					/******************** FIN TEST ECHEC ANTICIPE*********************/

					enregisterMatriceDeplacementPossible(deplacementPossible, "matDepPoss.txt");
				}
			}

			//Si pi�ce s�lectionn�e et que la case en contient une
			else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee != NULL){
				
				//S'il y a possibilit� de roque
				if (gererRoqueSiPossible(pieceSelectionnee, plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier, contexteRoque, l)){
					
					/********** TEST ECHEC ANTICIPE ! **************/
					Booleen echecAnticipe = calculerEchecAnticipe(plateau->echiquier, pieceSelectionnee, idCaseSelectionnee.colonne, idCaseSelectionnee.ligne, deplacementPossibleEchecAnticipe, vecteurDeplacement, *positionRoi, contexte);
					if (echecAnticipe)
						logPrint(INFO, "** ATTENTION ! ******** POSITION D'ECHEC ANTICIPEE DETECTEE ! **********");
					/********** FIN TEST ECHEC ANTICIPE ! **************/


					//On v�rifie une �ventuelle position d'�chec du c�t� adverse
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

					//On d�selectionne la pi�ce
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



				//Si le d�placement n'est pas possible
				else if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 0){
					supprimerSurbillancePiece(pieceSelectionnee, contexte);
					pieceSelectionnee = NULL;
					supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);
				}


				//S'il y a possibilit� de manger une pi�ce
				else if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 2){


					/********** TEST ECHEC ANTICIPE ! **************/
					Booleen echecAnticipe = calculerEchecAnticipe(plateau->echiquier, pieceSelectionnee, idCaseSelectionnee.colonne, idCaseSelectionnee.ligne, deplacementPossibleEchecAnticipe, vecteurDeplacement, *positionRoi, contexte);
					if (echecAnticipe)
						logPrint(INFO, "** ATTENTION ! ******** POSITION D'ECHEC ANTICIPEE DETECTEE ! **********");
					/********** FIN TEST ECHEC ANTICIPE ! **************/

					//On met la pi�ce en d�fausse

					IDPiece idPieceASortir = plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->idPiece;
					l->current->IDPieceManger = idPieceASortir;
					if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->couleur == BLANC)
						mettrePieceDefausse(plateau->defausseBlanc, plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], contexte);
					else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne]->couleur == NOIR)
						mettrePieceDefausse(plateau->defausseNoir, plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], contexte);

					//On mange la pi�ce 
					mangerPiece(plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier->tabPieces, l);
					plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = FALSE;
					

					//Ensuite on bouge la pi�ce s�lectionn�e sur la case nouvellement libre
					bougerPiece(pieceSelectionnee, plateau->echiquier->tabPieces, caseSelectionnee->identifiant.colonne, caseSelectionnee->identifiant.ligne, l);
					plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = TRUE;
					supprimerSurbillancePiece(pieceSelectionnee, contexte);

					//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'�chec par la suite)
					if (pieceSelectionnee->type == ROI){
						(*positionRoi[pieceSelectionnee->couleur]).colonne = caseSelectionnee->identifiant.colonne;
						(*positionRoi[pieceSelectionnee->couleur]).ligne = caseSelectionnee->identifiant.ligne;
						contexteRoque->roiDejaBouge[pieceSelectionnee->couleur] = TRUE;
					}
					//Si on vient de bouger une tour, on l'indique pour le roque
					if (pieceSelectionnee->type == TOUR){
						contexteRoque->tourDejaBouge[pieceSelectionnee->couleur][pieceSelectionnee->idPiece.numero] = TRUE;
					}

					//On v�rifie une �ventuelle position d'�chec du c�t� adverse
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


					//On d�selectionne la pi�ce
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


			//Si pi�ce s�lectionn�e et que la case n'en contient pas
			else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == NULL){
				if (pieceSelectionnee != NULL){
					//Si d�placement autoris�, on l'effectue
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
						l->current->IDPieceManger = pieceSelectionnee->idPiece; //Piece mang� = pi�ce s�lectionner pour fonction retour arri�re

						//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'�chec par la suite)
						if (pieceSelectionnee->type == ROI){
							(*positionRoi[pieceSelectionnee->couleur]).colonne = caseSelectionnee->identifiant.colonne;
							(*positionRoi[pieceSelectionnee->couleur]).ligne = caseSelectionnee->identifiant.ligne;
							contexteRoque->roiDejaBouge[pieceSelectionnee->couleur] = TRUE;
						}
						//Si on vient de bouger une tour, on l'indique pour le roque
						if (pieceSelectionnee->type == TOUR){
							contexteRoque->tourDejaBouge[pieceSelectionnee->couleur][pieceSelectionnee->idPiece.numero] = TRUE;
						}

						//On v�rifie une �ventuelle position d'�chec du c�t� adverse
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

						//Ensuite on d�selectionne la pi�ce
						pieceSelectionnee = NULL;
						supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);

						//Au tour de l'autre couleur de jouer, et on remet � 0 le chrono
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

					//Sinon, on d�selectionne la pi�ce
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