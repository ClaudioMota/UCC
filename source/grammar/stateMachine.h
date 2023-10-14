#ifndef STATE_MACHINE_HEADER
#define STATE_MACHINE_HEADER 1

#include "utils.h"
#include <stdbool.h>

typedef struct StateMachine StateMachine;
typedef struct StateMachineTransition StateMachineTransition;
typedef struct StateMachineState StateMachineState;

struct StateMachineTransition
{
  bool values[SUPPORTED_CHARACTERS];
  StateMachineState* target;
};

struct StateMachineState
{
  int index;
  int transitionCount;
  bool accepted;
  StateMachineTransition transitions[SUPPORTED_CHARACTERS];
};

struct StateMachine
{
  int stateCount, stateCapacity;
  StateMachineState** states;
  StateMachineState* start;
};

StateMachine StateMachine_create();

StateMachineState* StateMachine_createState(StateMachine* stateMachine);

StateMachineTransition* StateMachine_addTransition(StateMachine* stateMachine, StateMachineState* from, StateMachineState* to, unsigned char value);

void StateMachine_makeDeterministic(StateMachine* stateMachine);

StateMachineState* StateMachine_step(StateMachineState* state, unsigned char input);

void StateMachine_print(StateMachine* stateMachine);

void StateMachine_clean(StateMachine* stateMachine);

#endif