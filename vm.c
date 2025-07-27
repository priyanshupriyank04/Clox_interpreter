#include "common.h"
#include "vm.h"

VM vm;

void initVM()
{

}

void freeVM()
{
    
}

static InterpretResult run()
{
    #define READ_BYTE() (* vm.ip++) //function to keep track and update instruction pointer/program counter

    for(;;)
    {
        uint8_t instruction;    //single bytecode instruction line
        switch(instruction = READ_BYTE())
        {
            case OP_RETURN: //op return is the code for ending the program 
            {   
                return INTERPRET_OK;    //exits the program 
            }
        }
    }

    #undef READ_BYTE    //undefines the macro to ensure no program conflict
}

InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;   // stores the bytecode instruction
    vm.ip = vm.chunk->code; // instruction pointer keeps track of code being executed
    return run();   // helper function which helps running bytecode instructions
}