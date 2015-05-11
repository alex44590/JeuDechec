#include "commun.h"
#include "case.h"
#include "plateau.h"
#include "menu.h"
#include "piece.h"
#include "echiquier.h"
#include "plateauDeJeu.h"
#include "menuDroite.h"
#include "deplacementPossible.h"
#include "listeDeplacement.h"
#include "evenement.h"
#include "entrainement.h"



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

	//Cr�ation du vecteur de d�placements
	logPrint(INFO, "Cr�ation de l'objet Vecteur Deplacement");
	VecteurDeplacement* vecteurDeplacement = creerVecteurDeplacement();



	/******************************************/
	/***  OUTILS DE GESTION DES EVENEMENTS  ***/
	/******************************************/

	//Cr�ation de la structure input permettant la gestion des �v�nements
	logPrint(INFO, "Cr�ation de la Structure input permettant la gestion des �v�nements");
	Input in;
	memset(&in, 0, sizeof(in)); //Mise � 0 de toute la structure



	/******************************************/
	/*******  PARTIE INTERACTIVE DU JEU   *****/
	/******************************************/
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

	IDCase positionRoi[2];
	positionRoi[BLANC].colonne = D;
	positionRoi[BLANC].ligne = 7;
	positionRoi[NOIR].colonne = D;
	positionRoi[NOIR].ligne = 0;

	Booleen echec;

	while (!in.quit)
	{
		mettreAJourEvent(&in);

		/******************************************/
		/*********   GESTION DES MENUS   **********/
		/******************************************/

		//Cas du Menu princpal
		if (typeMenuEnCours == MENU_ACCUEIL){
			if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE){
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
						}
						enfoncerBouton(menu->tabBouton[i]);
						afficherMenu(menu, contexte);
					}
				}
			}
		}


		//Cas du Menu 2 joueurs
		if (typeMenuEnCours == MENU_2J){
			if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_M2J; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_2JOUEURS)
					{
						switch (menu2J->tabBouton[i]->idBouton){
						case ACCUEIL:
							typeMenuSelectionne = MENU_ACCUEIL;
							break;
						}
						enfoncerBouton(menu2J->tabBouton[i]);
					}
				}
			}
		}


		//Cas du Menu Entrainement
		if (typeMenuEnCours == MENU_ENTRAINEMENT){
			if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE){
				//Traitement des boutons du menu
				for (i = 0; i < NB_BOUTON_MENT; i++){
					if (CLIC_DOWN_SOURIS_BOUTON_MENU_ENTRAINEMENT)
					{
						switch (menuEntrainement->tabBouton[i]->idBouton){
						case ACCUEIL:
							typeMenuSelectionne = MENU_ACCUEIL;
							break;
						}
						enfoncerBouton(menuEntrainement->tabBouton[i]);
						afficherMenuEntrainement(menuEntrainement, contexte);
					}
				}
			}
		}

		//Relachement des boutons
		if (in.sourisRelachee){
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
						situationEchec = &situationEchec2J;
						afficherPlateauDeJeu(contexte, plateau);
						afficherMenuDroite(menuDroite, contexte);
						afficherTexteEchec(menuDroite, *situationEchec, contexte);
						typeMenuEnCours = MENU_2J;
					}

					else if (typeMenuSelectionne == MENU_ENTRAINEMENT){
						afficherMenuEntrainement(menuEntrainement, contexte);
						//Changement du plateau de jeu
						plateau = plateauEntrainement;
						menuEnCours.menuEntrainement = menuEntrainement;
						menuDroite = menuDroiteEntrainement;
						situationEchec = &situationEchecEntrainement;
						afficherPlateauDeJeu(contexte, plateau);
						afficherMenuDroite(menuDroite, contexte);
						afficherTexteEchec(menuDroite, *situationEchec, contexte);
						typeMenuEnCours = MENU_ENTRAINEMENT;
					}
				}
			}

			
			else if (typeMenuEnCours == MENU_2J){
				//On v�rifie que tous les boutons sont bien revenus � leur position initiale
				for (i = 0; i < NB_BOUTON_M2J; i++){
					if (menu2J->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menu2J->tabBouton[i]);
						afficherMenu2J(menu2J, contexte);
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

			
			else if (typeMenuEnCours == MENU_ENTRAINEMENT){
				//On v�rifie que tous les boutons sont bien revenus � leur position initiale
				for (i = 0; i < NB_BOUTON_MENT; i++){
					if (menuEntrainement->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menuEntrainement->tabBouton[i]);
						afficherMenuEntrainement(menuEntrainement, contexte);
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



		/******************************************/
		/********   GESTION DES PSEUDOS   *********/
		/******************************************/

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

			if (CLIC_SOURIS_INTERIEUR_PSEUDO_2 && continuerSaisiePseudo){
				deselectionnerZonePseudo2J(menu2J, menu2J->zone1, FALSE, contexte);
				selectionnerZonePseudo2J(menu2J, menu2J->zone2, TRUE, contexte);
				catSaisiePseudo(&in, menu2J->zone2, &continuerSaisiePseudo);
				menu2J->zone2->ttfPseudo = creerTexte(menu2J->zone2->pseudo, "calibri.ttf", 16, 240, 240, 240);
				afficherMenu2J(menu2J, contexte);
			}

			if (!CLIC_SOURIS_INTERIEUR_PSEUDO_1 && !CLIC_SOURIS_INTERIEUR_PSEUDO_2 && CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE || !continuerSaisiePseudo){
				deselectionnerZonePseudo2J(menu2J, menu2J->zone1, FALSE, contexte);
				deselectionnerZonePseudo2J(menu2J, menu2J->zone2, TRUE, contexte);
			}
		}


		else if (typeMenuEnCours == MENU_ENTRAINEMENT){
			if (in.sourisEnfoncee && (CLIC_SOURIS_INTERIEUR_PSEUDO_1 || CLIC_SOURIS_INTERIEUR_PSEUDO_2))
				continuerSaisiePseudo = 1;

			if (CLIC_SOURIS_INTERIEUR_PSEUDO_1 && continuerSaisiePseudo){
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone2, FALSE, contexte);
				selectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone1, TRUE, contexte);
				catSaisiePseudo(&in, menuEntrainement->zone1, &continuerSaisiePseudo);
				menuEntrainement->zone1->ttfPseudo = creerTexte(menuEntrainement->zone1->pseudo, "calibri.ttf", 16, 240, 240, 240);
				afficherMenuEntrainement(menuEntrainement, contexte);
			}

			if (CLIC_SOURIS_INTERIEUR_PSEUDO_2 && continuerSaisiePseudo){
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone1, FALSE, contexte);
				selectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone2, TRUE, contexte);
				catSaisiePseudo(&in, menuEntrainement->zone2, &continuerSaisiePseudo);
				menuEntrainement->zone2->ttfPseudo = creerTexte(menuEntrainement->zone2->pseudo, "calibri.ttf", 16, 240, 240, 240);
				afficherMenuEntrainement(menuEntrainement, contexte);
			}

			if (!CLIC_SOURIS_INTERIEUR_PSEUDO_1 && !CLIC_SOURIS_INTERIEUR_PSEUDO_2 && CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE || !continuerSaisiePseudo){
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone1, FALSE, contexte);
				deselectionnerZonePseudoEntrainement(menuEntrainement, menuEntrainement->zone2, TRUE, contexte);
			}
		}


		/**************************************************************/
		/*******  DISPOSITION DES PIECES - MODE ENTRAINEMENT   ********/
		/**************************************************************/



		/******************************************/
		/*******  GESTION DE L'ECHIQUIER   ********/
		/******************************************/

		if (CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER && in.sourisEnfoncee && (typeMenuEnCours == MENU_ENTRAINEMENT || typeMenuEnCours == MENU_2J)){
			caseSelectionnee = plateau->echiquier->tabCases[(in.clicSouris.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(in.clicSouris.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
			idCaseSelectionnee = caseSelectionnee->identifiant;

			//Si aucune pi�ce s�lectionn�e et que la case en contient une
			if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee == NULL){
				pieceSelectionnee = plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne];
				mettreEnSurbillancePiece(pieceSelectionnee, contexte);
				//Calcul des d�placements autoris�s pour la pi�ce nouvellement s�lectionn�e
				calculerDeplacementPossible(plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier, deplacementPossible, vecteurDeplacement, TRUE, contexte);
				enregisterMatriceDeplacementPossible(deplacementPossible, "matDepPoss.txt");
			}

			//Si pi�ce s�lectionn�e et que la case en contient une
			else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee != NULL){
				//Si le d�placement n'est pas possible
				if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 0){
					supprimerSurbillancePiece(pieceSelectionnee, contexte);
					pieceSelectionnee = NULL;
					supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);
				}

				//S'il y a possibilit� de manger une pi�ce
				else if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 2){


					//On met la pi�ce en d�fausse
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
					if (pieceSelectionnee->type == ROI && pieceSelectionnee->couleur == BLANC){
						positionRoi[BLANC].colonne = caseSelectionnee->identifiant.colonne;
						positionRoi[BLANC].ligne = caseSelectionnee->identifiant.ligne;
					}
					else if (pieceSelectionnee->type == ROI && pieceSelectionnee->couleur == NOIR){
						positionRoi[NOIR].colonne = caseSelectionnee->identifiant.colonne;
						positionRoi[NOIR].ligne = caseSelectionnee->identifiant.ligne;
					}

					//On v�rifie une �ventuelle position d'�chec du c�t� adverse
					echec = calculerEchec(!pieceSelectionnee->couleur, plateau->echiquier, deplacementPossibleEchec, vecteurDeplacement, positionRoi, contexte);
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
				}
			}


			//Si pi�ce s�lectionn�e et que la case n'en contient pas
			else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == NULL){
				if (pieceSelectionnee != NULL){
					//Si d�placement autoris�, on l'effectue
					if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 1){

						plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = FALSE;
						bougerPiece(pieceSelectionnee, plateau->echiquier->tabPieces, caseSelectionnee->identifiant.colonne, caseSelectionnee->identifiant.ligne, l);
						plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = TRUE;
						echec = calculerEchec(pieceSelectionnee->couleur, plateau->echiquier, deplacementPossibleEchec, vecteurDeplacement, positionRoi, contexte);
						supprimerSurbillancePiece(pieceSelectionnee, contexte);

						//Si on vient de bouger un roi, on enregistre sa nouvelle position (permet d'optimiser le calcul d'�chec par la suite)
						if (pieceSelectionnee->type == ROI && pieceSelectionnee->couleur == BLANC){
							positionRoi[BLANC].colonne = caseSelectionnee->identifiant.colonne;
							positionRoi[BLANC].ligne = caseSelectionnee->identifiant.ligne;
						}
						else if (pieceSelectionnee->type == ROI && pieceSelectionnee->couleur == NOIR){
							positionRoi[NOIR].colonne = caseSelectionnee->identifiant.colonne;
							positionRoi[NOIR].ligne = caseSelectionnee->identifiant.ligne;
						}

						//On v�rifie une �ventuelle position d'�chec du c�t� adverse
						Booleen echec = calculerEchec(!pieceSelectionnee->couleur, plateau->echiquier, deplacementPossibleEchec, vecteurDeplacement, positionRoi, contexte);
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
			afficherTexteEchec(menuDroite, *situationEchec, contexte);
		}

		SDL_RenderPresent(contexte);

	}

	SDL_DestroyWindow(screen);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}