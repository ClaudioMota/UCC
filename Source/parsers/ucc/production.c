#include "parsers/ucc/production.h"
#include <stdlib.h>
#include <string.h>

Production* UCC_createProduction(AllProductions* allProductions)
{
  UCCProduction* ret = new(sizeof(UCCProduction));
  memset(ret, 0, sizeof(UCCProduction));
  ret->next = allProductions->last;
  allProductions->last = ret;
  return (Production*)ret;
}

void UCC_deleteProduction(UCCProduction* prod)
{
  delete(prod);
}

AllProductions UCC_createProductionContainer()
{
  AllProductions ret = {0};
  return ret;
}

void UCC_freeProductionContainer(AllProductions* allProductions)
{
  UCCProduction* prod = allProductions->last;
  while(prod)
  {
    UCC_deleteProduction(prod);
    prod = prod->next;
  }
}