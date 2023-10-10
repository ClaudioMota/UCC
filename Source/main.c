#include<stdio.h>
#include "grammar/grammar.h"
#include "parsers/lexer.h"
#include "grammar/lalrMachine.h"
#include "generation/generation.h"

enum ReturnCodes
{
  OK,
  PARAM_ERROR,
  COMPILE_ERROR,
  GENERATION_ERROR,
  MEMORY_LEAK
};

int showHelp()
{
  printf("Usage: ucc GRAMAR_FIFE [NAMESPACE | OPTIONS]\n"
         "Options:\n"
         "  --test FILE     Attempts to parse a file using the grammar compiled"
         "  --print         Shows the state machines for the grammar compiled"
        );
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

    lalrStep = LalrMachine_step(lalrMachine, lalrStep, &grammar->tokens[token.type]);
    while(lalrStep.result == LALR_STEP_REDUCE)
      lalrStep = LalrMachine_step(lalrMachine, lalrStep, &grammar->tokens[token.type]);
    
    if(lalrStep.result != LALR_STEP_CONTINUE)
      break;
  }

  while(lalrStep.result == LALR_STEP_CONTINUE || lalrStep.result == LALR_STEP_REDUCE)
  {
    lalrStep = LalrMachine_step(lalrMachine, lalrStep, nullptr);
  }

  printf("Syntax test ended with code %i\n", lalrStep.result);

  delete(fileContent);

  return lalrStep.result;
}

int checkCliCommands(int numArgs, char** args, Grammar* grammar, LalrMachine* lalrMachine)
{
  int ret = OK;
  for(int i = 2; i < numArgs && ret == OK; i++)
  {
    if(strcmp(args[i], "--test") == 0 && numArgs > i + 1)
      ret = testFile(grammar, lalrMachine, args[++i]);
    if(strcmp(args[i], "--print") == 0)
    {
      for(int i = 0; i < grammar->tokenCount; i++)
      {
        printf("%s:\n", grammar->tokens[i].name);
        StateMachine_print(&grammar->tokens[i].stateMachine);
      }
      printf("Grammar:\n");
      LalrMachine_print(lalrMachine);
    }
    if(strlen(args[i]) > 0)
      if(!generateLexer(grammar, args[i]))
        ret = GENERATION_ERROR;
  }
  return ret;
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

  if(ret == OK) ret = checkCliCommands(numArgs, args, &grammar, &lalrMachine);

  LalrMachine_clean(&lalrMachine);
  Grammar_clean(&grammar);
  delete(fileContent);

  if(ret == OK && leakCount()) ret = MEMORY_LEAK;

  printf("finished with code %i\n", ret);

  return ret;
}