// vector.c

#include "inc/vector_point.h"

#define VECTOR_POINT_MAX_INIT_VALUE -32768
#define VECTOR_POINT_MIN_INIT_VALUE  32767



/**
 * @brief VectorPointInitMaxMinPoints
 * @param vector
 */
static void VectorPointInitMaxMinPoints(VectorPoint *vector);
//===================================================================


/**
 * @brief Increase the underlying data array capacity
 * if @p vector->size >= @p vector->capacity.
 *
 * This function expand data array capacity by allocating a number of slots
 * equal to VECTOR_POINT_DEFAULT_CAPACITY.
 *
 * @code
 *  vector->capacity += VECTOR_POINT_DEFAULT_CAPACITY;
    vector->data = realloc(vector->data, sizeof(Point) * vector->capacity);
 * @endcode
 *
 * @param vector[out]
 */
static void VectorPointResizeIfFull(VectorPoint *vector);
//===================================================================


/**
 * @brief Finds if a specific point has values greater or smaller than
 * the maximuns and minimuns stored in a VectorPoint struct.
 *
 * @param point
 * @param vector
 */
static void VectorPointUpdateMaxMinPoints(const Point *point,
                                          VectorPoint *vector);
//===================================================================






void VectorPointAppend(const Point *value, VectorPoint *vector)
{
  // make sure there's room to expand into
  VectorPointResizeIfFull(vector);

  // append the value and increment vector->size
  vector->data[vector->length++] = *value;

  VectorPointUpdateMaxMinPoints(value, vector);
}
//===================================================================


void DestroyVectorPoint(VectorPoint *vector)
{
  free(vector->data);
}
//===================================================================


VectorPoint *NewVectorPoint()
{
  // Create VectorPoint.
  VectorPoint *vector = malloc(sizeof(VectorPoint));

  // Initialize size and capacity
  vector->length = 0;
  vector->capacity = VECTOR_POINT_DEFAULT_CAPACITY;

  // Allocate memory for vector->data
  vector->data = malloc(sizeof(Point) * vector->capacity);

  VectorPointInitMaxMinPoints(vector);

  return vector;
}
//===================================================================


void VectorPointInsert(const uint16_t index,
                       const Point *value,
                       VectorPoint *vector)
{
  Point zero_point = {0};

  // Zero fill *vector until desired index.
  while (index >= vector->length)
  {
    VectorPointAppend(&zero_point, vector);
  }

  // Insert value at the desired index.
  vector->data[index] = *value;

  // Need to go through all the points to update maximum and minimun values.
  Point *aux_point;

  for(uint16_t i = 0; i < vector->length; i++)
  {
    aux_point = VectorPointValueRef(i, vector);

    VectorPointUpdateMaxMinPoints(aux_point, vector);
  }
}
//===================================================================


uint16_t VectorPointGetSize(const VectorPoint *vector)
{
  return vector->length;
}
//===================================================================


Point VectorPointGetValue(const int index, const VectorPoint *vector)
{
  if (index >= vector->length || index < 0)
  {
    printf("Index %d out of bounds for vector of size %d\n",
         index, vector->length);
    exit(1);
  }
  return vector->data[index];
}
//===================================================================


Point *VectorPointValueRef(const int index, const VectorPoint *vector)
{
  if (index >= vector->length || index < 0)
  {
    printf("Index %d out of bounds for vector of size %d\n",
         index, vector->length);
    exit(1);
  }
  return vector->data+index;
}
//===================================================================


void VectorPointRemoveLastPoint(VectorPoint *vector)
{
  if( vector->length <= 0 )
    return;

  // Direct access of VectorPoint member variable, in this case is safe.
  vector->length--;

  // Need to go through all the points to update maximum and minimun values.
  Point *aux_point;

  for(uint16_t i = 0; i < vector->length; i++)
  {
    aux_point = VectorPointValueRef(i, vector);

    VectorPointUpdateMaxMinPoints(aux_point, vector);
  }
}
//===================================================================


void VectorPointReset(VectorPoint *vector)
{
  vector->length = 0;

  VectorPointInitMaxMinPoints(vector);
}
//===================================================================






// ---- START Private Functions.

static void VectorPointInitMaxMinPoints(VectorPoint *vector)
{
  vector->max.x = VECTOR_POINT_MAX_INIT_VALUE;
  vector->max.y = VECTOR_POINT_MAX_INIT_VALUE;

  vector->min.x = VECTOR_POINT_MIN_INIT_VALUE;
  vector->min.y = VECTOR_POINT_MIN_INIT_VALUE;
}
//===================================================================


static void VectorPointResizeIfFull(VectorPoint *vector)
{
  if (vector->length >= vector->capacity)
  {
    vector->capacity += VECTOR_POINT_DEFAULT_CAPACITY;
    vector->data = realloc(vector->data, sizeof(Point) * vector->capacity);
  }
}
//===================================================================


static void VectorPointUpdateMaxMinPoints(const Point *point,
                                          VectorPoint *vector)
{
  if(point->x > vector->max.x)
  {
    vector->max.x = point->x;
  }
  else if(point->x < vector->min.x)
  {
    vector->min.x = point->x;
  }

  if(point->y > vector->max.y)
  {
    vector->max.y = point->y;
  }
  else if(point->y < vector->min.y)
  {
    vector->min.y = point->y;
  }
}
//===================================================================

// ---- END Private Functions.
