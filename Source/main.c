#include<stdio.h>
#include "grammar/grammar.h"
#include "parsers/lexer.h"
#include "grammar/lalrMachine.h"

enum ReturnCodes
{
  OK,
  PARAM_ERROR,
  COMPILE_ERROR,
  MEMORY_LEAK
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

static void nextToken(Grammar* grammar, char* content, int startIndex, int length, Token* ret)
{
  memset(ret, 0, sizeof(Token));
  ret->type = TOKEN_UNKNOWN;
  ret->index = startIndex;
  ret->length = 1;

  StateMachineState* states[grammar->tokenCount];
  for(int s = 0; s < grammar->tokenCount; s++)
    states[s] = grammar->tokens[s].stateMachine.start;

  bool any = true;
  int i = startIndex;
  while(any && i < length)
  {
    any = false;
    for(int s = 0; s < grammar->tokenCount; s++)
      if(states[s] != nullptr)
      {
        any = true;
        states[s] = StateMachine_step(states[s], content[i]);
        if(states[s] != nullptr && states[s]->accepted)
        {
          ret->type = s;
          ret->length = i + 1 - startIndex; 
        } 
      }

    if(any) i++;
  }
}

int testFile(Grammar* grammar, LalrMachine* lalrMachine, char* filePath)
{ 
  char* fileContent = readFile(filePath);
  if(!filePath) return showError("Could not open test file", PARAM_ERROR);
  int length = strlen(fileContent);
  int index = 0;

  LalrStep lalrStep;
  memset(&lalrStep, 0, sizeof(LalrStep));

  Token token;

  while(index < length)
  {
    nextToken(grammar, fileContent, index, length, &token);
    index += token.length;
    if(token.type == TOKEN_UNKNOWN)
      printf("UNKNOWN_TOKEN!\n");
    else
      printf("%s\n", grammar->tokens[token.type].name);

    lalrStep = LalrMachine_step(lalrMachine, lalrStep, &grammar->tokens[token.type]);
    while(lalrStep.result == LALR_STEP_REDUCE)
    {
      printf("lalr state: %i\n", lalrStep.stateStack[lalrStep.stackSize-1]->index);
      lalrStep = LalrMachine_step(lalrMachine, lalrStep, &grammar->tokens[token.type]);
    }

    printf("lalr state: %i\n", lalrStep.stateStack[lalrStep.stackSize-1]->index);

    if(lalrStep.result != LALR_STEP_CONTINUE)
    {
      printf("Syntax test ended with code %i\n", lalrStep.result);
      break;
    }
  }

  delete(fileContent);

  return OK;
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
  LalrMachine lalrMachine = LalrMachine_create(&grammar);
  
  LalrMachine_print(&lalrMachine);

  if(ret == OK && strcmp(args[2], "--test") == 0 && numArgs > 3) testFile(&grammar, &lalrMachine, args[3]);

  LalrMachine_clean(&lalrMachine);
  Grammar_clean(&grammar);
  delete(fileContent);

  if(ret == OK && leakCount()) ret = MEMORY_LEAK;

  printf("finished with code %i\n", ret);

  return ret;
}