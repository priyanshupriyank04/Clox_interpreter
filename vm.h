#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct
{
    Chunk *chunk; // chunk is included because VM would be running and executing these bytecode instructions i.e. Chunk
    uint8_t* ip;    //pointer of bytecode datatype to keep track of instruction line/ also known as program counter pointing to the next instruction which is supposed to be executed
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
}InterpretResult;


void initVM(); // sets up the VM to run code
void freeVM(); // resets the VM

InterpretResult interpret(Chunk* chunk);

#endif