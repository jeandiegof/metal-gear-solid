// vector.c

#include "inc/pointvector.h"

#define VECTORINT_DEFAULT_CAPACITY 5

void VectorPointAppend(const Point value, VectorPoint *vector)
{
  // make sure there's room to expand into
  VectorPointResizeIfFull(vector);

  // append the value and increment vector->size
  vector->data[vector->size++] = value;
}


void VectorPointFree(VectorPoint *vector)
{
  free(vector->data);
}


void VectorPointInit(VectorPoint *vector)
{
  // initialize size and capacity
  vector->size = 0;
  vector->capacity = VECTORINT_DEFAULT_CAPACITY;

  // allocate memory for vector->data
  vector->data = malloc(sizeof(Point) * vector->capacity);
}


void VectorPointInsert(const uint16_t index, const Point point, VectorPoint *vector)
{
  Point zero_point = {0};
  // Zero fill *vector until desired index.
  while (index >= vector->size)
  {
    VectorPointAppend(zero_point, vector);
  }

  // Insert value at the desired index.
  vector->data[index] = point;
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


// ---- START Private Functions.

void VectorPointResizeIfFull(VectorPoint *vector)
{
  if (vector->size >= vector->capacity)
  {
    // Double vector->capacity and resize the allocated memory
    // accordingly.
    vector->capacity += VECTORINT_DEFAULT_CAPACITY;
    vector->data = realloc(vector->data, sizeof(Point) * vector->capacity);
  }
}

// ---- END Private Functions.

