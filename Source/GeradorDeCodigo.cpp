#include <GeradorDeCodigo.h>
#include <map>

static std::string nameSpace = "";
static std::string dirBase = "";

static const std::string endGuard = "#endif\n";
static const std::string endNamespace = "}\n";
static const std::string endOfInputToken = "END_OF_INPUT";

static const std::string externCGuard = "#ifdef __cplusplus\nextern \"C\" {\n#endif\n";
static const std::string externCGuardEnd = "#ifdef __cplusplus\n}\n#endif\n";

void writeToFile(std::string fileName, std::string content)
{
  FILE* file = fopen(fileName.c_str(), "wb");
  if(file == NULL) return;
  fprintf(file, content.c_str());
  fclose(file);
}

std::string includeGuard(std::string guardName)
{
  return std::string("#ifndef ") + guardName + "\n#define " + guardName + "\n";
}

std::string include(std::string include)
{
  return std::string("#include<" + include + ">\n");
}

std::string startNamespace()
{
  return std::string("namespace ") + nameSpace + "\n{\n";
}

void copiarArquivo(char *nomeSrc, char* nomeDest)
{
  FILE* src = fopen(nomeSrc, "rb");
  FILE* dest = fopen(nomeDest, "wb");

  char c;

  while(fscanf(src,"%c",&c) != EOF)
  {
    fputc(c, dest);
  }

  fclose(src);
  fclose(dest);
}

void GeradorDeCodigo::setDiretorioBase(char* nome)
{
  nameSpace = std::string(nome);
  dirBase = std::string(nome) + "/";
}

void GeradorDeCodigo::gerarInfraestrutura()
{
  copiarArquivo("Templates/Utilitarios.h", "Output/Utilitarios.h");
  copiarArquivo("Templates/Utilitarios.cpp", "Output/Utilitarios.cpp");
  copiarArquivo("Templates/parser.h", "Output/parser.h");
  copiarArquivo("Templates/parser.c", "Output/parser.c");
}

std::string getTokensEnum(MaquinaToken* machines)
{
  std::string values = "\n  UNKNOWN = -2,\n  " + endOfInputToken + "= -1";
  
  while(machines != NULL)
  {
    values += ",\n  " + machines->getNomeCanonico("T_");
    machines = machines->getProxima();
  }

  return "enum TokenType\n{" + values + "\n};\n"; 
}

std::string getIgnoredExpression(MaquinaToken* machines, const std::string& variableName)
{
  std::string ret = "false";
  
  while(machines != NULL)
  {
    if(machines->ignore())
      ret += " || " + variableName + " == " + machines->getNomeCanonico("T_");
    machines = machines->getProxima();
  }

  return ret;
}

void gerarHeaderAnalizadorLexico(MaquinaToken* maquinas)
{
  FILE* arquivo = fopen("Output/AnalizadorLexico.h", "wb");

  std::string parserPath = dirBase + nameSpace + "Parser.h";

  if(arquivo == NULL) return;

  int numTokens = 0;
  while(maquinas){maquinas = maquinas->getProxima(); numTokens++;}

  fprintf(arquivo,"#ifndef AnalizadorLexico%s_Header_File\n#define AnalizadorLexico%s_Header_File\n\n"
                  "#include <stdio.h>\n#include <%s>\n", nameSpace.c_str(),
                  nameSpace.c_str(), parserPath.c_str());

  if(nameSpace.length() > 0)
  {
    fprintf(arquivo, "namespace %s\n{\n", nameSpace.c_str());
  }

  fprintf(arquivo, "\nclass AnalizadorLexico\n{\n");

  fprintf(arquivo,"public:\n\tenum Estados\n\t{\n\t\tACEITO = -2,\n\t\tERRO = -1,\t\t\n\t\tPROCESSANDO = 0\n\t};\nprivate:\n");
  fprintf(arquivo,"\tint linhaInicio, colunaInicio, ESPACO_TAB;\n");
  fprintf(arquivo,"\tToken* tokens;\n\tint estados[%i];\n\tint (*analizadores[%i])(int&, int);\n\n",
                  numTokens, numTokens);
  fprintf(arquivo,"public:\n\tAnalizadorLexico();\n\tToken* getTokens();\n\tvoid setTokens(Token* token);\n\tvirtual void analizar(char* textoArquivo, int tamanhoArquivo);\n\tvirtual void analizar(FILE* arquivo);\n\t~AnalizadorLexico();\n");
  fprintf(arquivo,"};\n");

  if(nameSpace.length() > 0)
  {
    fprintf(arquivo, "}\n");
  }

  fprintf(arquivo,"#endif");


  fclose(arquivo);
}

void gerarSourceAnalizadorLexico(MaquinaToken* maquinas)
{
  int i,j;
  FILE* arquivo = fopen("Output/AnalizadorLexico.cpp", "wb");

  std::string ignoredExpr = getIgnoredExpression(maquinas, "type");

  if(arquivo == NULL) return;

  fprintf(arquivo,"#include <%sAnalizadorLexico.h>\n#include <Utilitarios.h>\n#include <string.h>\n\n", dirBase.c_str());

  if(nameSpace.length() > 0)
  {
    fprintf(arquivo, "using namespace %s;\n", nameSpace.c_str());
  }

  MaquinaToken* auxMaquinas = maquinas;
  int numMaquinas = 0;

  while(auxMaquinas != NULL)
  {
    numMaquinas++;
    fprintf(arquivo,"static int func_%s(int &estado, int entrada)\n{\n\tswitch(estado)\n\t{\n", auxMaquinas->getNomeCanonico("").c_str());

    MaquinaToken::Estado** estados = auxMaquinas->getEstados();

    for(i = 0; estados[i] != NULL; i++)
    {
      fprintf(arquivo,"\t\tcase %i:\n", i);
      fprintf(arquivo,"\t\t\tswitch(entrada)\n\t\t\t{\n");

      MaquinaToken::Transicao* tran = estados[i]->transicoes;
      while(tran)
      {
        fprintf(arquivo,"\t\t\t\tcase %i: ", tran->valorEsperado);
        for(j = 0; estados[j] != NULL; j++)
        {
          if(estados[j] == tran->proximoEstado)
          {
            fprintf(arquivo,"estado = %i;", j);
            break;
          }
        }
        fprintf(arquivo," break;\n");
        tran = tran->proxima;
      }

      fprintf(arquivo,"\t\t\t\tdefault: estado = AnalizadorLexico::ERRO;\n\t\t\t}\n");

      fprintf(arquivo,"\t\tbreak;\n");
    }

    fprintf(arquivo,"\t\tdefault: estado = AnalizadorLexico::ERRO;\n\t}\n\tif(estado == AnalizadorLexico::ERRO) return AnalizadorLexico::ERRO;\n");

    fprintf(arquivo,"\tif(");

    bool first = true;

    for(i = 0; estados[i] != NULL; i++)
    {
      if(estados[i]->terminado)
      {
        if(!first) fprintf(arquivo," || ");
        else first = false;
        fprintf(arquivo,"estado == %i", i);
      }
    }

    fprintf(arquivo,") return AnalizadorLexico::ACEITO;\n\treturn AnalizadorLexico::PROCESSANDO;\n");

    fprintf(arquivo,"}\n");
    delete [] estados;

    auxMaquinas = auxMaquinas->getProxima();
  }

  fprintf(arquivo,"AnalizadorLexico::AnalizadorLexico()\n{\n\ttokens = NULL;\n\tlinhaInicio = colunaInicio = ESPACO_TAB = 1;\n");

  i = 0;
  auxMaquinas = maquinas;
  while(auxMaquinas != NULL)
  {
    fprintf(arquivo,"\t\tanalizadores[%i] = func_%s;\n", i, auxMaquinas->getNomeCanonico("").c_str());
    i++;
    auxMaquinas = auxMaquinas->getProxima();
  }

  fprintf(arquivo,"}\n");

  fprintf(arquivo,"Token* AnalizadorLexico::getTokens(){ return tokens;}\n\nvoid AnalizadorLexico::setTokens(Token* token){ tokens = token; }\n\n");


  fprintf(arquivo,"void AnalizadorLexico::analizar(FILE* arquivo)\n{\n");
  fprintf(arquivo,
  "\tint tamanhoArquivo;\n"
	"\tfseek(arquivo, 0, SEEK_END);\n"
	"\ttamanhoArquivo = ftell(arquivo);\n"
	"\trewind(arquivo);\n"
	"\tif(!tamanhoArquivo) return;\n"
	"\tchar* textoArquivo = new char[tamanhoArquivo+1];\n"
	"\ttextoArquivo[tamanhoArquivo] = '\\0';\n"
	"\tfread(textoArquivo, sizeof(char), tamanhoArquivo, arquivo);\n\n"

  "\tanalizar(textoArquivo, tamanhoArquivo);\n\n"

  "\tdelete [] textoArquivo;\n");
  fprintf(arquivo,"}\n");


  fprintf(arquivo,"void AnalizadorLexico::analizar(char* textoArquivo, int tamanhoArquivo)\n{\n");
  //Core analizador lexico
  fprintf(arquivo,
  "\tif(!tamanhoArquivo) return;\n"

  "\tint posicaoArquivo = 0, posicaoAceita = 0, posicaoInicio = 0;\n"

  "\tunsigned char entrada;\n"

  "\tToken* retorno = NULL;\n"
  "\tToken* ultimo = NULL;\n"
  "\tint maquinaApta = -1;\n");

  fprintf(arquivo,"\tmemset(estados,0,sizeof(int)*%i);\n",numMaquinas);

  fprintf(arquivo,
  "\twhile(posicaoArquivo <= tamanhoArquivo)\n"
  "\t{\n"
    "\t\tentrada = (unsigned char)textoArquivo[posicaoArquivo];\n"

    "\t\tbool hasLife = false;\n");

    fprintf(arquivo, "\t\tfor(int i = 0; i < %i; i++)\n\t\t{\n", numMaquinas);

    fprintf(arquivo,"\t\t\tif(estados[i] != ERRO)\n\t\t\t{\n");
    fprintf(arquivo,"\t\t\t\tint resultado = analizadores[i](estados[i], entrada);\n");
    fprintf(arquivo,"\t\t\t\tif(estados[i] != ERRO)\n\t\t\t\t{\n"
                    "\t\t\t\t\thasLife = true;\n"
                    );
    fprintf(arquivo,"\t\t\t\t\tif(resultado == ACEITO)\n\t\t\t\t\t{\n"
                    "\t\t\t\t\t\tposicaoAceita = posicaoArquivo;\n"
                    "\t\t\t\t\t\tmaquinaApta = i;\n"
                    );
    fprintf(arquivo,"\t\t\t\t\t}\n\t\t\t\t}\n\t\t\t}\n\t\t}\n");

    fprintf(arquivo,
    "\t\tif(!hasLife || !textoArquivo[posicaoArquivo])\n"
    "\t\t{\n"
      "\t\t\tToken* token = newToken();\n"
      "\t\t\ttoken->line = linhaInicio;\n"
      "\t\t\ttoken->column = colunaInicio;\n"

      "\t\t\tif(maquinaApta >= 0)\n"
      "\t\t\t{\n"
        "\t\t\t\tint type = maquinaApta;\n"
        "\t\t\t\ttoken->type = type;\n"
        "\t\t\t\ttoken->ignored = %s;\n"
        "\t\t\t\ttoken->index = posicaoInicio;\n"
        "\t\t\t\tint tamanho = posicaoAceita -posicaoInicio +1;\n"
        "\t\t\t\ttoken->length = tamanho;\n"
        "\t\t\t\ttoken->content = to_string(textoArquivo + posicaoInicio, tamanho);\n"
        "\t\t\t\tfor(int p = posicaoInicio; p <= posicaoAceita; p++)\n"
        "\t\t\t\t{\n"
          "\t\t\t\t\tif(textoArquivo[p] == '\\n')\n"
          "\t\t\t\t\t{\n"
            "\t\t\t\t\t\tlinhaInicio++;\n"
            "\t\t\t\t\t\tcolunaInicio = 1;\n"
          "\t\t\t\t\t}else\n"
          "\t\t\t\t\t{ if(textoArquivo[p] == '\\t')\n"
            "\t\t\t\t\t\t{\n"
              "\t\t\t\t\t\t\tcolunaInicio += ESPACO_TAB;\n"
            "\t\t\t\t\t\t}else\n"
            "\t\t\t\t\t\t{\n"
              "\t\t\t\t\t\t\tcolunaInicio++;\n"
            "\t\t\t\t\t\t}\n"
          "\t\t\t\t\t}\n"
        "\t\t\t\t}\n"

        "\t\t\t\tposicaoInicio = posicaoAceita+1;\n"
      "\t\t\t}else\n"
      "\t\t\t{\n"
        "\t\t\t\ttoken->type = UNKNOWN;\n"
        "\t\t\t\ttoken->ignored = false;\n"
        "\t\t\t\ttoken->index = posicaoInicio;\n"
        "\t\t\t\ttoken->content = to_string(textoArquivo + posicaoInicio, 1);\n"
        "\t\t\t\ttoken->length = 1;\n"
        "\t\t\t\tif(textoArquivo[posicaoInicio] == '\\n')\n"
        "\t\t\t\t{\n"
          "\t\t\t\t\tlinhaInicio++;\n"
          "\t\t\t\t\tcolunaInicio = 1;\n"
        "\t\t\t\t}else\n"
        "\t\t\t\t{\n\t\t\t\t\tif(textoArquivo[posicaoInicio] == '\\t')\n"
          "\t\t\t\t\t{\n"
            "\t\t\t\t\t\tcolunaInicio += ESPACO_TAB;\n"
          "\t\t\t\t\t}else\n"
          "\t\t\t\t\t{\n"
            "\t\t\t\t\t\tcolunaInicio++;\n"
          "\t\t\t\t\t}\n"
        "\t\t\t\t}\n"

        "\t\t\t\tposicaoInicio++;\n"
        "\t\t\t\tposicaoArquivo = posicaoInicio;\n"
      "\t\t\t}\n"

      "\t\t\tif(ultimo)\n"
      "\t\t\t{\n"
        "\t\t\t\tultimo->next = token;\n"
        "\t\t\t\tultimo = token;\n"
      "\t\t\t}else\n"
      "\t\t\t{\n"
        "\t\t\t\tretorno = token;\n"
        "\t\t\t\tultimo = retorno;\n"
      "\t\t\t}\n"

      "\t\t\tmaquinaApta = -1;\n", ignoredExpr.c_str());

      fprintf(arquivo,"\t\t\tmemset(estados,0,sizeof(int)*%i);\n",numMaquinas);

      fprintf(arquivo,
      "\t\t\tif(!textoArquivo[posicaoArquivo])\n"
      "\t\t\t{ break;}\n"
    "\t\t}else\n"
    "\t\t{\n"
      "\t\t\tposicaoArquivo++;\n"
    "\t\t}\n"
  "\t}\n"

  "\ttokens = retorno;\n");

  fprintf(arquivo,"}\n");

  fprintf(arquivo,"AnalizadorLexico::~AnalizadorLexico()\n{\n\tToken* aux = tokens;\n\twhile(aux){tokens = tokens->next; delete aux; aux = tokens;}\n}\n");

  fclose(arquivo);
}

void GeradorDeCodigo::gerarLexico(MaquinaToken* maquinas)
{
  gerarHeaderAnalizadorLexico(maquinas);
  gerarSourceAnalizadorLexico(maquinas);
}

void gerarHeaderProducao(MaquinaToken* maquinas, Producao* producoes,
   std::map<std::string, std::string> reducoes)
{
  std::string outputData;

  outputData += includeGuard(nameSpace + "_PRODUCTIONS_HEADER");
  outputData += externCGuard;
  outputData += include("somepath/parser.h");

  std::string enumData = "enum " + nameSpace + "_ProductionType\n{\n\t" + nameSpace + "_P_UNKONOWN_PROD";

  std::string visitType = std::string("extern VisitFunction ");
  std::string externs;
  std::string parentExterns = visitType + nameSpace + "_visit_defaultFunction;\n\n";
  std::string structures;
  std::map<std::string, bool> alreadyMapped;
  std::map<std::string, bool> parentsMapped;
  Producao* auxProd = producoes;
  while(auxProd)
  {
    std::string reduction = auxProd->getReducao(reducoes);
    if(alreadyMapped.find(reduction) == alreadyMapped.end())
    {
      alreadyMapped[reduction] = true;
      enumData += std::string(",\n\t") + nameSpace + "_P_" + reduction;
      externs += visitType + nameSpace + "_visit_" + reduction + ";\n";

      structures += std::string("typedef struct \n{\n\tint type;\n\tint nodeCount;\n");
      for(int i = 0; i < auxProd->numPartes; i++)
      {
        structures += "\tProductionNode ";
        if(auxProd->partes[i].token != NULL)
        {
          structures += auxProd->partes[i].token->getNomeCanonico("T_");
        }
        else
        {
          std::string partName = auxProd->partes[i].producao->getNome();
          if(reducoes.find(partName) != reducoes.end()) partName = reducoes[partName];
          structures += partName;
        }
        structures += std::to_string(i) + ";\n";
      }
      structures += std::string("} ") + nameSpace + "_" + reduction + ";\n\n";
    }

    std::string nameParent = auxProd->getNome();
    if(reducoes.find(auxProd->getNome()) != reducoes.end())
    { nameParent = reducoes[auxProd->getNome()]; }

    if(parentsMapped.find(nameParent) == parentsMapped.end())
    {
      parentsMapped[nameParent] = true;
      parentExterns += visitType + nameSpace + "_visit_" + nameParent + ";\n";
    }

    auxProd = auxProd->proxima;
  }

  enumData += "\n};\n";

  outputData += parentExterns + "\n" + externs + "\n" + structures + enumData + "\n";
  outputData += std::string("extern bool ") + nameSpace + "_nodeRedundancyTable[];";
  outputData += std::string("bool ") + nameSpace + "_visit(Production*, VisitData*);\n";
  outputData += "bool " + nameSpace + "_visitNodes(Production* production, VisitData* visitData);\n\n";
  outputData += externCGuardEnd;
  outputData += endGuard;

  writeToFile("Output/productions.h", outputData);
}

void gerarSourceProducao(MaquinaToken* maquinas, Producao* producoes,
    std::map<std::string, std::string> reducoes)
{
  std::string outputData;

  outputData += include(nameSpace + "/productions.h");

  std::string visitType = std::string("VisitFunction ");
  std::string visits = visitType + nameSpace + "_visit_defaultFunction = " + nameSpace + "_visitNodes;\n";
  std::string visitCalls;
  std::string parentCalls;
  std::string reducing;
  std::map<std::string, bool> alreadyMapped;
  std::map<std::string, std::string> parentsMapped;
  Producao* auxProd = producoes;
  while(auxProd)
  {
    std::string reduction = auxProd->getReducao(reducoes);
    if(alreadyMapped.find(reduction) == alreadyMapped.end())
    {
      alreadyMapped[reduction] = true;
      std::string prodVisit = nameSpace + "_visit_" + reduction;
      std::string prodType = nameSpace + "_P_" + reduction;
      visits += visitType + prodVisit + " = nullptr;\n";

      visitCalls += std::string("\t\tcase ") + prodType + ": visitFunction = " + prodVisit + "; break;\n";

      std::string nameParent = auxProd->getNome();
      if(reducoes.find(auxProd->getNome()) != reducoes.end())
      {
        nameParent = reducoes[auxProd->getNome()];
      }

      if(parentsMapped.find(nameParent) == parentsMapped.end())
      {
        parentsMapped[nameParent] = "";
        visits += visitType + nameSpace + "_visit_" + nameParent + " = nullptr;\n";
      }

      {
        bool shouldReduce = false;

        if(auxProd->numPartes == 1 && auxProd->partes[0].producao != nullptr)
        {
          std::string primeiraProdReduzida = auxProd->partes[0].producao->getNome();
          if(reducoes.find(primeiraProdReduzida) != reducoes.end())
          { primeiraProdReduzida = reducoes[primeiraProdReduzida]; }

          if(primeiraProdReduzida == nameParent) shouldReduce = true;
        }

        if(shouldReduce) reducing += "\t,true";
        else reducing += "\t,false";
        reducing += std::string(" // ") + reduction + "\n";
      }

      //if(reducoes.find(auxProd->getNome()) != reducoes.end())
      //{
        parentsMapped[nameParent] += std::string("\t\tcase ") + prodType + ":\n";
      //}
    }

    auxProd = auxProd->proxima;
  }

  for(auto it = parentsMapped.begin(); it != parentsMapped.end(); it++)
  {
    parentCalls += it->second + "\t\t\tvisitFunction = " + nameSpace + "_visit_" + it->first + ";\n\t\tbreak;\n";
  }

  std::string visitFunction = std::string("bool ") + nameSpace +
    "_visit(Production* production, VisitData* visitData)\n{\n\t" +
    visitType + "visitFunction = nullptr;\n\tswitch(production->type)\n\t{\n" +
    visitCalls + "\t}\n\n\tif(visitFunction != nullptr) return visitFunction(production, visitData);\n\n" +
    "\tswitch(production->type)\n\t{\n" +
    parentCalls + "\t}\n\n\tif(visitFunction != nullptr) return visitFunction(production, visitData);\n\n" +
    "\treturn " + nameSpace + "_visit_defaultFunction(production, visitData);\n}\n";

  outputData += visits + "\n" + visitFunction;

  outputData += "bool " + nameSpace +
  "_visitNodes(Production* production, VisitData* visitData)\n{ return visitNodes(production, visitData, " +
  nameSpace + "_visit); }\n";

  outputData += std::string("bool ") + nameSpace + "_nodeRedundancyTable[] = {\n\tfalse // UNKNOWN\n";
  outputData += reducing;
  outputData += "};\n";

  writeToFile("Output/productions.c", outputData);
}

void gerarHeaderAnalizadorSintatico(MaquinaToken* maquinas, Producao* producoes, GeradorLALR* lalr,
  std::map<std::string, std::string> reducoes)
{
  std::string guardName = nameSpace + "_PARSER_HEADER_FILE";
  std::string outputData;

  outputData += includeGuard(guardName);
  outputData += include("string") + include("somepath/parser.h");
  outputData += startNamespace();
  outputData += getTokensEnum(maquinas);
  outputData += "Parser parse(AllProductions* allProductions, Production* (*creationFunction)(AllProductions*), Token* tokens);\n";
  outputData += endNamespace;
  outputData += endGuard;

  writeToFile(std::string("Output/") + nameSpace + "Parser.h", outputData);
}

void gerarSourceAnalizadorSintatico(MaquinaToken* maquinas, Producao* producoes, GeradorLALR* lalr,std::map<std::string, std::string> reducoes)
{
  std::string outputData;
  std::string creationFunctions;
  std::map<std::string, int> alreadyMapped;

  Producao* auxProd = producoes;
  while(auxProd)
  {
    std::string nome = auxProd->getNome();
    if(reducoes.find(nome) == reducoes.end())
    {
      if(alreadyMapped.find(nome) == alreadyMapped.end())
      {
        alreadyMapped[nome] = 1;
      }
    }
    auxProd = auxProd->proxima;
  }

  auxProd = producoes;
  while(auxProd)
  {
    std::string reducao = auxProd->getReducao(reducoes);
    if(alreadyMapped.find(reducao) == alreadyMapped.end())
    {
      alreadyMapped[reducao] = 1;
    }
    auxProd = auxProd->proxima;
  }

  outputData += include("somepath/parser.h") + include(dirBase + "productions.h") +
                include(dirBase + nameSpace + "Parser.h") + "\n";

  int i;
  int stateCount = lalr->getNumEstados();
  Hash<void*, GeradorLALR::OperacaoTabela>* tabelaAcao = lalr->getTabelaAcao();
  Hash<void*, GeradorLALR::OperacaoTabela>* tabelaGoto = lalr->getTabelaGoto();

  std::string stateActions;
  std::string states;
  std::string goToTable = "static int goToTable(int state, int productionIndex)\n{\n\tswitch(state)\n\t{\n";

  for(i = 0; i < stateCount; i++)
  {
    Lista<void*> *listaKeys = tabelaGoto[i].getAllKeys();
    Lista<void*> *aux = listaKeys;

    if(aux)
    {
      goToTable += "\t\tcase " + std::to_string(i) + ":\n\t\tswitch(productionIndex)\n\t\t{\n";
      while(aux)
      {
        long long indiceProducao = (long long)(*(aux->objeto));
        goToTable += "\t\t\tcase " + std::to_string(indiceProducao) + ":";
        goToTable += " return " + std::to_string(tabelaGoto[i].get((void*)indiceProducao)->gotoEstado) + "; break;\n",
        aux = aux->proximo;
      }

      goToTable += "\t\t}\n""\t\tbreak;\n";
    }

    Lista<void*>::desmontar(listaKeys);
  }

  goToTable += "\t}\n\treturn 0;\n}\n\n";

  states = "\tState states[] = {\n";

  for(i = 0; i < stateCount; i++)
  {
    if(i) states += ",\n";
    std::map<MaquinaToken*, bool> mappedTokens;
    Lista<void*> *listaKeys = tabelaAcao[i].getAllKeys();

    std::string stateActionsVar = std::string("state") + std::to_string(i) + "Actions";
    std::string currentStateActions = std::string("\tAction ") + stateActionsVar + "[] = {\n";
    bool first = true;
    Lista<void*> * aux = listaKeys;
    int actionIndex = 0;
    while(aux != NULL)
    {
      actionIndex++;
      std::string expectedToken;
      MaquinaToken* maquina = (*((MaquinaToken**)(aux->objeto)));
      GeradorLALR::OperacaoTabela* op = tabelaAcao[i].get(maquina);

      if(mappedTokens.find(maquina) != mappedTokens.end())
      {
        aux = aux->proximo;
        continue;
      }

      mappedTokens[maquina] = true;

      if(!first)
      {
        currentStateActions += ",\n";
      }

      first = false;

      if(maquina != NULL)
      {
        expectedToken = nameSpace + "::TokenType::" + maquina->getNomeCanonico("T_");
      }else
      {
        expectedToken = nameSpace + "::TokenType::" + endOfInputToken;
      }

      if(op != NULL) // Isso tem que ser sempre verdade, mas pra garantir
      switch(op->tipo)
      {
        case GeradorLALR::OperacaoTabela::SHIFT:
          currentStateActions += std::string("\t\tcreateShift(") + expectedToken + "," + std::to_string(op->gotoEstado) + ")";
        break;

        case GeradorLALR::OperacaoTabela::REDUCE:
        {
          Lista<GeradorLALR::OperacaoTabela>* operacoes = tabelaAcao[i].getAll(maquina);

          std::string reduceIndexes;
          std::string reduceProdTypes;
          std::string reduceNodesCount;

          int optionsSize = 0;
          Lista<GeradorLALR::OperacaoTabela>* aux = operacoes;
          while(aux)
          {
            optionsSize++;
            aux = aux->proximo;
          }

          aux = operacoes;
          for(int i = 0; i < optionsSize; i++)
          {
            if(i)
            {
              reduceIndexes += ", ";
              reduceProdTypes += ", ";
              reduceNodesCount += ", ";
            }

            reduceIndexes += std::to_string(aux->objeto->gotoProducao->indice);
            reduceProdTypes += nameSpace + "_P_" + aux->objeto->gotoProducao->getReducao(reducoes);
            //reduceFunctions += std::string("create" + op->gotoProducao->getReducao(reducoes));
            reduceNodesCount += std::to_string(aux->objeto->gotoProducao->numPartes);
            aux = aux->proximo;
          }

          currentStateActions += std::string("\t\tcreateReduce") + std::to_string(optionsSize) + "(" +
            expectedToken + ", " + reduceIndexes + ", " + reduceProdTypes + ", " + reduceNodesCount + ")";

          Lista<GeradorLALR::OperacaoTabela>::desmontar(operacoes);
        }
        break;

        case GeradorLALR::OperacaoTabela::ACCEPT:
          currentStateActions += std::string("\t\tcreateAcceptAction()");
        break;
      }

      aux = aux->proximo;
    }

    currentStateActions += "\n\t};\n";
    states += std::string("\t\tcreateState(") + stateActionsVar + ", sizeof(" + stateActionsVar + ")/sizeof(Action))";

    stateActions += currentStateActions;

    Lista<void*>::desmontar(listaKeys);
  }

  states += "\n\t};\n";

  outputData += goToTable;

  outputData += std::string("Parser ") + nameSpace +
    "::parse(AllProductions* allProductions, Production* (*creationFunction)(AllProductions*), Token* token)\n{\n" +
    stateActions + states + "\treturn parse(allProductions, creationFunction, states, goToTable, token);\n}\n";

  writeToFile(std::string("Output/") + nameSpace + "Parser.cpp", outputData);
}

void GeradorDeCodigo::gerarSintatico(MaquinaToken* maquinas, Producao* producoes,
                                     GeradorLALR* lalr, std::map<std::string, std::string> reducoes,
                                     std::map<std::string, std::string> lists)
{
  printf("Gerando headers de producoes\n");
  gerarHeaderProducao(maquinas, producoes, reducoes);
  printf("Gerando sources de producoes\n");
  gerarSourceProducao(maquinas, producoes, reducoes);
  printf("Gerando headers de analise sintatica\n");
  gerarHeaderAnalizadorSintatico(maquinas, producoes, lalr, reducoes);
  printf("Gerando sources de analise sintatica\n");
  gerarSourceAnalizadorSintatico(maquinas, producoes, lalr, reducoes);
}
