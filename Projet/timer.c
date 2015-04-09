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
//principe : clock() nous donne le battement de proco depuis le début du programme. Pour creer le chronomètre il suffit de faire clock au lancement de la partie
//afin de pouvoir faire la difference est ainsi mettre à zéro le chronometre. A chaque coupe joué on fera appel à la fonction clock() à laquelle on apliquera difftime 
//afin d'avoir le bon temps
// il faudra creer{ une boucle qui dès que le jeu est lancé assigne une valeur à début de partie cad debut_partie = clock()