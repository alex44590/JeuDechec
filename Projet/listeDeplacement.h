#ifndef LISTEDEPLACEMENT_H
#define LISTEDEPLACEMENT_H

#include "deplacement.h"

//typedef struct{
//	Deplacement deplacement;
//	struct NodeDeplacement* next;
//	struct NodeDeplacement* before;
//}NodeDeplacement;

typedef struct {
	Deplacement first;
	Deplacement current;
	Deplacement last;
}ListDeplacement;


/**
* \brief      initialise � NULL ListeDeplacement
* \param[in/out] ListeDeplacement : parama�tres � mettre � NULL
*/
void initListDeplacement(ListDeplacement *l);

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
*/
void printFileCurrentList(ListDeplacement * l);

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

#endif