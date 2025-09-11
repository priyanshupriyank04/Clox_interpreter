#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

bool compile(const char *source, Chunk *chunk)
{
    initScanner(source);
    advance();  //function to move forward with the tokens
    expression();   //function to understand the mathematical/grammatical meaning of the code
    consume(TOKEN_EOF, "Expect end of the expression");
    // int line = -1;   //old method to compile the code line by line 

    // for (;;)
    // {
    //     Token token = scanToken();
    //     if (token.line != line)
    //     {
    //         printf("%4d ", token.line); // if token line number is not same, print and update the line variable with current token line number
    //         line = token.line;
    //     }
    //     else
    //     {
    //         printf(" | "); // else if same token line number then print | to indicate same line continuation
    //     }

    //     printf("%2d '%.*s \n", token.type, token.length, token, start);
    //     if (token.type == TOKEN_EOF)
    //     {
    //         break; // if token is special EOF or any error then stop the forever loop
    //     }
    // }
}

// void compile(const char* source) //old definition of the compile function
// {
//     initScanner(source);    //sets up the initial scanner which will convert raw characters into tokens
// }
