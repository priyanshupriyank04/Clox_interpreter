#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) // argc - argument counts and argv - actual text passed in each argument
{
    initVM(); // initialise vm whenever main function is called

    Chunk chunk; // chunk here is the user defined container where we are storing the dynamic array of bytecode instructions and //function which checks whole chunk.code array and converts the human readable format of the bytecode

    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2); // manually initialising the double constant to add

    writeChunk(&chunk, OP_CONSTANT, 123); // manually adding op code to the chunk data pool
    writeChunk(&chunk, constant, 123);    // manually adding the constant to the chunk data pool after the op code

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_ADD, 123);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_DIVIDE, 123);
    writeChunk(&chunk, OP_NEGATE, 123); // prints the negate of the input value
    writeChunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "test chunk");

    interpret(&chunk); // function to interpret the chunk bytecode instructions
    freeVM();          // free vm before exiting the main function
    freeChunk(&chunk);

    return 0;
}