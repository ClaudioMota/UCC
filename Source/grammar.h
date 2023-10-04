#ifndef GRAMMAR_HEADER
#define GRAMMAR_HEADER 1

#include "basics.h"

typedef struct Grammar Grammar;
typedef struct Helper Helper;
typedef struct TokenExpr TokenExpr;
typedef struct ProductionExpr ProductionExpr;
typedef struct ReducerExpr ReducerExpr;

struct Helper
{
  char name[STRING_LENGTH];
  char values[SUPPORTED_CHARACTERS];
};

struct TokenExpr
{
  char name[STRING_LENGTH];
  bool ignored;
  void* startState;
  TokenExpr* first, *second;
  int operation;
};

struct ProductionExpr
{
  char name[STRING_LENGTH];
  int stepCount;
  char steps[MAX_PRODUCTION_LENGTH][STRING_LENGTH];
};

struct ReducerExpr
{
  char from[STRING_LENGTH];
  char to[STRING_LENGTH];
  bool isArray;
};

struct Grammar
{
  int helperCount, tokenCount, productionCount, reducerCount;
  Helper helpers[ELEMENTS_MAX];
  TokenExpr tokens[ELEMENTS_MAX];
  ProductionExpr productions[ELEMENTS_MAX];
  ReducerExpr reducers[ELEMENTS_MAX];
  char* errorMessage;
};

Grammar Grammar_create();
bool Grammar_load(Grammar* grammar, char* content);
Helper* Grammar_declareHelper(Grammar* grammar, char* name);
TokenExpr* Grammar_declareToken(Grammar* grammar, char* name, bool ignored);
ProductionExpr* Grammar_addProduction(Grammar* grammar, char* name, int stepCount, char** steps);
ReducerExpr* Grammar_reduce(Grammar* grammar, char* from, char* to, bool array);
Helper* Grammar_getHelper(Grammar* grammar, char* name);
TokenExpr* Grammar_getToken(Grammar* grammar, char* name);
ProductionExpr* Grammar_getProduction(Grammar* grammar, char* name);
ReducerExpr* Grammar_getReducer(Grammar* grammar, char* name);
void Grammar_destroy(Grammar* grammar);

#endif