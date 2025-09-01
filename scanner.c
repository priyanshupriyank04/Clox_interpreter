#include <stdio.h>
#include <string.h>

#include "scanner.h"
#include "common.h"

typedef struct{
    const char* start;  //points to beginning of the current token
    const char* current;    //points to the character we are looking at  in the current token
    int line;   //tells line number for error reporting
} Scanner;

Scanner scanner;

void initScanner(const char* source)
{
    scanner.start = source;
    scanner.current = source;   //use the scanner instance and initialise start,current ptrs and set line number to 1
    scanner.line = 1;
}

