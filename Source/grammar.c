#include "grammar.h"
#include "parsers/lexer.h"
#include "parsers/ucc/production.h"
#include "parsers/ucc/productions.h"
#include "parsers/ucc/uccParser.h"
#include "parsers/ucc/conversion.h"
#include "stdio.h"

int UCC_lexerFunctionsCount = 24;
extern int (**UCC_lexerFunctions)(int* state, int input);
bool UCC_shouldIgnore(Token* token);

Grammar Grammar_create()
{
  Grammar ret;;
  memset(&ret, 0, sizeof(Grammar));
  return ret;
}

bool Grammar_load(Grammar* grammar, char* content)
{
  bool ret = true;
  Lexer lexer = Lexer_create(UCC_lexerFunctionsCount, UCC_lexerFunctions, UCC_shouldIgnore);
  Lexer_parse(&lexer, content);

  AllProductions allProductions = UCC_createProductionContainer();

  Parser parser = ucc_parse(&allProductions, UCC_createProduction, lexer.tokens);

  VisitData visitData;
  visitData.grammar = grammar;

  if(!parser.hasError)
  {
    setupVisitFunctions();
    ucc_visit(getMainProduction(&parser), &visitData);
  }
  else
  {
    ret = compilerError("Syntax error", parser.token);
  }

  UCC_freeProductionContainer(&allProductions);

  freeParser(&parser);
  Lexer_destroy(&lexer);
  return ret;
}

void Grammar_destroy(Grammar* grammar)
{
  if(grammar->errorMessage) free(grammar->errorMessage);
}