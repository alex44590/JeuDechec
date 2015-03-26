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
*/
void printFileCurrentList(ListDeplacement * l);

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

#endif