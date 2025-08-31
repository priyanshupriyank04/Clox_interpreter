#include <stdio.h> // fopen, fprintf, stderr, fseek, ftell, fread, fclose
#include <stdlib.h> // malloc, free, exit
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

//runfile - function for running a .lox file via interpreter 
static void runFile(const char* path)   //path represents the file path to run ./clox hello.lox -> here path will be of file hello.lox 
{
    char *source = readFile(path);  //reads entire file into memory as a string

    InterpretResult result = interpret(source); //passes the entire file content to interpret() function which returns a result - success/compile/runtime error

    free(source);    //free the memory once interpret is done, this is done since C doesnt have auto garbage collection so all memory initiated via malloc, readFile needs to be manually freed

    if(result==INTERPRET_COMPILE_ERROR)
    {
        exit(65);   //exit code 65 is for compile error
    }
    if(result==INTERPRET_RUNTIME_ERROR)
    {
        exit(70);   //exit code 70 is for runtime error
    }
}

static char* readFile(const char* path)     //function which reads entire file content and passes it into a C string 
{
    FILE* file = fopen(path, "rb"); //open the file at the path and rb is read and binary mode (binary mode ignores newline translations)
    
    if(file==NULL)
    {
        fprintf(stderr,"Could not open the file \%s\ .\n",path); 
        exit(74);   //conventional exit code for exit i/o errors
    }

    fseek(file,0L, SEEK_END); //moves the file pointer to end of the file to measure the file size
    size_t fileSize = ftell(file);   // measures the file size and stores it 

    rewind(file); //moves the file pointer back to beginning of the file 

    char* buffer = (char*)malloc(fileSize+1);   //create memory buffer to store the file content

    if(buffer==NULL)
    {
        fprintf("Not enough memory to read \%s\.\n",path);
        exit(74);   //prints message if error is thrown for not enough memory for fileread
    }
    

    size_t bytesRead = fread(buffer,sizeof(char), fileSize, file); //binary file read syntax - size_t fread(void* ptr, size_t size, size_t count, FILE* stream)

    buffer[bytesRead] = '\0';  //manually add null terminator to C string to make it compatible for functions like printf() or interpret()

    fclose(file);
    return buffer;
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