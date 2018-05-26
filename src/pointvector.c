// vector.c

#include "inc/pointvector.h"

static void VectorPointResizeIfFull(VectorPoint *vector);


void VectorPointAppend(const Point *value, VectorPoint *vector)
{
  // make sure there's room to expand into
  VectorPointResizeIfFull(vector);

  // append the value and increment vector->size
  vector->data[vector->size++] = *value;
}


void DestroyVectorPoint(VectorPoint *vector)
{
  free(vector->data);
}


VectorPoint *NewVectorPoint()
{
  // Create VectorPoint.
  VectorPoint *vector = malloc(sizeof(VectorPoint));

  // Initialize size and capacity
  vector->size = 0;
  vector->capacity = VECTOR_POINT_DEFAULT_CAPACITY;

  // Allocate memory for vector->data
  vector->data = malloc(sizeof(Point) * vector->capacity);

  return vector;
}


void VectorPointInsert(const uint16_t index,
                       const Point *value,
                       VectorPoint *vector)
{

  Point zero_point = {0};

  // Zero fill *vector until desired index.
  while (index >= vector->size)
  {
    VectorPointAppend(&zero_point, vector);
  }

  // Insert value at the desired index.
  vector->data[index] = *value;
}


uint16_t VectorPointSize(const VectorPoint *vector)
{
  return vector->size;
}


Point VectorPointValue(const int index, const VectorPoint *vector)
{
  if (index >= vector->size || index < 0)
  {
    printf("Index %d out of bounds for vector of size %d\n",
         index, vector->size);
    exit(1);
  }
  return vector->data[index];
}


Point *VectorPointValueRef(const int index, const VectorPoint *vector)
{
  if (index >= vector->size || index < 0)
  {
    printf("Index %d out of bounds for vector of size %d\n",
         index, vector->size);
    exit(1);
  }
  return vector->data+index;
}





// ---- START Private Functions.

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

static void VectorPointResizeIfFull(VectorPoint *vector)
{
  if (vector->size >= vector->capacity)
  {
    vector->capacity += VECTOR_POINT_DEFAULT_CAPACITY;
    vector->data = realloc(vector->data, sizeof(Point) * vector->capacity);
  }
}

// ---- END Private Functions.



