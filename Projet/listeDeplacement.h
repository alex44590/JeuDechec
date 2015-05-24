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
	char mangerPiece; // 1 si une pièce a été mangé, 0 sinon
}Deplacement;


typedef struct {
	Deplacement* first;
	Deplacement* current;
	Deplacement* last;
}ListDeplacement;

/**
* \brief      Créer un nouveau noeud de déplacement
* \param[in] tous les paramètres du déplacement effectué
* \return ListDeplacement : Le nouveau noeud créé
*/
Deplacement * newDeplacement(Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Deplacement* next, Deplacement* previous);

/**IDPiece piece, IDCase depart, IDCase arrivee, int numeroDeplacement, Timer heure
* \brief      initialise à NULL ListeDeplacement
* \param[in/out] ListeDeplacement : paramaètres à mettre à NULL
*/
ListDeplacement* initListDeplacement();
/**
* \brief      Vérifie si la liste des déplacement est vide
* \param[in] ListeDeplacement
* \return   1 si la liste est vide, 0 sinon
*/
int empty(ListDeplacement * l);

/**
* \brief      Vérifie si on se trouve au début de la liste des déplacement
* \param[in] ListeDeplacement
* \return    1 si on est au début de la liste, 0 sinon
*/
int first(ListDeplacement * l);

/**
* \brief      Vérifie si on est à la fin de la liste
* \param[in] ListeDeplacement
* \return    1 si on est à la fin de la liste, 0 sinon
*/
int last(ListDeplacement * l);

/**
* \brief      Vérifie si on est en dehors de la liste
* \param[in] ListeDeplacement
* \return    1 si on est en dehors de la liste, 0 sinon
*/
int outOfList(ListDeplacement * l);

/**
* \brief      Positionne le curseur au début de la liste
* \param[in/out] ListeDeplacement
*/
void setOnFirst(ListDeplacement * l);

/**
* \brief      Positionne le curseur à la fin de la liste
* \param[in/out] ListeDeplacement
*/
void setOnLast(ListDeplacement * l);

/**
* \brief      insert un noeud en premiere position
* \param[in/out] ListeDeplacement + éléments de déplacements
* \return 0 si le déplacement ne s'est pas bien passé 1 sinon
*/
int insertFirst(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);

int insertLast(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);
int insertAfterCurrentBL(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);
int createNewDeplacement(ListDeplacement *l, Piece *piece, IDCase depart, IDCase arrivee, int numeroDeplacement);


/**
* \brief      Positionne le curseur à la position suivante
* \param[in/out] ListeDeplacement
*/
void next(ListDeplacement * l);

/**
* \brief      Positionne le curseur à la position précédente
* \param[in/out] ListeDeplacement
*/
void previous(ListDeplacement *l);

/**
* \brief      indique où se trouve le curseur
* \param[in/out] ListeDeplacement
* \return     la posittion du curseur dans le fichier texte
*/
int getCurrent(ListDeplacement * l);

/**
* \brief     ecrit dans le fichier à l'emplacement courantdu curseur
*			 toutes les informations du déplacement effectué
* \param[in/out] ListeDeplacement
* \param[in/out] posCurseur  La position du curseur en lecture/écriture
*/
int printFileCurrentDeplacement(ListDeplacement * l, int *posCurseur);

/**
* \brief     Création du fichier contenant toutes les informations relatives
*			 aux déplacements pendant une partie
* \return    NULL si erreur de création
*/
int createHistoryFile(void);

/**
* \brief     Sauvegarde dans un fichier texte le déplacement qui vient d'être effectué
*			 puis décale le curseur pour se préparer pour la pochaine sauvegarde
* \return    Si la sauvegarde s'est bien passé
*/
int saveDeplacement(ListDeplacement *l);

void printPiece(ListDeplacement * l, int *posCurseur);

void printDepart(ListDeplacement * l, int *posCurseur);
void printArrivee(ListDeplacement * l, int *posCurseur);

void retourArriere(ListDeplacement *l, Piece* tabPiece[8][8]);

void deleteCurrent(ListDeplacement* l);
void deleteLast(ListDeplacement* l);

#endif
