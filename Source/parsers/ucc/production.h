#ifndef UCC_PRODUCTION_HEADER
#define UCC_PRODUCTION_HEADER 1

#include "parsers/parser.h"

typedef struct AllProductions AllProductions;
typedef struct UCCProduction UCCProduction;
typedef struct VisitData VisitData;

struct AllProductions
{
  UCCProduction* last;
};

struct UCCProduction
{
  int type;
  int nodeCount; 
  ProductionNode nodes[16];

  UCCProduction* next;
};

AllProductions UCC_createProductionContainer();
Production* UCC_createProduction(AllProductions* allProductions);
void UCC_freeProductionContainer(AllProductions* allProductions);

#endif