#include "grammar.h"
#include "parsers/lexer.h"
#include "stdio.h"

int UCC_lexerFunctionsCount = 24;
extern int (**UCC_lexerFunctions)(int* state, int input);

Grammar Grammar_create()
{
  Grammar ret;
  memset(&ret, 0, sizeof(Grammar));
  return ret;
}

bool treta(void*){return false;}

bool Grammar_load(Grammar* grammar, char* content)
{
  Lexer lexer = Lexer_create(UCC_lexerFunctionsCount, UCC_lexerFunctions, (void*)treta);
  Lexer_parse(&lexer, content);
  Lexer_destroy(&lexer);
  return false;
}

void Grammar_destroy(Grammar* grammar)
{
  if(grammar->errorMessage) free(grammar->errorMessage);
}