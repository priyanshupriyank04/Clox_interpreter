#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

void initChunk(Chunk *chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    initValueArray(&chunk->constants); // initialises list to store constants which appear in the code
}

void freeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity); // uint8_t represent 1 single byte instruction where chunk code represents a series of single byte instructions
    freeValueArray(&chunk->constants);                 // frees up the constant data pool
    initChunk(chunk);                                  // use this to reset the memory to initial reset states which are NULL and 0
}

void writeChunk(Chunk *chunk, uint8_t byte)
{
    if (chunk->capacity < chunk->count + 1) // this case is always hit when we initialise an array with capacity and count as 0
    {
        int oldcapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(chunk->capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldcapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
