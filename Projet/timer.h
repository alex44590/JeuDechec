#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <stdint.h>

//Tous les temps sont en ms 
typedef struct{
	uint32_t debut;
	uint32_t temps_actuel;
	uint32_t chrono;
}Timer;

Timer init_timer();

void update_timer(Timer t);

int chrono();
#endif