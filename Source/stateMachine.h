#ifndef STATE_MACHINE_HEADER
#define STATE_MACHINE_HEADER 1

#include "basics.h"
#include <stdbool.h>

typedef struct StateMachine StateMachine;
typedef struct StateMachineTransition StateMachineTransition;
typedef struct StateMachineState StateMachineState;

#define STATE_MACHINE_MAX_STATES 1024

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
  StateMachineTransition transitions[STATE_MACHINE_MAX_STATES];
};

struct StateMachine
{
  int stateCount;
  StateMachineState** states;
  StateMachineState* start;
};

StateMachine StateMachine_create();

StateMachineState* StateMachine_createState(StateMachine* stateMachine);

StateMachineTransition* StateMachine_addTransition(StateMachine* stateMachine, StateMachineState* from, StateMachineState* to, unsigned char value);

void StateMachine_destroy(StateMachine* stateMachine);

#endif