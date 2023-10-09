#include "grammar/lalrMachine.h"

#include "basics.h"
#include "grammar/grammar.h"
#include <string.h>
#include <stdio.h>

static void printState(LalrState* state)
{
  for(int i = 0; i < state->itemCount; i++)
  {
    if(state->items[i].production->base)
      printf(" %s -> ", state->items[i].production->base->name);
    else
      printf(" -> ");
    for(int j = 0; j <= state->items[i].production->stepCount; j++)
    {
      if(j == state->items[i].position) printf(". ");
      if(j < state->items[i].production->stepCount)
      {
        ProductionStep* step = &state->items[i].production->steps[j];
        if(step->token) printf("%s ", step->token->name);
        if(step->production) printf("%s ", step->production->name);
      }
    }

    printf("(%p), ", state->items[i].production);
    for(int j = 0; j < state->items[i].lookaheadCount; j++)
      if(!state->items[i].lookahead[j]) printf("$ ");
      else printf("%s ", state->items[i].lookahead[j]->name);

    if(i < state->transitionCount)
    { 
      LalrTransition* t = &state->transitions[i];
      printf("| %s -> %i", t->token ? t->token->name : t->production->name,  state->transitions[i].target->index);
    }
    printf("\n");
  }
}

static LalrState* LalrMachine_createState(LalrMachine* stateMachine, LalrItem** baseItems, int baseItemsCount);

static LalrItem* LalrState_createItem(LalrState* state, ProductionOption* production, int position, TokenExpr** lookahead, int lookaheadCount);

static void LalrState_clean(LalrState* state);

static bool isTokenListEqual(TokenExpr** a, int sizeA, TokenExpr** b, int sizeB)
{
  if(sizeA != sizeB) return false;
  
  for(int i = 0; i < sizeA; i++)
  {
    bool present = false;
    for(int j = 0; j < sizeB; j++)
      if(a[i] == b[j]) present = true;

    if(!present) return false;
  }

  return true;
}

static LalrItem* findItem(LalrState* state, ProductionOption* productionOption, int position, TokenExpr** lookahead, int lookaheadCount)
{
  LalrItem* found = nullptr;
  for(int i = 0; i < state->itemCount; i++)
  {
    LalrItem* item = &state->items[i];
    if(item->production == productionOption && item->position == position)
    {
      if(lookahead && !isTokenListEqual(lookahead, lookaheadCount, item->lookahead, item->lookaheadCount))
        continue;
      found = item;
      break;
    }
  }

  return found;
}

static int maybeAddToken(TokenExpr** tokens, int size, TokenExpr* value)
{
  for(int i = 0; i < size; i++)
    if(tokens[i] == value) return size;
  
  tokens[size++] = value;
  return size;
}

static int getFirstTokens(TokenExpr** tokens, int size, ProductionExpr* production, bool* reached)
{
  if(reached[production->index]) return size;
  reached[production->index] = true;
  for(int i = 0; i < production->optionCount; i++)
  {
    ProductionStep* step = &production->options[i].steps[0];
    if(step->token) size = maybeAddToken(tokens, size, step->token);
    else if(step->production != production) size = getFirstTokens(tokens, size, step->production, reached);
  }

  return size;
}

static int getLookahead(TokenExpr** lookahead, LalrItem* item)
{
  int count = 0;

  if(item->position >= item->production->stepCount -1)
    for(int i = 0; i < item->lookaheadCount; i++)
      count = maybeAddToken(lookahead, count, item->lookahead[i]);
  else
  {
    ProductionStep* step = &item->production->steps[item->position + 1];
    if(step->token) count = maybeAddToken(lookahead, count, step->token);
    else
    {
      bool reached[GRAMMAR_ELEMENTS_MAX];
      memset(reached, 0, sizeof(reached));
      count = getFirstTokens(lookahead, count, step->production, reached);
    }
  }

  return count;
}

static void expandItem(LalrState* state, LalrItem* item)
{
  if(item->position >= item->production->stepCount) return;
  ProductionExpr* currentProd = item->production->steps[item->position].production;
  if(!currentProd) return;

  int lookaheadCount;
  TokenExpr* lookahead[GRAMMAR_ELEMENTS_MAX + 1];
  
  memset(lookahead, 0, sizeof(lookahead));
  lookaheadCount = getLookahead(lookahead, item);

  for(int i = 0; i < currentProd->optionCount; i++)
  {
    LalrItem* existing = findItem(state, &currentProd->options[i], 0, nullptr, lookaheadCount);
    if(!existing)
      existing = LalrState_createItem(state, &currentProd->options[i], 0, lookahead, lookaheadCount);
    if(!isTokenListEqual(lookahead, lookaheadCount, existing->lookahead, existing->lookaheadCount));
      for(int l = 0; l < lookaheadCount; l++)
        existing->lookaheadCount = maybeAddToken(existing->lookahead, existing->lookaheadCount, lookahead[l]);
  }
}

static void expandStateItems(LalrState* state)
{
  for(int i = 0; i < state->itemCount; i++)
    expandItem(state, &state->items[i]);
}

static LalrState* findState(LalrMachine* stateMachine, LalrItem** baseItems, int baseItemCount)
{
  LalrState* found = nullptr;
  int candidateCount = 0;
  LalrState* candidates[GRAMMAR_ELEMENTS_MAX];
  LalrState state;
  memset(&state, 0, sizeof(state));

  for(int i = 0; i < stateMachine->stateCount; i++)
  {
    bool allPresent = true;
    for(int j = 0; j < baseItemCount; j++)
      if(!findItem(stateMachine->states[i], baseItems[j]->production, baseItems[j]->position, nullptr, baseItems[j]->lookaheadCount))
        allPresent = false;
    
    if(allPresent) candidates[candidateCount++] = stateMachine->states[i];
  }

  if(candidateCount)
  {
    for(int i = 0; i < baseItemCount; i++)
      LalrState_createItem(&state, baseItems[i]->production, baseItems[i]->position, baseItems[i]->lookahead, baseItems[i]->lookaheadCount);
    expandStateItems(&state);

    LalrItem* items = state.items;
    for(int i = 0; i < candidateCount; i++)
    {
      if(candidates[i]->itemCount != state.itemCount) continue;

      bool allPresent = true;
      for(int j = 0; j < state.itemCount; j++)
        if(!findItem(candidates[i], items[j].production, items[j].position, items[j].lookahead, items[j].lookaheadCount))
          allPresent = false;

      if(allPresent)
      {
        found = candidates[i];
        break;
      }
    }

    LalrState_clean(&state);
  }

  return found;
}

static void addTransition(LalrState* from, LalrState* to, TokenExpr* expectedToken, ProductionExpr* expectedProd)
{
  if(from->transitionCount >= from->transitionCapacity)
  {
    from->transitionCapacity *= 2;
    if(from->transitionCapacity == 0) from->transitionCapacity = INITIAL_CAPACITY;
    LalrTransition* transitions = new(sizeof(LalrTransition)*from->transitionCapacity);
    memcpy(transitions, from->transitions, sizeof(LalrTransition)*from->transitionCount);
    if(from->transitions) delete(from->transitions);
    from->transitions = transitions;
  }

  LalrTransition* transition = &from->transitions[from->transitionCount++];
  transition->target = to;
  transition->token = expectedToken;
  transition->production = expectedProd;
}

static void createTransitions(LalrMachine* stateMachine, LalrState* state)
{
  int baseItemCount = 0;
  bool visitedItems[state->itemCount];
  LalrItem* newItems = new(sizeof(LalrItem)*state->itemCount);
  LalrItem* baseItems[state->itemCount];
  for(int i = 0; i < state->itemCount; i++) baseItems[i] = &newItems[i];
  memset(visitedItems, 0, sizeof(visitedItems));

  for(int i = 0; i < state->itemCount; i++)
  {
    LalrItem* item = &state->items[i];
    if(item->position >= item->production->stepCount) visitedItems[i] = true;
  }

  for(int i = 0; i < state->itemCount; i++)
  {
    if(visitedItems[i]) continue;

    baseItemCount = 0;
    LalrItem* item = &state->items[i];
    TokenExpr* expectedToken = item->production->steps[item->position].token;
    ProductionExpr* expectedProd = item->production->steps[item->position].production;

    for(int j = i; j < state->itemCount; j++)
    {
      if(visitedItems[j]) continue;

      item = &state->items[j];
      if(expectedToken == item->production->steps[item->position].token && expectedProd == item->production->steps[item->position].production)
      {
        visitedItems[j] = true;
        memcpy(&newItems[baseItemCount], item, sizeof(LalrItem));
        newItems[baseItemCount++].position++;
      }
    }

    LalrState* target = findState(stateMachine, baseItems, baseItemCount);
    if(!target) target = LalrMachine_createState(stateMachine, baseItems, baseItemCount);
    addTransition(state, target, expectedToken, expectedProd);
  }

  delete(newItems);
}

LalrMachine LalrMachine_create(Grammar* grammar)
{
  LalrMachine ret;
  memset(&ret, 0, sizeof(LalrMachine));
  ret.grammar = grammar;
  
  if(grammar->productionCount > 0)
  {
    LalrItem bootstrapItem;
    memset(&bootstrapItem, 0, sizeof(LalrItem));
    bootstrapItem.production = &ret.bootstrap;
    bootstrapItem.position = 0;
    bootstrapItem.lookaheadCount = 1;
    bootstrapItem.lookahead[0] = LALR_LOOKAHEAD_EOF;

    ret.bootstrap.stepCount = 1;
    ret.bootstrap.base = nullptr;
    ret.bootstrap.steps[0].token = nullptr;
    ret.bootstrap.steps[0].production = &grammar->productions[0];

    LalrItem* items[1] = {&bootstrapItem};
    ret.start = LalrMachine_createState(&ret, items, 1);

    for(int i = 0; i < ret.stateCount; i++)
      createTransitions(&ret, ret.states[i]);
  }

  return ret;
}

LalrState* LalrMachine_createState(LalrMachine* stateMachine, LalrItem** baseItems, int baseItemCount)
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
  
  stateMachine->states[stateMachine->stateCount] = new(sizeof(LalrState));
  LalrState* state = stateMachine->states[stateMachine->stateCount];
  memset(state, 0, sizeof(LalrState));
  state->index = stateMachine->stateCount++;
  
  for(int i = 0; i < baseItemCount; i++)
    LalrState_createItem(state, baseItems[i]->production, baseItems[i]->position, baseItems[i]->lookahead, baseItems[i]->lookaheadCount);

  expandStateItems(state);

  return state;
}

LalrItem* LalrState_createItem(LalrState* state, ProductionOption* production, int position, TokenExpr** lookahead, int lookaheadCount)
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
  item->lookaheadCount = lookaheadCount;
  memcpy(item->lookahead, lookahead, sizeof(TokenExpr*)*lookaheadCount);

  return item;
}

void LalrMachine_print(LalrMachine* lalrMachine)
{
  for(int s = 0; s < lalrMachine->stateCount; s++)
  {
    LalrState* state = lalrMachine->states[s];
    printf("%i:", state->index);
    printState(state);
  }
}

void LalrState_clean(LalrState* state)
{
  if(state->items) delete(state->items);
  if(state->transitions) delete(state->transitions);
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