/**
* \file listDeplacement
* \brief gestion de la liste des D�placements
* \author VIGNAL A, MIQUEU C, MONNIER N, TASSE A.
* \version 1
*
*/
#ifndef LISTEDEPLACEMENT_H
#define LISTEDEPLACEMENT_H


#include "log.h"
#include "pieceCommun.h"

/**
* \struct Deplacement
* \brief caract�ristiques d'un d�placement
*
*/
typedef struct Deplacement{
	Piece * currentPiece;
	IDCase depart;
	IDCase arrivee;
	int numeroDeplacement;
	//Timer heure;
	struct Deplacement* next;
	struct Deplacement* previous;
	IDPiece IDPieceManger; // IDPieceManger si une pi�ce a �t� mang�, IDPieceCurrent sinon
	int deplacementRoque;
}Deplacement;

/**
* \struct listDeplacement
* \brief curseur sur la liste des d�placements
*
*/
typedef struct {
	Deplacement* first;
	Deplacement* current;
	Deplacement* last;
}ListDeplacement;

/**
* \fn Deplacement * newDeplacement(Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Deplacement* next, Deplacement* previous)
* \brief      Cr�er un nouveau noeud de d�placement
* \param[in] tous les param�tres du d�placement effectu�
* \return ListDeplacement : Le nouveau noeud cr��
*/
Deplacement * newDeplacement(Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Deplacement* next, Deplacement* previous);

/**
* \fn ListDeplacement* initListDeplacement()
* \brief      initialise � NULL ListeDeplacement
* \param[in/out] ListeDeplacement : parama�tres � mettre � NULL
*/
ListDeplacement* initListDeplacement();

/**
* \fn int empty(ListDeplacement * l)
* \brief      V�rifie si la liste des d�placement est vide
* \param[in] ListeDeplacement
* \return   1 si la liste est vide, 0 sinon
*/
int empty(ListDeplacement * l);

/**
* \fn int first(ListDeplacement * l)
* \brief      V�rifie si on se trouve au d�but de la liste des d�placement
* \param[in] ListeDeplacement
* \return    1 si on est au d�but de la liste, 0 sinon
*/
int first(ListDeplacement * l);

/**
* \fn int last(ListDeplacement * l)
* \brief      V�rifie si on est � la fin de la liste
* \param[in] ListeDeplacement
* \return    1 si on est � la fin de la liste, 0 sinon
*/
int last(ListDeplacement * l);

/**
* \fn int outOfList(ListDeplacement * l)
* \brief      V�rifie si on est en dehors de la liste
* \param[in] ListeDeplacement
* \return    1 si on est en dehors de la liste, 0 sinon
*/
int outOfList(ListDeplacement * l);

/**
* \fn void setOnFirst(ListDeplacement * l)
* \brief      Positionne le curseur au d�but de la liste
* \param[in/out] ListeDeplacement
*/
void setOnFirst(ListDeplacement * l);

/**
* \fn void setOnLast(ListDeplacement * l)
* \brief      Positionne le curseur � la fin de la liste
* \param[in/out] ListeDeplacement
*/
void setOnLast(ListDeplacement * l);

/**
* \fn int insertFirst(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
* \brief      insert un noeud en premiere position
* \param[in/out] ListeDeplacement + �l�ments de d�placements
* \return 0 si le d�placement ne s'est pas bien pass� 1 sinon
*/
int insertFirst(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

/**
* \fn int insertLast(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
* \brief      insert un noeud en derni�re position
* \param[in/out] ListeDeplacement + �l�ments de d�placements
* \return 0 si le d�placement ne s'est pas bien pass� 1 sinon
*/
int insertLast(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

/**
* \fn int insertAfterCurrentBL(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);
* \brief      insert un noeud apr�s le noeud courant
* \param[in/out] ListeDeplacement + �l�ments de d�placements
* \return 0 si le d�placement ne s'est pas bien pass� 1 sinon
*/
int insertAfterCurrentBL(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

/**
* \fn int createNewDeplacement(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
* \brief      Cr�er un nouveau noeud Deplacement
* \param[in/out] ListeDeplacement + �l�ments de d�placements
* \return 0 si le d�placement ne s'est pas bien pass� 1 sinon
*/
int createNewDeplacement(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);


/**
* \fn void next(ListDeplacement * l)
* \brief      Positionne le curseur � la position suivante
* \param[in/out] ListeDeplacement
*/
void next(ListDeplacement * l);

/**
* \fn void previous(ListDeplacement *l)
* \brief      Positionne le curseur � la position pr�c�dente
* \param[in/out] ListeDeplacement
*/
void previous(ListDeplacement *l);

/**
* \fn int getCurrent(ListDeplacement * l)
* \brief      indique o� se trouve le curseur
* \param[in/out] ListeDeplacement
* \return     la posittion du curseur dans le fichier texte
*/
int getCurrent(ListDeplacement * l);

/**
* \fn int printFileCurrentDeplacement(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier � l'emplacement courantdu curseur
*			 toutes les informations du d�placement effectu�
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/�criture
*/
int printFileCurrentDeplacement(ListDeplacement * l, int *posCurseur);

/**
* \fn int createHistoryFile(void)
* \brief     Cr�ation du fichier contenant toutes les informations relatives
*			 aux d�placements pendant une partie
* \return    NULL si erreur de cr�ation
*/
int createHistoryFile(void);

/**
* \fn int saveDeplacement(ListDeplacement *l)
* \brief     Sauvegarde dans un fichier texte le d�placement qui vient d'�tre effectu�
*			 puis d�cale le curseur pour se pr�parer pour la pochaine sauvegarde
* \return    Si la sauvegarde s'est bien pass�
*/
int saveDeplacement(ListDeplacement *l);



/**
* \fn void printPiece(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier � l'emplacement courantdu curseur
*			 L'ID de la pi�ce
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/�criture
*/
void printPiece(ListDeplacement * l, int *posCurseur);

/**
* \fn void printDepart(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier � l'emplacement courantdu curseur
*			 L'ID de la case de d�part du d�placement
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/�criture
*/
void printDepart(ListDeplacement * l, int *posCurseur);

/**
* \fn void printArrivee(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier � l'emplacement courantdu curseur
*			 L'ID de la case de d'arriv� du d�placement
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/�criture
*/
void printArrivee(ListDeplacement * l, int *posCurseur);

/**
* \fn void deleteCurrent(ListDeplacement* l)
* \brief     Supprime le d�placement courant
* \param[in/out] ListeDeplacement
*/
void deleteCurrent(ListDeplacement* l);

/**
* \fn void deleteLast(ListDeplacement* l)
* \brief     Supprime le dernier d�placement
* \param[in/out] ListeDeplacement
*/
void deleteLast(ListDeplacement* l);

#endif
