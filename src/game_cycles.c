#include "inc/game_cycles.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define _POSIX_C_SOURCE 199309L //For nanosleep(); to work.
#include <time.h>


static int ms_sleep(unsigned int ms);


void CyclesInit(const uint16_t dart_step,
                const uint16_t enemies_step,
                const uint16_t hero_step,
                GameCycles *cycles)
{
  cycles->actual = 0;
  cycles->dart = 0;
  cycles->enemies = 0;
  cycles->hero = 0;

  cycles->dart_step = dart_step;
  cycles->enemies_step = enemies_step;
  cycles->hero_step = hero_step;
}
//===================================================================


bool CyclesIsTimeUpDart(GameCycles *cycles)
{
  const uint16_t diff = cycles->actual - cycles->dart;

  if(diff >= cycles->dart_step)
  {
    cycles->dart = cycles->actual;
    return true;
  }
  return false;
}
//===================================================================


bool CyclesIsTimeUpEnemies(GameCycles *cycles)
{
  const uint16_t diff = cycles->actual - cycles->enemies;

  if(diff >= cycles->enemies_step)
  {
    cycles->enemies = cycles->actual;
    return true;
  }

  return false;
}
//===================================================================


bool CyclesIsTimeUpHero(GameCycles *cycles)
{
  const uint16_t diff = cycles->actual - cycles->hero;

  if(diff >= cycles->hero_step)
  {
    cycles->hero = cycles->actual;
    return true;
  }

  return false;
}
//===================================================================


void CyclesWait(GameCycles *cycles)
{
  ms_sleep(1);

  cycles->actual++;

  if(cycles->actual == 65535)
  {
    uint16_t diff_max;
    uint16_t diff_actual_dart = cycles->actual - cycles->dart;
    uint16_t diff_actual_enemies = cycles->actual - cycles->enemies;

    if(diff_actual_dart > diff_actual_enemies)
      diff_max = diff_actual_dart;
    else
      diff_max = diff_actual_enemies;

    uint16_t diff_actual_hero = cycles->actual - cycles->hero;

    if(diff_actual_hero > diff_max)
      diff_max = diff_actual_hero;

    cycles->actual = diff_max;
    cycles->dart = diff_max - diff_actual_dart;
    cycles->enemies = diff_max - diff_actual_enemies;
    cycles->hero = diff_max - diff_actual_hero;
  }
}
//===================================================================


void DestroyCycles(GameCycles *cycles)
{
  free(cycles);
}
//===================================================================


GameCycles *NewCycles()
{
  GameCycles *cycles = malloc(sizeof(GameCycles));

  cycles->actual = 0;
  cycles->dart = 0;
  cycles->enemies = 0;
  cycles->hero = 0;

  cycles->dart_step = 2;
  cycles->enemies_step = 32;
  cycles->hero_step = 4;

  return cycles;
}
//===================================================================

static int ms_sleep(unsigned int ms)
{
  int result = 0;

  {
    struct timespec ts_remaining =
    {
      ms / 1000,
      (ms % 1000) * 1000000L
    };

    do
    {
      struct timespec ts_sleep = ts_remaining;
      result = nanosleep(&ts_sleep, &ts_remaining);
    }
    while (EINTR == result);
  }

  if (result)
  {
    perror("nanosleep() failed");
    result = -1;
  }

  return result;
}
