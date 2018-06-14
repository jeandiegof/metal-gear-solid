/**
 * @file rectangle.h
 * @author Carlo Fornari and Jean Fontena
 * @date 21 may 2018
 *
 * @brief Code to define a Line object for terminal application enviorment.
 *
 * This file has a struct and functions to help a client to implement a
 * Rectangle object in a terminal.
 *
 * The functions in this file don't perform any sort of graphical operation.
 * They only manipulate the mathematical representation in an integer cartesian
 * coordinate system, i.e., xy coordinates in terminal.
 *
 * Rectangle is allocated on the heap. The task to free the memory is left to
 * the client. The memory is freed by calling DestroyRectangle().
 *
 * The code below provides a simple application to print a rectangle in the
 * terminal using "inc/display.h":
 * @code
 *  #include "inc/rectangle.h"
 *  #include "inc/display.h"
 *
 *  int main()
 *  {
 *    Rectangle *rec = NewRectangle();
 *
 *    Point corner_1 = {4,4};
 *    Point corner_2 = {8,8};
 *
 *    RectangleCreate(&corner_1, &corner_2, rec);
 *
 *    ShowRectangle(rec, "#");
 *
 *    DestroyRectangle(rec);
 *  }
 * @endcode
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#define RECTANGLE_H

#include <stdint.h>

#include "inc/vector_point.h"
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

  Point max;
  Point min;

}Rectangle;


/**
 * @brief Free the memory used by Rectangle
 * @param rectangle[out]
 */
void DestroyRectangle(Rectangle *rectangle);

/**
 * @brief Creates a Rectangle object.
 *
 * Creates a Rectangle object using malloc().
 *
 * @return A pointer to a Rectangle struct.
 */
Rectangle *NewRectangle();

/**
 * @brief Creates 4 Line objects in a rectangular shape.
 *
 * This function takes two oposed corners and creates a rectangle limited
 * by those coordinates.
 * If the input corners lie in the same horizontal or vertical line, the
 * code will finish the application, because the input points can't create a
 * rectangle.
 *
 * @param corner_1[in]
 * @param corner_2[in]
 * @param rectangle[out]
 *
 * @todo Handle a situation where a rectangle with pre-existing lines is a
 * parameter. Now, the function expects an empty *rectangle. Unexpected
 * behavior can occur if a rectangle non-empty is used.
 */
void RectangleCreate(const Point *corner_1,
                     const Point *corner_2,
                     Rectangle *rectangle);


#endif // RECTANGLE_H
