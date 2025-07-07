#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) \              
    ((capacity) < 8 ? 8 : (capacity) * 2) // here the \ means the macro continues on the next line, capacity is initialised as 8 and then 2x everytime

#define GROW_ARRAY(type, pointer, oldcount, newcount) \
    (type *)reallocate(pointer, sizeof(type) * oldcount, sizeof(type) * newcount) // reallocates old size to new size of type type, type* is used because the memory pointer will be reused

#define FREE_ARRAY(type, pointer, oldcount) \
    reallocate(pointer, sizeof(type) * oldcount, 0)

void *reallocate(void *pointer, size_t oldsize, size_t newsize);
#endif