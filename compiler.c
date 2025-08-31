#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source)
{
    initScanner(source);    //sets up the initial scanner which will convert raw characters into tokens
}
