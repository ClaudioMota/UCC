#ifndef BASICS_HEADER
#define BASICS_HEADER 1

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ELEMENTS_MAX 1024
#define SUPPORTED_CHARACTERS 256
#define STRING_LENGTH 64
#define MAX_PRODUCTION_LENGTH 16

typedef struct Token Token;

// Retrieves the a string with the content of the given file
// When not NULL the content must be freed aftwards
char* readFile(char* path);

bool compilerError(char* message, Token* location);

char* getStringActualContent(char* ret, char* data);

#endif