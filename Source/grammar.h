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
  void* startState;
};

struct ProductionExpr
{
  char name[STRING_LENGTH];
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
void Grammar_destroy(Grammar* grammar);

#endif