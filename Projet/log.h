#ifndef LOG_H
#define LOG_H
/*Définit les fonctions de bases d'un fichier de log qui sert à suivre l'avancement
dans le programme et à afficher les éventuelles erreurs ou évènements notables*/

#include <stdlib.h>
#include <stdio.h>

typedef enum { INFO, AVERTISSEMENT, ERREUR }LogType;


/*Fonction servant simplement à créer un nouveau fichier de log VIDE*/
void logInit();

//Fct permettant d'écrire un message de type info, avertissement ou erreur dans le fichier de log
void logPrint(LogType typeMessage, char* message);




#endif // !LOG_H
