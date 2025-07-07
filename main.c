#include "common.h"
#include "chunk.h"

int main(int argc, const char *argv[]) // argc - argument counts and argv - actual text passed in each argument
{
    Chunk chunk; // chunk here is the user defined container where we are storing the dynamic array of bytecode instructions
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    freeChunk(&chunk);

    return 0;
}