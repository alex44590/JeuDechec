#ifndef LISTEDEPLACEMENT_H
#define LISTEDEPLACEMENT_H


#include "log.h"
#include "pieceCommun.h"


typedef struct Deplacement{
	Piece * currentPiece;
	IDCase depart;
	IDCase arrivee;
	int numeroDeplacement;
	//Timer heure;
	struct Deplacement* next;
	struct Deplacement* previous;
	IDPiece IDPieceManger; // IDPieceManger si une pièce a été mangé, IDPieceCurrent sinon
	int deplacementRoque;
}Deplacement;


typedef struct {
	Deplacement* first;
	Deplacement* current;
	Deplacement* last;
}ListDeplacement;

/**
* \fn Deplacement * newDeplacement(Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Deplacement* next, Deplacement* previous)
* \brief      Créer un nouveau noeud de déplacement
* \param[in] tous les paramètres du déplacement effectué
* \return ListDeplacement : Le nouveau noeud créé
*/
Deplacement * newDeplacement(Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Deplacement* next, Deplacement* previous);

/**
* \fn ListDeplacement* initListDeplacement()
* \brief      initialise à NULL ListeDeplacement
* \param[in/out] ListeDeplacement : paramaètres à mettre à NULL
*/
ListDeplacement* initListDeplacement();

/**
* \fn int empty(ListDeplacement * l)
* \brief      Vérifie si la liste des déplacement est vide
* \param[in] ListeDeplacement
* \return   1 si la liste est vide, 0 sinon
*/
int empty(ListDeplacement * l);

/**
* \fn int first(ListDeplacement * l)
* \brief      Vérifie si on se trouve au début de la liste des déplacement
* \param[in] ListeDeplacement
* \return    1 si on est au début de la liste, 0 sinon
*/
int first(ListDeplacement * l);

/**
* \fn int last(ListDeplacement * l)
* \brief      Vérifie si on est à la fin de la liste
* \param[in] ListeDeplacement
* \return    1 si on est à la fin de la liste, 0 sinon
*/
int last(ListDeplacement * l);

/**
* \fn int outOfList(ListDeplacement * l)
* \brief      Vérifie si on est en dehors de la liste
* \param[in] ListeDeplacement
* \return    1 si on est en dehors de la liste, 0 sinon
*/
int outOfList(ListDeplacement * l);

/**
* \fn void setOnFirst(ListDeplacement * l)
* \brief      Positionne le curseur au début de la liste
* \param[in/out] ListeDeplacement
*/
void setOnFirst(ListDeplacement * l);

/**
* \fn void setOnLast(ListDeplacement * l)
* \brief      Positionne le curseur à la fin de la liste
* \param[in/out] ListeDeplacement
*/
void setOnLast(ListDeplacement * l);

/**
* \fn int insertFirst(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
* \brief      insert un noeud en premiere position
* \param[in/out] ListeDeplacement + éléments de déplacements
* \return 0 si le déplacement ne s'est pas bien passé 1 sinon
*/
int insertFirst(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

/**
* \fn int insertLast(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
* \brief      insert un noeud en dernière position
* \param[in/out] ListeDeplacement + éléments de déplacements
* \return 0 si le déplacement ne s'est pas bien passé 1 sinon
*/
int insertLast(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

/**
* \fn int insertAfterCurrentBL(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);
* \brief      insert un noeud après le noeud courant
* \param[in/out] ListeDeplacement + éléments de déplacements
* \return 0 si le déplacement ne s'est pas bien passé 1 sinon
*/
int insertAfterCurrentBL(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

/**
* \fn int createNewDeplacement(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement)
* \brief      Créer un nouveau noeud Deplacement
* \param[in/out] ListeDeplacement + éléments de déplacements
* \return 0 si le déplacement ne s'est pas bien passé 1 sinon
*/
int createNewDeplacement(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);


/**
* \fn void next(ListDeplacement * l)
* \brief      Positionne le curseur à la position suivante
* \param[in/out] ListeDeplacement
*/
void next(ListDeplacement * l);

/**
* \fn void previous(ListDeplacement *l)
* \brief      Positionne le curseur à la position précédente
* \param[in/out] ListeDeplacement
*/
void previous(ListDeplacement *l);

/**
* \fn int getCurrent(ListDeplacement * l)
* \brief      indique où se trouve le curseur
* \param[in/out] ListeDeplacement
* \return     la posittion du curseur dans le fichier texte
*/
int getCurrent(ListDeplacement * l);

/**
* \fn int printFileCurrentDeplacement(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier à l'emplacement courantdu curseur
*			 toutes les informations du déplacement effectué
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/écriture
*/
int printFileCurrentDeplacement(ListDeplacement * l, int *posCurseur);

/**
* \fn int createHistoryFile(void)
* \brief     Création du fichier contenant toutes les informations relatives
*			 aux déplacements pendant une partie
* \return    NULL si erreur de création
*/
int createHistoryFile(void);

/**
* \fn int saveDeplacement(ListDeplacement *l)
* \brief     Sauvegarde dans un fichier texte le déplacement qui vient d'être effectué
*			 puis décale le curseur pour se préparer pour la pochaine sauvegarde
* \return    Si la sauvegarde s'est bien passé
*/
int saveDeplacement(ListDeplacement *l);



/**
* \fn void printPiece(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier à l'emplacement courantdu curseur
*			 L'ID de la pièce
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/écriture
*/
void printPiece(ListDeplacement * l, int *posCurseur);

/**
* \fn void printDepart(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier à l'emplacement courantdu curseur
*			 L'ID de la case de départ du déplacement
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/écriture
*/
void printDepart(ListDeplacement * l, int *posCurseur);

/**
* \fn void printArrivee(ListDeplacement * l, int *posCurseur)
* \brief     ecrit dans le fichier à l'emplacement courantdu curseur
*			 L'ID de la case de d'arrivé du déplacement
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/écriture
*/
void printArrivee(ListDeplacement * l, int *posCurseur);

/**
* \fn void deleteCurrent(ListDeplacement* l)
* \brief     Supprime le déplacement courant
* \param[in/out] ListeDeplacement
*/
void deleteCurrent(ListDeplacement* l);

/**
* \fn void deleteLast(ListDeplacement* l)
* \brief     Supprime le dernier déplacement
* \param[in/out] ListeDeplacement
*/
void deleteLast(ListDeplacement* l);

#endif
