#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

typedef struct {
    void* data;
    size_t element_size;
    size_t size;
    size_t capacity;
} DynamicArray;

#endif