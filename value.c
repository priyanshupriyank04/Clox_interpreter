#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(ValueArray* array) // same initialisation just like chunk
{
    array->capacity = 0;
    array->count = 0;
    array->values = NULL;
}

void writeValueArray(ValueArray* array,Value value) //same function mechanism to write values in the chunk array
{
    if(array->capacity < array->count + 1)
    {
        int oldcapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldcapacity);
        array->values = GROW_ARRAY(Value, array->values, oldcapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) //same mechanism like chunk to free a value array (constant data pool)
{
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);  //reset the value array to reset state with null values in count , capacity and values
}

void printValue(Value value)
{
    printf("%g",value);
}

