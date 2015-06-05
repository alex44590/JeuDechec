#ifndef LOG_H
#define LOG_H
/*D�finit les fonctions de bases d'un fichier de log qui sert � suivre l'avancement
dans le programme et � afficher les �ventuelles erreurs ou �v�nements notables*/

#include <stdlib.h>
#include <stdio.h>

typedef enum { INFO, AVERTISSEMENT, ERREUR }LogType;


/*Fonction servant simplement � cr�er un nouveau fichier de log VIDE*/
/**
* \fn void logInit()
* \brief   Cr�er un nouveau fichier log vide
*/
void logInit();

//Fct permettant d'�crire un message de type info, avertissement ou erreur dans le fichier de log
/**
* \fn void logPrint(LogType typeMessage, char* message)
* \brief   Permet d'�crire unu message d'info, avertissement ou erreur dans le fichier log
* \param[in] LogType typeMessage,
* \param[in] char* message
*/
void logPrint(LogType typeMessage, char* message);


#endif // !LOG_H
