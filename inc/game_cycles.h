#ifndef GAME_CYCLES_H
#define GAME_CYCLES_H

#include <stdint.h>
#include <stdbool.h>

typedef struct GameCycles
{
  uint16_t actual;

  uint16_t dart;
  uint16_t dart_step;

  uint16_t enemies;
  uint16_t enemies_step;

  uint16_t hero;
  uint16_t hero_step;

}GameCycles;


void CyclesInit(const uint16_t dart_step,
                const uint16_t enemies_step,
                const uint16_t hero_step,
                GameCycles *cycles);
//===================================================================

bool CyclesIsTimeUpDart(GameCycles *cycles);
//===================================================================

bool CyclesIsTimeUpEnemies(GameCycles *cycles);
//===================================================================

bool CyclesIsTimeUpHero(GameCycles *cycles);
//===================================================================

void CyclesWait(GameCycles *cycles);
//===================================================================

void DestroyCycles(GameCycles *cycles);
//===================================================================

GameCycles *NewCycles();
//===================================================================



#endif // GAME_CYCLES_H
