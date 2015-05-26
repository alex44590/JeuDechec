#include "deplacement.h"

void retourArriere(ListDeplacement *l, Piece* tabPiece[8][8], Defausse* dBlanc, Defausse* dNoir, MenuDroite * m, SDL_Renderer* contexte)
{
	int flagPionManger = 0;
	int flagPionTransformé = 0;

	///////////////////////////////////////////////////////////
	///////////Définition de variable qui ne seront ///////////
	//////////utilisé que si uune pièce à été mangé////////////
	///////////////////////////////////////////////////////////
	IDPiece idPieceASortir = l->current->IDPieceManger;
	Lettre colonneArrivee = l->current->arrivee.colonne;
	Lettre ligneArrivee = l->current->arrivee.ligne;
	Piece *p = NULL;


	if (l->current != l->first)
	{
		if (l->current->IDPieceManger.couleur != l->current->currentPiece->idPiece.couleur)
		{
			flagPionManger = 1;
		}
		bougerPiece(l->current->currentPiece, tabPiece, l->current->depart.colonne, l->current->depart.ligne, l);
		deleteCurrent(l);
		deleteCurrent(l);
		if (flagPionManger == 1)
		{
			// On remet le dernier pion mangé à la place où il devait être
			p = sortirPieceDefausse(dBlanc, dNoir, idPieceASortir);
			bougerPiece(p, tabPiece, colonneArrivee, ligneArrivee, l);
			deleteCurrent(l);
			afficherMenuDroite(m, contexte);

		}
		if (flagPionTransformé == 1)
		{
			//On remet le pion transformé dans l'état Pion
		}
	}
}