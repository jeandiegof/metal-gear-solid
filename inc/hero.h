#ifndef HERO_H
#define HERO_H

#include <stdint.h>
#include "inc/personage_base.h"
#include "inc/map_manager.h"
#include "inc/game_base.h"

typedef struct Hero
{
  struct PersonageBase base;
  uint8_t speed; /**< Movement speed */
  uint8_t life; /**< Life counter. */
  uint8_t ammo; /**< Ammunition counter.*/
  uint8_t hostages;
  uint8_t key;
}Hero;
//===================================================================

void MoveHero(Map *map, Hero *hero, Direction direction);

#endif // HERO_H
