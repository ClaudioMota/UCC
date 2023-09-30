#include<stdio.h>
#include "grammar.h"

#define PARAM_ERROR 1

int showHelp()
{
  printf("Usage: UCC GRAMAR_FIFE NAMESPACE\n");
  return PARAM_ERROR;
}

int showError(char* error, int type)
{
  printf("%s\n", error);
  return type;
}

int compile(char* fileContent)
{
  Grammar grammar = Grammar_create();
  if(Grammar_load(&grammar, fileContent) == 0);
  Grammar_destroy(&grammar);
}

int mainOld(int numArgs, char** args);

int main(int numArgs, char** args)
{
  //return mainOld(numArgs, args);
  if(numArgs < 3) return showHelp();

  char* fileContent = readFile(args[1]);
  char* namespace = args[2];
  if(!fileContent)
    return showError("Could not open grammar file", PARAM_ERROR);

  int result = compile(fileContent);

  free(fileContent);

  return result;
}