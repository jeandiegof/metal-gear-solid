#include "transformation.h"

#include "debug.h"


void RotateSight(const enum Angles angle, Sight *sight)
{
	uint8_t repeats;

	repeats = angle / kAngle45;

	for(uint8_t j = 0; j < repeats; j++)
	{
		for(uint8_t i = 0; i < sight->lenght; i++)
		{
			Rotate45(i+1,
					 &(sight->bound1.points[i]),
					 &(sight->bound1.angle));

			Rotate45(i+1,
					 &(sight->bound2.points[i]),
					 &(sight->bound2.angle));
		}

		sight->angle += kAngle45;
		sight->bound1.angle += kAngle45;
		sight->bound2.angle += kAngle45;


		if(sight->angle > kAngle315)
			sight->angle = kAngle0;

		if(sight->bound1.angle > kAngle315)
			sight->bound1.angle = kAngle0;

		if(sight->bound2.angle > kAngle315)
			sight->bound2.angle = kAngle0;
	}

	SetBoundryOffset(sight);
}
//===================================================================


void Rotate45(const uint8_t scalar, Point *point, enum Angles *angle)
{
	switch(*angle)
	{
	case kAngle0:
		TranslateN(point, scalar);
		break;

	case kAngle45:
	case kAngle90:
		TranslateW(point, scalar);
		break;

	case kAngle135:
	case kAngle180:
		TranslateS(point, scalar);
		break;

	case kAngle225:
	case kAngle270:
		TranslateE(point, scalar);
		break;

	case kAngle315:
		TranslateN(point, scalar);
		break;

	default:
		printw("\n\nError in transformation.c -> rotate45() -> switch()\n\n");
		while (1);
	}
}
//===================================================================


void TranslateE(Point *point, const uint8_t scalar)
{
	point->x = point->x + scalar;
}
//===================================================================


void TranslateN(Point *point, const uint8_t scalar)
{
	point->y = point->y - scalar;
}
//===================================================================


void TranslateS(Point *point, const uint8_t scalar)
{
	point->y = point->y + scalar;
}
//===================================================================


void TranslateW(Point *point, const uint8_t scalar)
{
	point->x = point->x - scalar;
}
//===================================================================


void SetBoundryOffset(Sight *sight)
{
	// Make tweaks in x position, by changing offset value based on angle.
	switch(sight->angle)
	{
	case kAngle0:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = i;
			sight->bound2.offset[i].x = i;
		}
		break;

	case kAngle45:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound2.offset[i].x = i+1;
		}
		break;

	case kAngle90:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = -i;
			sight->bound2.offset[i].x =  i;
		}
		break;

	case kAngle135:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = -i-1;
		}
		break;

	case kAngle180:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = -i;
			sight->bound2.offset[i].x = -i;
		}
		break;

	case kAngle225:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound2.offset[i].x = -i-1;
		}
		break;

	case kAngle270:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x =  i;
			sight->bound2.offset[i].x = -i;
		}
		break;

	case kAngle315:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = i+1;
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


