#include "piece.h"

int numeroDeplacement = 0;

Piece* creerPiece(TypePiece type, Couleur couleur, char numPiece){
	Piece* p = malloc(sizeof(Piece));
	if (p == NULL){
		logPrint(ERREUR, "Echec de l'allocation de la piece");
	}

	//Initialisation des bool�ens
	p->active = FALSE;
	p->pieceSelectionne = FALSE;
	p->surbrillance = FALSE;
	p->surbrillanceReserve = FALSE;

	//Initialisation des autres attributs
	p->couleur = couleur;
	p->type = type;
	p->nbDeplacement = 0;
	p->dimension.hauteur = HAUTEUR_PIECE;
	p->dimension.largeur = LARGEUR_PIECE;
	p->deplacementPossibles = NULL;
	p->idPosition = (IDCase){ 8, 8 };

	//Cration de l'ID de la pi�ce
	//Gestion de la couleur
	if (couleur == NOIR)
		p->idPiece.couleur = 'N';
	else if (couleur == BLANC)
		p->idPiece.couleur = 'B';
	else
		logPrint(ERREUR, "La couleur renseign�e pour la cr�ation de la pi�ce n'est pas valide");

	//Gestion du type de pi�ce
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
		logPrint(ERREUR, "Le type renseign� pour la cr�ation de la pi�ce n'est pas valide");
		break;
	}

	//Gestion du numero
	p->idPiece.numero = numPiece;

	//Cr�ation de l'id complet sous forme de chaine de caract�re
	p->idPiece.id[0] = p->idPiece.type;
	p->idPiece.id[1] = p->idPiece.couleur;
	p->idPiece.id[2] = p->idPiece.numero;
	p->idPiece.id[3] = '\0';

	//Chargement de l'image (de la forme 'Type''Couleur'.png)
	char nomImage[14] = { 'P', 'i', 'e', 'c', 'e', 's', '/', p->idPiece.type, p->idPiece.couleur, '.', 'p', 'n', 'g', '\0' };
	p->imagePiece = p->imagePieceNormale = IMG_Load(nomImage);
	if (p->imagePiece == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de la pi�ce");
	char nomImageSurbrillance[15] = { 'P', 'i', 'e', 'c', 'e', 's', '/', p->idPiece.type, p->idPiece.couleur, 'S', '.', 'p', 'n', 'g', '\0' };
	p->imagePieceSurbrillance = IMG_Load(nomImageSurbrillance);
	if (p->imagePieceSurbrillance == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de surbrillance de la pi�ce");

	//Chargement de d�fausse l'image (de la forme 'Type''Couleur''D'.png)
	char nomImageDefausse[15] = { 'P', 'i', 'e', 'c', 'e', 's', '/', p->idPiece.type, p->idPiece.couleur, 'D', '.', 'p', 'n', 'g', '\0' };
	p->imagePieceDefausse = IMG_Load(nomImageDefausse);
	if (p->imagePieceDefausse == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de d�fausse de la pi�ce");

	//Chargement de r�serve l'image (de la forme 'Type''Couleur''R'.png)
	char nomImageReserve[15] = { 'P', 'i', 'e', 'c', 'e', 's', '/', p->idPiece.type, p->idPiece.couleur, 'R', '.', 'p', 'n', 'g', '\0' };
	p->imagePieceReserve = p->imagePieceReserveNormale = IMG_Load(nomImageReserve);
	if (p->imagePieceReserveNormale == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de r�serve de la pi�ce");
	char nomImageReserveSurbrillance[16] = { 'P', 'i', 'e', 'c', 'e', 's', '/', p->idPiece.type, p->idPiece.couleur, 'S', 'R', '.', 'p', 'n', 'g', '\0' };
	p->imagePieceReserveSurbrillance = IMG_Load(nomImageReserveSurbrillance);
	if (p->imagePieceReserveSurbrillance == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de r�serve en surbrillance de la pi�ce");
	return p;
}


void initAllPiece(Piece* tabPiece[8][8], ListDeplacement* l){
	int i;
	int j;
	//Pions Noirs
	for (i = 0; i < 8; i++){
		tabPiece[i][1] = creerPiece(PION, NOIR, i);
		bougerPiece(tabPiece[i][1], tabPiece, i, 1, l);
		tabPiece[i][1]->nbDeplacement = 1;
	}
	//Pions Blancs
	for (i = 0; i < 8; i++){
		tabPiece[i][6] = creerPiece(PION, BLANC, i);
		bougerPiece(tabPiece[i][6], tabPiece, i, 6, l);
		tabPiece[i][6]->nbDeplacement = 1;
	}
	//Tours Noires
	tabPiece[0][0] = creerPiece(TOUR, NOIR, 0);
	tabPiece[7][0] = creerPiece(TOUR, NOIR, 1);
	bougerPiece(tabPiece[0][0], tabPiece, 0, 0, l);
	bougerPiece(tabPiece[7][0], tabPiece, 7, 0, l);
	//Tours Blanches
	tabPiece[0][7] = creerPiece(TOUR, BLANC, 0);
	tabPiece[7][7] = creerPiece(TOUR, BLANC, 1);
	bougerPiece(tabPiece[0][7], tabPiece, 0, 7, l);
	bougerPiece(tabPiece[7][7], tabPiece, 7, 7, l);
	//Cavaliers Noirs
	tabPiece[1][0] = creerPiece(CAVALIER, NOIR, 0);
	tabPiece[6][0] = creerPiece(CAVALIER, NOIR, 1);
	bougerPiece(tabPiece[1][0], tabPiece, 1, 0, l);
	bougerPiece(tabPiece[6][0], tabPiece, 6, 0, l);
	//Cavaliers Blancs
	tabPiece[1][7] = creerPiece(CAVALIER, BLANC, 0);
	tabPiece[6][7] = creerPiece(CAVALIER, BLANC, 1);
	bougerPiece(tabPiece[1][7], tabPiece, 1, 7, l);
	bougerPiece(tabPiece[6][7], tabPiece, 6, 7, l);
	//Fous Noirs
	tabPiece[2][0] = creerPiece(FOU, NOIR, 0);
	tabPiece[5][0] = creerPiece(FOU, NOIR, 1);
	bougerPiece(tabPiece[2][0], tabPiece, 2, 0, l);
	bougerPiece(tabPiece[5][0], tabPiece, 5, 0, l);
	//Fous Blancs
	tabPiece[2][7] = creerPiece(FOU, BLANC, 0);
	tabPiece[5][7] = creerPiece(FOU, BLANC, 1);
	bougerPiece(tabPiece[2][7], tabPiece, 2, 7, l);
	bougerPiece(tabPiece[5][7], tabPiece, 5, 7, l);
	//Rois
	tabPiece[4][0] = creerPiece(ROI, NOIR, 0);
	tabPiece[4][7] = creerPiece(ROI, BLANC, 0);
	bougerPiece(tabPiece[4][0], tabPiece, 4, 0, l);
	bougerPiece(tabPiece[4][7], tabPiece, 4, 7, l);
	//Dames
	tabPiece[3][0] = creerPiece(DAME, NOIR, 0);
	tabPiece[3][7] = creerPiece(DAME, BLANC, 0);
	bougerPiece(tabPiece[3][0], tabPiece, 3, 0, l);
	bougerPiece(tabPiece[3][7], tabPiece, 3, 7, l);
	//Initialisation des autres cases � NULL
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



void bougerPiece(Piece* p, Piece* tabPiece[8][8], Lettre colonneArrivee, Lettre ligneArrivee, ListDeplacement* l){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de bouger la pi�ce car il s'agit de l'�l�ment NULL");
	//static int numeroDeplacement = 0;
	//On bouge la pi�ce dans le tableau de pi�ce de l'�chiquier
	if ((p->idPosition.colonne != 8) && (p->idPosition.ligne != 8))//On �vite le cas ou il s'agit de l'initialisation de la position de la pi�ce.
		tabPiece[p->idPosition.colonne][p->idPosition.ligne] = NULL;
	tabPiece[colonneArrivee][ligneArrivee] = p;
	//On modifie la position enregistr�e de mani�re interne � la pi�ce
	IDCase caseDepart = p->idPosition;
	p->idPosition.colonne = colonneArrivee;
	p->idPosition.ligne = ligneArrivee;
	p->nbDeplacement++;
	createNewDeplacement(l, p , caseDepart, p->idPosition, numeroDeplacement);
	numeroDeplacement++;
}

void mangerPiece(Piece* p, Piece* tabPiece[8][8], ListDeplacement* l){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de manger la pi�ce car il s'agit de l'�l�ment NULL");
	if ((p->idPosition.colonne != 8) && (p->idPosition.ligne != 8))//On �vite le cas ou il s'agit de l'initialisation de la position de la pi�ce.
		tabPiece[p->idPosition.colonne][p->idPosition.ligne] = NULL;
	//On range la pi�ce dans sa position fictive d'initialisation la case 8.8
	p->idPosition.colonne = 8;
	p->idPosition.ligne = 8;
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
		logPrint(ERREUR, "Impossible de mettre en surbrillance la pi�ce s'il s'agit de l'�l�ment null");
	p->imagePiece = p->imagePieceSurbrillance;
	p->surbrillance = TRUE;
	afficherPiece(p, contexte);
}

void supprimerSurbillancePiece(Piece* p, SDL_Renderer* contexte){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de supprimer la surbrillance de la pi�ce s'il s'agit de l'�l�ment null");
	p->imagePiece = p->imagePieceNormale;
	p->surbrillance = FALSE;
	afficherPiece(p, contexte);
}

