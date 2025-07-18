#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char *argv[]) // argc - argument counts and argv - actual text passed in each argument
{
    Chunk chunk; // chunk here is the user defined container where we are storing the dynamic array of bytecode instructions and //function which checks whole chunk.code array and converts the human readable format of the bytecode
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    disassembleChunk(&chunk, "test chunk");
    freeChunk(&chunk);

    return 0;
}