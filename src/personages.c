/*
 * TODO: Recognize all points inside sight area.
 * Store those points for some erase function erase those points before
 * plotting them in new position.
 *
 * TODO: Enemy detection logic.
 * Implement a function to detec if a point is inside sight's area or in
 * the same spot as the enemy. The return should be a boolean type.
*/

#include "inc/personages.h"
#include <string.h>

void InitEnemy(const uint8_t x,
               const uint8_t y,
               const uint8_t sight_lenght,
               Enemy *enemy)
{
	// Init enemy position.
  enemy->icon.point.x = x;
  enemy->icon.point.y = y;

	// Init enemy image;
  strcpy(enemy->icon.img, U_ENEMY);

	// Validates Sight lenght. Should be at least 1.
  if(sight_lenght < 1)
		enemy->sight.lenght = 1;
	else
    enemy->sight.lenght = sight_lenght;

  enemy->sight.angle = ANGLE_0;

	// Set each boundry's angle to +- 45° from main angle, 0° in this case.
  enemy->sight.bound1.angle = ANGLE_45;
  enemy->sight.bound2.angle = ANGLE_315;
	//
  enemy->sight.bound3.angle = ANGLE_90;

	// Init boundries offset with 0.
	for(uint8_t i = 0; i < SIGHT_LENGHT_MAX_SIZE; i++)
	{
    enemy->sight.bound1.offset[i].x = 0;
    enemy->sight.bound1.offset[i].y = 0;
    enemy->sight.bound2.offset[i].x = 0;
    enemy->sight.bound2.offset[i].y = 0;
	}

	// Create sight boundries for an angle of 0 degrees.
	for(uint8_t i = 1; i <= enemy->sight.lenght; i++)
	{
    enemy->sight.bound1.points[i-1].x = enemy->icon.point.x + i;
    enemy->sight.bound1.points[i-1].y = enemy->icon.point.y - i;

    enemy->sight.bound2.points[i-1].x = enemy->icon.point.x + i;
    enemy->sight.bound2.points[i-1].y = enemy->icon.point.y + i;
	}


	// TODO: Create sight boundry 3 for an angle of 0°.
//	for(uint8_t i = 0; i <= enemy; i++)
//	{
//		enemy->sight.boundry3.
//	}

  strcpy(enemy->sight.bound1.img, U_DOTLINE_NE);
  strcpy(enemy->sight.bound2.img, U_DOTLINE_NW);
}

