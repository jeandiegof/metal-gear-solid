#ifndef HERO_H
#define HERO_H

#include <stdint.h>

#include "inc/personage_base.h"
#include "inc/game_enums.h"
#include "inc/manager_map.h"
#include "inc/game_enums.h"
#include "inc/point.h"

typedef struct Hero
{
  PersonageBase base;
  uint8_t speed; /**< Movement speed */
  uint8_t life; /**< Life counter. */
  uint8_t ammo; /**< Ammunition counter.*/
  uint8_t hostages;
  uint8_t key;
  uint16_t score;
  Direction last_direction;
} Hero;
//===================================================================

Hero *NewHero(uint8_t life, uint8_t ammo, Point *origin);
//===================================================================

void DestroyHero(Hero *hero);
//===================================================================

GameScreen HeroDetectedSignal(Map *map, Hero *hero);
//===================================================================

void HeroReset(Hero *hero, Point *origin);
//===================================================================

GameScreen HeroMove(Map *map, Hero *hero, Direction direction);
//===================================================================

GameScreen HeroManager(const char option, Map *map, Hero *hero);
//===================================================================

#endif // HERO_H
