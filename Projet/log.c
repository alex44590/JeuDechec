#include "log.h"

void logInit(){
	FILE* fichierLog = fopen("log.txt", "w");
	fclose(fichierLog);
}

void logPrint(LogType typeMessage, char* message){
	FILE* fichierLog = fopen("log.txt", "a");
	switch (typeMessage){
	case INFO:
		fprintf(fichierLog, "\nINFO : ");
		fprintf(fichierLog, message);
		break;

	case AVERTISSEMENT:
		fprintf(fichierLog, "\nAVERTISSEMENT : ");
		fprintf(fichierLog, message);
		break;

	case ERREUR:
		fprintf(fichierLog, "\nERREUR : ");
		fprintf(fichierLog, message);
		break;

	default:
		fprintf(fichierLog, "\nTYPE DE MESSAGE NON RENSEIGNE : ");
		fprintf(fichierLog, message);
		break;
	}
	fclose(fichierLog);
}