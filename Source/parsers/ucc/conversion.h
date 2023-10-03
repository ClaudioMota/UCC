#ifndef PRODUCTION_CONVERSION_HEADER
#define PRODUCTION_CONVERSION_HEADER 1

typedef struct Grammar Grammar;

struct VisitData
{
  Grammar* grammar;
};

void setupVisitFunctions();

#endif