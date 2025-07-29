#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256   

typedef struct
{
    Chunk *chunk; // chunk is included because VM would be running and executing these bytecode instructions i.e. Chunk
    uint8_t* ip;    //pointer of bytecode datatype to keep track of instruction line/ also known as program counter pointing to the next instruction which is supposed to be executed
    Value stack[STACK_MAX]; //creation of stack of max stack length
    Value* stackTop;    //Value type pointer which increments/decrements based on push/pop function
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

//both stack push/pop operations
void push(Value value); //adds value type to stack
Value pop();    //pops value type from stack

#endif