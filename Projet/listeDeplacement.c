#include "listeDeplacement.h"

Deplacement* newDeplacement(IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Timer heure, Deplacement* next, Deplacement* previous)
{
	Deplacement* new = malloc(sizeof(Deplacement));

	if (new == NULL)
	{
		return NULL;
	}
	new->currentPiece = piece;
	new->depart = depart;
	new->arrivee = arrivee;
	new->numeroDeplacement = numeroDeplacement;
	new->heure = heure;
	new->next = next;
	new->previous = previous;

	return new;
}

void initListdeplacement(ListDeplacement *l)
{
	l->current = l->first = l->last = NULL;
}

int empty(ListDeplacement *l)
{
	return (l->first == NULL);
}

int first(ListDeplacement * l)
{
	return (l->current == l->first);
}

int last(ListDeplacement * l)
{
	return (l->current == l->last);
}

int outOfList(ListDeplacement * l)
{
	return (l->current == NULL);
}

void setOnFirst(ListDeplacement * l)
{
	l->current = l->first;
}

void setOnLast(ListDeplacement * l)
{
	l->current = l->last;
}

int insertFirst(ListDeplacement *l, IDPiece piece1, IDCase depart1, IDCase arrivee1, int numeroDeplacement, Timer heure)
{
	Deplacement* new = newDeplacement(piece1, depart1, arrivee1, numeroDeplacement, heure, l->first, NULL);
	if (new == NULL)
	{
		return 0;
	}

	if (empty(l))
	{
		l->last = l->current = new;
	}
	l->first = new;

	return 1;
}

int insertLast(ListDeplacement *l, IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Timer heure)
{
	Deplacement* new = newDeplacement(piece, depart, arrivee, numeroDeplacement, heure, NULL, l->last);
	if (new == NULL)
	{
		return 0;
	}

	if (empty(l))
	{
		l->first = l->current = new;
	}
	l->last = new;
	new->next = NULL;

	return 1;
}

int insertAfterCurrent(ListDeplacement *l, IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Timer heure)
{
	if (empty(l))
	{
		insertFirst(l, piece, depart, arrivee, numeroDeplacement, heure);
		l->current = l->current = l->last;

		return 1;
	}
	else
	{
		if (l->current == l->last)
		{
			insertLast(l, piece, depart, arrivee, numeroDeplacement, heure);
		}
		else
		{
			Deplacement* new = newDeplacement(piece, depart, arrivee, numeroDeplacement, heure, l->current->next, l->current);

			if (new == NULL);
			{
				return 0;
			}
			l->current->next = new;

			return 1;
		}
	}
}

void next(ListDeplacement * l)
{
	l->current = l->current->next;
}

void previous(ListDeplacement *l)
{
	l->current = l->current->previous;
}

//int getCurrent(ListDeplacement * l)
//{
//	return ();
//}

int printFileCurrentList(ListDeplacement * l, int *posCurseur)
{
	FILE * fichierhistorique = NULL;

	if ((fichierhistorique = fopen("Historique.txt", "w")) == NULL)
	{
		logPrint(ERREUR, "Erreur d'ouverture du fichier historique depuis printFile");
		return -1;
	}
	logPrint(INFO, "ouverture du fichier historique depuis printFile avec succès");
	
	printPiece(l, *posCurseur);
	


	fclose(fichierhistorique);
	return 0;
}

int createHistoryFile(void)
{
	FILE* fichierhistorique = fopen("Historique.txt", "w+");
	fclose(fichierhistorique);





	return 1;
}

void printPiece(ListDeplacement * l, int *posCurseur)
{
	FILE * fichierhistorique = NULL;

	if ((fichierhistorique = fopen("Historique.txt", "r+")) == NULL)
	{
		logPrint(ERREUR, "Erreur d'ouverture du fichier historique depuis printPiece");
	}
	fseek(fichierhistorique, *posCurseur, SEEK_SET);
	fprintf(fichierhistorique, "%c", l->current->currentPiece.type);
	fprintf(fichierhistorique, "%d", l->current->currentPiece.couleur);
	fprintf(fichierhistorique, "%2.d", l->current->currentPiece.numero);
	*posCurseur += 4;
	fclose(fichierhistorique);
}

void printDepart(ListDeplacement * l, int *posCurseur)
{
	FILE * fichierhistorique = NULL;

	if ((fichierhistorique = fopen("Historique.txt", "r+")) == NULL)
	{
		logPrint(ERREUR, "Erreur d'ouverture du fichier historique depuis printDepart");
	}
	fseek(fichierhistorique, *posCurseur, SEEK_SET);
	fprintf(fichierhistorique, "%d", l->current->depart.colonne);
	fprintf(fichierhistorique, "%d", l->current->depart.ligne);
	*posCurseur += 2;
	fclose(fichierhistorique);
}
	


