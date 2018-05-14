#ifndef DRAWING_H
#define DRAWING_H

#include <ncursesw/ncurses.h>
#include <string.h>

#include "personages.h"
#include "transformation.h"

// ---- START Drawing Functions.

/**
 *
 */
void drawEnemy(soEnemy *enemy);
//===================================================================


/**
 *
 */
void drawPersonage(saPersonageBase *personage);
//===================================================================


/**
 *
 */
void drawEnemySight(saSight *sight);
//===================================================================

// ---- END Drawing Functions.







// ---- START Private Function.

/**
 * @brief Changes the unicode symbol for sight boundries after rotation.
 *
 * This function should be called after the sight is rotated, it updates
 * boundries's unicode symbol to be displayed according to the
 * shight's orientation.
 *
 * @param sight Pointer to some sight struct.
 */

void updateDotLineSightImg(saSight *sight);
//===================================================================

// ---- ENDPrivate Function.

#endif // DRAWING_H
