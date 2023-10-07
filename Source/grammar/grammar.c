#include "grammar/grammar.h"
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

static void makeTokensDeterministic(Grammar* grammar)
{
  for(int i = 0; i < grammar->tokenCount; i++)
    StateMachine_makeDeterministic(&grammar->tokens[i].stateMachine);
}

static bool processProductions(Grammar* grammar, Production* mainProd)
{
  VisitData visitData;
  visitData.grammar = grammar;
  setupVisitFunctions();
  if(!ucc_visit(mainProd, &visitData))
    return compilerError("Failed to process productions", nullptr);
  makeTokensDeterministic(grammar);
  return true;
}

bool Grammar_load(Grammar* grammar, char* content)
{
  bool ret = true;
  Lexer lexer = Lexer_create(UCC_lexerFunctionsCount, UCC_lexerFunctions, UCC_shouldIgnore);
  Lexer_parse(&lexer, content);

  AllProductions allProductions = UCC_createProductionContainer();

  Parser parser = ucc_parse(&allProductions, UCC_createProduction, lexer.tokens);

  if(!parser.hasError)
  {
    Production* mainProd = getMainProduction(&parser);
    reduceNodes(mainProd, ucc_nodeRedundancyTable);
    ret = processProductions(grammar, mainProd);
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

Helper* Grammar_declareHelper(Grammar* grammar, char* name)
{
  if(grammar->helperCount >= ELEMENTS_MAX) return nullptr;
  if(Grammar_getHelper(grammar, name)) return nullptr;

  int index = grammar->helperCount++;
  strcpy(grammar->helpers[index].name, name);
  return &grammar->helpers[index];
}

TokenExpr* Grammar_declareToken(Grammar* grammar, char* name, bool ignored)
{
  if(grammar->tokenCount >= ELEMENTS_MAX) return nullptr;
  if(Grammar_getHelper(grammar, name)) return nullptr;
  if(Grammar_getToken(grammar, name)) return nullptr;

  int index = grammar->tokenCount++;
  strcpy(grammar->tokens[index].name, name);
  grammar->tokens[index].ignored = ignored;
  grammar->tokens[index].stateMachine = StateMachine_create();

  return &grammar->tokens[index];
}

ProductionExpr* Grammar_addProduction(Grammar* grammar, char* name, int stepCount, char** steps)
{
  if(grammar->productionCount >= ELEMENTS_MAX) return nullptr;
  if(Grammar_getHelper(grammar, name)) return nullptr;
  if(Grammar_getToken(grammar, name)) return nullptr;

  int index = grammar->productionCount++;
  grammar->productions[index].stepCount = stepCount;

  for(int i = 0; i < stepCount; i++)
    strcpy(grammar->productions[index].steps[i], steps[i]);

  strcpy(grammar->productions[index].name, name);
  return &grammar->productions[index];
}

ReducerExpr* Grammar_reduce(Grammar* grammar, char* from, char* to, bool array);

Helper* Grammar_getHelper(Grammar* grammar, char* name)
{
  for(int i = 0; i < grammar->helperCount; i++)
    if(strcmp(name, grammar->helpers[i].name) == 0)
      return &grammar->helpers[i];

  return nullptr;
}

TokenExpr* Grammar_getToken(Grammar* grammar, char* name)
{
  for(int i = 0; i < grammar->tokenCount; i++)
    if(strcmp(name, grammar->tokens[i].name) == 0)
      return &grammar->tokens[i];

  return nullptr;
}


ProductionExpr* Grammar_getProduction(Grammar* grammar, char* name)
{
  for(int i = 0; i < grammar->productionCount; i++)
    if(strcmp(name, grammar->productions[i].name) == 0)
      return &grammar->productions[i];

  return nullptr;
}


ReducerExpr* Grammar_getReducer(Grammar* grammar, char* name)
{
  for(int i = 0; i < grammar->reducerCount; i++)
    if(strcmp(name, grammar->reducers[i].from) == 0)
      return &grammar->reducers[i];

  return nullptr;
}


void Grammar_destroy(Grammar* grammar)
{
  if(grammar->errorMessage) delete(grammar->errorMessage);
  for(int i = 0; i < grammar->tokenCount; i++)
  {
    StateMachine_destroy(&grammar->tokens[i].stateMachine);
  }
}