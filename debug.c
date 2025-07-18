#include <stdio.h>

#include "debug.h"
#include "value.h"

// forward declaration of 1byte debugging simpleInstruction function to be able to use it before defining it
static int simpleInstruction(const char *name, int offset);
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

    uint8_t instruction = chunk->code[offset]; // stores unsigned 8 bit integer type instruction code using offset

    switch (instruction)
    {
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT", chunk, offset);
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
    uint8_t constant = chunk->code[offset + 1]; //finds the index of the constant
    printf("-16s %4d '", name, constant);   //prints the op code and index of the constant
    printValue(chunk->constants.values[constant]);  //prints the constant value via index from the data pool - currently this supports only the double value format to be changed for a general data type
    printf("\n");
    return offset + 2;  //tells the compiler where the next instruction starts 
}