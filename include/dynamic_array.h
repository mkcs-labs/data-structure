#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

typedef struct {
  void *data;
  size_t element_size;
  size_t size;
  size_t capacity;
} DynamicArray;

typedef enum { DYNAMIC_ARRAY_SUCCESS = 0 } DynamicArrayError;

void dynamic_array_init(DynamicArray *dynamicArray, size_t element_size);
void dynamic_array_free(DynamicArray *dynamicArray);

void *dynamic_array_peek(DynamicArray *dynamicArray, size_t index);
DynamicArrayError dynamic_array_insert(DynamicArray *dynamicArray, size_t index,
                                       void *element);
DynamicArrayError dynamic_array_delete(DynamicArray *dynamicArray,
                                       size_t index);
DynamicArrayError dynamic_array_realloc(DynamicArray *dynamicArray);

#endif