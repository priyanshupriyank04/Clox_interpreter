#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h" // tells the compiler to first look for it in the local project folder and <> tells to look for in the system's standard library

typedef enum
{ // create named number type using typedef which reduces task of writing enum everytime
    OP_RETURN,
} Op_code;

typedef struct
{
    int count;     // count of filled capacity
    int capacity;  // count of total capacity
    uint8_t *code; // dynamic array of storing dynamic number of instructions, once completely filled new arr of 2x size copy array and free old memory
} Chunk;

void initChunk(Chunk *chunk); // function to initialise a chunk which is dynamic and stores all the byte instructions

void writeChunk(Chunk *chunk, uint8_t byte);

#endif