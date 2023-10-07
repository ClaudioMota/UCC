#ifndef LALR_HEADER
#define LALR_HEADER 1

#include "basics.h"

typedef struct Token Token;
typedef struct ProductionExpr ProductionExpr;
typedef struct Grammar Grammar;
typedef struct LalrItem LalrItem;
typedef struct LalrState LalrState;
typedef struct LalrMachine LalrMachine;

#define LALR_LOOKAHEAD_EOF_INDEX ELEMENTS_MAX

struct LalrItem
{
  ProductionExpr* production;
  int position;
  int lookaheadIndex[ELEMENTS_MAX + 1];
};

struct LalrState
{
  int index;
  int itemCount, itemCapacity;
  LalrItem* items;
};

struct LalrMachine
{
  Grammar* grammar;
  int stateCount, stateCapacity;
  LalrState** states;
  LalrState* start;
};

LalrMachine LalrMachine_create(Grammar* grammar);

LalrState* LalrMachine_createState(LalrMachine* stateMachine, LalrItem** baseItems, int baseItemsCount);

LalrItem* LalrState_createItem(LalrState* state, ProductionExpr* production, int position);

LalrState* LalrMachine_step(LalrState* state, Token* input);

void LalrState_clean(LalrState* state);

void LalrMachine_clean(LalrMachine* stateMachine);

#endif