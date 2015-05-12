#include "entrainement.h"

Reserve* creerReserve(Couleur couleur){
	Reserve* reserve = (Reserve*)malloc(sizeof(Reserve));
	if (reserve == NULL){
		logPrint(ERREUR, "Allocation dynamique de la Reserve échouée");
	}

	reserve->couleur = couleur;
	reserve->dimension = TAILLE_RESERVE;

	if (couleur == NOIR)
		reserve->position = POSITION_RESERVE_NOIRE;
	else if (couleur == BLANC)
		reserve->position = POSITION_RESERVE_BLANCHE;
	else
		logPrint(ERREUR, "La couleur renseignée lors de la création de la réserve n'est pas valide");

	reserve->imageReserve = IMG_Load("Reserve.png");
	if (reserve->imageReserve == NULL)
		logPrint(AVERTISSEMENT, "Echec du chargement de l'image de la reserve");

	//Vidage du tableau de piece reservees
	int i;
	for (i = 0; i < 8; i++){
		reserve->tabPiecesReserve[0][i] = NULL;
		reserve->tabPiecesReserve[1][i] = NULL;
	}
	return reserve;
}


void afficherReserve(Reserve* r, SDL_Renderer* contexte){
	SDL_Texture* textureReserve = SDL_CreateTextureFromSurface(contexte, r->imageReserve);
	if (textureReserve == NULL)
		logPrint(ERREUR, "Echec de la création de la texture de la réserve depuis son image");
	SDL_Rect positionAffichage;
	positionAffichage.x = r->position.x;
	positionAffichage.y = r->position.y;
	positionAffichage.w = r->dimension.largeur;
	positionAffichage.h = r->dimension.hauteur;
	SDL_RenderCopy(contexte, textureReserve, NULL, &positionAffichage);
	SDL_DestroyTexture(textureReserve);
	SDL_free(&positionAffichage);
}


void initAllPiecesReserve(Piece* tabPiece[2][8], Couleur c){
	int i;

	if (c == NOIR){
		//Pions Noirs
		for (i = 0; i < 8; i++){
			tabPiece[0][i] = creerPiece(PION, NOIR, i);
		}
		//Tours Noires
		tabPiece[1][0] = creerPiece(TOUR, NOIR, 0);
		tabPiece[1][7] = creerPiece(TOUR, NOIR, 1);
		//Cavaliers Noirs
		tabPiece[1][1] = creerPiece(CAVALIER, NOIR, 0);
		tabPiece[1][6] = creerPiece(CAVALIER, NOIR, 1);
		//Fous Noirs
		tabPiece[1][2] = creerPiece(FOU, NOIR, 0);
		tabPiece[1][5] = creerPiece(FOU, NOIR, 1);
		//Roi Noir
		tabPiece[1][3] = creerPiece(ROI, NOIR, 0);
		//Dame Noir
		tabPiece[1][4] = creerPiece(DAME, NOIR, 0);
	}


	if (c == BLANC){
		//Pions Blancs
		for (i = 0; i < 8; i++){
			tabPiece[0][i] = creerPiece(PION, BLANC, i);
		}
		//Tours Blanches
		tabPiece[1][0] = creerPiece(TOUR, BLANC, 0);
		tabPiece[1][7] = creerPiece(TOUR, BLANC, 1);
		//Cavaliers Blancs
		tabPiece[1][1] = creerPiece(CAVALIER, BLANC, 0);
		tabPiece[1][6] = creerPiece(CAVALIER, BLANC, 1);
		//Fous Blancs
		tabPiece[1][2] = creerPiece(FOU, BLANC, 0);
		tabPiece[1][5] = creerPiece(FOU, BLANC, 1);
		//Roi Blanc
		tabPiece[1][3] = creerPiece(ROI, BLANC, 0);
		//Dame Blanc
		tabPiece[1][4] = creerPiece(DAME, BLANC, 0);
	}
}


void afficherPieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte, int x, int y){
	SDL_Texture* texturePiece = SDL_CreateTextureFromSurface(contexte, p->imagePieceReserve);
	if (texturePiece == NULL)
		logPrint(ERREUR, "Echec de la création de la texture de la pièce dans la réserve");
	SDL_Rect positionAffichage;
	positionAffichage.x = x;
	positionAffichage.y = y;
	positionAffichage.w = LARGEUR_PIECE_RESERVE;
	positionAffichage.h = HAUTEUR_PIECE_RESERVE;
	SDL_RenderCopy(contexte, texturePiece, NULL, &positionAffichage);
	SDL_DestroyTexture(texturePiece);
	SDL_free(&positionAffichage);
}


void afficherAllPiecesReserve(Reserve* r, SDL_Renderer* contexte){
	int i, j;
	int x, y;
	for (j = 0; j < 2; j++){
		for (i = 0; i < 8; i++){
			if (r->tabPiecesReserve[j][i] != NULL){
				x = r->position.x + OFFSET_GAUCHE_PIECE_RESERVE + i*(LARGEUR_ESPACE_PIECE_RESERVE + LARGEUR_PIECE_RESERVE);
				y = r->position.y + OFFSET_HAUT_PIECE_RESERVE + j*(HAUTEUR_ESPACE_PIECE_RESERVE + HAUTEUR_PIECE_RESERVE);
				afficherPieceReserve(r, r->tabPiecesReserve[j][i], contexte, x, y);
			}
		}
	}
}

Piece* selectionnerPieceReserve(Reserve* rb, Reserve* rn, int x, int y, SDL_Renderer* contexte){
	int colonne;
	int ligne;
	if (y >= rb->position.y + OFFSET_HAUT_PIECE_RESERVE && y <= (rb->position.y + OFFSET_HAUT_PIECE_RESERVE + 2 * HAUTEUR_PIECE_RESERVE + HAUTEUR_ESPACE_PIECE_RESERVE)){
		if (x >= rb->position.x + OFFSET_GAUCHE_PIECE_RESERVE && x <= (rb->position.x + OFFSET_GAUCHE_PIECE_RESERVE + 8 * LARGEUR_PIECE_RESERVE + 7 * LARGEUR_ESPACE_PIECE_RESERVE)){
			colonne = (x - rb->position.x - OFFSET_GAUCHE_PIECE_RESERVE) / (LARGEUR_ESPACE_PIECE_RESERVE + LARGEUR_PIECE_RESERVE);
			ligne = (y - rb->position.y - OFFSET_HAUT_PIECE_RESERVE) / (HAUTEUR_ESPACE_PIECE_RESERVE + HAUTEUR_PIECE_RESERVE);
			mettreEnSurbillancePieceReserve(rb, rb->tabPiecesReserve[ligne][colonne], contexte);
			return rb->tabPiecesReserve[ligne][colonne];
		}
		return NULL;
	}

	else if (y >= rn->position.y + OFFSET_HAUT_PIECE_RESERVE && y <= (rn->position.y + OFFSET_HAUT_PIECE_RESERVE + 2 * HAUTEUR_PIECE_RESERVE + HAUTEUR_ESPACE_PIECE_RESERVE)){
		if (x >= rn->position.x + OFFSET_GAUCHE_PIECE_RESERVE && x <= (rn->position.x + OFFSET_GAUCHE_PIECE_RESERVE + 8 * LARGEUR_PIECE_RESERVE + 7 * LARGEUR_ESPACE_PIECE_RESERVE)){
			colonne = (x - rn->position.x - OFFSET_GAUCHE_PIECE_RESERVE) / (LARGEUR_ESPACE_PIECE_RESERVE + LARGEUR_PIECE_RESERVE);
			ligne = (y - rn->position.y - OFFSET_HAUT_PIECE_RESERVE) / (HAUTEUR_ESPACE_PIECE_RESERVE + HAUTEUR_PIECE_RESERVE);
			mettreEnSurbillancePieceReserve(rn, rn->tabPiecesReserve[ligne][colonne], contexte);
			return rn->tabPiecesReserve[ligne][colonne];
		}
		return NULL;
	}

	else
		return NULL;	
}


void deselectionnerPieceReserve(Reserve* rb, Reserve* rn, Piece* p, Couleur c, SDL_Renderer* contexte){
	if (c == BLANC)
		supprimerSurbillancePieceReserve(rb, p, contexte);

	else
		supprimerSurbillancePieceReserve(rn, p, contexte);
}


void mettreEnSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de mettre en surbrillance la pièce dans la reserve s'il s'agit de l'élément null");
	p->imagePieceReserve = p->imagePieceReserveSurbrillance;
	p->surbrillanceReserve = TRUE;
}

void supprimerSurbillancePieceReserve(Reserve* r, Piece* p, SDL_Renderer* contexte){
	if (p == NULL)
		logPrint(ERREUR, "Impossible de mettre en surbrillance la pièce dans la reserve s'il s'agit de l'élément null");
	p->imagePieceReserve = p->imagePieceReserveNormale;
	p->surbrillanceReserve = FALSE;
}
