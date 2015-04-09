#include "listeDeplacement.h"

Deplacement* newDeplacement(IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Deplacement* next, Deplacement* previous)
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
	//new->heure = heure;
	new->next = next;
	new->previous = previous;

	return new;
}

ListDeplacement* initListDeplacement()
{
	ListDeplacement* l = malloc(sizeof(ListDeplacement));
	l->current = l->first = l->last = NULL;

	return l;
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

int insertFirst(ListDeplacement *l, IDPiece piece1, IDCase depart1, IDCase arrivee1, int numeroDeplacement)
{
	Deplacement* new = newDeplacement(piece1, depart1, arrivee1, numeroDeplacement, l->first, NULL);
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

int insertLast(ListDeplacement *l, IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
{
	Deplacement* new = newDeplacement(piece, depart, arrivee, numeroDeplacement, NULL, l->last);
	if (new == NULL)
	{
		return 0;
	}

	if (empty(l))
	{
		l->first = l->current = new;
	}
	while (!last(l))
	{
		next(l);
	}
	l->current->next= l->last=new;
	new->next = NULL;

	return 1;
}

int insertAfterCurrentBL(ListDeplacement *l, IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
{
	if (empty(l))
	{
		insertFirst(l, piece, depart, arrivee, numeroDeplacement);
		l->current = l->current = l->last;

	}
	else
	{
		if (l->current == l->last)
		{
			insertLast(l, piece, depart, arrivee, numeroDeplacement);
		}
		else
		{
			Deplacement* new = newDeplacement(piece, depart, arrivee, numeroDeplacement, l->current->next, l->current);

			if (new == NULL);
			{
				return 0;
			}
			l->current->next = new;
		}
	}
	return 1;
}

int createNewDeplacement(ListDeplacement *l, IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
{
	static int posCurseur = 0;
	if (l->first == l->last)
	{
		insertFirst(l, piece, depart, arrivee, numeroDeplacement);
	}
	else
	{
		insertAfterCurrentBL(l, piece, depart, arrivee, numeroDeplacement);
		next(l);
	}
	printFileCurrentDeplacement(l, &posCurseur);

	return 1;
}

void next(ListDeplacement * l)
{
	l->current = l->current->next;
}

void previous(ListDeplacement *l)
{
	l->current = l->current->previous;
}

int printFileCurrentDeplacement(ListDeplacement * l, int *posCurseur) // Ne pas oubliez le curseur !! sans lui on est pas capable de se positionner dans le fichier
{
	FILE * fichierhistorique = NULL;
	printPiece(l, posCurseur);
	printDepart(l, posCurseur);
	printArrivee(l, posCurseur);


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

	fprintf(fichierhistorique, "%.2d:%c%c%d ",l->current->numeroDeplacement, l->current->currentPiece.type, l->current->currentPiece.couleur, l->current->currentPiece.numero);
	
	*posCurseur += 7;

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
	fprintf(fichierhistorique, "%d%d -> ", l->current->depart.colonne, l->current->depart.ligne);
	*posCurseur += 8;
	fclose(fichierhistorique);
}

void printArrivee(ListDeplacement * l, int *posCurseur)
{
	FILE * fichierhistorique = NULL;

	if ((fichierhistorique = fopen("Historique.txt", "r+")) == NULL)
	{
		logPrint(ERREUR, "Erreur d'ouverture du fichier historique depuis printArrivee");
	}
	fseek(fichierhistorique, *posCurseur, SEEK_SET);
	fprintf(fichierhistorique, "%d%d\n", l->current->arrivee.colonne, l->current->arrivee.ligne);
	*posCurseur += 4;
	fclose(fichierhistorique);
}
	


