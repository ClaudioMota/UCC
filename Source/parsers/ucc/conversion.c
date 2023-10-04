#include "basics.h"
#include "parsers/lexer.h"
#include "parsers/parser.h"
#include "parsers/ucc/conversion.h"
#include "parsers/ucc/production.h"
#include "parsers/ucc/productions.h"

#include "grammar.h"

static inline UCCProduction* uccProduction(Production* prod){ return (UCCProduction*)prod; }

static inline void copyResult(UCCProduction* dest, UCCProduction* src)
{
  memcpy(dest->helperValue, src->helperValue, SUPPORTED_CHARACTERS);
  dest->helper = src->helper;
  dest->token = src->token;
  dest->production = src->production;
  dest->reducer = src->reducer;
}

static bool visitHelper(ucc_Helper_identifier_attrib_Expr_semicolon* production, VisitData* visitData)
{
  visitData->mode = MODE_HELPER;
  bool ret = ucc_visit_defaultFunction((Production*)production, visitData);
 
  if(ret)
  {
    Helper* decl = Grammar_declareHelper(visitData->grammar, production->T_identifier0.token->content);
    if(!decl) return compilerError("Could not declare helper", production->T_identifier0.token);
    memcpy(decl->values, ((UCCProduction*)production->Expr2.production)->helperValue, SUPPORTED_CHARACTERS);
  }

  return ret;
}

static void setHelperValue(int index, char value, char* outValue)
{
  if(index >= 0 && index < SUPPORTED_CHARACTERS)
    outValue[index] = value;
}

static int getLiteralAsInteger(Production* literal)
{
  Token* token = literal->nodes[0].token;
  int len = strlen(token->content);
  char actual[len];

  switch(literal->type)
  {
    case ucc_P_Literal_decimal: return atoi(token->content);
    case ucc_P_Literal_charLiteral:
      if(len >= 3) return getStringActualContent(actual, token->content)[0];
    default:
      return 0;
  }
}

static bool calcHelperValue(UCCProduction* production)
{
  switch(production->type)
  {
    case ucc_P_Expr_Literal_to_Literal:
    {
      int start = getLiteralAsInteger(production->nodes[0].production);
      int end = getLiteralAsInteger(production->nodes[2].production);
      for(int i = start; i <= end; i++)
        setHelperValue(i, 1, production->helperValue);
    }
    break;
    case ucc_P_Expr_Literal:
    {
      int index = getLiteralAsInteger(production->nodes[0].production);
      setHelperValue(index, 1, production->helperValue);
    }
    break;
    case ucc_P_Expr_identifier:
    {
      memcpy(production->helperValue, ((Helper*)production->helper)->values, SUPPORTED_CHARACTERS);
    }
    break;
  }

  return true;
}

static bool visitExpr(Production* production, VisitData* visitData)
{
  bool ret = ucc_visit_defaultFunction((Production*)production, visitData);
 
  if(!ret) return ret;

  if(production->type == ucc_P_Expr_o_parentheses_Expr_c_parentheses)
  {
    copyResult(uccProduction(production), uccProduction(production->nodes[1].production));
    return ret;
  }
  switch(visitData->mode)
  {
    case MODE_HELPER: return calcHelperValue(uccProduction(production)); break;
    default:
  }

  return ret;
}

static bool visitIdentifierExpr(UCCProduction* production, VisitData* visitData)
{
  char* name = production->nodes[0].token->content;

  if(visitData->mode == MODE_PRODUCTION) return visitExpr((Production*)production, visitData);

  production->helper = Grammar_getHelper(visitData->grammar, name);
  if(production->helper) return visitExpr((Production*)production, visitData);

  production->token = Grammar_getToken(visitData->grammar, name);
  if(production->token) return visitExpr((Production*)production, visitData);

  production->production = Grammar_getProduction(visitData->grammar, name);
  if(production->production) return visitExpr((Production*)production, visitData);

  return compilerError("Could not find reference", production->nodes[0].token);
}

static StateMachineState* createStateMachineStates(Production* expr, StateMachine* stateMachine, StateMachineState* current)
{
  switch(expr->type)
  {
    case ucc_P_Expr_Expr_Expr:
    {
      StateMachineState* end = createStateMachineStates(expr->nodes[0].production, stateMachine, current);
      return createStateMachineStates(expr->nodes[1].production, stateMachine, end);
    }
    case ucc_P_Expr_Expr_Op:
    {
      StateMachineState* end = createStateMachineStates(expr->nodes[0].production, stateMachine, current);
      if(expr->nodes[1].production->type != ucc_P_Op_question)
        if(failIfNull(StateMachine_addTransition(stateMachine, end, current, 0), "Could not create transitions"))
          return current;
      if(expr->nodes[1].production->type == ucc_P_Op_sum)
        return end;
      else
        return current;
    }
    case ucc_P_Expr_Expr_Op_Expr:
    {
      StateMachineState* firstEnd = createStateMachineStates(expr->nodes[0].production, stateMachine, current);
      StateMachineState* secondEnd = createStateMachineStates(expr->nodes[2].production, stateMachine, current);
      StateMachineState* end = StateMachine_createState(stateMachine);
      if(failIfNull(end, "Could not create state")) return current;
      if(failIfNull(StateMachine_addTransition(stateMachine, firstEnd, end, 0), "Could not create transitions"))
        return current;
      if(failIfNull(StateMachine_addTransition(stateMachine, secondEnd, end, 0), "Could not create transitions"))
        return current;
      return end;
    }
    case ucc_P_Expr_identifier:
    {
      StateMachineState* end = StateMachine_createState(stateMachine);
      if(failIfNull(end, "Could not create state")) return current;
      Helper* helper = uccProduction(expr)->helper;
      if(failIfNull(helper, "When defining a token identifiers must be a helper")) return current;
      for(int i = 0; i < SUPPORTED_CHARACTERS; i++)
        if(helper->values[i])
          if(failIfNull(StateMachine_addTransition(stateMachine, current, end, i), "Could not create transitions"))
            return current;
      return end;
    }
    case ucc_P_Expr_Literal:
    {
      Token* token = expr->nodes[0].production->nodes[0].token;
      int len = strlen(token->content);
      char actual[len];
      len = strlen(getStringActualContent(actual, token->content));
      for(int i = 0; i < len; i++)
      {
        StateMachineState* s = StateMachine_createState(stateMachine);
        if(failIfNull(StateMachine_addTransition(stateMachine, current, s, actual[i]), "Could not create transitions"))
          return current;
        current = s;
      }
      return current;
    }
    case ucc_P_Expr_o_parentheses_Expr_c_parentheses:
      return createStateMachineStates(expr->nodes[1].production, stateMachine, current);
  }
}

static bool visitToken(UCCProduction* production, VisitData* visitData)
{
  visitData->mode = MODE_TOKEN;
  bool ret = ucc_visit_defaultFunction((Production*)production, visitData);

  if(ret)
  {
    int offset = (production->type == ucc_P_Token_identifier_attrib_Expr_semicolon) ? 0 : 1;
    Token* token =  production->nodes[offset].token;
    TokenExpr* decl = Grammar_declareToken(visitData->grammar, token->content, offset == 1);
    if(!decl) return compilerError("Could not declare token", token);

    StateMachineState* last = createStateMachineStates(production->nodes[offset + 2].production, &decl->stateMachine, decl->stateMachine.start);
    last->accepted = true;
  }

  return ret;
}

static int getInlineProductions(Production* expr, Production** out)
{
  int index = 0;
  if(expr && expr->nodeCount > 2 && expr->nodes[1].production && expr->nodes[1].production->type == ucc_P_Op_or)
  {
    index = getInlineProductions(expr->nodes[0].production, out);
    out[index++] = expr->nodes[2].production;
  }
  else
    out[index++] = expr;

  return index;
}

static int countProdPossibilities(Production* expr)
{
  int ret = 1;
  for(int i = 0; i < expr->nodeCount; i++)
  {
    if(expr->nodes[i].production)
      ret *= countProdPossibilities(expr->nodes[i].production);
    if(expr->type == ucc_P_Op_question)
      ret *= 2;
  }

  return ret;
}

static int getProdPossibility(Production* expr, int* index, char** steps, int stepIndex)
{
  if(expr->type == ucc_P_Expr_Expr_Op)
  {
    if((*index & 1) == 0) return stepIndex;
    *index >>= 2;
  }

  for(int i = 0; i < expr->nodeCount; i++)
  {
    if(expr->nodes[i].production)
      stepIndex = getProdPossibility(expr->nodes[i].production, index, steps, stepIndex);
    else if(expr->nodes[i].token && expr->type == ucc_P_Expr_identifier)
    {
      strcpy(steps[stepIndex++], expr->nodes[i].token->content);
    }
  }

  return stepIndex;
}

static bool visitProduction(ucc_Production_identifier_attrib_Expr_semicolon* production, VisitData* visitData)
{
  visitData->mode = MODE_PRODUCTION;
  bool ret = ucc_visit_defaultFunction((Production*)production, visitData);

  if(ret)
  {
    Production* prods[ELEMENTS_MAX];
    int prodsCount = getInlineProductions(production->Expr2.production, prods);
    for(int i = 0; i < prodsCount; i++)
    {
      int possibilityCount = countProdPossibilities(prods[i]);
      for(int p = 0; p < possibilityCount; p++)
      {
        char stepsNames[MAX_PRODUCTION_LENGTH][STRING_LENGTH];
        char* steps[MAX_PRODUCTION_LENGTH];
        for(int s = 0; s < MAX_PRODUCTION_LENGTH; s++) steps[s] = stepsNames[s];
        int index = p;
        int stepCount = getProdPossibility(prods[i], &index, steps, 0);
        
        ProductionExpr* decl = Grammar_addProduction(visitData->grammar, production->T_identifier0.token->content, stepCount, steps);
        if(!decl) return compilerError("Could not declare production", production->T_identifier0.token);
      }
    }
  }

  return ret;
}

static bool visitReducer(UCCProduction* production, VisitData* visitData)
{
  visitData->mode = MODE_REDUCE;
  bool ret = ucc_visit_defaultFunction((Production*)production, visitData);

  if(ret)
  {
    //ProductionExpr* decl = Grammar_reduce(visitData->grammar, );
    //if(!decl) return compilerError("Could not declare token", production->T_identifier0.token);
  }

  return ret;
}

void setupVisitFunctions()
{
  ucc_visit_Helper_identifier_attrib_Expr_semicolon = (void*)visitHelper;
  ucc_visit_Token = (void*)visitToken;
  ucc_visit_Production_identifier_attrib_Expr_semicolon = (void*)visitProduction;
  ucc_visit_Reducer = (void*)visitReducer;
  ucc_visit_Expr_identifier = (void*)visitIdentifierExpr;
  ucc_visit_Expr = (void*)visitExpr;
}

