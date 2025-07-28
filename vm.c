#include <stdio.h>

#include "common.h"
#include "vm.h"
#include "debug.h"

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
    #define READ_CONSTANT() ( vm.chunk->constants.values[READ_BYTE()]) //calls read byte to get the index of the numeric code and then uses returns it 
    for(;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code)); //prints the instruction dynamically for which it requires integer index vm.ip gives the current instruction position and vm.chunk->code gives the first index of the bytecode array so subtracting them gives us the index of the current instruction
#endif
        uint8_t instruction;    //single bytecode instruction line
        switch(instruction = READ_BYTE())
        {
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT(); //reads the numeric constant via index from read byte and gives it as output 
                printValue(constant);
                printf("\n");
                break;
            }

            case OP_RETURN: //op return is the code for ending the program 
            {   
                return INTERPRET_OK;    //exits the program 
            }

            
        }
    }

    #undef READ_BYTE    //undefines the macro to ensure no program conflict
    #undef READ_CONSTANT //undefines the macro we defined earlier in the code 
}

InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;   // stores the bytecode instruction
    vm.ip = vm.chunk->code; // instruction pointer keeps track of code being executed
    return run();   // helper function which helps running bytecode instructions
}