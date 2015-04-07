#include "piece.h"

Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece){
	Piece* p = malloc(sizeof(Piece));
	if (p == NULL){
		logPrint(ERREUR, "Echec de l'allocation de la piece");
	}

	//Initialisation des booléens
	p->active = FALSE;
	p->pieceSelectionne = FALSE;
	p->surbrillance = FALSE;

	//Initialisation des autres attributs
	p->couleur = couleur;
	p->type = type;
	p->dimension.hauteur = HAUTEUR_PIECE;
	p->dimension.largeur = LARGEUR_PIECE;
	p->deplacementPossibles = NULL;
	p->idPosition = (IDCase){ -1, -1 };

	//Cration de l'ID de la pièce
	//Gestion de la couleur
	if (couleur == NOIR)
		p->idPiece.couleur = 'N';
	else if (couleur == BLANC)
		p->idPiece.couleur = 'B';
	else
		logPrint(ERREUR, "La couleur renseignée pour la création de la pièce n'est pas valide");

	//Gestion du type de pièce
	switch (type){
	case ROI:
		p->idPiece.type = 'R';
		break;
	case DAME:
		p->idPiece.type = 'D';
		break;
	case FOU:
		p->idPiece.type = 'F';
		break;
	case CAVALIER:
		p->idPiece.type = 'C';
		break;
	case TOUR:
		p->idPiece.type = 'T';
		break;
	case PION:
		p->idPiece.type = 'P';
		break;
	default:
		logPrint(ERREUR, "Le type renseigné pour la création de la pièce n'est pas valide");
		break;
	}

	//Gestion du numero
	p->idPiece.numero = numPiece;

	//Création de l'id complet sous forme de chaine de caractère
	p->idPiece.id[0] = p->idPiece.type;
	p->idPiece.id[1] = p->idPiece.couleur;
	p->idPiece.id[2] = p->idPiece.numero;
	p->idPiece.id[3] = '\0';

	//Chargement de l'image (de la forme 'Type''Couleur'.png)
	char nomImage[14] = { 'P', 'i', 'e', 'c', 'e', 's', '/', p->idPiece.type, p->idPiece.couleur, '.', 'p', 'n', 'g', '\0' };
	p->imagePiece = p->imagePieceNormale = IMG_Load(nomImage);
	if (p->imagePiece == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de la pièce");
	char nomImageSurbrillance[15] = { 'P', 'i', 'e', 'c', 'e', 's', '/', p->idPiece.type, p->idPiece.couleur, 'S', '.', 'p', 'n', 'g', '\0' };
	p->imagePieceSurbrillance = IMG_Load(nomImageSurbrillance);
	if (p->imagePieceSurbrillance == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de surbrillance de la pièce");
	return p;
}


void initAllPiece(Piece* tabPiece[8][8]){
	int i;
	int j;
	//Pions Noirs
	for (i = 0; i < 8; i++){
		tabPiece[i][1] = creerPiece(PION, NOIR, i);
		bougerPiece(tabPiece[i][1], tabPiece, i, 1);
		tabPiece[i][1]->nbDeplacement = 1;
	}
	//Pions Blancs
	for (i = 0; i < 8; i++){
		tabPiece[i][6] = creerPiece(PION, BLANC, i);
		bougerPiece(tabPiece[i][6], tabPiece, i, 6);
		tabPiece[i][6]->nbDeplacement = 1;
	}
	//Tours Noires
	tabPiece[0][0] = creerPiece(TOUR, NOIR, 0);
	tabPiece[7][0] = creerPiece(TOUR, NOIR, 1);
	bougerPiece(tabPiece[0][0], tabPiece, 0, 0);
	bougerPiece(tabPiece[7][0], tabPiece, 7, 0);
	//Tours Blanches
	tabPiece[0][7] = creerPiece(TOUR, BLANC, 0);
	tabPiece[7][7] = creerPiece(TOUR, BLANC, 1);
	bougerPiece(tabPiece[0][7], tabPiece, 0, 7);
	bougerPiece(tabPiece[7][7], tabPiece, 7, 7);
	//Cavaliers Noirs
	tabPiece[1][0] = creerPiece(CAVALIER, NOIR, 0);
	tabPiece[6][0] = creerPiece(CAVALIER, NOIR, 1);
	bougerPiece(tabPiece[1][0], tabPiece, 1, 0);
	bougerPiece(tabPiece[6][0], tabPiece, 6, 0);
	//Cavaliers Blancs
	tabPiece[1][7] = creerPiece(CAVALIER, BLANC, 0);
	tabPiece[6][7] = creerPiece(CAVALIER, BLANC, 1);
	bougerPiece(tabPiece[1][7], tabPiece, 1, 7);
	bougerPiece(tabPiece[6][7], tabPiece, 6, 7);
	//Fous Noirs
	tabPiece[2][0] = creerPiece(FOU, NOIR, 0);
	tabPiece[5][0] = creerPiece(FOU, NOIR, 1);
	bougerPiece(tabPiece[2][0], tabPiece, 2, 0);
	bougerPiece(tabPiece[5][0], tabPiece, 5, 0);
	//Fous Blancs
	tabPiece[2][7] = creerPiece(FOU, BLANC, 0);
	tabPiece[5][7] = creerPiece(FOU, BLANC, 1);
	bougerPiece(tabPiece[2][7], tabPiece, 2, 7);
	bougerPiece(tabPiece[5][7], tabPiece, 5, 7);
	//Rois
	tabPiece[3][0] = creerPiece(ROI, NOIR, 0);
	tabPiece[3][7] = creerPiece(ROI, BLANC, 0);
	bougerPiece(tabPiece[3][0], tabPiece, 3, 0);
	bougerPiece(tabPiece[3][7], tabPiece, 3, 7);
	//Dames
	tabPiece[4][0] = creerPiece(DAME, NOIR, 0);
	tabPiece[4][7] = creerPiece(DAME, BLANC, 0);
	bougerPiece(tabPiece[4][0], tabPiece, 4, 0);
	bougerPiece(tabPiece[4][7], tabPiece, 4, 7);
	//Initialisation des autres cases à NULL
	for (i = 0; i < 8; ++i){
		for (j = 2; j < 6; ++j){
			tabPiece[i][j] = NULL;
		}
	}
}
void afficherPiece(Piece* p, SDL_Renderer* contexte){
	SDL_Texture* texturePiece = SDL_CreateTextureFromSurface(contexte, p->imagePiece);
	SDL_Rect positionAffichage;
	positionAffichage.x = POSITION_FROM_ID_PIECE(p->idPosition.colonne, p->idPosition.ligne).x;
	positionAffichage.y = POSITION_FROM_ID_PIECE(p->idPosition.colonne, p->idPosition.ligne).y;
	positionAffichage.w = p->dimension.largeur;
	positionAffichage.h = p->dimension.hauteur;
	SDL_RenderCopy(contexte, texturePiece, NULL, &positionAffichage);
	SDL_DestroyTexture(texturePiece);
	SDL_free(&positionAffichage);
}


void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de bouger la pièce car il s'agit de l'élément NULL");
	//On bouge la pièce dans le tableau de pièce de l'échiquier
	if ((p->idPosition.colonne != -1) && (p->idPosition.ligne != -1))
		tabPiece[p->idPosition.colonne][p->idPosition.ligne] = NULL;
	tabPiece[colonneArrivee][ligneArrivee] = p;
	//On modifie la position enregistrée de manière interne à la pièce
	p->idPosition.colonne = colonneArrivee;
	p->idPosition.ligne = ligneArrivee;
	p->nbDeplacement++;
}

void afficherAllPiece(Piece* tabPiece[8][8], SDL_Renderer* contexte){
	int i;
	int j;
	for (i = 0; i < 8; ++i){
		for (j = 0; j < 8; ++j){
			if (tabPiece[i][j] != NULL){
				SDL_Texture* texturePiece = SDL_CreateTextureFromSurface(contexte, tabPiece[i][j]->imagePiece);
				SDL_Rect positionAffichage;
				positionAffichage.x = POSITION_FROM_ID_PIECE(tabPiece[i][j]->idPosition.colonne, tabPiece[i][j]->idPosition.ligne).x;
				positionAffichage.y = POSITION_FROM_ID_PIECE(tabPiece[i][j]->idPosition.colonne, tabPiece[i][j]->idPosition.ligne).y;
				positionAffichage.w = tabPiece[i][j]->dimension.largeur;
				positionAffichage.h = tabPiece[i][j]->dimension.hauteur;
				SDL_RenderCopy(contexte, texturePiece, NULL, &positionAffichage);
				SDL_DestroyTexture(texturePiece);
				SDL_free(&positionAffichage);
			}
		}
	}
}

void mettreEnSurbillancePiece(Piece* p, SDL_Renderer* contexte){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de mettre en surbrillance la pièce s'il s'agit de l'élément null");
	p->imagePiece = p->imagePieceSurbrillance;
	p->surbrillance = TRUE;
	afficherPiece(p, contexte);
}

void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de supprimer la surbrillance de la pièce s'il s'agit de l'élément null");
	p->imagePiece = p->imagePieceNormale;
	p->surbrillance = FALSE;
	afficherPiece(p, contexte);
}

