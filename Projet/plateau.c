#include "plateau.h"

void afficherCadre(SDL_Renderer* contexte){
	SDL_Surface* barreVerticaleG = IMG_Load("BarVG.png");
	SDL_Texture* textBarVG = SDL_CreateTextureFromSurface(contexte, barreVerticaleG);
	SDL_Rect positionAffichage;
	positionAffichage.x = OFFSET_BARRE_GAUCHE;
	positionAffichage.y = OFFSET_BARRE_HAUT;
	positionAffichage.w = LARGEUR_BARRE;
	positionAffichage.h = LONGUEUR_BARRE;
	SDL_RenderCopy(contexte, textBarVG, NULL, &positionAffichage);
	SDL_FreeSurface(barreVerticaleG);
	SDL_DestroyTexture(textBarVG);

	SDL_Surface* barreVerticaleD = IMG_Load("BarVD.png");
	SDL_Texture* textBarVD = SDL_CreateTextureFromSurface(contexte, barreVerticaleD);
	positionAffichage.x = OFFSET_BARRE_DROITE;
	SDL_RenderCopy(contexte, textBarVD, NULL, &positionAffichage);
	SDL_FreeSurface(barreVerticaleD);
	SDL_DestroyTexture(textBarVD);

	SDL_Surface* barreHorizontaleH = IMG_Load("BarHH.png");
	SDL_Texture* textBarHH = SDL_CreateTextureFromSurface(contexte, barreHorizontaleH);
	positionAffichage.x = OFFSET_BARRE_GAUCHE;
	positionAffichage.w = LONGUEUR_BARRE;
	positionAffichage.h = LARGEUR_BARRE;
	SDL_RenderCopy(contexte, textBarHH, NULL, &positionAffichage);
	SDL_FreeSurface(barreHorizontaleH);
	SDL_DestroyTexture(textBarHH);

	SDL_Surface* barreHorizontaleB = IMG_Load("BarHB.png");
	SDL_Texture* textBarHB = SDL_CreateTextureFromSurface(contexte, barreHorizontaleB);
	positionAffichage.y = OFFSET_BARRE_BAS;
	SDL_RenderCopy(contexte, textBarHB, NULL, &positionAffichage);
	SDL_FreeSurface(barreHorizontaleH);
	SDL_DestroyTexture(textBarHH);
}

void creerPlateau(Case* Plateau[8][8]){
	int i, j;
	for (i = 0; i < 7; i += 2){
		for (j = 0; j < 7; j += 2){
			Plateau[i][j] = creerCaseBlanche((IDCase){ i, j });
			Plateau[i][j + 1] = creerCaseNoire(((IDCase){ i, j + 1 }));
		}
	}
	for (i = 1; i < 8; i += 2){
		for (j = 0; j < 7; j += 2){
			Plateau[i][j + 1] = creerCaseBlanche((IDCase){ i, j + 1 });
			Plateau[i][j] = creerCaseNoire(((IDCase){ i, j }));
		}
	}
}

void afficherPlateau(Case* Plateau[8][8], SDL_Renderer* contexte){
	int i, j;
	for (i = 0; i < 7; i += 2){
		for (j = 0; j < 7; j += 2){
			afficherCase(Plateau[i][j], contexte);
			afficherCase(Plateau[i][j + 1], contexte);
		}
	}
	for (i = 1; i < 8; i += 2){
		for (j = 0; j < 7; j += 2){
			afficherCase(Plateau[i][j], contexte);
			afficherCase(Plateau[i][j + 1], contexte);
		}
	}
}