#ifndef PRODUCTION_CONVERSION_HEADER
#define PRODUCTION_CONVERSION_HEADER 1

typedef struct Grammar Grammar;
typedef struct UCCProduction UCCProduction;

enum VisitMode
{
  MODE_HELPER,
  MODE_TOKEN,
  MODE_PRODUCTION,
  MODE_REDUCE
};

struct UCCProduction
{
  int type;
  int nodeCount; 
  ProductionNode nodes[16];

  void* helper, *token, *production, *reducer;
  char helperValue[SUPPORTED_CHARACTERS];

  UCCProduction* next;
};

struct VisitData
{
  int mode;
  Grammar* grammar;
};

void setupVisitFunctions();

#endif