#include "stateMachine.h"

typedef struct CompoundState CompoundState;
typedef struct CompoundTransition CompoundTransition;

#define COMPOUND_STATE_MAX 16

struct CompoundTransition
{
  bool values[SUPPORTED_CHARACTERS];
  CompoundState* target;
};

struct CompoundState
{
  int count;
  int transitionCount;
  bool accepted;
  int index;
  StateMachineState* states[COMPOUND_STATE_MAX];
  CompoundTransition transitions[STATE_MACHINE_MAX_STATES];
};

static void doCreate(StateMachine* stateMachine)
{
  memset(stateMachine, 0, sizeof(StateMachine));
  stateMachine->states = malloc(sizeof(StateMachineState*)*STATE_MACHINE_MAX_STATES);
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
  
  StateMachineState* ret = malloc(sizeof(StateMachineState));
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

static void getNullReachableStates(
    StateMachineState* state,
    CompoundState** compoundStateMapper,
    CompoundState* deterministicStates,
    int* deterministicStateCount
  )
{
  if(compoundStateMapper[state->index]) return;
  compoundStateMapper[state->index] = &deterministicStates[*deterministicStateCount];
  CompoundState* detState = compoundStateMapper[state->index];
  detState->index = (*deterministicStateCount)++;
  detState->states[detState->count++] = state;
  if(state->accepted) detState->accepted = true;

  for(int i = 0; i < state->transitionCount; i++)
    if(state->transitions[i].values[0])
    {
      StateMachineState* target = state->transitions[i].target;
      if(target != state) detState->states[detState->count++] = target;
      if(target->accepted) detState->accepted = true;
    }
  
  for(int i = 0; i < detState->count; i++)
  {
    StateMachineState* target = detState->states[i];
    getNullReachableStates(target, compoundStateMapper, deterministicStates, deterministicStateCount);
    mergeCompoundState(detState, compoundStateMapper[target->index]);
  }
}

static CompoundState* findExistingCompoundState(CompoundState* deterministicStates, CompoundState* subject, int deterministicStateCount)
{
  for(int i = 0; i < deterministicStateCount; i++)
  {
    if(deterministicStates[i].count == subject->count)
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

static void replaceWithDeterministicStates(StateMachine* stateMachine, CompoundState* deterministicStates, int deterministicStateCount)
{
  StateMachine_destroy(stateMachine);
  doCreate(stateMachine);
  for(int i = 0; i < deterministicStateCount; i++)
    StateMachine_createState(stateMachine);

  for(int i = 0; i < deterministicStateCount; i++)
    for(int j = 0; j < deterministicStates[i].transitionCount; j++)
    {
      CompoundTransition* ct = &deterministicStates[i].transitions[j];
      StateMachineTransition* transition =
        StateMachine_addTransition(stateMachine, stateMachine->states[i], stateMachine->states[ct->target->index], 1);
      memcpy(transition->values, ct->values, SUPPORTED_CHARACTERS);
    }
}

void StateMachine_makeDeterministic(StateMachine* stateMachine)
{
  int deterministicStateCount = 0;
  CompoundState* compoundStateMapper[STATE_MACHINE_MAX_STATES];
  CompoundState* deterministicStates = malloc(sizeof(CompoundState)*STATE_MACHINE_MAX_STATES);
  memset(compoundStateMapper, 0, sizeof(compoundStateMapper));
  memset(deterministicStates, 0, sizeof(deterministicStates));
  
  for(int i = 0; i < stateMachine->stateCount; i++)
    getNullReachableStates(stateMachine->states[i], compoundStateMapper, deterministicStates, &deterministicStateCount);

  for(int i = 0; i < stateMachine->stateCount; i++)
  {
    CompoundState* detState = compoundStateMapper[stateMachine->states[i]->index];
    for(int v = 1; v < SUPPORTED_CHARACTERS; v++)
    {
      CompoundState compoundState;
      CompoundTransition compoundTransition;
      memset(&compoundState, 0, sizeof(compoundState));
      memset(&compoundTransition, 0, sizeof(compoundTransition));
      for(int d = 0; d < detState->count; d++)
        for(int t = 0; t < detState->states[d]->transitionCount; t++)
        {
          StateMachineTransition* transition = &detState->states[d]->transitions[t];
          if(transition->values[v])
          {
            mergeCompoundState(&compoundState, compoundStateMapper[transition->target->index]);
            compoundTransition.values[v] = true;
          }
        }
      
      compoundTransition.target = findExistingCompoundState(deterministicStates, &compoundState, deterministicStateCount);
      if(!compoundTransition.target)
      {
        compoundTransition.target = &deterministicStates[deterministicStateCount];
        compoundTransition.target->index = deterministicStateCount++;
        memcpy(compoundTransition.target, &compoundState, sizeof(compoundState));
      }
      memcpy(&detState->transitions[detState->transitionCount++], &compoundTransition, sizeof(compoundTransition));
    }
  }

  replaceWithDeterministicStates(stateMachine, deterministicStates, deterministicStateCount);

  free(deterministicStates);
}

void StateMachine_destroy(StateMachine* stateMachine)
{
  for(int i = 0; i < stateMachine->stateCount; i++)
    free(stateMachine->states[i]);
  free(stateMachine->states);
}