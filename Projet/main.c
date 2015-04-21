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


#define MOUVEMENT_SOURIS_INTERIEUR_ECHIQUIER (event.motion.x > OFFSET_PLATEAU_GAUCHE && event.motion.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && event.motion.y > OFFSET_PLATEAU_HAUT && event.motion.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
#define MOUVEMENT_SOURIS_EXTERIEUR_ECHIQUIER (event.motion.x < OFFSET_PLATEAU_GAUCHE || event.motion.x > LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE || event.motion.y < OFFSET_PLATEAU_HAUT || event.motion.y > HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)
#define CLIC_DOWN_SOURIS_SUR_BOUTON_MENU_GAUCHE (event.button.x > menu->tabBouton[i]->positionInit.x && event.button.x < menu->tabBouton[i]->positionInit.x + menu->tabBouton[i]->dimension.largeur && event.button.y > menu->tabBouton[i]->positionInit.y && event.button.y < menu->tabBouton[i]->positionInit.y + menu->tabBouton[i]->dimension.hauteur)
#define CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE (event.button.x > 0 && event.button.x < OFFSET_PLATEAU_GAUCHE)
#define CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER (event.button.x > OFFSET_PLATEAU_GAUCHE && event.button.x < LARGEUR_FENETRE - OFFSET_PLATEAU_DROITE && event.button.y > OFFSET_PLATEAU_HAUT && event.button.y < HAUTEUR_FENETRE - OFFSET_PLATEAU_BAS)


int main(int argc, char* argv[]){

	//Création ou réinitialisation du fichier de log "log.txt"
	logInit();


	//Création ou réinitialisation du fichier d'historique "Historique.txt"
	createHistoryFile();
	logPrint(INFO, "Création du fichier historique");


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


	//Création de la Liste chaînée des déplacements
	ListDeplacement* l = initListDeplacement();


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
		logPrint(ERREUR, "Création du contexte échoué");


	//Création de l'échiquier 
	Echiquier* echiquier = NULL;
	logPrint(INFO, "Création de l'échiquier");
	echiquier = creerEchiquier(l);
	if (echiquier == NULL)
		logPrint(ERREUR, "Echec de la création de l'échiquier");


	//Création des défausses
	logPrint(INFO, "Création de la défausse blanche");
	Defausse* defausseB = creerDefausse(BLANC);
	if (defausseB == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse blanche");


	logPrint(INFO, "Création de la défausse noire");
	Defausse* defausseN = creerDefausse(NOIR);
	if (defausseB == NULL)
		logPrint(ERREUR, "Echec de la création de la défausse noire");


	//Création du plateau de jeu
	logPrint(INFO, "Création du plateau de jeu");
	PlateauDeJeu* plateau = creerPlateauDeJeu(echiquier, defausseB, defausseN);
	if (plateau == NULL)
		logPrint(ERREUR, "Echec de la création du plateau de jeu");
	afficherPlateauDeJeu(contexte, plateau);


	//Création du menu
	logPrint(INFO, "Création du menu");
	Menu* menu = creerMenu();
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la création du menu");
	afficherMenu(menu, contexte);


	//Création du menu de droite (contenant les défausses)
	logPrint(INFO, "Création du menu de droite");
	MenuDroite* menuDroite = creerMenuDroite(defausseB, defausseN);
	if (menu == NULL)
		logPrint(ERREUR, "Echec de la création du menuDroite");
	afficherFondMenuDroite(menuDroite, contexte);


	//Affichage des défausses
	logPrint(INFO, "Affichage de la défausse blanche");
	afficherDefausse(defausseB, contexte);
	logPrint(INFO, "Affichage de la défausse noire");
	afficherDefausse(defausseN, contexte);


	//Création de l'objet Déplacement Possible
	logPrint(INFO, "Création de l'objet Déplacement Possible");
	DeplacementPossible* deplacementPossible = creerDeplacementPossible();


	//Création du vecteur de déplacements
	logPrint(INFO, "Création de l'objet Vecteur Deplacement");
	VecteurDeplacement* vecteurDeplacement = creerVecteurDeplacement();


	//Création du menu 2 joueurs 
	logPrint(INFO, "Création du menu 2 joueurs");
	Menu2J* menu2J = creerMenuDeuxJoueurs();

	SDL_RenderPresent(contexte);




	//BOUCLE PRINCIPALE 
	logPrint(INFO, "Lancement de la boucle principale du jeu");

	int menuSelectionne = 0; //0=Menu principal, 1=Menu2J
	int menuEnCours = 0; //0=Menu principal, 1=Menu2J

	int continuer = 1;
	int continuerSaisiePseudo = 0;
	int i, j = 0;

	SDL_Event event;
	SDL_Event eventPseudo;
	Position oldPosSouris;

	oldPosSouris.x = 0;
	oldPosSouris.y = 0;

	Case* oldCasePointee = NULL;// plateau->echiquier->tabCases[0][0];
	Case* casePointee = NULL;//  plateau->echiquier->tabCases[0][0];

	Piece* pieceSelectionnee = NULL;
	Case* caseSelectionnee = NULL;
	IDCase idCaseSelectionnee;



	while (continuer)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;



		case SDL_MOUSEBUTTONDOWN:
			//Cas du Menu princpal
			if (menuEnCours == 0){
				if (CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE){
					//Traitement des boutons du menu
					for (i = 0; i < NB_BOUTON_MP; i++){
						if (CLIC_DOWN_SOURIS_SUR_BOUTON_MENU_GAUCHE)
						{
							switch (menu->tabBouton[i]->idBouton){
							case DEUXJOUEURS:
								menuSelectionne = 1;
								break;
							}
							enfoncerBouton(menu->tabBouton[i]);
							afficherMenu(menu, contexte);
						}
					} //Fin du traitement des boutons
				}
			}


			//Cas du Menu 2 joueurs
			else if (menuEnCours == 1){
				if (CLIC_SOURIS_INTERIEUR_PSEUDO_1){
					deselectionnerZonePseudo(menu2J, menu2J->zone2, FALSE, contexte);
					selectionnerZonePseudo(menu2J, menu2J->zone1, TRUE, contexte);
					continuerSaisiePseudo = 1;

					while (continuerSaisiePseudo == 1){
						SDL_WaitEvent(&eventPseudo);
						catSaisiePseudo(eventPseudo, menu2J->zone1, &continuerSaisiePseudo, &continuer);
						menu2J->zone1->ttfPseudo = creerTexte(menu2J->zone1->pseudo, "calibri.ttf", 16, 240, 240, 240);
						afficherMenu2J(menu2J, contexte);
						SDL_RenderPresent(contexte);
						SDL_Delay(10);
					}
					event = eventPseudo;
					deselectionnerZonePseudo(menu2J, menu2J->zone1, TRUE, contexte);
				}

				if (CLIC_SOURIS_INTERIEUR_PSEUDO_2){
					deselectionnerZonePseudo(menu2J, menu2J->zone1, FALSE, contexte);
					selectionnerZonePseudo(menu2J, menu2J->zone2, TRUE, contexte);
					continuerSaisiePseudo = 1;

					while (continuerSaisiePseudo == 1){
						SDL_WaitEvent(&eventPseudo);
						catSaisiePseudo(eventPseudo, menu2J->zone2, &continuerSaisiePseudo, &continuer);
						menu2J->zone2->ttfPseudo = creerTexte(menu2J->zone2->pseudo, "calibri.ttf", 16, 240, 240, 240);
						afficherMenu2J(menu2J, contexte);
						SDL_RenderPresent(contexte);
						SDL_Delay(10);
					}
					event = eventPseudo;
					deselectionnerZonePseudo(menu2J, menu2J->zone2, TRUE, contexte);
				}

				if (!CLIC_SOURIS_INTERIEUR_PSEUDO_1 && !CLIC_SOURIS_INTERIEUR_PSEUDO_2 && CLIC_DOWN_SOURIS_INTERIEUR_MENU_GAUCHE){
					deselectionnerZonePseudo(menu2J, menu2J->zone1, FALSE, contexte);
					deselectionnerZonePseudo(menu2J, menu2J->zone2, TRUE, contexte);
				}

			}


			//Cas de l'échiquier
			if (CLIC_DOWN_SOURIS_INTERIEUR_ECHIQUIER){
				caseSelectionnee = plateau->echiquier->tabCases[(event.button.x - OFFSET_PLATEAU_GAUCHE) / LARGEUR_CASE][(event.button.y - OFFSET_PLATEAU_HAUT) / HAUTEUR_CASE];
				idCaseSelectionnee = caseSelectionnee->identifiant;

				//Si aucune pièce sélectionnée et que la case en contient une
				if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee == NULL){
					pieceSelectionnee = plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne];
					mettreEnSurbillancePiece(pieceSelectionnee, contexte);
					//Calcul des déplacements autorisés pour la pièce nouvellement sélectionnée
					calculerDeplacementPossible(plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne], plateau->echiquier, deplacementPossible, vecteurDeplacement, contexte);
					enregisterMatriceDeplacementPossible(deplacementPossible, "matDepPoss.txt");
				}

				//Si pièce sélectionnée et que la case en contient une
				else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] != NULL && pieceSelectionnee != NULL){
					//Si le déplacement n'est pas possible
					if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 0){
						supprimerSurbillancePiece(pieceSelectionnee, contexte);
						pieceSelectionnee = NULL;
						supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);
					}

					//S'il y a possibilité de manger une pièce
					else if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 2){

						//On met la pièce en défausse
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

						//On déselectionne la pièce
						pieceSelectionnee = NULL;
						supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);
					}
				}


				//Si pièce sélectionnée et que la case n'en contient pas
				else if (plateau->echiquier->tabPieces[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == NULL){
					if (pieceSelectionnee != NULL){
						//Si déplacement autorisé, on l'effectue
						if (deplacementPossible->deplacementPossible[idCaseSelectionnee.colonne][idCaseSelectionnee.ligne] == 1){
							plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = FALSE;
							bougerPiece(pieceSelectionnee, plateau->echiquier->tabPieces, caseSelectionnee->identifiant.colonne, caseSelectionnee->identifiant.ligne, l);
							plateau->echiquier->tabCases[pieceSelectionnee->idPosition.colonne][pieceSelectionnee->idPosition.ligne]->occupee = TRUE;
							supprimerSurbillancePiece(pieceSelectionnee, contexte);
							//Ensuite on déselectionne la pièce
							pieceSelectionnee = NULL;
							supprimerSurbrillanceDeplacementPossibles(deplacementPossible, plateau->echiquier, contexte);
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
			}
			break;



		case SDL_MOUSEBUTTONUP:
			if (menuEnCours == 0){
				//On vérifie que tous les boutons sont bien revenus à leur position initiale
				for (i = 0; i < NB_BOUTON_MP; i++){
					if (menu->tabBouton[i]->enfonce == TRUE){
						desenfoncerBouton(menu->tabBouton[i]);
						afficherMenu(menu, contexte);
					}
				}

				//Si un changement de menu a été demandé, on l'effectue
				if (menuSelectionne != menuEnCours){
					if (menuSelectionne == 1){
						afficherMenu2J(menu2J, contexte);
						menuEnCours = 1;
					}
				}
			}
			break;

		}

		SDL_RenderPresent(contexte);
		SDL_Delay(10);
	}

	SDL_DestroyWindow(screen);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}