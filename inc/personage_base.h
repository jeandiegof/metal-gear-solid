#ifndef PERSONAGEBASE_H
#define PERSONAGEBASE_H

#include "point.h"
#include "inc/unicodes.h"

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

#endif // PERSONAGEBASE_H
