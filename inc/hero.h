#ifndef HERO_H
#define HERO_H

#include <stdint.h>
#include "inc/personage_base.h"
#include "inc/map_manager.h"
#include "inc/game_base.h"
#include "inc/point.h"

typedef struct Hero
{
  struct PersonageBase base;
  uint8_t speed; /**< Movement speed */
  uint8_t life; /**< Life counter. */
  uint8_t ammo; /**< Ammunition counter.*/
  uint8_t hostages;
  uint8_t key;
  uint16_t score;
} Hero;

Hero NewHero(uint8_t life, uint8_t ammo, Point *origin);
Screen MoveHero(Map *map, Hero *hero, Direction direction);
Screen HeroManager(Map *map, Hero *hero);

#endif // HERO_H
