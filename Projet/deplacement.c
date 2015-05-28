#include "deplacement.h"

void retourArriere(ListDeplacement *l, PlateauDeJeu *pl, MenuDroite * m, SDL_Renderer* contexte, Couleur couleurAJouer)
{
	int flagPionManger = 0;
	int flagPionTransformé = 0;

	///////////////////////////////////////////////////////////
	///////////Définition de variable qui ne seront ///////////
	//////////utilisé que si uune pièce à été mangé////////////
	///////////////////////////////////////////////////////////
	

	Lettre colonneArrivee = l->current->arrivee.colonne;
	Lettre ligneArrivee = l->current->arrivee.ligne;
	Piece *p = NULL;


	if (l->current->numeroDeplacement > 31)
	{
		if (l->current->IDPieceManger.couleur != l->current->currentPiece->idPiece.couleur)
		{
			flagPionManger = 1;
		}


		//On indique que l'ancienne case n'est plus occupee (la fct bougerPiece ne peut le faire...)
		pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = FALSE;

		bougerPiece(l->current->currentPiece, pl->echiquier->tabPieces, l->current->depart.colonne, l->current->depart.ligne, l);

		//On indique que la case sur laquelle est revenue la piece est occupee (idem...)
		pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = TRUE;

		deleteCurrent(l);
		deleteCurrent(l);

		//C'est ici qu'il fallait calculer l'id, pas avant !
		IDPiece* idPieceASortir = &(l->current->IDPieceManger);

		if (flagPionManger == 1)
		{
			// On remet le dernier pion mangé à la place où il devait être
			p = sortirPieceDefausse(pl->defausseBlanc, pl->defausseNoir, *idPieceASortir);

			pl->echiquier->tabCases[p->idPosition.colonne][p->idPosition.ligne]->occupee = FALSE;
			bougerPiece(p, pl->echiquier->tabPieces, colonneArrivee, ligneArrivee, l);
			pl->echiquier->tabCases[p->idPosition.colonne][p->idPosition.ligne]->occupee = TRUE;
			
			deleteCurrent(l);
			afficherMenuDroite(m, couleurAJouer,contexte);
		}
		if (flagPionTransformé == 1)
		{
			//On remet le pion transformé dans l'état Pion
		}
		afficherPlateauDeJeu(contexte, pl);
	}
}