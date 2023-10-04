#ifndef PRODUCTION_CONVERSION_HEADER
#define PRODUCTION_CONVERSION_HEADER 1

typedef struct Grammar Grammar;

enum VisitMode
{
  MODE_HELPER,
  MODE_TOKEN,
  MODE_PRODUCTION,
  MODE_REDUCE
};

struct VisitData
{
  int mode;
  Grammar* grammar;
};

void setupVisitFunctions();

#endif