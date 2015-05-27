#include "deplacement.h"

void retourArriere(ListDeplacement *l, PlateauDeJeu *pl, MenuDroite * m, SDL_Renderer* contexte, Couleur couleurAJouer)
{
	int flagPionManger = 0;
	int flagPionTransform� = 0;

	///////////////////////////////////////////////////////////
	///////////D�finition de variable qui ne seront ///////////
	//////////utilis� que si uune pi�ce � �t� mang�////////////
	///////////////////////////////////////////////////////////
	IDPiece idPieceASortir = l->current->IDPieceManger;
	Lettre colonneArrivee = l->current->arrivee.colonne;
	Lettre ligneArrivee = l->current->arrivee.ligne;
	Piece *p = NULL;


	if (l->current->numeroDeplacement > 31)
	{
		if (l->current->IDPieceManger.couleur != l->current->currentPiece->idPiece.couleur)
		{
			flagPionManger = 1;
		}
		bougerPiece(l->current->currentPiece, pl->echiquier->tabPieces, l->current->depart.colonne, l->current->depart.ligne, l);
		deleteCurrent(l);
		deleteCurrent(l);
		if (flagPionManger == 1)
		{
			// On remet le dernier pion mang� � la place o� il devait �tre
			p = sortirPieceDefausse(pl->defausseBlanc, pl->defausseNoir, idPieceASortir);
			bougerPiece(p, pl->echiquier->tabPieces, colonneArrivee, ligneArrivee, l);
			deleteCurrent(l);
			afficherMenuDroite(m, couleurAJouer,contexte);
		}
		if (flagPionTransform� == 1)
		{
			//On remet le pion transform� dans l'�tat Pion
		}
		afficherPlateauDeJeu(contexte, pl);
	}
}