#ifndef PRODUCTION_HEADER
#define PRODUCTION_HEADER 1

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PRODUCTIONS 2048

typedef struct Production Production;

struct AllProductions
{
  Production* productionContainer[MAX_PRODUCTIONS];
  int containerCount;
  int currentContainerIndex;
};

AllProductions createProductionContainer();

Production* createProduction(AllProductions* allProductions);

void freeProductions(AllProductions* allProductions);

#ifdef __cplusplus
}
#endif

#endif