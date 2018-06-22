// vector.c

#include "inc/vector_line.h"

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
static void VectorLineResizeIfFull(VectorLine *vector);
//===================================================================


void VectorLineAppend(const Line *value, VectorLine *vector)
{
  // make sure there's room to expand into
  VectorLineResizeIfFull(vector);

  Line *new_line = NewLine();

  LineCopy(value, new_line);

  // append the value and increment vector->size
  vector->data[vector->length] = new_line;

  vector->length++;
}
//===================================================================

void VectorLineAppendVector(const VectorLine *input, VectorLine *output)
{
  for(uint16_t i = 0; i < input->length; i++)
  {
    VectorLineAppend(VectorLineGetLine(i, input), output);
  }
}
//===================================================================

void DestroyVectorLine(VectorLine *vector)
{
  for(uint16_t i = 0; i < vector->length; i++)
  {
    DestroyLine(vector->data[i]);
  }
  free(vector->data);
}
//===================================================================


VectorLine *NewVectorLine()
{
  // Create VectorLine.
  VectorLine *vector = malloc(sizeof(VectorLine));

  // Initialize size and capacity
  vector->length = 0;
  vector->capacity = VECTOR_LINE_DEFAULT_CAPACITY;

  // Allocate memory for vector->data
  vector->data = malloc(sizeof(Line) * vector->capacity);

  return vector;
}
//===================================================================


void VectorLineInsert(const uint16_t index,
                      const Line *value,
                      VectorLine *vector)
{
  Line *zero_line = NewLine();

  // Zero fill *vector until desired index.
  while (index >= vector->length)
  {
    VectorLineAppend(zero_line, vector);
  }

  DestroyLine(zero_line);

  Line *new_line = NewLine();

  LineCopy(value, new_line);

  // Insert value at the desired index.
  vector->data[index] = new_line;
}
//===================================================================


uint16_t VectorLineGetSize(const VectorLine *vector)
{
  return vector->length;
}
//===================================================================


Line *VectorLineGetLine(const int index, const VectorLine *vector)
{
  if (index >= vector->length || index < 0)
  {
    printf("\n\nIndex %d out of bounds for VectorLine of size %d\n\n\n",
         index, vector->length);
    exit(1);
  }
  return vector->data[index];
}
//===================================================================


void VectorLineRemoveLastLine(VectorLine *vector)
{
  if( vector->length <= 0 )
    return;

  DestroyLine(vector->data[vector->length-1]);

  vector->length--;
}
//===================================================================


void VectorLineReset(VectorLine *vector)
{
  for(uint16_t i = 0; i < vector->length; i++)
  {
    DestroyLine(vector->data[i]);
  }
  vector->length = 0;
}
//===================================================================




// ---- START Private Functions.

static void VectorLineResizeIfFull(VectorLine *vector)
{
  if (vector->length >= vector->capacity)
  {
    vector->capacity += VECTOR_LINE_DEFAULT_CAPACITY;
    vector->data = realloc(vector->data, sizeof(Line) * vector->capacity);
  }
}
//===================================================================

// ---- END Private Functions.
