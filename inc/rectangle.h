#ifndef RECTANGLE_H
#define RECTANGLE_H

#define RECTANGLE_H

#include <stdint.h>

#include "inc/pointvector.h"
#include "inc/line.h"

typedef struct Rectangle
{
  Point corner_1;
  Point corner_2;

  Line *bottom_line;
  Line *right_line;
  Line *top_line;
  Line *left_line;

  int16_t width;
  int16_t height;

  struct
  {
    int16_t x;
    int16_t y;
  } max, min;

}Rectangle;

void DestroyRectangle(Rectangle *rectangle);

Rectangle *NewRectangle();

void RectangleCreate(const Point *corner_1,
                     const Point *corner_2,
                     Rectangle *rectangle);


#endif // RECTANGLE_H
