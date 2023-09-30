#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "parsers/parser.h"
#include "parsers/lexer.h"

static const int START_STACK_SIZE = 1024;
static const int MAX_PARSERS_OPTIONS = 64000;
static const int END_OF_INPUT = -1;

enum ParseResult
{
  ERROR = -1,
  ACCEPTED = 0,
  SHIFT = 1,
  REDUCE = 2
};

struct AllParsers
{
  Parser* parsers;
  int parserCount;
};

Token* newToken()
{
  Token* token = malloc(sizeof(Token));
  memset(token, 0, sizeof(Token));
  return token;
}

static Parser* createParser(AllProductions* allProductions, Production* (*creationFunction)(AllProductions*), AllParsers* allParsers)
{
  allParsers->parserCount = 0;
  allParsers->parsers = malloc(MAX_PARSERS_OPTIONS*sizeof(Parser));
  Parser* ret = &allParsers->parsers[allParsers->parserCount++];

  ret->pos = 0;
  ret->stackSize = START_STACK_SIZE;
  
  int size = (ret->stackSize+1)*sizeof(int);
  ret->stateStack = malloc(size);
  memset(ret->stateStack, 0, size);
  size = (ret->stackSize+1)*sizeof(ProductionNode);
  ret->nodesStack = malloc(size);
  memset(ret->nodesStack, 0, size);
  ret->nextOption = nullptr;
  ret->hasError = false;

  ret->allParsers = allParsers;
  ret->productionCreator = creationFunction;
  ret->allProductions = allProductions;

  return ret;
}

static Parser* createParserOption(Parser* old)
{
  Parser* newParser = &old->allParsers->parsers[old->allParsers->parserCount++];
  
  newParser->pos = old->pos;
  newParser->stackSize = old->stackSize;
  newParser->nextOption = old->nextOption;
  old->nextOption = newParser;
  newParser->hasError = old->hasError;
  newParser->token = old->token;

  newParser->stateStack = malloc((newParser->stackSize+1) * sizeof(int));
  newParser->nodesStack = malloc((newParser->stackSize+1) * sizeof(ProductionNode));
  newParser->allParsers = old->allParsers;
  newParser->productionCreator = old->productionCreator;
  newParser->allProductions = old->allProductions;

  for(int i = 0; i <= newParser->pos + 1; i++)
  {
    newParser->stateStack[i] = old->stateStack[i];
    newParser->nodesStack[i] = old->nodesStack[i];
  }
  
  return newParser;
}

static void checkAndIncreaseStacks(Parser* parser)
{
  if(parser->pos >= parser->stackSize -1)
  {
    parser->stackSize = parser->stackSize*2;
    parser->stateStack = realloc(parser->stateStack, (parser->stackSize+1) * sizeof(int));
    parser->nodesStack = realloc(parser->nodesStack, (parser->stackSize+1) * sizeof(ProductionNode));
  }
}

Action createShift(int token, int targetState)
{
  Action action;
  
  action.accept = false;
  action.isShift = true;
  action.expectedToken = token;
  action.shiftTo = targetState;

  return action;
}

static Action createReduce(int token, int* productions, int* prodTypes, int* nodeCounts, int optionsCount)
{
  Action action;
  
  action.accept = false;
  action.isShift = false;
  action.expectedToken = token;
  action.optionsCount = optionsCount;
  for(int i = 0; i < optionsCount; i++)
  {
    action.productionOptions[i] = productions[i];
    action.productionTypes[i] = prodTypes[i];
    action.productionNodeCount[i] = nodeCounts[i];
  }

  return action;
}

Action createReduce1(int token, int prodIndex0, int prodType0, int nodeCount0)
{
  int indexes[] = { prodIndex0 };
  int prodTypes[] = { prodType0 };
  int nodeCounts[] = { nodeCount0 };
  return createReduce(token, indexes, prodTypes, nodeCounts, 1);
}

Action createReduce2(int token, int prodIndex0, int prodIndex1,
                     int prodType0, int prodType1,
                     int nodeCount0, int nodeCount1)
{
  int indexes[] = { prodIndex0, prodIndex1 };
  int prodTypes[] = { prodType0, prodType1 };
  int nodeCounts[] = { nodeCount0, nodeCount1 };
  return createReduce(token, indexes, prodTypes, nodeCounts, 2);
}

Action createReduce3(int token, int prodIndex0, int prodIndex1, int prodIndex2,
                     int prodType0, int prodType1, int prodType2,
                     int nodeCount0, int nodeCount1, int nodeCount2)
{
  int indexes[] = { prodIndex0, prodIndex1, prodIndex2 };
  int prodTypes[] = { prodType0, prodType1, prodType2 };
  int nodeCounts[] = { nodeCount0, nodeCount1, nodeCount2 };
  return createReduce(token, indexes, prodTypes, nodeCounts, 3);
}

Action createReduce4(int token, int prodIndex0, int prodIndex1, int prodIndex2, int prodIndex3,
                     int prodType0, int prodType1, int prodType2, int prodType3,
                     int nodeCount0, int nodeCount1, int nodeCount2, int nodeCount3)
{
  int indexes[] = { prodIndex0, prodIndex1, prodIndex2, prodIndex3 };
  int prodTypes[] = { prodType0, prodType1, prodType2, prodType3};
  int nodeCounts[] = { nodeCount0, nodeCount1, nodeCount2, nodeCount3 };
  return createReduce(token, indexes, prodTypes, nodeCounts, 4);
}

Action createAcceptAction()
{
  Action action;
  
  action.accept = true;
  action.isShift = false;
  action.optionsCount = 0;
  action.expectedToken = END_OF_INPUT;
  return action;
}

State createState(Action* actions, int actionCount)
{
  State state;

  state.actions = actions;
  state.actionCount = actionCount;

  return state;
}

static ProductionNode createTokenNode(Token* token)
{
  ProductionNode node;

  node.token = token;
  node.production = nullptr;

  return node;
}

static ProductionNode createProductionNode(Production* production)
{
  ProductionNode node;

  node.token = nullptr;
  node.production = production;

  return node;
}

static void reduce(int (*goToTable)(int, int), Parser* parser, Action* action, int index)
{
  Production* reduction = parser->productionCreator(parser->allProductions);
  reduction->type = action->productionTypes[index];
  int nodeCount = action->productionNodeCount[index];
  reduction->nodeCount = nodeCount;
  for(int i = 0; i < nodeCount; i++)
  {
    reduction->nodes[i] = parser->nodesStack[parser->pos - nodeCount + i];
  }

  parser->pos -= nodeCount;
  parser->nodesStack[parser->pos] = createProductionNode(reduction);
  parser->pos++;
  parser->stateStack[parser->pos] = goToTable(parser->stateStack[parser->pos-1], action->productionOptions[index]);
}

static void createReduceOptions(int (*goToTable)(int, int), Parser* parser, Action* action)
{
  for(int i = 1; i < action->optionsCount; i++)
  {
    Parser* copy = createParserOption(parser);
    reduce(goToTable, copy, action, i);
  }

  reduce(goToTable, parser, action, 0);
}

static Action* findAction(State* state, int tokenType)
{
  // TODO should be a binary search
  for(int i = 0; i < state->actionCount; i++)
  {
    if(tokenType == state->actions[i].expectedToken)
    {
      return &state->actions[i];
    }
  }
  return nullptr;
}

static int parseStep(State* states,  int (*goToTable)(int, int), Parser* parser, Token* token)
{
  State* state = &states[parser->stateStack[parser->pos]];

  int tokenType = END_OF_INPUT;
  if(token != nullptr)
  {
    tokenType = token->type;
  }

  Action* action = findAction(state, tokenType);
  if(action != nullptr)
  {
    if(action->isShift)
    {
      parser->nodesStack[parser->pos] = createTokenNode(token);
			parser->pos++;
			parser->stateStack[parser->pos] = action->shiftTo;
			token = token->next;

      return SHIFT;
    }
    else if(!action->accept)
    { 
      createReduceOptions(goToTable, parser, action);

      return REDUCE;
    }
    else 
      return ACCEPTED;
  }
  else
  {
    return ERROR;
  }
}

static inline bool isRelevantToken(Token* token)
{
  return !token->ignored;
}

static void showGrammarStack(Parser* parser)
{
  int aux = parser->pos;
  while(aux){ printf("->%i\n", parser->stateStack[aux--]); }
}

static Parser* getMainErrorParser(Parser* parser)
{
  int targetError = 0;
	int longest = 0;
 
  AllParsers* all = parser->allParsers;

  for(int i = 0; i < all->parserCount; i++)
  {
    Parser* current = &all->parsers[i];
    if(current->hasError)
    {
      if(current->token == nullptr){ targetError = i; break; }
      if(current->token->line > longest)
      {
        longest = current->token->line;
        targetError = i;
      }
    }
  }
  
  return &all->parsers[targetError];
}

Production* getMainProduction(Parser* parser)
{
  if(parser->hasError)
    return nullptr;
  else
    return parser->nodesStack[0].production;
}

bool reduceNodes(Production* production, bool* nodeRedundancyTable)
{
  for(int i = 0; i < production->nodeCount; i++)
  {
    Production* aux = production->nodes[i].production;
    if(aux != nullptr)
    {
      if(reduceNodes(aux, nodeRedundancyTable))
      {
        production->nodes[i].production = aux->nodes[0].production;
        aux->nodes[0].production = nullptr;
      }
    }
  }

  return nodeRedundancyTable[production->type];
}

int getProductionList(Production* production, Production** outList)
{
  bool recursion = false;
  int numProds = 0;

  int currentIndex = 0;

  for(int i = 0; i < production->nodeCount; i++)
    if(production->nodes[i].production) numProds++;
  
  for(int i = 0; i < production->nodeCount; i++)
  {
    Production* prod = production->nodes[i].production;
    if(prod)
    {
      if(recursion || numProds == 1)
      {
        if(outList != nullptr) outList[currentIndex] = prod;
        currentIndex++;
      }
      else
      {
        recursion = true;
        currentIndex = getProductionList(prod, outList);
      }
    }
  }

  return currentIndex;
}

int getProductionListSize(Production* production)
{
  return getProductionList(production, nullptr);
}

bool visitNodes(Production* production, VisitData* visitData, VisitFunction visitFunction)
{
  for(int i = 0; i < production->nodeCount; i++)
  {
    Production* child = production->nodes[i].production;
    if(child != nullptr)
    {
      if(!visitFunction(child, visitData)) return false;
    }
  }

  return true;
}

void freeParser(Parser* parser)
{
  free(parser->nodesStack);
  free(parser->stateStack);
}

static void freeOtherParsers(Parser* parser)
{
  AllParsers* all = parser->allParsers;
  for(int i = 0; i < all->parserCount; i++)
  {
    if(&all->parsers[i] != parser)
    {
      freeParser(&all->parsers[i]);
    }
  }
  free(all->parsers);
}

Parser parse(AllProductions* allProductions, Production* (*creationFunction)(AllProductions*), State* states, int (*goToTable)(int, int), Token* token)
{
  AllParsers allParsers;
  Parser* parser = createParser(allProductions, creationFunction, &allParsers);
  while(parser->pos >= 0)
  {
    if(token == nullptr || isRelevantToken(token))
    {
      checkAndIncreaseStacks(parser);
      parser->token = token;
      int result = parseStep(states, goToTable, parser, token);
      if(result == SHIFT)
      {
        token = token->next;
        continue;
      }
      else if(result == REDUCE)
        continue;
      else if(result == ACCEPTED)
        break;
      else
      {
#ifdef SHOW_GRAMMAR_STACK
				showGrammarStack(parser);
#endif
        parser->hasError = true;
        if(parser->nextOption)
        {
          parser = parser->nextOption;
          token = parser->token;
          continue;
        }

        parser = getMainErrorParser(parser);
        break;
      }
    }
    else
    {
      token = token->next;
    }
  }

  Parser ret = *parser;
  ret.nextOption = nullptr;
  ret.allParsers = nullptr;
  freeOtherParsers(parser);
  return ret;
}
