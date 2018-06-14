#include <ncursesw/ncurses.h>
#include <math.h>

#include "inc/rectangle.h"

#define REC_POINT_MAX_INIT_VALUE -32768
#define REC_POINT_MIN_INIT_VALUE  32767

static void RectangleInitMaxMinPoints(Rectangle *rectangle);
//===================================================================

static void RectangleUpdateMaxMinPoints(const Line *line,
                                        Rectangle *rectangle);
//===================================================================

static void ValidateCornersInput(const Point *corner_1,
                                 const Point *corner_2,
                                 Rectangle *rectangle);
//===================================================================


void DestroyRectangle(Rectangle *rectangle)
{
  DestroyLine(rectangle->bottom_line);
  DestroyLine(rectangle->right_line);
  DestroyLine(rectangle->top_line);
  DestroyLine(rectangle->left_line);
  free(rectangle);
}
//===================================================================


Rectangle *NewRectangle()
{
  Rectangle *rectangle = malloc(sizeof(Rectangle));

  rectangle->corner_1.x = 0;
  rectangle->corner_1.y = 0;
  rectangle->corner_2.x = 0;
  rectangle->corner_2.y = 0;

  RectangleInitMaxMinPoints(rectangle);

  rectangle->width = 0;
  rectangle->height = 0;

  rectangle->bottom_line = NewLine();
  rectangle->right_line = NewLine();
  rectangle->top_line = NewLine();
  rectangle->left_line = NewLine();

  return rectangle;
}
//===================================================================


void RectangleCreate(const Point *corner_1,
                     const Point *corner_2,
                     Rectangle *rectangle)
{
  rectangle->width  = abs ( corner_2->x - corner_1->x ) + 1;
  rectangle->height = abs ( corner_2->y - corner_1->y ) + 1;

  ValidateCornersInput(corner_1, corner_2, rectangle);

  // Bottom line.
  LineCreate(&(rectangle->corner_1),
             ANGLE_0,
             rectangle->width,
             rectangle->bottom_line);

  RectangleUpdateMaxMinPoints(rectangle->bottom_line, rectangle);

  // Right line.
  LineCreate(&(rectangle->corner_2),
             ANGLE_270,
             rectangle->height,
             rectangle->right_line);

  RectangleUpdateMaxMinPoints(rectangle->right_line, rectangle);

  // Top Line.
  LineCreate(&(rectangle->corner_2),
             ANGLE_180,
             rectangle->width,
             rectangle->top_line);

  RectangleUpdateMaxMinPoints(rectangle->top_line, rectangle);

  // Left Line.
  LineCreate(&(rectangle->corner_1),
             ANGLE_90,
             rectangle->height,
             rectangle->left_line);

  RectangleUpdateMaxMinPoints(rectangle->left_line, rectangle);
}
//===================================================================


static void RectangleInitMaxMinPoints(Rectangle *rectangle)
{
  rectangle->max.x = REC_POINT_MAX_INIT_VALUE;
  rectangle->max.y = REC_POINT_MAX_INIT_VALUE;

  rectangle->min.x = REC_POINT_MIN_INIT_VALUE;
  rectangle->min.y = REC_POINT_MIN_INIT_VALUE;
}
//===================================================================


/**
 * @brief Finds if a specific point has values greater or smaller than
 * the maximuns and minimuns stored in a Rectangle struct.
 *
 * @param point[in]
 * @param rectangle[out]
 */

static void RectangleUpdateMaxMinPoints(const Line *line,
                                        Rectangle *rectangle)
{
  if(line->max.x > rectangle->max.x)

    rectangle->max.x = line->max.x;

  else if(line->min.x < rectangle->min.x)

    rectangle->min.x = line->min.x;

  if(line->max.y > rectangle->max.y)

    rectangle->max.y = line->max.y;

  else if(line->min.y < rectangle->min.y)

    rectangle->min.y = line->min.y;
}
//===================================================================


static void ValidateCornersInput(const Point *corner_1,
                                 const Point *corner_2,
                                 Rectangle *rectangle)
{
  // Is a rectangle?
  if(corner_1->x == corner_2->x ||
     corner_1->y == corner_2->y)
  {

    printf("\n\nYou are trying to create some rectangle with invalid parameters.");
    printf("\n\n\n");
    exit(1);
  }

  // IF the corners do make a rectangle THEN:
  // Organize the points, so the rectangle->corner_1 will be in the bottom-left,
  // and the rectangle->corner_2 in the top-right.

  /* Situation where:
   *                 o  x2, y2
   *    x1, y1  o
   */
  if(corner_2->x > corner_1->x && corner_2->y < corner_1->y)
  {
    rectangle->corner_1 = *corner_1;
    rectangle->corner_2 = *corner_2;
  }
  /* Situation where:
   *    x2, y2  o
   *                 o  x1, y1
   */
  else if(corner_2->x < corner_1->x && corner_2->y < corner_1->y)
  {
    rectangle->corner_1.x = corner_2->x;
    rectangle->corner_1.y = corner_1->y;

    rectangle->corner_2.x = corner_1->x;
    rectangle->corner_2.y = corner_2->y;
  }
  /* Situation where:
   *                 o  x1, y1
   *    x2, y2  o
   */
  else if(corner_2->x < corner_1->x && corner_2->y > corner_1->y)
  {
    rectangle->corner_1 = *corner_2;
    rectangle->corner_2 = *corner_1;
  }
  /* Situation where:
   *    x1, y1  o
   *                 o  x2, y2
   */
  else if(corner_2->x > corner_1->x && corner_2->y > corner_1->y)
  {
    rectangle->corner_1.x = corner_1->x;
    rectangle->corner_1.y = corner_2->y;

    rectangle->corner_2.x = corner_2->x;
    rectangle->corner_2.y = corner_1->y;
  }
}
