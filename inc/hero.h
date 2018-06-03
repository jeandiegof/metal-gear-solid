#ifndef HERO_H
#define HERO_H

#include <stdint.h>

#include "personage_base.h"

typedef struct Hero
{
  struct PersonageBase base;

  uint8_t speed; /**< Movement speed */

  uint8_t life; /**< Life counter. */

  uint8_t ammo; /**< Ammunition counter.*/

}Hero;
//===================================================================

#endif // HERO_H
