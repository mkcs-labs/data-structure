#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} DynamicArray;

typedef enum {
    DYNAMIC_ARRAY_SUCCESS = 0,
    DYNAMIC_ARRAY_ERROR_OUT_OF_BOUNDS = 1
} DynamicArrayError;

#define DYNAMIC_ARRAY_INITIAL_CAPACITY 16
#define DYNAMIC_ARRAY_GROWTH_FACTOR 2

void dynamic_array_init(DynamicArray *dynamicArray, size_t element_size);

void dynamic_array_free(const DynamicArray *dynamicArray);

void *dynamic_array_peek(const DynamicArray *dynamicArray, size_t index);

DynamicArrayError dynamic_array_insert(DynamicArray *dynamicArray, size_t index, const void *element);

DynamicArrayError dynamic_array_delete(DynamicArray *dynamicArray, size_t index);

DynamicArrayError dynamic_array_realloc(DynamicArray *dynamicArray);

#endif
