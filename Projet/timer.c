#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include <time.h>

volatile time_t debut_partie = 0;

Timer init_timer(time_t chr, time_t deb){
	Timer t;
	t.chrono = chr;
	t.debut = deb;
	}


void timer () {
	Timer t;
	clock_t temps; 
	clock_t chrono;
	if (time_t != 0){
		temps = clock();
	}


	
}
//principe : clock() nous donne le battement de proco depuis le d�but du programme. Pour creer le chronom�tre il suffit de faire clock au lancement de la partie
//afin de pouvoir faire la difference est ainsi mettre � z�ro le chronometre. A chaque coupe jou� on fera appel � la fonction clock() � laquelle on apliquera difftime 
//afin d'avoir le bon temps
// il faudra creer{ une boucle qui d�s que le jeu est lanc� assigne une valeur � d�but de partie cad debut_partie = clock()