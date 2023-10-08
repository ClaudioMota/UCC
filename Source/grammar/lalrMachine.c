#include "grammar/lalrMachine.h"

#include "basics.h"
#include "grammar/grammar.h"
#include <string.h>

LalrMachine LalrMachine_create(Grammar* grammar)
{
  LalrMachine ret;
  memset(&ret, 0, sizeof(LalrMachine));
  ret.grammar = grammar;
  ret.start = LalrMachine_createState(&ret, nullptr, 0);
  
  ProductionExpr* prodExpr = &grammar->productions[0];
  for(int i = 0; i < prodExpr->optionCount; i++)
    LalrState_createItem(ret.start, &prodExpr->options[i], 0);

  return ret;
}

LalrState* LalrMachine_createState(LalrMachine* stateMachine, LalrItem** baseItems, int baseItemsCount)
{
  if(stateMachine->stateCount >= stateMachine->stateCapacity)
  {
    stateMachine->stateCapacity *= 2;
    if(stateMachine->stateCapacity == 0) stateMachine->stateCapacity = INITIAL_CAPACITY;
    LalrState** states = new(sizeof(LalrState*)*stateMachine->stateCapacity);
    for(int i = 0; i < stateMachine->stateCount; i++)
      states[i] = stateMachine->states[i];
    if(stateMachine->states) delete(stateMachine->states);
    stateMachine->states = states;
  }

  LalrState* state = stateMachine->states[stateMachine->stateCount++];
  memset(state, 0, sizeof(LalrState));

  for(int i = 0; i < baseItemsCount; i++)
    LalrState_createItem(state, baseItems[i]->production, baseItems[i]->position);

  return state;
}

LalrItem* LalrState_createItem(LalrState* state, ProductionOption* production, int position)
{
  if(state->itemCount >= state->itemCapacity)
  {
    state->itemCapacity *= 2;
    if(state->itemCapacity == 0) state->itemCapacity = INITIAL_CAPACITY;
    LalrItem* items = new(sizeof(LalrItem)*state->itemCapacity);
    memcpy(items, state->items, sizeof(LalrItem)*state->itemCount);
    if(state->items) delete(state->items);
    state->items = items;
  }

  LalrItem* item = &state->items[state->itemCount++];
  item->production = production;
  item->position = position;

  return item;
}

void LalrState_clean(LalrState* state)
{
  if(state->items) delete(state->items);
  memset(state, 0, sizeof(LalrState));
}

void LalrMachine_clean(LalrMachine* stateMachine)
{
  for(int i = 0; i < stateMachine->stateCount; i++)
  {
    LalrState_clean(stateMachine->states[i]);
    delete(stateMachine->states[i]);
  }

  if(stateMachine->states) delete(stateMachine->states);
  memset(stateMachine, 0, sizeof(LalrMachine));
}