#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <unistd.h>

#define GAME_CYCLE_TIME         100

void TimeManager(clock_t start_clock, uint8_t *game_cycles);

#endif // TIMER_H