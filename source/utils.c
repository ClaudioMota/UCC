#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <parsers/lexer.h>

static int leaks = 0;

void* new(long long size)
{
  leaks++;
  return malloc(size);
}

void delete(void* pointer)
{
  leaks--;
  free(pointer);
}

int leakCount()
{
  return leaks;
}

char* readFile(char* path)
{
  FILE* file = openFile(path);
  if(!file) return 0;
  fseek(file, 0, SEEK_END);
  long long size = ftell(file);
  rewind(file);
  char* ret = new(size + 1);
  ret[size] = '\0';
  fread(ret, 1, size, file);
  closeFile(file);
  return ret;
}

bool compilerError(char* message, Token* location)
{
  if(location)
    printf("%s %i:%i\n", message, location->line, location->column);
  else
    printf("%s\n", message);

  return false;
}

bool failIfNull(void* pointer, char* errorMessage)
{
  if(pointer)
    return false;
  else
    return !compilerError(errorMessage, nullptr);
}

char* getStringActualContent(char* ret, char* data)
{
  int size = strlen(data);
  int o = 0;
  for(int i = 1; i < size -1; i++)
  {
    if(data[i] == '\\')
    {
      i++;
      if(i >= size -1) break;

      char escaped;
      switch(data[i])
      {
        case 'n': escaped = '\n'; break;
        case 't': escaped = '\t'; break;
        case 'r': escaped = '\r'; break;
        case '0': escaped = '\0'; break;
        case 'b': escaped = '\b'; break;
        case 'a': escaped = '\a'; break;
        default: escaped = data[i];
      }
      ret[o++] = escaped;
    }
    else
      ret[o++] = data[i];
  }

  ret[o] = 0;
  return ret;
}

FILE* createFile(char* basePath, char* fileName)
{
  char fullPath[STRING_LENGTH*3];
  strcpy(fullPath, basePath);
  strcat(fullPath, fileName);

  FILE* file = fopen(fullPath, "wb");
  if(file) leaks++;
  return file;
}

FILE* openFile(char* path)
{
  FILE* file = fopen(path, "rb");
  if(file) leaks++;
  return file;
}

bool copyFile(char *from, char* toBasePath, char* to)
{
  char* content = readFile(from);
  if(content == nullptr) return false;
  bool ret = false;
  FILE* dest = createFile(toBasePath, to);
  if(dest != nullptr)
  {
    long long length = strlen(content);
    ret = length == fwrite(content, sizeof(char), length, dest);
    closeFile(dest);
  }

  delete(content);

  return ret;
}

void closeFile(FILE* file)
{
  fclose(file);
  leaks--;
}