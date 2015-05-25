#include "deplacement.h"

void retourArriere(ListDeplacement *l, Piece* tabPiece[8][8])
{
	int flagPionManger = 0;
	int flagPionTransformé = 0;
	if (l->current != l->first)
	{
		if (l->current->mangerPiece == 1)
		{
			flagPionManger = 1;
		}
		bougerPiece(l->current->currentPiece, tabPiece, l->current->depart.colonne, l->current->depart.ligne, l);
		deleteCurrent(l);
		deleteCurrent(l);
		if (flagPionManger == 1)
		{
			// On remet le dernier pion mangé à la place où il devait être
		}
		if (flagPionTransformé == 1)
		{
			//On remet le pion transformé dans l'état Pion
		}
	}
}