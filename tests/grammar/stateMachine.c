#include "test.h"
#include "grammar/stateMachine.h"

void setup(TestEnvironment* env)
{
  env->helperPointer = malloc(sizeof(StateMachine));
  StateMachine* stateMachine = env->helperPointer;
  *stateMachine = StateMachine_create(); 
}

void clean(TestEnvironment* env)
{
  StateMachine* stateMachine = env->helperPointer;
  StateMachine_clean(stateMachine);
  // Asserts no memory leaks happened 
  if(leakCount() != 0)
    printf("[WARN] memory leak detected on %s:%i\n", _sourceFile, env->testLine);
}

🐛
setupFunction = setup;
cleanFunction = clean;

context("StateMachine_create")
{
  test("Initializes the state machine correctly")
  {
    StateMachine stateMachine = StateMachine_create();
    assert(stateMachine.start == stateMachine.states[0]);
    assert(stateMachine.stateCount == 1);
    assert(stateMachine.stateCapacity > 0);
    StateMachine_clean(&stateMachine);
  }
}

context("StateMachine_createState")
{
  test("Creates a new state to the state machine")
  {
    StateMachine* stateMachine = testEnv->helperPointer;
    StateMachineState* state = StateMachine_createState(stateMachine);
    assert(state);
    assert(state == stateMachine->states[stateMachine->stateCount-1]);
    assert(state->index == stateMachine->stateCount-1);
    assert(stateMachine->stateCapacity >= stateMachine->stateCount);
  }

  test("Increases the capacity when it is reached")
  {
    StateMachine* stateMachine = testEnv->helperPointer;
    int initialCapacity = stateMachine->stateCapacity;
    for(int i = 0; i < initialCapacity * 2; i++)
    {
      StateMachineState* state = StateMachine_createState(stateMachine);
      assert(state);
      assert(stateMachine->stateCapacity >= stateMachine->stateCount);
    }

    assert(stateMachine->stateCapacity >= initialCapacity * 2);
  }
}

context("StateMachine_addTransition")
{
  test("Creates a transition from a state to the other")
  {
    StateMachine* stateMachine = testEnv->helperPointer;
    StateMachineState* a = StateMachine_createState(stateMachine);
    StateMachineState* b = StateMachine_createState(stateMachine);
    StateMachineTransition* t = StateMachine_addTransition(stateMachine, a, b, 10);
    assert(t);
    assert(t->target == b);
    assert(&a->transitions[a->transitionCount-1] == t);
    assert(t->values[10] == true);
    for(int i = 0; i < SUPPORTED_CHARACTERS; i++)
      if(i != 10)
        refute(t->values[i]);
  }

  test("Reuses a transition that already exists")
  {
    StateMachine* stateMachine = testEnv->helperPointer;
    StateMachineState* a = StateMachine_createState(stateMachine);
    StateMachineState* b = StateMachine_createState(stateMachine);
    StateMachineTransition* t = StateMachine_addTransition(stateMachine, a, b, 10);
    StateMachineTransition* t2 = StateMachine_addTransition(stateMachine, a, b, 15);
    assert(t == t2);
    assert(t->target == b);
    assert(a->transitionCount == 1);
    assert(t->values[10] == true);
    assert(t->values[15] == true);
  }

  test("Creates a new transition when does not exists")
  {
    StateMachine* stateMachine = testEnv->helperPointer;
    StateMachineState* a = StateMachine_createState(stateMachine);
    StateMachineState* b = StateMachine_createState(stateMachine);
    StateMachineState* c = StateMachine_createState(stateMachine);
    StateMachineTransition* t = StateMachine_addTransition(stateMachine, a, b, 10);
    StateMachineTransition* t2 = StateMachine_addTransition(stateMachine, a, c, 15);
    assert(t != t2);
    assert(t2->target == c);
    assert(a->transitionCount == 2);
  }
}

context("StateMachine_makeDeterministic")
{
  test("Makes an or operation deterministic")
  {
    StateMachine* stateMachine = testEnv->helperPointer;
    StateMachineState* a = StateMachine_createState(stateMachine);
    StateMachineState* b = StateMachine_createState(stateMachine);
    StateMachineState* end = StateMachine_createState(stateMachine);
    end->accepted = true;
    
    StateMachine_addTransition(stateMachine, stateMachine->start, a, 'a');
    StateMachine_addTransition(stateMachine, stateMachine->start, b, 'b');
    StateMachine_addTransition(stateMachine, a, end, 0);
    StateMachine_addTransition(stateMachine, b, end, 0);

    StateMachine_makeDeterministic(stateMachine);

    assert(stateMachine->start->transitionCount == 1);

    refute(stateMachine->start->accepted);
    assert(StateMachine_step(stateMachine->start, 'a')->accepted);
    assert(StateMachine_step(stateMachine->start, 'b')->accepted);
    refute(StateMachine_step(stateMachine->start, 0));
  }

  test("Makes an cycle operation deterministic")
  {
    StateMachine* stateMachine = testEnv->helperPointer;
    StateMachineState* middle = StateMachine_createState(stateMachine);
    StateMachineState* end = StateMachine_createState(stateMachine);
    end->accepted = true;
    
    StateMachine_addTransition(stateMachine, stateMachine->start, middle, 'a');
    StateMachine_addTransition(stateMachine, middle, end, 'b');
    StateMachine_addTransition(stateMachine, middle, stateMachine->start, 0);

    StateMachine_makeDeterministic(stateMachine);

    middle = StateMachine_step(stateMachine->start, 'a');
    assert(middle);
    refute(middle->accepted);
    refute(StateMachine_step(stateMachine->start, 'b'));
    assert(StateMachine_step(middle, 'b')->accepted);
    assert(StateMachine_step(middle, 'a') == middle);
    refute(StateMachine_step(middle, 0));
  }
}

context("StateMachine_clean")
{
  test("cleans all data created by the state machine")
  {
    int initialMemory = leakCount();
    StateMachine stateMachine = StateMachine_create();
    StateMachineState* a = StateMachine_createState(&stateMachine);
    StateMachineState* b = StateMachine_createState(&stateMachine);
    StateMachine_addTransition(&stateMachine, a, b, 10);
    StateMachine_clean(&stateMachine);
    StateMachine zero = {0};
    assert(memcmp(&zero, &stateMachine, sizeof(StateMachine)) == 0);
    assert(initialMemory == leakCount());
  }
}
🚀
