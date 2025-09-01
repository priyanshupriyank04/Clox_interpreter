#include <stdio.h>
#include <string.h>

#include "scanner.h"
#include "common.h"

typedef struct
{
    const char *start;   // points to beginning of the current token
    const char *current; // points to the character we are looking at  in the current token
    int line;            // tells line number for error reporting
} Scanner;

Scanner scanner;

void initScanner(const char *source)
{
    scanner.start = source;
    scanner.current = source; // use the scanner instance and initialise start,current ptrs and set line number to 1
    scanner.line = 1;
}

static bool isAtEnd()
{
    return *scanner.current == '\0'; // checks if the curr ptr of scanner has reached the null termination assuming that the source file has been added in form of C string
}

static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;  //token will be created of the specified type
    token.start = scanner.start;    //start ptr to be set at start ptr of scanner
    token.length = (int)(scanner.current - scanner.start);  //curr ptr points one ahead of end of token so length will be curr - start ptr
    token.line = scanner.line;  //token line is same as scanner line

    return token;
}

static Token errorToken(const char* message)
{
    Token token;
    token.type = TOKEN_ERROR;   //token being created specially for error type
    token.start = message;  //start ptr to be pointing at the message string being passed as the argument   
    token.length = (int)strlen(message);    //length will be of the string message
    token.line = scanner.line;      

    return token;
}
Token scantoken()
{
    scanner.start = scanner.current; // assign start pointer at the current ptr location in the file
    if (isAtEnd())
    {
        return makeToken(TOKEN_EOF); // if ptr reaches end of file generate eof token error and stops scanning for more tokens
    }

    return errorToken("Unexpected character."); // else manually report unexpected token error until other token handling is done
}
