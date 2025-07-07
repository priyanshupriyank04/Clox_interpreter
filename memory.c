#include <stdlib.h>

#include "memory.h"

void* reallocate(void* pointer, size_t oldsize, size_t newsize)   //size_t represents unsigned integer for objects whose size is represented in bytes
{
    if(newsize==0)
    {
        free(pointer);      //new size 0 case being handled
        return NULL;
    }

    void* result = realloc(pointer,newsize);
    if(result==NULL) exit(1);   //terminates the program with exit status 1 which usually means something went wrong or didnt finish as intended
    return result;      
}