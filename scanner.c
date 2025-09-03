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

static bool isAlpha(char c) // checks if the character is alpha or an underscore
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
static bool isDigit(char c) // checks if the character is digit
{
    return c >= '0' && c <= '9';
}

static bool isAtEnd()
{
    return *scanner.current == '\0'; // checks if the curr ptr of scanner has reached the null termination assuming that the source file has been added in form of C string
}

static char advance()
{
    scanner.current++;          // increment the scanner curr ptr by 1
    return scanner.current[-1]; // return one back the character of scanner
}

// quick diff peek() checks the next character advances is yet to consume while peekNext() points to the next of the character yet to be consumed
static char peek()
{
    return *scanner.current; // return the character being pointer by the curr ptr without updating the curr ptr
}

static char peekNext()
{
    if (isAtEnd())
    {
        return '\0';
    }
    return scanner.current[1];
}
static bool match(char expected) // function to check for dual punctuation tokens
{
    if (isAtEnd())
    {
        return false; // if EOF return false
    }

    if (*scanner.current != expected) // if next character doesnt match return false
    {
        return false;
    }

    scanner.current++;
    return true;
}
static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;                                     // token will be created of the specified type
    token.start = scanner.start;                           // start ptr to be set at start ptr of scanner
    token.length = (int)(scanner.current - scanner.start); // curr ptr points one ahead of end of token so length will be curr - start ptr
    token.line = scanner.line;                             // token line is same as scanner line

    return token;
}

static Token errorToken(const char *message)
{
    Token token;
    token.type = TOKEN_ERROR;            // token being created specially for error type
    token.start = message;               // start ptr to be pointing at the message string being passed as the argument
    token.length = (int)strlen(message); // length will be of the string message
    token.line = scanner.line;

    return token;
}

static void skipWhitespace()
{
    for (;;)
    {
        char c = peek(); // current character without updating the curr ptr
        switch (c)
        {
        case ' ':      // whitespace character
        case '\r':     // old style carriage return
        case '\t':     // tab character
            advance(); // skip the character
            break;

        case '\n':
            scanner.line++;
            advance();
            break;

        case '/':
            if (peekNext() == '/') // then check if next is also '/'
            {
                while (peek() != '\n' && isAtEnd()) // if next is also slash and we have also reached end of line and end of comment then return
                {
                    advance();
                }
            }
            else
            {
                return; // else return out of loop and let scan token handle the slash as division operator
            }
            break;
        default:
            return; // non skippable character so exit the loop
        }
    }
}

static TokenType checkKeyword(int start, int length, const char *rest, TokenType type)  //check keywords compares the actual string with the keyword string 
{
    if (scanner.current - scanner.start == start + length && memcmp(scanner.start + start, rest, length) == 0)
    {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static TokenType identifierType()   //to check which of the reserved keywords is this 
{
    switch (scanner.start[0])
    {
    case 'a':
        return checkKeyword(1, 2, "nd", TOKEN_AND);
    case 'c':
        return checkKeyword(1, 4, "lass", TOKEN_CLASS);
    case 'e':
        return checkKeyword(1, 3, "lse", TOKEN_ELSE);
    case 'f':       //nested switch for multiple possible reserved keywords
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'a':
                return checkKeyword(2, 3, "lse", TOKEN_FALSE);
            case 'o':
                return checkKeyword(2, 1, "r", TOKEN_FOR);
            case 'u':
                return checkKeyword(2, 1, "n", TOKEN_FUN);
            }
        }
        break;
    case 'i':
        return checkKeyword(1, 1, "f", TOKEN_IF);
    case 'n':
        return checkKeyword(1, 2, "il", TOKEN_NIL);
    case 'o':
        return checkKeyword(1, 1, "r", TOKEN_OR);
    case 'p':
        return checkKeyword(1, 4, "rint", TOKEN_PRINT);
    case 'r':
        return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
    case 's':
        return checkKeyword(1, 4, "uper", TOKEN_SUPER);
    case 't':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'h':
                return checkKeyword(2, 2, "is", TOKEN_THIS);
            case 'r':
                return checkKeyword(2, 2, "ue", TOKEN_TRUE);
            }
        }
        break;
    case 'v':
        return checkKeyword(1, 2, "ar", TOKEN_VAR);
    case 'w':
        return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    }
    return TOKEN_IDENTIFIER;
}

static Token identifier()   //to check if the identifier is a user defined or a reserved keyword 
{
    while (isAlpha(peek()) || isDigit(peek()))
    {
        advance();
    }

    return makeToken(identifierType());
}

static Token number()
{
    while (isDigit(peek()))
    {
        advance();
    }

    // look for the fractional part using dot(.)
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance(); // consume the dot as part of fraction

        while (isDigit(peek()))
        {
            advance();
        }
    }

    return makeToken(TOKEN_NUMBER);
}

static Token string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
        {
            scanner.line++;
        }
        advance();
    }

    if (isAtEnd())
    {
        return errorToken("Unterminated string.");
    }

    advance();
    return makeToken(TOKEN_STRING);
}

Token scantoken()
{
    skipWhitespace();
    scanner.start = scanner.current; // assign start pointer at the current ptr location in the file
    if (isAtEnd())
    {
        return makeToken(TOKEN_EOF); // if ptr reaches end of file generate eof token error and stops scanning for more tokens
    }

    char c = advance(); // function to grab one by one character from source and then move it to switch

    if (isAlpha(c))
    {
        return identifier();
    }
    if (isDigit(c)) // check if the number is token to return a number token
    {
        return number();
    }

    switch (c)
    { // different characters pointing to create different types of tokens
    // single character tokens
    case '(':
        return makeToken(TOKEN_LEFT_PAREN);
    case ')':
        return makeToken(TOKEN_RIGHT_PAREN);
    case '{':
        return makeToken(TOKEN_LEFT_BRACE);
    case '}':
        return makeToken(TOKEN_RIGHT_BRACE);
    case ';':
        return makeToken(TOKEN_SEMICOLON);
    case ',':
        return makeToken(TOKEN_COMMA);
    case '.':
        return makeToken(TOKEN_DOT);
    case '-':
        return makeToken(TOKEN_MINUS);
    case '+':
        return makeToken(TOKEN_PLUS);
    case '/':
        return makeToken(TOKEN_SLASH);
    case '*':
        return makeToken(TOKEN_STAR);

    // two character punctuation tokens
    // uses a match function to check the next character if it matches then first option else it is a single character token
    case '!':
        return makeToken(
            match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
        return makeToken(
            match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
        return makeToken(
            match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
        return makeToken(
            match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);

    case '"':
        return string();
    }

    return errorToken("Unexpected character."); // else manually report unexpected token error until other token handling is done
}
