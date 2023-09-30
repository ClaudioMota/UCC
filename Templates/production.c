#include <somepath/production.h>
#include <somepath/parser.h>

AllProductions createProductionContainer()
{
  AllProductions ret;
  ret.containerCount = 0;
  ret.currentContainerIndex = MAX_PRODUCTIONS;
  return ret;
}

Production* createProduction(AllProductions* allProductions)
{
  if(allProductions->currentContainerIndex >= MAX_PRODUCTIONS)
  {
    allProductions->productionContainer[allProductions->containerCount++] = malloc(sizeof(Production) * MAX_PRODUCTIONS);
    allProductions->currentContainerIndex = 0;
  }
  return &(allProductions->productionContainer[allProductions->containerCount-1][allProductions->currentContainerIndex++]);
}

void freeProductions(AllProductions* allProductions)
{ 
  for(int i = 0; i < allProductions->containerCount; i++)
  {
    free(&allProductions->productionContainer[i]);
  }
}


