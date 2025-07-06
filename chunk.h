#ifndef clox_chunk_h
#define clox_chunk_h 

#include "common.h"     // tells the compiler to first look for it in the local project folder and <> tells to look for in the system's standard library

typedef enum {      // create named number type using typedef which reduces task of writing enum everytime 
    OP_RETURN,
} Op_code;

#endif