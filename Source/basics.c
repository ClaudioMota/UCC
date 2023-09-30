#include "basics.h"

#include <stdio.h>

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