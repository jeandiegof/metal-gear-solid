#include <math.h>

#include "inc/debug.h"
#include "inc/transformation.h"

//void RotateSight(const int16_t angle, Sight *sight)
//{
//	uint8_t repeats;

//  repeats = angle / ANGLE_45;

//	for(uint8_t j = 0; j < repeats; j++)
//	{
//		for(uint8_t i = 0; i < sight->lenght; i++)
//		{
//      Rotate45(i+1,
//           &(sight->bound1.points[i]),
//           &(sight->bound1.angle));

//      Rotate45(i+1,
//           &(sight->bound2.points[i]),
//           &(sight->bound2.angle));
//		}

//    sight->angle += ANGLE_45;
//    sight->bound1.angle += ANGLE_45;
//    sight->bound2.angle += ANGLE_45;


//    if(sight->angle > ANGLE_315)
//      sight->angle = ANGLE_0;

//    if(sight->bound1.angle > ANGLE_315)
//      sight->bound1.angle = ANGLE_0;

//    if(sight->bound2.angle > ANGLE_315)
//      sight->bound2.angle = ANGLE_0;
//	}

//  SetBoundryOffset(sight);
//}
//===================================================================


void Rotate45(const Point center_point, Line *line)
{
//  DebugLine(line);
  Point *line_point;

  int16_t magnitude;

  for(uint16_t i = 0; i < line->lenght; i++)
  {
    line_point = LineGetPointRef(i, line);
    switch(line->angle)
    {
      case ANGLE_0:
      case ANGLE_315:
        magnitude = abs( line_point->x - center_point.x );
        TranslateN(magnitude, line_point);
        LineInsertPoint( i, line_point, line );
        break;

      case ANGLE_45:
      case ANGLE_90:
        magnitude = abs( line_point->y - center_point.y );
        TranslateW(magnitude, line_point);
        LineInsertPoint( i, line_point , line );
        break;

      case ANGLE_135:
      case ANGLE_180:
        magnitude = abs( line_point->x - center_point.x );
        TranslateS(magnitude, line_point);
        LineInsertPoint( i, line_point, line );
        break;

      case ANGLE_225:
      case ANGLE_270:
        magnitude = abs( line_point->y - center_point.y );
        TranslateE(magnitude, line_point);
        LineInsertPoint( i, line_point, line );
        break;
    }
  }
  line->angle += ANGLE_45;
//  DebugLine(line);
}
//===================================================================


void TranslateE(const int16_t scalar, Point *point)
{
  point->x = point->x + scalar;
}
//===================================================================


void TranslateN(const int16_t scalar, Point *point)
{
  point->y = point->y - scalar;
}
//===================================================================


void TranslateS(const int16_t scalar, Point *point)
{
  point->y = point->y + scalar;
}
//===================================================================


void TranslateW(const int16_t scalar, Point *point)
{
	point->x = point->x - scalar;
}
//===================================================================


void SetBoundryOffset(Sight *sight)
{
	// Make tweaks in x position, by changing offset value based on angle.
	switch(sight->angle)
	{
  case ANGLE_0:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = i;
			sight->bound2.offset[i].x = i;
		}
		break;

  case ANGLE_45:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound2.offset[i].x = i+1;
		}
		break;

  case ANGLE_90:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = -i;
			sight->bound2.offset[i].x =  i;
		}
		break;

  case ANGLE_135:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = -i-1;
		}
		break;

  case ANGLE_180:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = -i;
			sight->bound2.offset[i].x = -i;
		}
		break;

  case ANGLE_225:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound2.offset[i].x = -i-1;
		}
		break;

  case ANGLE_270:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x =  i;
			sight->bound2.offset[i].x = -i;
		}
		break;

  case ANGLE_315:
		for(uint8_t i=0; i < sight->lenght; i++)
		{
			sight->bound1.offset[i].x = i+1;
		}
		break;
	}
}
//===================================================================


