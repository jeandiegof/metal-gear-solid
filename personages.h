#ifndef STRUCTPERSONAGE_H
#define STRUCTPERSONAGE_H

#include <stdint.h>

#include "unicodes.h"
#include "enumAngles.h"

#define SIGHT_POINTS_MAX_SIZE 30
#define SIGHT_LENGHT_MAX_SIZE 10


// ---- START Abstract Structs.

/**
 * @brief Abstract struct for point x, y coordinate system.
*/
typedef struct saPoint
{
	int16_t x;
	int16_t y;

}saPoint;
//===================================================================


/**
 * @brief Abstract struct for personage creation.
 *
 * This is the base class for sHero, sEnemy and sHostage.
 *
 * It contains:
 *     Image displayed in console.
 *     Coordinates in x,y format.
*/
typedef struct saPersonageBase
{
	char img[U_LENGHT]; /**< 11 characters for unicode string. */

	struct saPoint point;

}saPersonageBase;
//===================================================================


typedef struct saBoundry
{
	char img[U_LENGHT];

	saPoint points[SIGHT_LENGHT_MAX_SIZE];

	struct saPoint offset[SIGHT_LENGHT_MAX_SIZE]; /**< Hack, magical numbers.*/

	enum eAngles angle;

}saBoundry;
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
typedef struct saSight
{
	enum eAngles angle;

	uint8_t lenght; /**< Triangle's height lenght. */

	struct saBoundry boundry1;
	struct saBoundry boundry2;
	struct saBoundry boundry3; /**< Its not displayed, just for colision algorithm.*/

}saSight;
//===================================================================


// ---- END Abstract Structs.




// ---- START Personage Structs.

typedef struct soHostage
{
	struct saPersonageBase base;

}soHostage;
//===================================================================


typedef struct soEnemy
{
	struct saPersonageBase base;

	struct saSight sight;

}soEnemy;
//===================================================================


typedef struct soHero
{
	struct saPersonageBase base;

	uint8_t speed; /**< Movement speed */

	uint8_t life; /**< Life counter. */

	uint8_t ammo; /**< Ammunition counter.*/

}soHero;
//===================================================================



// ------ START Functions


void initBase();

void initEnemy(soEnemy *enemy, uint8_t x, uint8_t y, uint8_t sightLenght);

void initHero();

void initSight(saSight *sight, uint8_t sightLenght);


// ------ END Functions



// ------ START Private Functions



// ------ END Private Functions







#endif // STRUCTPERSONAGE_H
