#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct
{
    Chunk *chunk; // chunk is included because VM would be running and executing these bytecode instructions i.e. Chunk
} VM;

void initVM(); // sets up the VM to run code
void freeVM(); // resets the VM

#endif