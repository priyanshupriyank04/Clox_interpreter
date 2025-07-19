#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

//size of constant data pool is not known at compile time so we need dynamic data structure ValueArray to hold values and grow dynamically 
typedef struct{
    int capacity;
    int count;
    Value* values;
}ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array);
void freeValueArray(ValueArray* array);




#endif