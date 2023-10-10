#ifndef LALR_HEADER
#define LALR_HEADER 1

#include "basics.h"
#include "grammar/grammar.h"

typedef struct LalrItem LalrItem;
typedef struct LalrTransition LalrTransition;
typedef struct LalrState LalrState;
typedef struct LalrMachine LalrMachine;
typedef struct LalrStep LalrStep;

#define LALR_LOOKAHEAD_EOF nullptr

struct LalrItem
{
  ProductionOption* production;
  int position;
  int lookaheadCount;
  TokenExpr* lookahead[GRAMMAR_ELEMENTS_MAX + 1];
};

struct LalrTransition
{
  LalrState* target;
  TokenExpr* token;
  ProductionExpr* production;
};

struct LalrState
{
  int index;
  int itemCount, itemCapacity;
  int transitionCount, transitionCapacity;
  LalrItem* items;
  LalrTransition* transitions;
};

struct LalrMachine
{
  Grammar* grammar;
  int stateCount, stateCapacity;
  LalrState** states;
  LalrState* start;
  ProductionOption bootstrap;
};

enum LalrStepResult
{
  LALR_STEP_CONTINUE,
  LALR_STEP_REDUCE,
  LALR_STEP_ACCEPTED,
  LALR_STEP_REDUCE_REDUCE,
  LALR_STEP_SYNTAX_ERROR
};

struct LalrStep
{
  int result;
  int stackSize, reduceCount;
  LalrState* stateStack[GRAMMAR_ELEMENTS_MAX];
  ProductionExpr* reduces[GRAMMAR_ELEMENTS_MAX];
};

LalrMachine LalrMachine_create(Grammar* grammar);

LalrStep LalrMachine_step(LalrMachine* lalrMachine, LalrStep step, TokenExpr* input);

void LalrMachine_print(LalrMachine* lalrMachine);

void LalrMachine_clean(LalrMachine* lalrMachine);

#endif