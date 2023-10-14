#ifndef UCC_GENERATION_HEADER
#define UCC_GENERATION_HEADER 1

#include <stdbool.h>

typedef struct Grammar Grammar;
typedef struct LalrMachine LalrMachine;

bool generateGrammar(Grammar* grammar, LalrMachine* lalrMachine, char* namespace);

#endif