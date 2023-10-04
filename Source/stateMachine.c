#include "stateMachine.h"

StateMachine StateMachine_create()
{
  StateMachine ret;
  memset(&ret, 0, sizeof(ret));
  ret.states = malloc(sizeof(StateMachineState*)*STATE_MACHINE_MAX_STATES);
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

void StateMachine_destroy(StateMachine* stateMachine)
{
  for(int i = 0; i < stateMachine->stateCount; i++)
    free(stateMachine->states[i]);
  free(stateMachine->states);
}