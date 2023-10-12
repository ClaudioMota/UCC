#ifndef BASICS_HEADER
#define BASICS_HEADER 1

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define GRAMMAR_ELEMENTS_MAX 1024
#define SUPPORTED_CHARACTERS 256
#define STRING_LENGTH 64
#define MAX_PRODUCTION_LENGTH 16
#define INITIAL_CAPACITY 64

#ifndef nullptr
#define nullptr 0
#endif

typedef struct Token Token;

void* new(long long size);

void delete(void* pointer);

int leakCount();

// Retrieves the a string with the content of the given file
// When not NULL the content must be freed aftwards
char* readFile(char* path);

bool compilerError(char* message, Token* location);

char* getStringActualContent(char* ret, char* data);

bool failIfNull(void* pointer, char* errorMessage);

bool createDirectory(char* path);

FILE* createFile(char* basePath, char* name);

FILE* openFile(char* path);

void closeFile(FILE* file);

#endif