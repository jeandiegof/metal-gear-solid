/*
 * TODO: Recognize all points inside sight area.
 * Store those points for some erase function erase those points before
 * plotting them in new position.
 *
 * TODO: Enemy detection logic.
 * Implement a function to detec if a point is inside sight's area or in
 * the same spot as the enemy. The return should be a boolean type.
*/

#include "personages.h"
#include <string.h>

void initEnemy(soEnemy *enemy, uint8_t x, uint8_t y, uint8_t sightLenght)
{
	// Init enemy position.
	enemy->base.point.x = x;
	enemy->base.point.y = y;

	// Init enemy image;
	strcpy(enemy->base.img, U_ENEMY);

	// Validates Sight lenght. Should be at least 1.
	if(sightLenght < 1)
		enemy->sight.lenght = 1;
	else
		enemy->sight.lenght = sightLenght;

	enemy->sight.angle = angle0;

	// Set each boundry's angle to +- 45° from main angle, 0° in this case.
	enemy->sight.boundry1.angle = angle45;
	enemy->sight.boundry2.angle = angle315;
	//
	enemy->sight.boundry3.angle = angle90;

	// Init boundries offset with 0.
	for(uint8_t i = 0; i < SIGHT_LENGHT_MAX_SIZE; i++)
	{
		enemy->sight.boundry1.offset[i].x = 0;
		enemy->sight.boundry1.offset[i].y = 0;
		enemy->sight.boundry2.offset[i].x = 0;
		enemy->sight.boundry2.offset[i].y = 0;
	}

	// Create sight boundries for an angle of 0 degrees.
	for(uint8_t i = 1; i <= enemy->sight.lenght; i++)
	{
		enemy->sight.boundry1.points[i-1].x = enemy->base.point.x + i;
		enemy->sight.boundry1.points[i-1].y = enemy->base.point.y - i;

		enemy->sight.boundry2.points[i-1].x = enemy->base.point.x + i;
		enemy->sight.boundry2.points[i-1].y = enemy->base.point.y + i;
	}


	// TODO: Create sight boundry 3 for an angle of 0°.
//	for(uint8_t i = 0; i <= enemy; i++)
//	{
//		enemy->sight.boundry3.
//	}

	strcpy(enemy->sight.boundry1.img, U_DOTLINE_NE);
	strcpy(enemy->sight.boundry2.img, U_DOTLINE_NW);
}

