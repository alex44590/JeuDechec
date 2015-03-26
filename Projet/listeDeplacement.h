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
* \brief      initialise à NULL ListeDeplacement
* \param[in/out] ListeDeplacement : paramaètres à mettre à NULL
*/
void initListDeplacement(ListDeplacement *l);

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
int outOfList(ListDeplacement* * l);

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

//123456cbcb



#endif