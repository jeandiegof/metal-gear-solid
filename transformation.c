#include "transformation.h"

#include "debug.h"


void rotateSight(saSight *sight, enum eAngles inputAngle)
{
	uint8_t repeats;

	repeats = inputAngle / angle45;

	for(uint8_t j = 0; j < repeats; j++)
	{
		for(uint8_t i = 0; i < sight->lenght; i++)
		{
			rotate45(&(sight->boundry1.points[i]),
					 &(sight->boundry1.angle),
					 i+1);

			rotate45(&(sight->boundry2.points[i]),
					 &(sight->boundry2.angle),
					 i+1);
		}

		sight->angle += angle45;
		sight->boundry1.angle += angle45;
		sight->boundry2.angle += angle45;


		if(sight->angle > angle315)
			sight->angle = angle0;

		if(sight->boundry1.angle > angle315)
			sight->boundry1.angle = angle0;

		if(sight->boundry2.angle > angle315)
			sight->boundry2.angle = angle0;
	}

	setBoundryOffset(sight);
}
//===================================================================


void rotate45(saPoint *point, enum eAngles *angle, uint8_t scalar)
{
	switch(*angle)
	{
	case angle0:
		translateN(point, scalar);
		break;

	case angle45:
	case angle90:
		translateW(point, scalar);
		break;

	case angle135:
	case angle180:
		translateS(point, scalar);
		break;

	case angle225:
	case angle270:
		translateE(point, scalar);
		break;

	case angle315:
		translateN(point, scalar);
		break;

	default:
		printw("\n\nError in transformation.c -> rotate45() -> switch()\n\n");
		while (1);
	}
}
//===================================================================


void translateE(saPoint *point, const uint8_t scalar)
{
	point->x = point->x + scalar;
}
//===================================================================


void translateN(saPoint *point, const uint8_t scalar)
{
	point->y = point->y - scalar;
}
//===================================================================


void translateS(saPoint *point, const uint8_t scalar)
{
	point->y = point->y + scalar;
}
//===================================================================


void translateW(saPoint *point, const uint8_t scalar)
{
	point->x = point->x - scalar;
}
//===================================================================


void setBoundryOffset(saSight *sight)
{
	// Make tweaks in x position, by changing offset value based on angle.
	switch(sight->angle)
	{
	case angle0:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry1.offset[i].x = i;
			sight->boundry2.offset[i].x = i;
		}
		break;

	case angle45:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry2.offset[i].x = i+1;
		}
		break;

	case angle90:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry1.offset[i].x = -i;
			sight->boundry2.offset[i].x =  i;
		}
		break;

	case angle135:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry1.offset[i].x = -i-1;
		}
		break;

	case angle180:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry1.offset[i].x = -i;
			sight->boundry2.offset[i].x = -i;
		}
		break;

	case angle225:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry2.offset[i].x = -i-1;
		}
		break;

	case angle270:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry1.offset[i].x =  i;
			sight->boundry2.offset[i].x = -i;
		}
		break;

	case angle315:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->boundry1.offset[i].x = i+1;
		}
		break;

	default:
		printw("\n\nError in transformation.c -> setBoundryOffset -> switch()\n\n");
		refresh();
		while (1);
		break;
	}
}
//===================================================================


