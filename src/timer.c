#include <stdint.h>
#include "inc/timer.h"

void TimeManager(clock_t start_clock, uint8_t *game_cycles) {
  clock_t total_clock;
  total_clock = clock() - start_clock;
  
  double time_taken;
  time_taken =  total_clock/CLOCKS_PER_SEC;
  sleep((double)(GAME_CYCLE_TIME/1000)-time_taken);

  if(++(*game_cycles) == 255) {
    game_cycles = 0;
  }
}