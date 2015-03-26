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
	p->idPosition = (IDCase){ 0, 0 };

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
	char nomImage[14] = { 'P','i','e','c','e','s','/',p->idPiece.type, p->idPiece.couleur, '.', 'p', 'n', 'g','\0'};
	p->imagePiece = IMG_Load(nomImage);
	if (p->imagePiece == NULL)
		logPrint(ERREUR, "Echec du chargement de l'image de la pièce");

	return p;
}

void initAllPiece(Piece* tabPiece[32]){
	int i = 0;
	//Pions Noirs
	for (i = 0; i < 8; i++){
		tabPiece[i] = creerPiece(PION, NOIR, i);
		bougerPiece(tabPiece[i], i, 1);
	}
	//Pions Blancs
	for (i = 0; i < 8; i++){
		tabPiece[i + 8] = creerPiece(PION, BLANC, i);
		bougerPiece(tabPiece[i+8], i, 6);
	}
	//Tours Noires
	tabPiece[16] = creerPiece(TOUR, NOIR, 0);
	tabPiece[17] = creerPiece(TOUR, NOIR, 1);
	bougerPiece(tabPiece[16], 0, 0);
	bougerPiece(tabPiece[17], 7, 0);
	//Tours Blanches
	tabPiece[18] = creerPiece(TOUR, BLANC, 0);
	tabPiece[19] = creerPiece(TOUR, BLANC, 1);
	bougerPiece(tabPiece[18], 0, 7);
	bougerPiece(tabPiece[19], 7, 7);
	//Cavaliers Noirs
	tabPiece[20] = creerPiece(CAVALIER, NOIR, 0);
	tabPiece[21] = creerPiece(CAVALIER, NOIR, 1);
	bougerPiece(tabPiece[20], 1, 0);
	bougerPiece(tabPiece[21], 6, 0);
	//Cavaliers Blancs
	tabPiece[22] = creerPiece(CAVALIER, BLANC, 0);
	tabPiece[23] = creerPiece(CAVALIER, BLANC, 1);
	bougerPiece(tabPiece[22], 1, 7);
	bougerPiece(tabPiece[23], 6, 7);
	//Fous Noirs
	tabPiece[24] = creerPiece(FOU, NOIR, 0);
	tabPiece[25] = creerPiece(FOU, NOIR, 1);
	bougerPiece(tabPiece[24], 2, 0);
	bougerPiece(tabPiece[25], 5, 0);
	//Fous Blancs
	tabPiece[26] = creerPiece(FOU, BLANC, 0);
	tabPiece[27] = creerPiece(FOU, BLANC, 1);
	bougerPiece(tabPiece[26], 2, 7);
	bougerPiece(tabPiece[27], 5, 7);
	//Rois
	tabPiece[28] = creerPiece(ROI, NOIR, 0);
	tabPiece[29] = creerPiece(ROI, BLANC, 0);
	bougerPiece(tabPiece[28], 3, 0);
	bougerPiece(tabPiece[29], 3, 7);
	//Dames
	tabPiece[30] = creerPiece(DAME, NOIR, 0);
	tabPiece[31] = creerPiece(DAME, BLANC, 0);
	bougerPiece(tabPiece[30], 4, 0);
	bougerPiece(tabPiece[31], 4, 7);
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


void bougerPiece(Piece* p, Lettre colonneArrivee, Lettre ligneArrivee){
	p->idPosition.colonne = colonneArrivee;
	p->idPosition.ligne = ligneArrivee;
}

void afficherAllPiece(Piece* tabPiece[32], SDL_Renderer* contexte){
	int i;
	for (i = 0; i < 32; ++i){
		SDL_Texture* texturePiece = SDL_CreateTextureFromSurface(contexte, tabPiece[i]->imagePiece);
		SDL_Rect positionAffichage;
		positionAffichage.x = POSITION_FROM_ID_PIECE(tabPiece[i]->idPosition.colonne, tabPiece[i]->idPosition.ligne).x;
		positionAffichage.y = POSITION_FROM_ID_PIECE(tabPiece[i]->idPosition.colonne, tabPiece[i]->idPosition.ligne).y;
		positionAffichage.w = tabPiece[i]->dimension.largeur;
		positionAffichage.h = tabPiece[i]->dimension.hauteur;
		SDL_RenderCopy(contexte, texturePiece, NULL, &positionAffichage);
		SDL_DestroyTexture(texturePiece);
		SDL_free(&positionAffichage);
	}
}