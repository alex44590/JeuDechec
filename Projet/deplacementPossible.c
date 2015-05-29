#include "deplacementPossible.h"

DeplacementPossible* creerDeplacementPossible(){
	DeplacementPossible* d = (DeplacementPossible *)malloc(sizeof(DeplacementPossible));
	if (d == NULL)
		logPrint(ERREUR, "Allocation de la mémoire pour la structure DeplacementPossible échouée...");
	int i;
	int j;

	d->pieceConcernee = NULL;

	//En théorie pas besoin d'initialiser à 0 mais bon...
	for (i = 0; i < LARGEUR_MATRICE_DEPLACEMENT_POSSIBLE; ++i){
		for (j = 0; j < HAUTEUR_MATRICE_DEPLACEMENT_POSSIBLE; ++j){
			d->deplacementPossible[i][j] = 0;
		}
	}

	return d;
}


void calculerDeplacementPossible(Piece* p, Echiquier* e, DeplacementPossible* d, VecteurDeplacement* v, Booleen surbrillance, SDL_Renderer* contexte){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de calculer les déplacements possible de l'élément NULL");
	int x = p->idPosition.colonne;//idPosition pièce colonne
	int y = p->idPosition.ligne;//idPosition pièce ligne
	d->pieceConcernee = p;
	int newx;
	int newy;
	int i, j; //Variable de boucle

	switch (p->idPiece.type){
	case 'C':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice
		for (i = 0; i < 8; ++i){
			newx = x + v->deltaCavalier[0][i];
			newy = y + v->deltaCavalier[1][i];
			calculerDeplacementPossibleCaseParCase(e, d, contexte, x, y, newx, newy, surbrillance);
		}
		break;


	case 'R':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice
		for (i = 0; i < 8; ++i){
			newx = x + v->deltaRoi[0][i];
			newy = y + v->deltaRoi[1][i];
			calculerDeplacementPossibleCaseParCase(e, d, contexte, x, y, newx, newy, surbrillance);
		}
		break;


	case 'T':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice
		int continuer = 1;
		for (j = 0; j < 4; j++){
			continuer = 1;
			for (i = j * 7; i < (j + 1) * 7 && continuer; ++i){
				newx = x + v->deltaTour[0][i];
				newy = y + v->deltaTour[1][i];
				continuer = calculerDeplacementPossibleCaseParCase(e, d, contexte, x, y, newx, newy, surbrillance); //On met en surbrillance et on s'arrête si on rencontre une case pleine
			}
		}
		break;


	case 'F':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice
		for (j = 0; j < 4; j++){
			continuer = 1;
			for (i = j * 7; i < (j + 1) * 7 && continuer; ++i){
				newx = x + v->deltaFou[0][i];
				newy = y + v->deltaFou[1][i];
				continuer = calculerDeplacementPossibleCaseParCase(e, d, contexte, x, y, newx, newy, surbrillance); //On met en surbrillance et on s'arrête si on rencontre une case pleine
			}
		}
		break;


	case 'D': //Dans le cas de la dame : on combine fou et tour
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice
		for (j = 0; j < 4; j++){
			continuer = 1;
			for (i = j * 7; i < (j + 1) * 7 && continuer; ++i){
				newx = x + v->deltaTour[0][i];
				newy = y + v->deltaTour[1][i];
				continuer = calculerDeplacementPossibleCaseParCase(e, d, contexte, x, y, newx, newy, surbrillance); //On met en surbrillance et on s'arrête si on rencontre une case pleine
			}
		}
		for (j = 0; j < 4; j++){
			continuer = 1;
			for (i = j * 7; i < (j + 1) * 7 && continuer; ++i){
				newx = x + v->deltaFou[0][i];
				newy = y + v->deltaFou[1][i];
				continuer = calculerDeplacementPossibleCaseParCase(e, d, contexte, x, y, newx, newy, surbrillance); //On met en surbrillance et on s'arrête si on rencontre une case pleine
			}
		}
		break;


	case 'P':
		memset(d->deplacementPossible, 0, sizeof(d->deplacementPossible));// On remet à 0 toute la matrice

		if (p->idPiece.couleur == 'N'){
			//Partie Déplacement
			newx = x + v->deltaPionNoir[0][0];
			newy = y + v->deltaPionNoir[1][0];
			if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == FALSE){
				d->deplacementPossible[newx][newy] = 1;
				//On met en surbrillance les cases où l'on peut se déplacer
				if (surbrillance)
					mettreEnSurbrillance(e->tabCases[newx][newy], contexte);
				/*if (e->tabPieces[newx][newy] != NULL)
					afficherPiece(e->tabPieces[newx][newy], contexte);*/
			}
			if (p->nbDeplacement == 1){
				newx = x + v->deltaPionNoir[0][1];
				newy = y + v->deltaPionNoir[1][1];
				//Si le pion ne s'est jamais déplacé, il peut avancer de deux cases si les 2 cases devant lui sont libres
				if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == FALSE && e->tabCases[newx][newy - 1]->occupee == FALSE){
					d->deplacementPossible[newx][newy] = 1;
					//On met en surbrillance les cases où l'on peut se déplacer
					if (surbrillance)
						mettreEnSurbrillance(e->tabCases[newx][newy], contexte);
					/*	if (e->tabPieces[newx][newy] != NULL)
							afficherPiece(e->tabPieces[newx][newy], contexte);*/
				}
			}

			//Partie Prise
			for (i = 0; i < 2; i++){
				newx = x + v->deltaPionNoirPrise[0][i];
				newy = y + v->deltaPionNoirPrise[1][i];
				if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == TRUE){
					if (e->tabPieces[newx][newy]->couleur == BLANC){
						d->deplacementPossible[newx][newy] = 2;
						//On met en surbrillance les cases où l'on peut manger la pièce
						if (surbrillance){
							mettreEnSurbrillanceOccupee(e->tabCases[newx][newy], contexte);
							if (e->tabPieces[newx][newy] != NULL)
								afficherPiece(e->tabPieces[newx][newy], contexte);
						}
					}
				}
			}
		}

		else if (p->idPiece.couleur == 'B'){
			//Partie déplacement
			newx = x + v->deltaPionBlanc[0][0];
			newy = y + v->deltaPionBlanc[1][0];
			if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == FALSE){
				d->deplacementPossible[newx][newy] = 1;
				//On met en surbrillance les cases où l'on peut se déplacer
				if (surbrillance)
					mettreEnSurbrillance(e->tabCases[newx][newy], contexte);
				/*if (e->tabPieces[newx][newy] != NULL)
					afficherPiece(e->tabPieces[newx][newy], contexte);*/
			}
			if (p->nbDeplacement == 1){
				newx = x + v->deltaPionBlanc[0][1];
				newy = y + v->deltaPionBlanc[1][1];
				if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == FALSE && e->tabCases[newx][newy + 1]->occupee == FALSE){
					d->deplacementPossible[newx][newy] = 1;
					//On met en surbrillance les cases où l'on peut se déplacer
					if (surbrillance)
						mettreEnSurbrillance(e->tabCases[newx][newy], contexte);
					/*if (e->tabPieces[newx][newy] != NULL)
						afficherPiece(e->tabPieces[newx][newy], contexte);*/
				}
			}

			//Partie prise
			for (i = 0; i < 2; i++){
				newx = x + v->deltaPionBlancPrise[0][i];
				newy = y + v->deltaPionBlancPrise[1][i];
				if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0 && e->tabCases[newx][newy]->occupee == TRUE){
					if (e->tabPieces[newx][newy]->couleur == NOIR){
						d->deplacementPossible[newx][newy] = 2;
						//On met en surbrillance les cases où l'on peut manger la pièce
						if (surbrillance){
							mettreEnSurbrillanceOccupee(e->tabCases[newx][newy], contexte);
							if (e->tabPieces[newx][newy] != NULL)
								afficherPiece(e->tabPieces[newx][newy], contexte);
						}
					}
				}
			}
		}
		break;

	default:
		for (i = 0; i < 8; ++i){
			for (j = 0; j < 8; ++j){
				d->deplacementPossible[j][i] = 1;
			}
		}
		break;
	}//End switch
}


//Fonction qui rend vrai si le roi de la couleur c est en échec
//La pièce p correspond à la pièce qui va être jouée ou vient d'être jouée
Booleen calculerEchec(Couleur c, Echiquier* e, DeplacementPossible* dEchec, VecteurDeplacement* v, IDCase* posRoi, SDL_Renderer* contexte){
	int i, j;

	//Pour toutes les pièces de l'échiquier
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			if (e->tabPieces[j][i] != NULL){

				//Si la pièce testée est de la couleur adverse
				if (e->tabPieces[j][i]->couleur != c){

					//On calcule tous ses déplacements possibles
					calculerDeplacementPossible(e->tabPieces[j][i], e, dEchec, v, FALSE, contexte);
					//Si la case contenant le roi possiblement en danger coincide avec un deplacement autorisé de la pièce testée
					if (dEchec->deplacementPossible[posRoi[c].colonne][posRoi[c].ligne] == 2){
						return TRUE;
					}
				}
			}
		}
	}

	//Si on n'a pas détecté de position d'échec
	return FALSE;
}


//Fonction qui rend vrai si le roi de la couleur c est en échec
//La pièce p correspond à la pièce qui va être jouée ou vient d'être jouée
Booleen calculerEchecAnticipe(Echiquier* e, Piece* p, Lettre colonneArrivee, Lettre ligneArrivee, DeplacementPossible* d, VecteurDeplacement* v, IDCase posRoi[], SDL_Renderer* contexte){
	int i, j;
	Lettre ligneDepart = p->idPosition.ligne;
	Lettre colonneDepart = p->idPosition.colonne;
	Piece* pieceCaseArrivee = NULL;
	Booleen echecAnticipe = FALSE;
	Booleen continuer = TRUE;

	if (e->tabPieces[colonneArrivee][ligneArrivee] != NULL){
		pieceCaseArrivee = e->tabPieces[colonneArrivee][ligneArrivee];
	}

	//On bouge la pièce
	e->tabPieces[p->idPosition.colonne][p->idPosition.ligne] = NULL;
	e->tabPieces[colonneArrivee][ligneArrivee] = p;
	e->tabCases[p->idPosition.colonne][p->idPosition.ligne]->occupee = FALSE;
	e->tabCases[colonneArrivee][ligneArrivee]->occupee = TRUE;

	//S'il s'agit d'un roi, on modifie le tableau posRoi (empeche le roi de se mettre lui meme en echec)
	if (p->type == ROI){
		posRoi[p->couleur].colonne = colonneArrivee;
		posRoi[p->couleur].ligne = ligneArrivee;
	}

	//On modifie la position enregistrée de manière interne à la pièce
	p->idPosition.colonne = colonneArrivee;
	p->idPosition.ligne = ligneArrivee;

	//Pour toutes les pièces de l'échiquier
	for (i = 0; i < 8 && continuer; i++){
		for (j = 0; j < 8 && continuer; j++){
			if (e->tabPieces[j][i] != NULL){
				//Si la pièce testée est de la couleur adverse
				if (e->tabPieces[j][i]->couleur != p->couleur){
					//On calcule tous ses déplacements possibles
					calculerDeplacementPossible(e->tabPieces[j][i], e, d, v, FALSE, contexte);
					//Si la case contenant le roi possiblement en danger coincide avec un deplacement autorisé de la pièce testée
					if (d->deplacementPossible[posRoi[p->couleur].colonne][posRoi[p->couleur].ligne] == 2){
						echecAnticipe = TRUE;
					}
				}
			}
		}
	}

	//On bouge la pièce
	e->tabPieces[p->idPosition.colonne][p->idPosition.ligne] = pieceCaseArrivee;
	e->tabPieces[colonneDepart][ligneDepart] = p;
	e->tabCases[colonneDepart][ligneDepart]->occupee = TRUE;
	if (pieceCaseArrivee == NULL)
		e->tabCases[p->idPosition.colonne][p->idPosition.ligne]->occupee = FALSE;
	else
		e->tabCases[p->idPosition.colonne][p->idPosition.ligne]->occupee = TRUE;

	//On remet le roi dans sa position initiale
	if (p->type == ROI){
		posRoi[p->couleur].colonne = colonneDepart;
		posRoi[p->couleur].ligne = ligneDepart;
	}

	//On modifie la position enregistrée de manière interne à la pièce
	p->idPosition.colonne = colonneDepart;
	p->idPosition.ligne = ligneDepart;

	return echecAnticipe;
}



//Fonction permettant de mettre en surbrillance les cases où la pièce peut soit se déplacer, soit manger une pièce adverse
//return 1 si la case est libre 0 si elle est occupee
int calculerDeplacementPossibleCaseParCase(Echiquier* e, DeplacementPossible* d, SDL_Renderer* contexte, int x, int y, int newx, int newy, Booleen surbrillance){
	if (newx < 8 && newx >= 0 && newy < 8 && newy >= 0){
		if (e->tabCases[newx][newy]->occupee == FALSE){
			d->deplacementPossible[newx][newy] = 1;
			if (surbrillance)
				mettreEnSurbrillance(e->tabCases[newx][newy], contexte);//On met en surbrillance les cases où l'on peut se déplacer
			return 1;
		}
		else if (e->tabCases[newx][newy]->occupee == TRUE && e->tabPieces[newx][newy]->couleur != e->tabPieces[x][y]->couleur){
			d->deplacementPossible[newx][newy] = 2;
			if (surbrillance)
				mettreEnSurbrillanceOccupee(e->tabCases[newx][newy], contexte);//On met en surbrillance rouge la case où l'on peut manger une pièce de la couleur adverse
			afficherPiece(e->tabPieces[newx][newy], contexte);
			return 0;
		}
		else{
			return 0;
		}
	}
	return 0;
}




//Fonction utile pendant le développement du logiciel nous permettant de visualiser la matrice deplacementPossible dans un fichier texte
void enregisterMatriceDeplacementPossible(DeplacementPossible* d, char* nomFichierSortie){
	FILE* fichier = NULL;
	int i, j;

	fichier = fopen(nomFichierSortie, "w");

	if (fichier == NULL)
		logPrint(ERREUR, "Erreur lors de l'ouverture du fichier pour l'enregistrement de la matrice déplacement possible");
	if (d == NULL)
		logPrint(ERREUR, "Impossible d'enregistrer la matrice des deplacements possible dans un fichier s'il s'agit de l'élément NULL");
	if (d->pieceConcernee == NULL)
		logPrint(ERREUR, "Impossible d'enregistrer la matrice des deplacements possible dans un fichier car la piece concernee dans le deplacement vaut NULL");

	fprintf(fichier, "Piece concernee : %s\n\n", d->pieceConcernee->idPiece.id);
	for (j = 0; j < 8; ++j){
		for (i = 0; i < 8; ++i){
			fprintf(fichier, "%d", d->deplacementPossible[i][j]);
		}
		fprintf(fichier, "\n");
	}
	fclose(fichier);
}


//supprime la surbrillance de toutes les cases de l'échiquier et réaffiche les pièces s'il y en a sur les cases dont on a supprimé la surbrillance
void supprimerSurbrillanceDeplacementPossibles(DeplacementPossible* d, Echiquier* e, SDL_Renderer* contexte){
	if (d == NULL)
		logPrint(AVERTISSEMENT, "Impossible de supprimer la surbrillances des cases où le déplacement est possible si l'objet DeplacementPossible est NULL");
	else{
		int i, j;
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				if (d->deplacementPossible[j][i] == 1 || d->deplacementPossible[j][i] == 2){
					supprimerSurbrillance(e->tabCases[j][i], contexte);
					if (e->tabPieces[j][i] != NULL)
						afficherPiece(e->tabPieces[j][i], contexte);
				}
			}
		}
	}
}


VecteurDeplacement* creerVecteurDeplacement(){
	VecteurDeplacement* v = (VecteurDeplacement*)malloc(sizeof(VecteurDeplacement));
	if (v == NULL)
		logPrint(ERREUR, "Allocation de la mémoire pour la structure VecteurDeplacement échouée...");

	//Création du delta cavalier (pas trouvé de méthode plus simple qui marche...)
	//v->deltaCavalier = (int[2][8]){ { 2, 2, 1, -1, -2, -2, -1, 1 }, { 1, -1, -2, -2, -1, 1, 2, 2 } }; //Marche pas ...
	v->deltaCavalier[0][0] = 2;
	v->deltaCavalier[1][0] = -1;
	v->deltaCavalier[0][1] = 2;
	v->deltaCavalier[1][1] = 1;
	v->deltaCavalier[0][2] = 1;
	v->deltaCavalier[1][2] = 2;
	v->deltaCavalier[0][3] = -1;
	v->deltaCavalier[1][3] = 2;
	v->deltaCavalier[0][4] = -2;
	v->deltaCavalier[1][4] = 1;
	v->deltaCavalier[0][5] = -2;
	v->deltaCavalier[1][5] = -1;
	v->deltaCavalier[0][6] = -1;
	v->deltaCavalier[1][6] = -2;
	v->deltaCavalier[0][7] = 1;
	v->deltaCavalier[1][7] = -2;

	//Création du delta roi
	v->deltaRoi[0][0] = 1;
	v->deltaRoi[1][0] = -1;
	v->deltaRoi[0][1] = 1;
	v->deltaRoi[1][1] = 0;
	v->deltaRoi[0][2] = 1;
	v->deltaRoi[1][2] = 1;
	v->deltaRoi[0][3] = 0;
	v->deltaRoi[1][3] = 1;
	v->deltaRoi[0][4] = -1;
	v->deltaRoi[1][4] = 1;
	v->deltaRoi[0][5] = -1;
	v->deltaRoi[1][5] = 0;
	v->deltaRoi[0][6] = -1;
	v->deltaRoi[1][6] = -1;
	v->deltaRoi[0][7] = 0;
	v->deltaRoi[1][7] = -1;

	//Création du delta tour
	v->deltaTour[0][0] = 0;
	v->deltaTour[1][0] = 1;
	v->deltaTour[0][1] = 0;
	v->deltaTour[1][1] = 2;
	v->deltaTour[0][2] = 0;
	v->deltaTour[1][2] = 3;
	v->deltaTour[0][3] = 0;
	v->deltaTour[1][3] = 4;
	v->deltaTour[0][4] = 0;
	v->deltaTour[1][4] = 5;
	v->deltaTour[0][5] = 0;
	v->deltaTour[1][5] = 6;
	v->deltaTour[0][6] = 0;
	v->deltaTour[1][6] = 7;
	v->deltaTour[0][7] = 0;
	v->deltaTour[1][7] = -1;
	v->deltaTour[0][8] = 0;
	v->deltaTour[1][8] = -2;
	v->deltaTour[0][9] = 0;
	v->deltaTour[1][9] = -3;
	v->deltaTour[0][10] = 0;
	v->deltaTour[1][10] = -4;
	v->deltaTour[0][11] = 0;
	v->deltaTour[1][11] = -5;
	v->deltaTour[0][12] = 0;
	v->deltaTour[1][12] = -6;
	v->deltaTour[0][13] = 0;
	v->deltaTour[1][13] = -7;
	v->deltaTour[0][14] = 1;
	v->deltaTour[1][14] = 0;
	v->deltaTour[0][15] = 2;
	v->deltaTour[1][15] = 0;
	v->deltaTour[0][16] = 3;
	v->deltaTour[1][16] = 0;
	v->deltaTour[0][17] = 4;
	v->deltaTour[1][17] = 0;
	v->deltaTour[0][18] = 5;
	v->deltaTour[1][18] = 0;
	v->deltaTour[0][19] = 6;
	v->deltaTour[1][19] = 0;
	v->deltaTour[0][20] = 7;
	v->deltaTour[1][20] = 0;
	v->deltaTour[0][21] = -1;
	v->deltaTour[1][21] = 0;
	v->deltaTour[0][22] = -2;
	v->deltaTour[1][22] = 0;
	v->deltaTour[0][23] = -3;
	v->deltaTour[1][23] = 0;
	v->deltaTour[0][24] = -4;
	v->deltaTour[1][24] = 0;
	v->deltaTour[0][25] = -5;
	v->deltaTour[1][25] = 0;
	v->deltaTour[0][26] = -6;
	v->deltaTour[1][26] = 0;
	v->deltaTour[0][27] = -7;
	v->deltaTour[1][27] = 0;

	//Création du delta fou
	v->deltaFou[0][0] = 1;
	v->deltaFou[1][0] = 1;
	v->deltaFou[0][1] = 2;
	v->deltaFou[1][1] = 2;
	v->deltaFou[0][2] = 3;
	v->deltaFou[1][2] = 3;
	v->deltaFou[0][3] = 4;
	v->deltaFou[1][3] = 4;
	v->deltaFou[0][4] = 5;
	v->deltaFou[1][4] = 5;
	v->deltaFou[0][5] = 6;
	v->deltaFou[1][5] = 6;
	v->deltaFou[0][6] = 7;
	v->deltaFou[1][6] = 7;
	v->deltaFou[0][7] = -1;
	v->deltaFou[1][7] = -1;
	v->deltaFou[0][8] = -2;
	v->deltaFou[1][8] = -2;
	v->deltaFou[0][9] = -3;
	v->deltaFou[1][9] = -3;
	v->deltaFou[0][10] = -4;
	v->deltaFou[1][10] = -4;
	v->deltaFou[0][11] = -5;
	v->deltaFou[1][11] = -5;
	v->deltaFou[0][12] = -6;
	v->deltaFou[1][12] = -6;
	v->deltaFou[0][13] = -7;
	v->deltaFou[1][13] = -7;
	v->deltaFou[0][14] = -1;
	v->deltaFou[1][14] = 1;
	v->deltaFou[0][15] = -2;
	v->deltaFou[1][15] = 2;
	v->deltaFou[0][16] = -3;
	v->deltaFou[1][16] = 3;
	v->deltaFou[0][17] = -4;
	v->deltaFou[1][17] = 4;
	v->deltaFou[0][18] = -5;
	v->deltaFou[1][18] = 5;
	v->deltaFou[0][19] = -6;
	v->deltaFou[1][19] = 6;
	v->deltaFou[0][20] = -7;
	v->deltaFou[1][20] = 7;
	v->deltaFou[0][21] = 1;
	v->deltaFou[1][21] = -1;
	v->deltaFou[0][22] = 2;
	v->deltaFou[1][22] = -2;
	v->deltaFou[0][23] = 3;
	v->deltaFou[1][23] = -3;
	v->deltaFou[0][24] = 4;
	v->deltaFou[1][24] = -4;
	v->deltaFou[0][25] = 5;
	v->deltaFou[1][25] = -5;
	v->deltaFou[0][26] = 6;
	v->deltaFou[1][26] = -6;
	v->deltaFou[0][27] = 7;
	v->deltaFou[1][27] = -7;

	v->deltaPionNoir[0][0] = 0;
	v->deltaPionNoir[1][0] = 1;
	v->deltaPionNoir[0][1] = 0;
	v->deltaPionNoir[1][1] = 2;

	v->deltaPionNoirPrise[0][0] = 1;
	v->deltaPionNoirPrise[1][0] = 1;
	v->deltaPionNoirPrise[0][1] = -1;
	v->deltaPionNoirPrise[1][1] = 1;

	v->deltaPionBlanc[0][0] = 0;
	v->deltaPionBlanc[1][0] = -1;
	v->deltaPionBlanc[0][1] = 0;
	v->deltaPionBlanc[1][1] = -2;

	v->deltaPionBlancPrise[0][0] = -1;
	v->deltaPionBlancPrise[1][0] = -1;
	v->deltaPionBlancPrise[0][1] = 1;
	v->deltaPionBlancPrise[1][1] = -1;

	return v;
}


ContexteRoque* creerContexteRoque(){
	ContexteRoque* c = (ContexteRoque*)malloc(sizeof(ContexteRoque));
	c->roiDejaBouge[BLANC] = FALSE;
	c->roiDejaBouge[NOIR] = FALSE;
	c->tourDejaBouge[BLANC][0] = FALSE;
	c->tourDejaBouge[NOIR][0] = FALSE;
	c->tourDejaBouge[BLANC][1] = FALSE;
	c->tourDejaBouge[NOIR][1] = FALSE;
	return c;
}


Booleen gererRoqueSiPossible(Piece* p1, Piece* p2, Echiquier* e, ContexteRoque* c, ListDeplacement* l){
	if (p1->type == ROI && p2->type == TOUR){
		//S'il sont de la même couleur
		if (p1->couleur == p2->couleur){
			//Si le roi et la tour n'ont jamais bougé.
			if (c->roiDejaBouge[p1->couleur] == FALSE && c->tourDejaBouge[p2->couleur][p2->idPiece.numero] == FALSE){
				//Si les deux cases séparant le roi de la tour sont libres
				//Cas où la tour est à gauche
				if (p2->idPiece.numero == 0){
					if (e->tabPieces[p2->idPosition.colonne + 1][p2->idPosition.ligne] == NULL && e->tabPieces[p2->idPosition.colonne + 2][p2->idPosition.ligne] == NULL && e->tabPieces[p2->idPosition.colonne + 3][p2->idPosition.ligne] == NULL){
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = FALSE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = FALSE;
						bougerPiece(p1, e->tabPieces, p1->idPosition.colonne - 2, p1->idPosition.ligne, l);
						bougerPiece(p2, e->tabPieces, p2->idPosition.colonne + 3, p2->idPosition.ligne, l);
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = TRUE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = TRUE;
						c->roiDejaBouge[p1->couleur] = TRUE;
						c->tourDejaBouge[p2->couleur][p2->idPiece.numero] = TRUE;
						l->current->deplacementRoque = 1;
						return TRUE;
					}
				}
				else if (p2->idPiece.numero == 1){
					if (e->tabPieces[p2->idPosition.colonne - 1][p2->idPosition.ligne] == NULL && e->tabPieces[p2->idPosition.colonne - 2][p2->idPosition.ligne] == NULL){
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = FALSE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = FALSE;
						bougerPiece(p1, e->tabPieces, p1->idPosition.colonne + 2, p1->idPosition.ligne, l);
						bougerPiece(p2, e->tabPieces, p2->idPosition.colonne - 2, p2->idPosition.ligne, l);
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = TRUE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = TRUE;
						c->roiDejaBouge[p1->couleur] = TRUE;
						c->tourDejaBouge[p2->couleur][p2->idPiece.numero] = TRUE;
						l->current->deplacementRoque = 1;
						return TRUE;
					}
				}


			}
		}
	}

	else if (p1->type == TOUR && p2->type == ROI){
		//S'il sont de la même couleur
		if (p1->couleur == p2->couleur){
			//Si le roi et la tour n'ont jamais bougé.
			if (c->roiDejaBouge[p2->couleur] == FALSE && c->tourDejaBouge[p1->couleur][p1->idPiece.numero] == FALSE){
				//Si les deux cases séparant le roi de la tour sont libres
				//Cas où la tour est à gauche
				if (p1->idPiece.numero == 0){
					if (e->tabPieces[p1->idPosition.colonne + 1][p1->idPosition.ligne] == NULL && e->tabPieces[p1->idPosition.colonne + 2][p1->idPosition.ligne] == NULL){
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = FALSE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = FALSE;
						bougerPiece(p2, e->tabPieces, p2->idPosition.colonne - 2, p2->idPosition.ligne, l);
						bougerPiece(p1, e->tabPieces, p1->idPosition.colonne + 3, p1->idPosition.ligne, l);
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = TRUE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = TRUE;
						c->roiDejaBouge[p2->couleur] = TRUE;
						c->tourDejaBouge[p1->couleur][p1->idPiece.numero] = TRUE;
						l->current->deplacementRoque = 1;
						return TRUE;
					}
				}
				else if (p1->idPiece.numero == 1){
					if (e->tabPieces[p1->idPosition.colonne - 1][p1->idPosition.ligne] == NULL && e->tabPieces[p1->idPosition.colonne - 2][p1->idPosition.ligne] == NULL){
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = FALSE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = FALSE;
						bougerPiece(p2, e->tabPieces, p2->idPosition.colonne + 2, p2->idPosition.ligne, l);
						bougerPiece(p1, e->tabPieces, p1->idPosition.colonne - 2, p1->idPosition.ligne, l);
						e->tabCases[p1->idPosition.colonne][p1->idPosition.ligne]->occupee = TRUE;
						e->tabCases[p2->idPosition.colonne][p2->idPosition.ligne]->occupee = TRUE;
						c->roiDejaBouge[p2->couleur] = TRUE;
						c->tourDejaBouge[p1->couleur][p1->idPiece.numero] = TRUE;
						l->current->deplacementRoque = 1;
						return TRUE;
					}	
				}
			}
		}
	}

	return FALSE;
}


void supprimerDeplacementPossibleEchecAnticipe(Echiquier* e, Piece* p, DeplacementPossible* d, DeplacementPossible* dEchecAnticipe, VecteurDeplacement* v, IDCase posRoi[], SDL_Renderer* contexte){
	int i, j;
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			if (d->deplacementPossible[i][j] == 1 || d->deplacementPossible[i][j] == 2){
				if (calculerEchecAnticipe(e, p, (Lettre)i, (Lettre)j, dEchecAnticipe, v, posRoi, contexte)){
					d->deplacementPossible[i][j] = 0;
					supprimerSurbrillance(e->tabCases[i][j], contexte);
					logPrint(AVERTISSEMENT, "**** Case supprimée de la matrice des déplacement autorisé car échec si la pièce s'y rendait ! ****");
				}
			}
		}
	}
}


Booleen calculerEchecEtMatEtPat(Couleur c, Echiquier* e, DeplacementPossible* dEchecEtMat, DeplacementPossible* dEchecAnticipe, VecteurDeplacement* v, IDCase* posRoi, Booleen* pat, SDL_Renderer* contexte){
	int i, j, k, l;
	Booleen continuer = TRUE;

	for (j = 0; j < 8; j++){
		for (i = 0; i < 8; i++){
			if (e->tabPieces[i][j] != NULL){
				if (e->tabPieces[i][j]->couleur == c){
					calculerDeplacementPossible(e->tabPieces[i][j], e, dEchecEtMat, v, FALSE, contexte);
					supprimerDeplacementPossibleEchecAnticipe(e, e->tabPieces[i][j], dEchecEtMat, dEchecAnticipe, v, posRoi, contexte);
					for (l = 0; l < 8; l++){
						for (k = 0; k < 8; k++){
							if (dEchecEtMat->deplacementPossible[k][l] != 0)
								return FALSE;
						}
					}
				}
			}
		}
	}

	//Cas ou il y a en fait PAT ! ==> la couleur n'est pas en echec, mais ne peut plus se deplacer nulle part sans s'y mettre
	if (!calculerEchec(c, e, dEchecEtMat, v, posRoi, contexte)){
		*pat = TRUE;
		return FALSE;
	}

	return TRUE;
}

/*Booleen calculerPat(Couleur c, Echiquier* e, DeplacementPossible* dEchecEtMat, DeplacementPossible* dEchecAnticipe, VecteurDeplacement* v, IDCase* posRoi, Booleen* pat, SDL_Renderer* contexte){

}*/