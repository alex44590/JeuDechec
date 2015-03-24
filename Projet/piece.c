#include "piece.h"

Piece* newPiece(Id position, int numero, TypePiece t, Couleur c, char* cheminImage){
	Piece* p = malloc(sizeof(Piece));
	if (p == NULL){
		fprintf(stderr, "Allocation dynamique de la nouvelle piece échouée...\n");
		exit(EXIT_FAILURE);
	}
	p->active = FALSE;
	p->pieceSelectionne = FALSE;
	p->surbrillance = FALSE;
	p->deplacementPossibles = NULL;
	p->idPosition = position;
	p->idPiece.numero = numero;
	p->imagePiece = IMG_Load(cheminImage);
	p->dimension.hauteur = HAUTEUR_PIECE;
	p->dimension.largeur = LARGEUR_PIECE;

	if (c == BLANC)
		p->idPiece.couleur = 'B';

	else if (c == NOIR)
		p->idPiece.couleur = 'N';

	switch (t){
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
		break;
	}

	return  p;
}


void initAllPiece(Piece* tabPiece[32]){
	int i = 0;
	//Pions Noirs
	for (i = 0; i < 8; i++){
		tabPiece[i] = newPiece((Id){ i, 1 }, i, PION, NOIR, "Pieces/PN.png");
	}
	//Pions Blancs
	for (i = 0; i < 8; i++){
		tabPiece[i + 8] = newPiece((Id){ i, 6 }, i, PION, BLANC, "Pieces/PB.png");
	}
	//Tours Noires
	tabPiece[16] = newPiece((Id){ 0, 0 }, 0, TOUR, NOIR, "Pieces/TN.png");
	tabPiece[17] = newPiece((Id){ 7, 0 }, 1, TOUR, NOIR, "Pieces/TN.png");
	//Tours Blanches
	tabPiece[18] = newPiece((Id){ 0, 7 }, 0, TOUR, BLANC, "Pieces/TB.png");
	tabPiece[19] = newPiece((Id){ 7, 7 }, 1, TOUR, BLANC, "Pieces/TB.png");
	//Cavaliers Noirs
	tabPiece[20] = newPiece((Id){ 1, 0 }, 0, CAVALIER, NOIR, "Pieces/CN.png");
	tabPiece[21] = newPiece((Id){ 6, 0 }, 1, CAVALIER, NOIR, "Pieces/CN.png");
	//Cavaliers Blancs
	tabPiece[22] = newPiece((Id){ 1, 7 }, 0, CAVALIER, BLANC, "Pieces/CB.png");
	tabPiece[23] = newPiece((Id){ 6, 7 }, 1, CAVALIER, BLANC, "Pieces/CB.png");
	//Fous Noirs
	tabPiece[24] = newPiece((Id){ 2, 0 }, 0, FOU, NOIR, "Pieces/FN.png");
	tabPiece[25] = newPiece((Id){ 5, 0 }, 1, FOU, NOIR, "Pieces/FN.png");
	//Fous Blancs
	tabPiece[26] = newPiece((Id){ 2, 7 }, 0, FOU, BLANC, "Pieces/FB.png");
	tabPiece[27] = newPiece((Id){ 5, 7 }, 1, FOU, BLANC, "Pieces/FB.png");
	//Rois
	tabPiece[28] = newPiece((Id){ 3, 0 }, 0, ROI, NOIR, "Pieces/RN.png");
	tabPiece[29] = newPiece((Id){ 3, 7 }, 0, ROI, BLANC, "Pieces/RB.png");
	//Dames
	tabPiece[30] = newPiece((Id){ 4, 0 }, 0, DAME, NOIR, "Pieces/DN.png");
	tabPiece[31] = newPiece((Id){ 4, 7 }, 0, DAME, BLANC, "Pieces/DB.png");
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

