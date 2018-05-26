#ifndef DRAWING_H
#define DRAWING_H

#include <ncursesw/ncurses.h>
#include <string.h>

#include "inc/line.h"
#include "inc/rectangle.h"
#include "inc/personages.h"
#include "inc/transformation.h"

// ---- START Drawing Functions.


void ShowLine(const Line *line, const char img[]);

void ShowRectangle(const Rectangle *rectangle, const char img[]);

/**
 *
 */
void ShowEnemy(Enemy *enemy);
//===================================================================


/**
 *
 */
void ShowPersonage(PersonageBase *personage);
//===================================================================


/**
 *
 */
void ShowEnemySight(Sight *sight);
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

void UpdateDotLineSightImg(Sight *sight);
//===================================================================

// ---- ENDPrivate Function.

#endif // DRAWING_H
