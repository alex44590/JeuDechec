#ifndef LISTEDEPLACEMENT_H
#define LISTEDEPLACEMENT_H


//#include "deplacement.h"
#include "log.h"
#include "header.h"


typedef struct Deplacement{
	Piece * currentPiece;
	IDCase depart;
	IDCase arrivee;
	int numeroDeplacement;
	//Timer heure;
	struct Deplacement* next;
	struct Deplacement* previous;
	char mangerPiece; // 1 si une pi�ce a �t� mang�, 0 sinon
}Deplacement;


typedef struct {
	Deplacement* first;
	Deplacement* current;
	Deplacement* last;
}ListDeplacement;

/**
* \brief      Cr�er un nouveau noeud de d�placement
* \param[in] tous les param�tres du d�placement effectu�
* \return ListDeplacement : Le nouveau noeud cr��
*/
Deplacement * newDeplacement(Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Deplacement* next, Deplacement* previous);

/**IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Timer heure
* \brief      initialise � NULL ListeDeplacement
* \param[in/out] ListeDeplacement : parama�tres � mettre � NULL
*/
ListDeplacement* initListDeplacement();
/**
* \brief      V�rifie si la liste des d�placement est vide
* \param[in] ListeDeplacement
* \return   1 si la liste est vide, 0 sinon
*/
int empty(ListDeplacement * l);

/**
* \brief      V�rifie si on se trouve au d�but de la liste des d�placement
* \param[in] ListeDeplacement
* \return    1 si on est au d�but de la liste, 0 sinon
*/
int first(ListDeplacement * l);

/**
* \brief      V�rifie si on est � la fin de la liste
* \param[in] ListeDeplacement
* \return    1 si on est � la fin de la liste, 0 sinon
*/
int last(ListDeplacement * l);

/**
* \brief      V�rifie si on est en dehors de la liste
* \param[in] ListeDeplacement
* \return    1 si on est en dehors de la liste, 0 sinon
*/
int outOfList(ListDeplacement * l);

/**
* \brief      Positionne le curseur au d�but de la liste
* \param[in/out] ListeDeplacement
*/
void setOnFirst(ListDeplacement * l);

/**
* \brief      Positionne le curseur � la fin de la liste
* \param[in/out] ListeDeplacement
*/
void setOnLast(ListDeplacement * l);

/**
* \brief      insert un noeud en premiere position
* \param[in/out] ListeDeplacement + �l�ments de d�placements
* \return 0 si le d�placement ne s'est pas bien pass� 1 sinon
*/
int insertFirst(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

int insertLast(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);
int insertAfterCurrentBL(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);
int createNewDeplacement(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);


/**
* \brief      Positionne le curseur � la position suivante
* \param[in/out] ListeDeplacement
*/
void next(ListDeplacement * l);

/**
* \brief      Positionne le curseur � la position pr�c�dente
* \param[in/out] ListeDeplacement
*/
void previous(ListDeplacement *l);

/**
* \brief      indique o� se trouve le curseur
* \param[in/out] ListeDeplacement
* \return     la posittion du curseur dans le fichier texte
*/
int getCurrent(ListDeplacement * l);

/**
* \brief     ecrit dans le fichier � l'emplacement courantdu curseur
*			 toutes les informations du d�placement effectu�
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/�criture
*/
int printFileCurrentDeplacement(ListDeplacement * l, int *posCurseur);

/**
* \brief     Cr�ation du fichier contenant toutes les informations relatives
*			 aux d�placements pendant une partie
* \return    NULL si erreur de cr�ation
*/
int createHistoryFile(void);

/**
* \brief     Sauvegarde dans un fichier texte le d�placement qui vient d'�tre effectu�
*			 puis d�cale le curseur pour se pr�parer pour la pochaine sauvegarde
* \return    Si la sauvegarde s'est bien pass�
*/
int saveDeplacement(ListDeplacement *l);

void printPiece(ListDeplacement * l, int *posCurseur);

void printDepart(ListDeplacement * l, int *posCurseur);
void printArrivee(ListDeplacement * l, int *posCurseur);

void retourArriere(ListDeplacement *l, Piece* tabPiece[8][8]);

void deleteCurrent(ListDeplacement* l);
void deleteLast(ListDeplacement* l);

#endif
