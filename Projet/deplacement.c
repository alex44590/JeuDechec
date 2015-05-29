#include "deplacement.h"

void retourArriere(ListDeplacement *l, PlateauDeJeu *pl, MenuDroite * m, SDL_Renderer* contexte, Couleur couleurAJouer, ContexteRoque* c)
{
	int flagPionManger = 0;
	int flagPionTransform� = 0;

	///////////////////////////////////////////////////////////
	///////////D�finition de variable qui ne seront ///////////
	//////////utilis� que si uune pi�ce � �t� mang�////////////
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

		/****************************************************************************
		****On g�re ici le cas o� le d�placement � supprimer est un roque************
		*****************************************************************************/
		if (l->current->deplacementRoque == 1)
		{
			pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = FALSE;

			bougerPiece(l->current->currentPiece, pl->echiquier->tabPieces, l->current->depart.colonne, l->current->depart.ligne, l);

			//On indique que la case sur laquelle est revenue la piece est occupee (idem...)
			pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = TRUE;

			//On r�actualise 
			if (l->current->currentPiece->idPiece.type == 'R')
			{
				if (l->current->currentPiece->idPiece.couleur == 'N')
					c->roiDejaBouge[NOIR] = FALSE;
				else if (l->current->currentPiece->idPiece.couleur == 'B')
					c->roiDejaBouge[BLANC] = FALSE;				
			}
			else if (l->current->currentPiece->idPiece.type == 'T')
			{
				if ((l->current->currentPiece->idPiece.couleur == 'N') && (l->current->currentPiece->idPiece.numero == 0))
					c->tourDejaBouge[NOIR][0] = FALSE;
				else if ((l->current->currentPiece->idPiece.couleur == 'N') && (l->current->currentPiece->idPiece.numero == 1))
					c->tourDejaBouge[NOIR][1] = FALSE;
				else if ((l->current->currentPiece->idPiece.couleur == 'B') && (l->current->currentPiece->idPiece.numero == 0))
					c->tourDejaBouge[BLANC][0] = FALSE;
				else if ((l->current->currentPiece->idPiece.couleur == 'B') && (l->current->currentPiece->idPiece.numero == 1))
					c->tourDejaBouge[BLANC][1] = FALSE;
			}
			deleteCurrent(l);
			numeroDeplacement--;

			deleteCurrent(l);
			numeroDeplacement--;


			pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = FALSE;

			bougerPiece(l->current->currentPiece, pl->echiquier->tabPieces, l->current->depart.colonne, l->current->depart.ligne, l);

			//On indique que la case sur laquelle est revenue la piece est occupee (idem...)
			pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = TRUE;

			//On r�actualise 
			if (l->current->currentPiece->idPiece.type == 'R')
			{
				if (l->current->currentPiece->idPiece.couleur == 'N')
					c->roiDejaBouge[NOIR] = FALSE;
				else if (l->current->currentPiece->idPiece.couleur == 'B')
					c->roiDejaBouge[BLANC] = FALSE;
			}
			else if (l->current->currentPiece->idPiece.type == 'T')
			{
				if ((l->current->currentPiece->idPiece.couleur == 'N') && (l->current->currentPiece->idPiece.numero == 0))
					c->tourDejaBouge[NOIR][0] = FALSE;
				else if ((l->current->currentPiece->idPiece.couleur == 'N') && (l->current->currentPiece->idPiece.numero == 1))
					c->tourDejaBouge[NOIR][1] = FALSE;
				else if ((l->current->currentPiece->idPiece.couleur == 'B') && (l->current->currentPiece->idPiece.numero == 0))
					c->tourDejaBouge[BLANC][0] = FALSE;
				else if ((l->current->currentPiece->idPiece.couleur == 'B') && (l->current->currentPiece->idPiece.numero == 1))
					c->tourDejaBouge[BLANC][1] = FALSE;
			}

			deleteCurrent(l);
			numeroDeplacement--;

			deleteCurrent(l);
			numeroDeplacement--;
		}

		/****************************************************************************
		*******************On g�re ici tous les autres d�placement*******************
		*****************************************************************************/
		else
		{
			//On indique que l'ancienne case n'est plus occupee (la fct bougerPiece ne peut le faire...)
			pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = FALSE;

			bougerPiece(l->current->currentPiece, pl->echiquier->tabPieces, l->current->depart.colonne, l->current->depart.ligne, l);

			//On indique que la case sur laquelle est revenue la piece est occupee (idem...)
			pl->echiquier->tabCases[l->current->currentPiece->idPosition.colonne][l->current->currentPiece->idPosition.ligne]->occupee = TRUE;

			//On v�rifie si la pi�ce revenu en arri�re est un Roi pour pouvoir remettre le Roque en place si jamais il est revenu � sa position iniitale
			if (l->current->currentPiece->idPiece.type == 'R')
			{
				if (l->current->currentPiece->idPiece.couleur == 'N')
				{
					if ((l->current->arrivee.colonne == 4) && (l->current->arrivee.ligne == 0))
						c->roiDejaBouge[NOIR] = FALSE;
				}
				else if (l->current->currentPiece->idPiece.couleur == 'B')
				{
					if ((l->current->arrivee.colonne == 4) && (l->current->arrivee.ligne == 7))
						c->roiDejaBouge[BLANC] = FALSE;
				}
			}
			//On fait la m�me chose avec les tours maintenant 
			else if (l->current->currentPiece->idPiece.type == 'T')
			{
				if (l->current->currentPiece->idPiece.couleur == 'N')
				{
					if (l->current->currentPiece->idPiece.numero == 0)
					{
						if ((l->current->arrivee.colonne == 0) && (l->current->arrivee.ligne == 0))
							c->tourDejaBouge[NOIR][0] = FALSE;
					}
					else if (l->current->currentPiece->idPiece.numero == 1)
					{
						if ((l->current->arrivee.colonne == 7) && (l->current->arrivee.ligne == 0))
							c->tourDejaBouge[NOIR][1] = FALSE;
					}
				}
				else if (l->current->currentPiece->idPiece.couleur == 'B')
				{
					if (l->current->currentPiece->idPiece.numero == 0)
					{
						if ((l->current->arrivee.colonne == 0) && (l->current->arrivee.ligne == 7))
							c->tourDejaBouge[BLANC][0] = FALSE;
					}
					else if (l->current->currentPiece->idPiece.numero == 1)
					{
						if ((l->current->arrivee.colonne == 7) && (l->current->arrivee.ligne == 7))
							c->tourDejaBouge[BLANC][1] = FALSE;
					}
				}
			}

			//La suppression de 2 d�placement correspond : au d�placemenr effectu� pour remettre la pi�ce � son endroit initiale et le 2e au d�placement voulant �tre supprim� initialement
			deleteCurrent(l);
			numeroDeplacement--;

			deleteCurrent(l);
			numeroDeplacement--;

			//C'est ici qu'il fallait calculer l'id, pas avant !
			IDPiece* idPieceASortir = &(l->current->IDPieceManger);

			if (flagPionManger == 1)
			{
				// On remet le dernier pion mang� � la place o� il devait �tre
				p = sortirPieceDefausse(pl->defausseBlanc, pl->defausseNoir, *idPieceASortir);

				pl->echiquier->tabCases[p->idPosition.colonne][p->idPosition.ligne]->occupee = FALSE;
				bougerPiece(p, pl->echiquier->tabPieces, colonneArrivee, ligneArrivee, l);
				pl->echiquier->tabCases[p->idPosition.colonne][p->idPosition.ligne]->occupee = TRUE;

				deleteCurrent(l);
				numeroDeplacement--;
				afficherMenuDroite(m, couleurAJouer, contexte);
			}
			if (flagPionTransform� == 1)
			{
				//On remet le pion transform� dans l'�tat Pion
			}
			
		}

		afficherPlateauDeJeu(contexte, pl);
	}
}