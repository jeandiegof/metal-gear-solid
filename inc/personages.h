#ifndef STRUCTPERSONAGE_H
#define STRUCTPERSONAGE_H

#include <stdint.h>

#include "inc/unicodes.h"
#include "inc/angles.h"
#include "inc/geometry.h"

#define SIGHT_LENGHT_MAX_SIZE 5


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

typedef struct Boundry
{
	char img[U_LENGHT];

  Point points[SIGHT_LENGHT_MAX_SIZE];

  struct Point offset[SIGHT_LENGHT_MAX_SIZE]; /**< Hack, magical numbers.*/

  int16_t angle;

}Boundry;
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

  struct Boundry bound1;

  struct Boundry bound2;

  /** Its not displayed, just for colision algorithm. */
  struct Boundry bound3;

}Sight;
//===================================================================

// ---- END Abstract Structs.





// ---- START Personage's Structs.

typedef struct Hostage
{
  struct PersonageBase base;

}Hostage;
//===================================================================

typedef struct Enemy
{
  struct PersonageBase base;

  struct Sight sight;

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

/**
 * @brief
 * @param[in]  x
 * @param[in]  y
 * @param[in]  sight_lenght
 * @param[out] enemy
 */
void InitEnemy(const uint8_t x,
               const uint8_t y,
               const uint8_t sight_lenght,
               Enemy *enemy);

void InitHero();

void InitSight(Sight *sight, uint8_t sightLenght);

// ------ END Functions





// ------ START Private Functions


// ------ END Private Functions







#endif // STRUCTPERSONAGE_H
