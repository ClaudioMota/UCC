#include "generation/generation.h"
#include "basics.h"
#include "stdio.h"
#include "grammar/grammar.h"

static char* generationPath = "output/";
static char* baseOutputPath = "output/parsers/";
static char* linkToRepo = "https://github.com/ClaudioMota/UCC";

static void generateHeaderGuardsStart(FILE* file, char* headerTitle)
{
  char fullTitle[STRING_LENGTH*3];
  strcpy(fullTitle, headerTitle);
  strcat(fullTitle, "_HEADER");
  fprintf(file, "#ifndef %s\n", fullTitle);
  fprintf(file, "#define %s 1\n", fullTitle);
  fprintf(file, "#ifdef __cplusplus\n");
  fprintf(file, "extern \"C\" {\n");
  fprintf(file, "#endif\n\n");
}

static void generateHeaderGuardsEnd(FILE* file)
{
  fprintf(file, "\n#ifdef __cplusplus\n");
  fprintf(file, "}\n");
  fprintf(file, "#endif\n");
  fprintf(file, "#endif\n");
}

static void generatedFileDisclaimer(FILE* file)
{
  fprintf(file, "// This file was generated by UCC. Manual changes are discouraged as they may be overwritten in future generations.\n");
  fprintf(file, "// See %s for more in information.\n\n", linkToRepo);
}

static bool generateParserHeader(FILE* file, Grammar* grammar, char* namespace)
{
  char headerTitle[STRING_LENGTH*2];
  strcpy(headerTitle, namespace);
  strcat(headerTitle, "_PARSER");

  generatedFileDisclaimer(file);
  generateHeaderGuardsStart(file, headerTitle);
  
  fprintf(file, "enum %s_Tokens\n{\n  %s_T_UNKNOWN = -2,\n  %s_T_END_OF_INPUT = -1", namespace, namespace, namespace);
  for(int i = 0; i < grammar->tokenCount; i++)
    fprintf(file, ",\n  %s_T_%s", namespace, grammar->tokens[i].name);
  fprintf(file, "\n};\n\n");

  fprintf(file, "extern int (**%s_lexerFunctions)(int* state, int input);\n", namespace);
  fprintf(file, "extern int %s_lexerFunctionCount;\n\n", namespace);
  fprintf(file, "bool %s_shouldIgnoreToken(Token* token);\n", namespace);
  fprintf(file, "bool %s_visit(Production* production, VisitData* visitData);\n", namespace);
  fprintf(file, "bool %s_visitNodes(Production* production, VisitData* visitData);\n", namespace);
  fprintf(file, "extern bool %s_nodeRedundancyTable[];\n\n", namespace);
  fprintf(file, "Parser %s_parse(Token* tokens, int productionStructSize);\n", namespace);

  generateHeaderGuardsEnd(file);

  return true;
}

static void generateTokenFunction(FILE* file, TokenExpr* token)
{
  fprintf(file, "static int func_%s(int* state, int input)\n{\n", token->name);
  fprintf(file, "  switch(*state)\n  {\n");
  for(int i = 0; i < token->stateMachine.stateCount; i++)
  {
    StateMachineState* state = token->stateMachine.states[i];
    fprintf(file, "    case %i:\n", state->index);
    fprintf(file,"    switch(input)\n    {\n      ");
    for(int j = 0; j < state->transitionCount; j++)
    {
      StateMachineTransition* transition = &state->transitions[j];
      for(int k = 0; k < SUPPORTED_CHARACTERS; k++)
        if(transition->values[k])
          fprintf(file,"case %i: ", k);
      fprintf(file,"*state = %i; break;\n      ", transition->target->index);
    }

    fprintf(file,"default: *state = LEXER_ERROR;\n    }\n    break;\n");
  }

  fprintf(file,"    default: *state = LEXER_ERROR;\n  }\n");
  fprintf(file, "  if(*state == LEXER_ERROR) return LEXER_ERROR;\n  switch(*state)\n  {\n    ");
  for(int i = 0; i < token->stateMachine.stateCount; i++)
    if(token->stateMachine.states[i]->accepted)
      fprintf(file,"case %i: ", i);

  fprintf(file,"return LEXER_ACCEPTED;\n    default: return LEXER_PROCESSING;\n  }\n}\n\n");
}

static void generateLexerSource(FILE* file, Grammar* grammar, char* namespace)
{
  for(int i = 0; i < grammar->tokenCount; i++) generateTokenFunction(file, &grammar->tokens[i]);

  fprintf(file, "static int (*functions[])(int* state, int input) = {");
  for(int i = 0; i < grammar->tokenCount; i++)
  {
    if(i) fprintf(file, ",");
    fprintf(file, "\n  func_%s", grammar->tokens[i].name);
  }

  fprintf(file, "\n};\n\nint (**%s_lexerFunctions)(int* state, int input) = functions;\n", namespace);
  fprintf(file, "int %s_lexerFunctionCount = %i;\n\n", namespace, grammar->tokenCount);
  fprintf(file, "bool %s_shouldIgnoreToken(Token* token)\n{\n  switch(token->type){\n    ", namespace);

  bool hasIgnored = false;
  for(int i = 0; i < grammar->tokenCount; i++)
    if(grammar->tokens[i].ignored)
    {
      hasIgnored = true;
      fprintf(file, "case %i: ", grammar->tokens[i].index);
    }
  if(hasIgnored) fprintf(file, "return true;\n    ");
  fprintf(file, "default: return false;\n  }\n");
  fprintf(file, "}\n\n");
}

static int getProductionFullName(ProductionOption* production, Grammar* grammar, char* output)
{
  int ret = 0;
  ProductionExpr* prodExpr = Grammar_getReduced(grammar, production->base);
  if(!prodExpr) prodExpr = production->base; 
  ret += strlen(prodExpr->name);
  if(output) strcpy(output, prodExpr->name);
  
  for(int i = 0; i < production->stepCount; i++)
  {
    ret++;
    if(output) strcat(output, "_");
    if(production->steps[i].token)
    {
      ret += strlen(production->steps[i].token->name);
      if(output) strcat(output, production->steps[i].token->name);
    }
    else
    {
      prodExpr = Grammar_getReduced(grammar, production->steps[i].production);
      if(!prodExpr) prodExpr = production->steps[i].production;
      ret += strlen(prodExpr->name);
      if(output) strcat(output, prodExpr->name);
    }
  }
  
  return ret;
}

static int maybeMapFullName(char* fullName, char** mappedFullNames, int* mapSize)
{
  for(int k = 0; k < *mapSize; k++)
    if(strcmp(mappedFullNames[k], fullName) == 0)
      return k;

  int length = strlen(fullName);
  char* copy = new(sizeof(char)*(length + 1));
  strcpy(copy, fullName);
  mappedFullNames[*mapSize] = copy;
  return (*mapSize)++;
}

static int createProductionFullNameMaps(Grammar* grammar, char*** fullNamesP, int** prodToFullNameP, int** mapOptionToFullNameP)
{
  int optionIndex = 0, mapSize = 0;
  int maxFullNames = grammar->productionCount;
  for(int i = 0; i < grammar->productionCount; i++)
    maxFullNames += grammar->productions[i].optionCount;

  char** mappedFullNames = new(sizeof(char*)*maxFullNames);
  int* prodToFullName = new(sizeof(int)*grammar->productionCount);
  int* mapOptionToFullName = new(sizeof(char*)*maxFullNames);
  memset(mappedFullNames, 0, sizeof(char*)*maxFullNames);
  memset(prodToFullName, 0, sizeof(int)*grammar->productionCount);
  memset(mapOptionToFullName, 0, sizeof(int)*maxFullNames);

  for(int i = 0; i < grammar->productionCount; i++)
  {
    ProductionExpr* prodExpr = Grammar_getReduced(grammar, &grammar->productions[i]);
    if(!prodExpr) prodExpr = &grammar->productions[i];
    char fullName[STRING_LENGTH + 1];
    strcpy(fullName, prodExpr->name);
    prodToFullName[i] = maybeMapFullName(fullName, mappedFullNames, &mapSize);

    for(int j = 0; j < grammar->productions[i].optionCount; j++)
    {
      ProductionOption* option = &grammar->productions[i].options[j];
      int length = getProductionFullName(option, grammar, nullptr);
      char fullName[length + 1];
      fullName[0] = '\0';
      getProductionFullName(option, grammar, fullName);
      mapOptionToFullName[optionIndex++] = maybeMapFullName(fullName, mappedFullNames, &mapSize);
    }
  }

  *fullNamesP = mappedFullNames;
  *prodToFullNameP = prodToFullName;
  *mapOptionToFullNameP = mapOptionToFullName;
  return mapSize;
}

static void generateProductionsHeader(FILE* file, Grammar* grammar, LalrMachine* lalrMachine, char* namespace)
{
  char headerTitle[STRING_LENGTH*2];
  strcpy(headerTitle, namespace);
  strcat(headerTitle, "_PRODUCTIONS");
  generatedFileDisclaimer(file);
  generateHeaderGuardsStart(file, headerTitle);

  char** fullNames;
  int* mapOptionToFullName, *mapProdToFullName;
  int fullNameCount = createProductionFullNameMaps(grammar, &fullNames, &mapProdToFullName, &mapOptionToFullName);

  // Visit functions
  char* visitType = "extern VisitFunction ";
  fprintf(file, "%s%s_visit_defaultFunction;\n\n", visitType, namespace);
  for(int i = 0; i < fullNameCount; i++)
    fprintf(file, "%s%s_visit_%s;\n", visitType, namespace, fullNames[i]);

  // Productions enum
  fprintf(file, "\nenum %s_ProductionType\n{\n  %s_P_UNKNOWN", namespace, namespace);
  for(int i = 0; i < fullNameCount; i++)
  {
    bool isBaseProdName = false;
    for(int j = 0; j < grammar->productionCount; j++)
      if(mapProdToFullName[j] == i) isBaseProdName = true;
    if(!isBaseProdName) fprintf(file, ",\n  %s_P_%s", namespace, fullNames[i]);
  }
  fprintf(file, "\n}\n");

  // Productions structs
  int optionIndex = 0;
  for(int i = 0; i < grammar->productionCount; i++)
    for(int j = 0; j < grammar->productions[i].optionCount; j++)
    {
      ProductionOption* prod = &grammar->productions[i].options[j];
      char* fullName = fullNames[mapOptionToFullName[optionIndex]];
      fprintf(file, "\ntypedef struct \n{\n  int type;\n  int nodeCount;\n");
      for(int k = 0; k < prod->stepCount; k++)
      {
        char* stepName;
        if(prod->steps[k].token) stepName = prod->steps[k].token->name;
        else
        {
          ProductionExpr* prodExpr = Grammar_getReduced(grammar, prod->steps[k].production);
          if(!prodExpr) prodExpr = prod->steps[k].production;
          stepName = prodExpr->name;
        }
        fprintf(file, "  ProductionNode %s%i\n", stepName, k);
      }
      fprintf(file, "} %s_%s;\n", namespace, fullName);
      optionIndex++;
    }

  generateHeaderGuardsEnd(file);

  for(int i = 0; i < fullNameCount; i++)
    if(fullNames[i]) delete(fullNames[i]);
  delete(mapProdToFullName);
  delete(mapOptionToFullName);
  delete(fullNames);
}

static void generateProductionsSource(FILE* file, Grammar* grammar, LalrMachine* lalrMachine, char* namespace)
{
  char** fullNames;
  int* mapOptionToFullName, *mapProdToFullName;
  int fullNameCount = createProductionFullNameMaps(grammar, &fullNames, &mapProdToFullName, &mapOptionToFullName);
  bool* shouldReduce = new(sizeof(bool)*fullNameCount);

  // Visit functions
  char* visitType = "VisitFunction ";
  fprintf(file, "%s%s_visit_defaultFunction = %s_visitNodes;\n\n", visitType, namespace, namespace);
  for(int i = 0; i < fullNameCount; i++)
    fprintf(file, "%s%s_visit_%s = nullptr;\n", visitType, namespace, fullNames[i]);

  fprintf(
    file, "\nbool %s_visitNodes(Production* production, VisitData* visitData){ return visitNodes(production, visitData, %s_visit);}\n", namespace, namespace);
  
  // Node redundancy table
  int optionIndex = 0;
  for(int i = 0; i < grammar->productionCount; i++)
    for(int j = 0; j < grammar->productions[i].optionCount; j++)
    {
      ProductionOption* prodOption = &grammar->productions[i].options[j];
      int reducedIndex = mapOptionToFullName[optionIndex];
      shouldReduce[reducedIndex] = false;
      if(prodOption->stepCount == 1 && prodOption->steps[0].production)
      {
        ProductionExpr* base = Grammar_getReduced(grammar, &grammar->productions[i]);
        if(!base) base = &grammar->productions[i];
        ProductionExpr* step = Grammar_getReduced(grammar, prodOption->steps[0].production);
        if(!step) step = prodOption->steps[0].production;
        shouldReduce[reducedIndex] = base == step;
      }
      optionIndex++;
    }
  
  fprintf(file, "\nbool %s_nodeRedundancyTable[] = {\n  false, // UNKNOWN\n", namespace);
  for(int i = 0; i < fullNameCount; i++)
  {
    bool isBaseProdName = false;
    for(int j = 0; j < grammar->productionCount; j++)
      if(mapProdToFullName[j] == i) isBaseProdName = true;
    if(!isBaseProdName)
      fprintf(file, "  %s%s //%s\n", shouldReduce[i] ? "true" : "false", i < fullNameCount -1 ? "," : "", fullNames[i]);
  }
  fprintf(file, "}\n");

  // visit function
  fprintf(file, "\nbool %s_visit(Production* production, VisitData* visitData)\n{\n", namespace);
  fprintf(file, "  %s visitFunction = nullptr;\n  switch(production->type)\n  {\n", visitType);
  for(int i = 0; i < fullNameCount; i++)
  {
    bool isBaseProdName = false;
    for(int j = 0; j < grammar->productionCount; j++)
      if(mapProdToFullName[j] == i) isBaseProdName = true;
    if(!isBaseProdName)
      fprintf(file, "    case %s_P_%s: visitFunction = %s_visit_%s; break;\n", namespace, fullNames[i], namespace, fullNames[i]);
  }
  fprintf(file, "  }\n  if(visitFunction != nullptr) return visitFunction(production, visitData);\n\n");
  fprintf(file, "  switch(production->type)\n  {\n");
  char* lastBaseProdFullName = nullptr;
  for(int i = 0; i < fullNameCount; i++)
  {
    bool isBaseProdName = false;
    for(int j = 0; j < grammar->productionCount; j++)
      if(mapProdToFullName[j] == i) isBaseProdName = true;
    if(isBaseProdName) lastBaseProdFullName = fullNames[i];
    else fprintf(file, "    case %s_P_%s: visitFunction = %s_visit_%s; break;\n", namespace, fullNames[i], namespace, lastBaseProdFullName);
  }
  fprintf(file, "  }\n  if(visitFunction != nullptr) return visitFunction(production, visitData);\n\n");
  fprintf(file, "  return %s_visit_defaultFunction(production, visitData);\n}\n\n", namespace);

  for(int i = 0; i < fullNameCount; i++)
    if(fullNames[i]) delete(fullNames[i]);
  delete(mapProdToFullName);
  delete(mapOptionToFullName);
  delete(shouldReduce);
  delete(fullNames);
}

static void generateParserSource(FILE* file, Grammar* grammar, LalrMachine* lalrMachine, char* namespace)
{
  generatedFileDisclaimer(file);

  fprintf(file, "#include \"parsers/lexer.h\"\n");
  fprintf(file, "#include \"parsers/parser.h\"\n");
  fprintf(file, "#include \"%s/parsers/productions.h\"\n", namespace);
  
  generateLexerSource(file, grammar, namespace);
  generateProductionsSource(file, grammar, lalrMachine, namespace);
}

bool generateGrammar(Grammar* grammar, LalrMachine* lalrMachine, char* namespace)
{
  char finalBasePath[STRING_LENGTH*3];

  strcpy(finalBasePath, baseOutputPath);
  strcat(finalBasePath, namespace);
  strcat(finalBasePath, "/");

  createDirectory(generationPath);
  createDirectory(baseOutputPath);
  createDirectory(finalBasePath);

  FILE* file = createFile(finalBasePath, "parser.h");
  if(!file) return false;
  generateParserHeader(file, grammar, namespace);
  closeFile(file);

  file = createFile(finalBasePath, "productions.h");
  if(!file) return false;
  generateProductionsHeader(file, grammar, lalrMachine, namespace);
  closeFile(file);

  file = createFile(finalBasePath, "parser.c");
  if(!file) return false;
  generateParserSource(file, grammar, lalrMachine, namespace);
  closeFile(file);

  return true;
}
