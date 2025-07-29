#include <stdio.h>

#include "debug.h"
#include "value.h"

// forward declaration of 1byte debugging simpleInstruction function to be able to use it before defining it
static int simpleInstruction(const char *name, int offset);
static int constantInstruction(const char *name, Chunk *chunk, int offset);
void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("%s \n", name); // prints chunk name

    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}

int disassembleInstruction(Chunk *chunk, int offset)
{
    printf("%04d ", offset); // prints offset till 4 digits
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
    {
        printf(" | "); // if more than one bytecode instructions are written in the same line then we need to print the offset line number index only for the first bytecode instruction in that line print | for other bytecode instructions
    }
    else
    {
        printf("%4d", chunk->lines[offset]); // if the bytecode instruction is the first in its line then print the line number which is present in the chunk offset data pool
    }

    uint8_t instruction = chunk->code[offset]; // stores unsigned 8 bit integer type instruction code using offset

    switch (instruction)
    {
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, offset);
    case OP_NEGATE:
        return simpleInstruction("OP_NEGATE", offset);  //prints the offset at which the next instruction is to be executed
    case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset); // prints the instruction in brief along with the offset at which the next instruction is supposed to be executed


    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}

static int simpleInstruction(const char *name, int offset) // handles checking and printing op return bytecode instruction for every 1-byte
{
    printf("%s \n", name);
    return offset + 1;
}

static int constantInstruction(const char *name, Chunk *chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];    // finds the index of the constant
    printf(" %-16s %4d '", name, constant);        // prints the op code and index of the constant
    printValue(chunk->constants.values[constant]); // prints the constant value via index from the data pool - currently this supports only the double value format to be changed for a general data type
    printf(" \n");
    return offset + 2; // tells the compiler where the next instruction starts
}