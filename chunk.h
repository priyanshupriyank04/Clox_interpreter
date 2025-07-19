#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h" // tells the compiler to first look for it in the local project folder and <> tells to look for in the system's standard library
#include "value.h"

typedef enum
{ // create named number type using typedef which reduces task of writing enum everytime
    OP_CONSTANT,
    OP_RETURN,
} Op_code;

typedef struct
{
    int count;            // count of filled capacity
    int capacity;         // count of total capacity
    uint8_t *code;        // dynamic array of storing dynamic number of instructions, once completely filled new arr of 2x size copy array and free old memory
    ValueArray constants; // stores the constants which appear in the code including dynamic data like strings
} Chunk;

void initChunk(Chunk *chunk); // function to initialise a chunk which is dynamic and stores all the byte instructions

void freeChunk(Chunk *chunk);                // function to free the unused memory
void writeChunk(Chunk *chunk, uint8_t byte); // function to write in bytes on the specified memory location

int addConstant(Chunk *chunk, Value value);

#endif