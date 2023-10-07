#include "grammar/stateMachine.h"

#include <stdio.h>

typedef struct CompoundState CompoundState;
typedef struct CompoundTransition CompoundTransition;

#define COMPOUND_STATE_MAX 16

struct CompoundTransition
{
  int value;
  CompoundState* target;
};

struct CompoundState
{
  int count;
  int transitionCount;
  bool accepted;
  int index;
  bool reachable;
  StateMachineState* states[COMPOUND_STATE_MAX];
  CompoundTransition transitions[STATE_MACHINE_MAX_STATES];
};

static void doCreate(StateMachine* stateMachine)
{
  memset(stateMachine, 0, sizeof(StateMachine));
  stateMachine->states = new(sizeof(StateMachineState*)*STATE_MACHINE_MAX_STATES);
}

StateMachine StateMachine_create()
{
  StateMachine ret;
  doCreate(&ret);
  StateMachine_createState(&ret);
  return ret;
}

StateMachineState* StateMachine_createState(StateMachine* stateMachine)
{
  if(stateMachine->stateCount >= STATE_MACHINE_MAX_STATES) return nullptr;
  int index = stateMachine->stateCount++;
  
  StateMachineState* ret = new(sizeof(StateMachineState));
  memset(ret, 0, sizeof(StateMachineState));

  stateMachine->states[index] = ret;
  ret->index = index;

  if(index == 0) stateMachine->start = ret;

  return ret;
}

StateMachineTransition* StateMachine_addTransition(StateMachine* stateMachine, StateMachineState* from, StateMachineState* to, unsigned char value)
{
  StateMachineTransition* transition = nullptr;
  for(int i = 0; i < from->transitionCount; i++)
    if(from->transitions[i].target == to)
      transition = &from->transitions[i];

  if(!transition)
  {
    if(from->transitionCount >= STATE_MACHINE_MAX_STATES) return nullptr;
    transition = &from->transitions[from->transitionCount++];
    transition->target = to;
  }

  transition->values[value] = true;

  return transition;
}

static void mergeCompoundState(CompoundState* dest, CompoundState* src)
{
  dest->accepted = dest->accepted || src->accepted;
  for(int i = 0; i < src->count; i++)
  {
    bool alreadyPresent = false;
    for(int j = 0; j < dest->count; j++)
      if(src->states[i] == dest->states[j])
        alreadyPresent = true;

    if(!alreadyPresent)
    {
      dest->states[dest->count++] = src->states[i];
      if(src->states[i]->accepted) dest->accepted = true;
    }
  }
}

static CompoundState* findExistingCompoundState(CompoundState* deterministicStates, CompoundState* subject, int deterministicStateCount)
{
  for(int i = 0; i < deterministicStateCount; i++)
  {
    if(deterministicStates[i].count == subject->count && deterministicStates[i].accepted == subject->accepted)
    {
      bool miss = false;
      for(int j = 0; j < subject->count; j++)
      {
        bool present = false;
        for(int k = 0; k < subject->count; k++)
          present = present || deterministicStates[i].states[j] == subject->states[k];
        if(!present) miss = true;
      }

      if(!miss) return &deterministicStates[i];
    }
  }
  return nullptr;
}

static void getNullReachableStates(
    StateMachineState* state,
    CompoundState** compoundStateMapper,
    CompoundState* deterministicStates,
    int* deterministicStateCount
  )
{
  if(compoundStateMapper[state->index]) return;

  compoundStateMapper[state->index] = (void*)-1;

  CompoundState compoundState;
  memset(&compoundState, 0, sizeof(compoundState));
  if(state->accepted) compoundState.accepted = true;

  bool hasNonEmptyTransition = false;
  for(int i = 0; i < state->transitionCount; i++)
    for(int v = 1; v < SUPPORTED_CHARACTERS; v++)
      if(state->transitions[i].values[v]) hasNonEmptyTransition = true;

  if(hasNonEmptyTransition || state->transitionCount == 0)
    compoundState.states[compoundState.count++] = state;

  for(int i = 0; i < state->transitionCount; i++)
    if(state->transitions[i].values[0])
    {
      StateMachineState* target = state->transitions[i].target;
      if(target != state)
      {
        getNullReachableStates(target, compoundStateMapper, deterministicStates, deterministicStateCount);
        mergeCompoundState(&compoundState, compoundStateMapper[target->index]);
      }
    }

  CompoundState* detState = findExistingCompoundState(deterministicStates, &compoundState, *deterministicStateCount);
  if(!detState)
  {
    detState = &deterministicStates[*deterministicStateCount];
    memcpy(detState, &compoundState, sizeof(compoundState));
    detState->index = (*deterministicStateCount)++;
  }

  compoundStateMapper[state->index] = detState;
}

static void replaceWithDeterministicStates(StateMachine* stateMachine, CompoundState* deterministicStates, int deterministicStateCount)
{
  int map[ELEMENTS_MAX];
  StateMachine_destroy(stateMachine);
  doCreate(stateMachine);
  for(int i = 0; i < deterministicStateCount; i++)
  {
    if(deterministicStates[i].reachable)
    {
      StateMachineState* state = StateMachine_createState(stateMachine);
      state->accepted = deterministicStates[i].accepted;
      map[deterministicStates[i].index] = state->index;
    }
  }
  stateMachine->start = stateMachine->states[0];

  for(int i = 0; i < deterministicStateCount; i++)
  {
    if(deterministicStates[i].reachable)
      for(int j = 0; j < deterministicStates[i].transitionCount; j++)
      {
        int s = map[deterministicStates[i].index];
        CompoundTransition* ct = &deterministicStates[i].transitions[j];
        StateMachineTransition* transition =
          StateMachine_addTransition(stateMachine, stateMachine->states[s], stateMachine->states[map[ct->target->index]], ct->value);
      }
  }
}

void StateMachine_makeDeterministic(StateMachine* stateMachine)
{
  int deterministicStateCount = 0;
  CompoundState* compoundStateMapper[STATE_MACHINE_MAX_STATES];
  CompoundState* deterministicStates = new(sizeof(CompoundState)*STATE_MACHINE_MAX_STATES);
  memset(compoundStateMapper, 0, sizeof(compoundStateMapper));
  memset(deterministicStates, 0, sizeof(deterministicStates));

  for(int i = 0; i < stateMachine->stateCount; i++)
    getNullReachableStates(stateMachine->states[i], compoundStateMapper, deterministicStates, &deterministicStateCount);

  deterministicStates[0].reachable = true;

  for(int i = 0; i < deterministicStateCount; i++)
  {
    CompoundState* detState = &deterministicStates[i];
    for(int v = 1; v < SUPPORTED_CHARACTERS; v++)
    {
      CompoundState targetCompoundState;
      CompoundTransition compoundTransition;
      memset(&targetCompoundState, 0, sizeof(targetCompoundState));
      memset(&compoundTransition, 0, sizeof(compoundTransition));
      
      bool any = false;
      for(int d = 0; d < detState->count; d++)
        for(int t = 0; t < detState->states[d]->transitionCount; t++)
        {
          StateMachineTransition* transition = &detState->states[d]->transitions[t];

          if(transition->values[v])
          {
            compoundTransition.value = v;
            any = true;
            mergeCompoundState(&targetCompoundState, compoundStateMapper[transition->target->index]);
          }
        }

      if(!any) continue;

      compoundTransition.target = findExistingCompoundState(deterministicStates, &targetCompoundState, deterministicStateCount);
      if(!compoundTransition.target)
      {
        compoundTransition.target = &deterministicStates[deterministicStateCount];
        memcpy(compoundTransition.target, &targetCompoundState, sizeof(targetCompoundState));
        compoundTransition.target->index = deterministicStateCount++;
      }
      compoundTransition.target->reachable = true;
      memcpy(&detState->transitions[detState->transitionCount++], &compoundTransition, sizeof(compoundTransition));
    }
  }

  replaceWithDeterministicStates(stateMachine, deterministicStates, deterministicStateCount);

  delete(deterministicStates);
}

StateMachineState* StateMachine_step(StateMachineState* state, unsigned char input)
{
  for(int i = 0; i < state->transitionCount; i++)
    if(state->transitions[i].values[input])
      return state->transitions[i].target;

  return nullptr;
}

void StateMachine_print(StateMachine* stateMachine)
{
  for(int i = 0; i < stateMachine->stateCount; i++)
  {
    if(stateMachine->start == stateMachine->states[i]) printf("->");
    if(stateMachine->states[i]->accepted) printf("*");
    printf("%i\n", stateMachine->states[i]->index);
    for(int j = 0; j < stateMachine->states[i]->transitionCount; j++)
    {
      for(int v = 0; v < SUPPORTED_CHARACTERS; v++)
        if(stateMachine->states[i]->transitions[j].values[v]) printf(" %c", v);
      printf(" -> %i\n", stateMachine->states[i]->transitions[j].target->index);
    }
  }
}

void StateMachine_destroy(StateMachine* stateMachine)
{
  for(int i = 0; i < stateMachine->stateCount; i++)
    delete(stateMachine->states[i]);
  delete(stateMachine->states);
}