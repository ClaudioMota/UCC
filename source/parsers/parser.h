#ifndef PARSER_HEADER
#define PARSER_HEADER 1
#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#ifndef nullptr
#define nullptr 0
#endif
#endif

#define CONTAINER_MAX_PRODUCTIONS 1024

typedef struct VisitData VisitData;
typedef struct Production Production;
typedef struct ProductionNode ProductionNode;
typedef struct Parser Parser;
typedef struct State State;
typedef struct Token Token;
typedef struct Action Action;
typedef struct AllParsers AllParsers;
typedef struct ProductionContainer ProductionContainer;
typedef bool (*VisitFunction)(Production*, VisitData*);

struct Action
{
  int shiftTo;
  int expectedToken;
  bool accept;

  int productionOptions[4];
  int productionTypes[4];
  int productionNodeCount[4];
  int optionsCount;
  bool isShift;
};

struct State
{
  Action* actions;
  int actionCount;
};

struct ProductionNode
{
  Token* token;
  Production* production;
};

struct Production
{
  int type;
  int nodeCount; 
  ProductionNode nodes[16];
};

struct Parser
{
  int pos;
  int* stateStack;
  ProductionNode* nodesStack;
  int stackSize;

  Token* token;
  bool hasError;

  Parser* nextOption;
  AllParsers* allParsers;
  ProductionContainer* productionContainer;
};

struct ProductionContainer
{
  void* containers[CONTAINER_MAX_PRODUCTIONS];
  int containerCount;
  int currentContainerIndex;
  int productionStructSize;
};

ProductionContainer createProductionContainer(int productionStructSize);

void cleanProductionContainer(ProductionContainer* allProductions);

Token* newToken();

Action createShift(int token, int targetState);

Action createReduce1(int token, int prodIndex0, int prodType0, int nodeCount0);

Action createReduce2(int token, int prodIndex0, int prodIndex1, int prodType0, int prodType1,  int nodeCount0, int nodeCount1);

Action createReduce3(int token, int prodIndex0, int prodIndex1, int prodIndex2,
                     int prodType0, int prodType1, int prodType2,
                     int nodeCount0, int nodeCount1, int nodeCount2);

Action createReduce4(int token, int prodIndex0, int prodIndex1, int prodIndex2, int prodIndex3,
                     int prodType0, int prodType1, int prodType2, int prodType3,
                     int nodeCount0, int nodeCount1, int nodeCount2, int nodeCount3);

Action createAcceptAction();

State createState(Action* actions, int actionCount);

Parser parse(ProductionContainer* productionContainer, State* states, int (*goToTable)(int, int), Token* token);

Production* getMainProduction(Parser* parser);

bool reduceNodes(Production* production, bool* nodeRedundancyTable);

int getProductionList(Production* production, Production** outList);

int getProductionListSize(Production* production);

bool visitNodes(Production* production, VisitData* visitData, VisitFunction visitFunction);

void freeParser(Parser* parser);

#ifdef __cplusplus
}
#endif
#endif