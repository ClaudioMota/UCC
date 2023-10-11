#include "grammar/grammar.h"
#include "parsers/lexer.h"
#include "parsers/ucc/lexerFunctions.h"
#include "parsers/ucc/production.h"
#include "parsers/ucc/productions.h"
#include "parsers/ucc/uccParser.h"
#include "parsers/ucc/conversion.h"
#include "stdio.h"

Grammar Grammar_create()
{
  Grammar ret;
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
  Lexer lexer = Lexer_create(ucc_lexerFunctionCount, ucc_lexerFunctions, ucc_shouldIgnoreToken);
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
  Lexer_clean(&lexer);
  return ret;
}

Helper* Grammar_declareHelper(Grammar* grammar, char* name)
{
  if(grammar->helperCount >= GRAMMAR_ELEMENTS_MAX) return nullptr;
  if(Grammar_getHelper(grammar, name)) return nullptr;

  int index = grammar->helperCount++;
  strcpy(grammar->helpers[index].name, name);
  return &grammar->helpers[index];
}

TokenExpr* Grammar_declareToken(Grammar* grammar, char* name, bool ignored)
{
  if(grammar->tokenCount >= GRAMMAR_ELEMENTS_MAX) return nullptr;
  if(Grammar_getHelper(grammar, name)) return nullptr;
  if(Grammar_getToken(grammar, name)) return nullptr;

  int index = grammar->tokenCount++;
  strcpy(grammar->tokens[index].name, name);
  grammar->tokens[index].index = index;
  grammar->tokens[index].ignored = ignored;
  grammar->tokens[index].stateMachine = StateMachine_create();

  return &grammar->tokens[index];
}

static ProductionExpr* findOrCreateProduction(Grammar* grammar, char* name)
{
  ProductionExpr* prodExpr = Grammar_getProduction(grammar, name);
  
  if(!prodExpr)
  {
    if(grammar->productionCount >= GRAMMAR_ELEMENTS_MAX) return nullptr;
    int index = grammar->productionCount++;
    prodExpr = &grammar->productions[index];
    prodExpr->index = index;

    if(!prodExpr->options)
    {
      prodExpr->options = new(sizeof(ProductionOption)*GRAMMAR_ELEMENTS_MAX);
      memset(prodExpr->options, 0, sizeof(ProductionOption)*GRAMMAR_ELEMENTS_MAX);
    }
    
    strcpy(prodExpr->name, name);
  }

  return prodExpr;
}

ProductionExpr* Grammar_addProduction(Grammar* grammar, char* name, int stepCount, char** steps)
{
  if(Grammar_getHelper(grammar, name)) return nullptr;
  if(Grammar_getToken(grammar, name)) return nullptr;

  ProductionExpr* prodExpr = findOrCreateProduction(grammar, name);
  if(!prodExpr || prodExpr->optionCount >= GRAMMAR_ELEMENTS_MAX) return nullptr;
  ProductionOption* production = &prodExpr->options[prodExpr->optionCount++];

  production->base = prodExpr;
  production->stepCount = stepCount;

  for(int i = 0; i < stepCount; i++)
  {
    production->steps[i].token = Grammar_getToken(grammar, steps[i]);
    if(!production->steps[i].token)
      production->steps[i].production = findOrCreateProduction(grammar, steps[i]);
  }

  return prodExpr;
}

ReducerExpr* Grammar_reduce(Grammar* grammar, char* from, char* to)
{
  ProductionExpr* fromProd = Grammar_getProduction(grammar, from);
  if(!fromProd) return nullptr;
  if(Grammar_getReducer(grammar, from)) return nullptr;
  
  int index = grammar->reducerCount++;
  ReducerExpr* reducer = &grammar->reducers[index];
  strcpy(reducer->to, to);
  reducer->from = fromProd;

  return reducer;
}

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
    if(strcmp(name, grammar->reducers[i].from->name) == 0)
      return &grammar->reducers[i];

  return nullptr;
}


void Grammar_clean(Grammar* grammar)
{
  for(int i = 0; i < grammar->tokenCount; i++)
    StateMachine_clean(&grammar->tokens[i].stateMachine);
  
  for(int i = 0; i < grammar->productionCount; i++)
    delete(grammar->productions[i].options);

  memset(grammar, 0, sizeof(Grammar));
}