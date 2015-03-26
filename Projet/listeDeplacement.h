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
int outOfList(ListDeplacement* * l);

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

//123456cbcb



#endif