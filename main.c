#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

// REPL = read ->eval -> print -> loop
//read - get user input 
//eval - run the input 
//print - print the output (if any)
//loop - rerun the loop
static void repl(){             //it is static because repl is private to the file (main.c)
    char line[1024];    //to hold the user input per line

    for(;;) //just a forever loop with no initiation updation, keeps on going until EOF or until something breaks it
    {
        printf("> ");    //indicate user time to write some line input

        if(!fgets(line,sizeof(line), stdin))    //if the fgets gets NULL due to sudden closure or EOF then print new line and close the loop 
        {
            printf("\n");
            break;
        }

        interpret(line);    //pass on the line input to the VM 
    }
}
int main(int argc, const char *argv[]) // argc - argument counts and argv - actual text passed in each argument
{
    initVM(); // initialise vm whenever main function is called, prepares memory stack,space everything required

    if(argc==1)
    {
        repl();         //if argc is 1 that is only filename is passed then read-eval-print loop is executed which executes each line of code one by one just like in python terminal
    }

    else if(argc==2)
    {
        runFile(argv[1]);   //if argc = 2 it means that along with file script name is also passed as argument so the script is read-> scan -> compile -> run
    }

    else{
        fprintf(stderr, "Usage: clox [path]\n");    //if argc >=2 then give error 
        exit(64); //standard unix style code for exit
    }
    
    //Manual chunk bytecodes being passed to VM
    // Chunk chunk; // chunk here is the user defined container where we are storing the dynamic array of bytecode instructions and //function which checks whole chunk.code array and converts the human readable format of the bytecode

    // initChunk(&chunk);

    // int constant = addConstant(&chunk, 1.2); // manually initialising the double constant to add

    // writeChunk(&chunk, OP_CONSTANT, 123); // manually adding op code to the chunk data pool
    // writeChunk(&chunk, constant, 123);    // manually adding the constant to the chunk data pool after the op code

    // constant = addConstant(&chunk, 3.4);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk, constant, 123);

    // writeChunk(&chunk, OP_ADD, 123);

    // constant = addConstant(&chunk, 5.6);
    // writeChunk(&chunk, OP_CONSTANT, 123);
    // writeChunk(&chunk, constant, 123);

    // writeChunk(&chunk, OP_DIVIDE, 123);
    // writeChunk(&chunk, OP_NEGATE, 123); // prints the negate of the input value
    // writeChunk(&chunk, OP_RETURN, 123);

    // disassembleChunk(&chunk, "test chunk");

    // interpret(&chunk); // function to interpret the chunk bytecode instructions
    freeVM();          // free vm before exiting the main function
    // freeChunk(&chunk);

    return 0;
}