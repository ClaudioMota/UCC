#include "basics.h"

#include <stdio.h>
#include <parsers/lexer.h>

char* readFile(char* path)
{
  FILE* file = fopen(path, "rb");
  if(!file) return 0;
  fseek(file, 0, SEEK_END);
  long long size = ftell(file);
  rewind(file);
  char* ret = malloc(size + 1);
  ret[size] = '\0';
  fread(ret, 1, size, file);
  return ret;
}

bool compilerError(char* message, Token* location)
{
  if(location)
    printf("%s %i:%i\n", message, location->line, location->column);
  else
    printf("%s\n", message);
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