#include<stdio.h>
#include "grammar.h"

enum ReturnCodes
{
  OK,
  PARAM_ERROR,
  COMPILE_ERROR
};

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

int compile(Grammar* grammar, char* fileContent)
{ 
  if(!Grammar_load(grammar, fileContent)) return COMPILE_ERROR;
  
  return OK;
}

int mainOld(int numArgs, char** args);

void testToken(Grammar* grammar, char* str)
{ 
  int length = strlen(str);
  StateMachineState* states[grammar->tokenCount];
  for(int s = 0; s < grammar->tokenCount; s++)
    states[s] = grammar->tokens[s].stateMachine.start;

  for(int i = 0; i < length; i++)
    for(int s = 0; s < grammar->tokenCount; s++)
      if(states[s] != nullptr)
        states[s] = StateMachine_step(states[s], str[i]);
  
  for(int s = 0; s < grammar->tokenCount; s++)
    if(states[s] != nullptr && states[s]->accepted)
      printf("%s\n", grammar->tokens[s].name);
}

int main(int numArgs, char** args)
{
  //return mainOld(numArgs, args);
  if(numArgs < 3) return showHelp();

  char* fileContent = readFile(args[1]);
  if(!fileContent)
    return showError("Could not open grammar file", PARAM_ERROR);

  Grammar grammar = Grammar_create();
  int ret = compile(&grammar, fileContent);

  if(ret == OK && strcmp(args[2], "-token") == 0) testToken(&grammar, args[3]);

  Grammar_destroy(&grammar);
  free(fileContent);

  printf("finished with code %i\n", ret);

  return ret;
}