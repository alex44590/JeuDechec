#ifndef LOG_H
#define LOG_H
/*Définit les fonctions de bases d'un fichier de log qui sert à suivre l'avancement
dans le programme et à afficher les éventuelles erreurs ou évènements notables*/

#include <stdlib.h>
#include <stdio.h>

typedef enum { INFO, AVERTISSEMENT, ERREUR }LogType;


/*Fonction servant simplement à créer un nouveau fichier de log VIDE*/
/**
* \fn void logInit()
* \brief   Créer un nouveau fichier log vide
*/
void logInit();

//Fct permettant d'écrire un message de type info, avertissement ou erreur dans le fichier de log
/**
* \fn void logPrint(LogType typeMessage, char* message)
* \brief   Permet d'écrire unu message d'info, avertissement ou erreur dans le fichier log
* \param[in] LogType typeMessage,
* \param[in] char* message
*/
void logPrint(LogType typeMessage, char* message);


#endif // !LOG_H
