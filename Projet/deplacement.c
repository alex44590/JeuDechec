#include "deplacement.h"

void retourArriere(ListDeplacement *l, Piece* tabPiece[8][8])
{
	int flagPionManger = 0;
	int flagPionTransform� = 0;
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
			// On remet le dernier pion mang� � la place o� il devait �tre
		}
		if (flagPionTransform� == 1)
		{
			//On remet le pion transform� dans l'�tat Pion
		}
	}
}