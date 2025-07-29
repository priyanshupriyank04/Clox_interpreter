#include <stdio.h>

#include "common.h"
#include "vm.h"
#include "debug.h"

VM vm;

static void resetStack()
{
    vm.stackTop = vm.stack; //since no index is specified it will directly point to the first index of the array always
}

void initVM()
{
    resetStack();
}

void freeVM()
{
    
}

void push(Value value)
{
    *vm.stackTop = value;   //store value on pointer location
    vm.stackTop++;  //increments pointer location
}

Value pop()
{
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run()
{
    #define READ_BYTE() (* vm.ip++) //function to keep track and update instruction pointer/program counter
    #define READ_CONSTANT() ( vm.chunk->constants.values[READ_BYTE()]) //calls read byte to get the index of the numeric code and then uses returns it 
    for(;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
    printf("           ");
    for(Value* slot = vm.stack; slot<vm.stackTop;slot++)    //prints the whole stack everytime we call this function
    {
        printf("[");
        printValue(*slot);
        printf("]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code)); //prints the instruction dynamically for which it requires integer index vm.ip gives the current instruction position and vm.chunk->code gives the first index of the bytecode array so subtracting them gives us the index of the current instruction
#endif
        uint8_t instruction;    //single bytecode instruction line
        switch(instruction = READ_BYTE())
        {
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT(); //reads the numeric constant via index from read byte and gives it as output 
                push(constant); //adds the value to the data stack
                break;
            }

            case OP_ADD:    //these 4 are binary operations to be done with the topmost and second top most element in the stack 
            {
                BINARY_OP(+);
                break;
            }

            case OP_SUBTRACT:
            {
                BINARY_OP(-);
                break;
            }

            case OP_MULTIPLY:
            {
                BINARY_OP(*);
                break;
            }

            case OP_DIVIDE:
            {
                BINARY_OP(/);
                break;
            }
            case OP_NEGATE:     //this is the unary negation operation to be done with the topmost element of the stack
            {
                push(-pop());   //first pop the value negate it and then push it again on the stack to compute negate of a number
                break;
            }
            case OP_RETURN: //op return is the code for ending the program 
            {   
                printValue(pop());  //prints the stackTop value before popping it out
                printf("\n");   
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

