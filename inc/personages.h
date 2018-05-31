#ifndef STRUCTPERSONAGE_H
#define STRUCTPERSONAGE_H

#include <stdint.h>

#include "inc/unicodes.h"
#include "inc/angles.h"
#include "inc/line.h"
#include "inc/rectangle.h"

// ---- START Abstract Structs.

/**
 * @brief Abstract struct for personage creation.
 *
 * This is the base struct for Hero, Enemy and Hostage.
 *
 * It contains:
 *     Image displayed in console.
 *     Coordinates in x,y format.
 */
typedef struct PersonageBase
{
  /** @brief 11 characters for unicode string. */
  char img[U_LENGHT];

  struct Point point;

}PersonageBase;
//===================================================================

typedef struct SightBoundry
{
  char img[U_LENGHT];

  uint8_t lenght;

  int16_t angle;

  Line *directional_line;

  Line *offset_line;

  Line *limit;

}SightBoundry;
//===================================================================

/**
 * @brief Abstract struct. Gives sight to the object.
 *
 *
 * Sight is a triangle which origin's at personage position.
 * The orientation is related to personage's angle, the height of this
 * triangle has its size determined by #lenght.
 *
 */
typedef struct Sight
{
  int16_t angle;

  /** Triangle's height lenght. */
  uint8_t lenght;

  struct SightBoundry *bound1;

  struct SightBoundry *bound2;

  /** Its not displayed, just for colision algorithm. */
  struct Line bound3;

}Sight;
//===================================================================

// ---- END Abstract Structs.





// ---- START Personage's Structs.

typedef struct Hostage
{
  struct PersonageBase icon;

}Hostage;
//===================================================================

typedef struct Enemy
{
  /** Image and its position at the terminal.*/
  struct PersonageBase icon;

  struct Sight *sight;

  /** @brief A box around the enemy used for detection algorith and limits
   *  for translation.
   */
  struct Rectangle box;

}Enemy;
//===================================================================


typedef struct Hero
{
  struct PersonageBase base;

	uint8_t speed; /**< Movement speed */

	uint8_t life; /**< Life counter. */

	uint8_t ammo; /**< Ammunition counter.*/

}Hero;
//===================================================================

// ---- END Personage's Structs.





// ------ START Functions

void InitBase();

Enemy *NewEnemy(const Point *origin, const uint8_t sight_lenght);

void DestroyEnemy(Enemy *enemy);

void InitHero();

void InitSight(Sight *sight, uint8_t sightLenght);

// ------ END Functions





// ------ START Private Functions


// ------ END Private Functions

#endif // STRUCTPERSONAGE_H
