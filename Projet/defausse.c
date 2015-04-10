#include "defausse.h"


Defausse* creerDefausse(Couleur couleur){
	Defausse* defausse = (Defausse*)malloc(sizeof(Defausse));
	if (defausse == NULL){
		logPrint(ERREUR, "Allocation dynamique de la Defausse échouée");
	}

	defausse->couleur = couleur;
	defausse->dimension = TAILLE_DEFAUSSE;

	if (couleur == NOIR)
		defausse->position = POSITION_DEFAUSSE_NOIRE;
	else if (couleur == BLANC)
		defausse->position = POSITION_DEFAUSSE_BLANCHE;
	else
		logPrint(ERREUR, "La couleur renseignée lors de la création de la défausse n'est pas valide");	

	defausse->imageDefausse = IMG_Load("defausse2.png");
	if (defausse->imageDefausse == NULL)
		logPrint(AVERTISSEMENT, "Echec du chargement de l'image de la defausse");
	
	//Vidage du tableau de piece defaussees
	int i;
	for (i = 0; i < 8; i++){
		defausse->tabPiecesDefaussees[0][i] = NULL;
		defausse->tabPiecesDefaussees[1][i] = NULL;
	}
	return defausse;
}


void afficherDefausse(Defausse* d, SDL_Renderer* contexte){
	SDL_Texture* textureDefausse = SDL_CreateTextureFromSurface(contexte, d->imageDefausse);
	if (textureDefausse == NULL)
		logPrint(ERREUR, "Echec de la création de la texture de la défausse depuis son image");
	SDL_Rect positionAffichage;
	positionAffichage.x = d->position.x;
	positionAffichage.y = d->position.y;
	positionAffichage.w = d->dimension.largeur;
	positionAffichage.h = d->dimension.hauteur;
	SDL_RenderCopy(contexte, textureDefausse, NULL, &positionAffichage);
	SDL_DestroyTexture(textureDefausse);
	SDL_free(&positionAffichage);
}

void mettrePieceDefausse(Defausse* d, Piece* p, SDL_Renderer* contexte){
	int i, j;
	int x, y;
	int continuer = 1;
	for (j = 0; j < 2 && continuer; j++){
		for (i = 0; i < 8 && continuer; i++){
			if (d->tabPiecesDefaussees[j][i] == NULL){
				d->tabPiecesDefaussees[j][i] = p;
				x = d->position.x + OFFSET_GAUCHE_PIECE_DEFAUSSE + i*(LARGEUR_ESPACE_PIECE_DEFAUSSE+LARGEUR_PIECE_DEFAUSSE);
				y = d->position.y + OFFSET_HAUT_PIECE_DEFAUSSE + j*(HAUTEUR_ESPACE_PIECE_DEFAUSSE+HAUTEUR_PIECE_DEFAUSSE);
				afficherPieceDefausse(d, p, contexte, x, y);
				continuer = 0;
			}
		}
	}
}

void afficherPieceDefausse(Defausse* d, Piece* p, SDL_Renderer* contexte, int x, int y){
	SDL_Texture* texturePiece = SDL_CreateTextureFromSurface(contexte, p->imagePieceDefausse);
	if (texturePiece == NULL)
		logPrint(ERREUR, "Echec de la création de la texture de la pièce dans la défausse");
	SDL_Rect positionAffichage;
	positionAffichage.x = x;
	positionAffichage.y = y;
	positionAffichage.w = LARGEUR_PIECE_DEFAUSSE;
	positionAffichage.h = HAUTEUR_PIECE_DEFAUSSE;
	SDL_RenderCopy(contexte, texturePiece, NULL, &positionAffichage);
	SDL_DestroyTexture(texturePiece);
	SDL_free(&positionAffichage);
}
