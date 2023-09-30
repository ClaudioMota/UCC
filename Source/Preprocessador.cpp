#include <Preprocessador.h>

//NoSintaticoHelper
Preprocessador::NoSintaticoHelper::NoSintaticoHelper()
{
  operacao = INDEFINIDO;
  primeiroFilho = NULL;
  segundoFilho = NULL;
}

inline bool Preprocessador::NoSintaticoHelper::analizarOU(char* expr, int tam)
{
  int i;
  int profundidade = 0;
  bool modoString = false;
  for(i = 0; i < tam; i++)
  {
    while(modoString && expr[i] == '\\'){i += 2;}
    if(expr[i] == '\'') modoString = !modoString;
    if(modoString) continue;

    if(expr[i] == '('){profundidade++; continue;}
    if(expr[i] == ')'){profundidade--; continue;}
    if((expr[i] == '+' || expr[i] == '-') && profundidade == 0)
    {
      primeiroFilho = new NoSintaticoHelper();
      primeiroFilho->analizar(expr, i);
      if(expr[i] == '+') operacao = UNIAO;
      else operacao = SUBTRACAO;
      segundoFilho = new NoSintaticoHelper();
      segundoFilho->analizar(expr+i+1, tam -(i+1));
      return true;
    }
  }
  return false;
}

inline bool Preprocessador::NoSintaticoHelper::analizarE(char* expr, int tam)
{
  int i;
  int profundidade = 0;
  bool modoString = false;
  for(i = 0; i < tam; i++)
  {
    while(modoString && expr[i] == '\\'){i += 2;}
    if(expr[i] == '\'') modoString = !modoString;
    if(modoString) continue;

    if(expr[i] == '(') {profundidade++; continue;}
    if(expr[i] == ')') {profundidade--; continue;}

    if((expr[i] == '*' || expr[i] == '.' && (i < tam-1) && expr[i+1] == '.') && profundidade == 0)
    {
      primeiroFilho = new NoSintaticoHelper();
      primeiroFilho->analizar(expr, i);
      if(expr[i] == '.'){i++; operacao = ATE;}
      else{operacao = PRODUTO;}
      segundoFilho = new NoSintaticoHelper();
      segundoFilho->analizar(expr+i+1, tam -(i+1));
      return true;
    }
  }
  return false;
}

inline bool Preprocessador::NoSintaticoHelper::analizarParenteses(char* expr, int tam)
{
  int i;
  int profundidade = 0;

  if(expr[0] == '(')
  { bool modoString = false;
    for(i = 0; i < tam; i++)
    {
      while(modoString && expr[i] == '\\'){i += 2;}
      if(expr[i] == '\'') modoString = !modoString;
      if(modoString) continue;
      if(expr[i] == '(') profundidade++;
      if(expr[i] == ')')
      { profundidade--;
        if(profundidade == 0)
        {
          if(i != tam-1)
          {
            return false;
          }else
          {
            operacao = PARENTESES;
            primeiroFilho = new NoSintaticoHelper();
            primeiroFilho->analizar(expr+1, i-1);
            return true;
          }
        }
      }
    }
  }else if(expr[0] == '\'')
  {
    for(i = 1; i < tam; i++)
    {
      while(expr[i] == '\\'){i += 2;}
      if(expr[i] == '\'')
      {
        if(i == tam-1)
        {
          cadeia = expr+1;
          tamanho = tam-2;
          operacao = STRING;
          return true;
        }else
        { return false;}
      }
    }
  }
  return false;
}

void Preprocessador::NoSintaticoHelper::analizar(char* expr, int tam)
{
  while(isspace(expr[0]))
  {
    expr++;
    tam--;
  }
  while(isspace(expr[tam-1]))
  { tam--;}

  //printf("->%.*s", tam, expr);getchar();
  if(!analizarParenteses(expr, tam))
  if(!analizarOU(expr, tam))
  if(!analizarE(expr, tam))
  {
    cadeia = expr;
    tamanho = tam;
    if(expr[0] >= '0' && expr[0] <= '9') operacao = NUMERO;
    else operacao = IDENTIFICADOR;
  }
}

Preprocessador::Helper* Preprocessador::NoSintaticoHelper::extrairHelper(std::map<std::string, Preprocessador::Helper*> &helpers)
{
  Helper* retorno = NULL;
  Helper* aux;
  char* auxStr;
  int c = 0;
  int i = 0;

  Helper* A;
  Helper* B;

  switch(operacao)
  {
    case STRING:
      auxStr = to_ASCII_string(cadeia, tamanho);
      retorno = new Helper(auxStr, strlen(auxStr), NULL);
    break;
    case NUMERO:
      c = 0;
      i = 0;
      while(i < tamanho)
      { c = c*10 + cadeia[i]-48;
        i++;
      }
      auxStr = new char[2];
      auxStr[0] = c;
      auxStr[1] = '\0';
      retorno = new Helper(auxStr, 1, NULL);
    break;
    case IDENTIFICADOR:
      auxStr = to_string(cadeia, tamanho);
      aux = helpers[auxStr];
      delete [] auxStr;
      if(aux != NULL)
      {
        retorno = new Helper(to_string(aux->cadeia, aux->tamanho), aux->tamanho, NULL);
        retorno->add(aux->proximo);
      }
    break;
    case PRODUTO:
      retorno = primeiroFilho->extrairHelper(helpers);
      aux = segundoFilho->extrairHelper(helpers);
      retorno->mul(aux);
      Helper::destruir(aux);
    break;
    case ATE:
      if((primeiroFilho->operacao == STRING || primeiroFilho->operacao == NUMERO) &&
         (segundoFilho->operacao == STRING || segundoFilho->operacao == NUMERO))
      {
        A = primeiroFilho->extrairHelper(helpers);
        B = segundoFilho->extrairHelper(helpers);
        retorno = Helper::expandir((unsigned char)A->cadeia[0], (unsigned char)B->cadeia[0]);
        delete A;
        delete B;
      }
    break;
    case PARENTESES:
      retorno = primeiroFilho->extrairHelper(helpers);
    break;
    case UNIAO:
      retorno = primeiroFilho->extrairHelper(helpers);
      aux = segundoFilho->extrairHelper(helpers);
      retorno->add(aux);
      Helper::destruir(aux);
    break;
    case SUBTRACAO:
      retorno = primeiroFilho->extrairHelper(helpers);
      aux = segundoFilho->extrairHelper(helpers);
      retorno->sub(aux);
      Helper::destruir(aux);
    break;
  }
  return retorno;
}

void Preprocessador::NoSintaticoHelper::print()
{
  if(operacao == UNIAO)
  {printf("{U}(");}
  if(operacao == ATE)
  {printf("{ATE}(");}
  if(operacao == PRODUTO)
  {printf("{PRO}(");}
  if(operacao == PARENTESES)
  {printf("{PAR}(");}
  if(operacao == NUMERO)
  {printf("{NUM}(%.*s",tamanho, cadeia);}
  if(operacao == SUBTRACAO)
  {printf("{SUB}(");}
  if(operacao == INDEFINIDO)
  {printf("{?}(%.*s",tamanho, cadeia);}
  if(operacao == STRING)
  {printf("{STR}(%.*s",tamanho, cadeia);}
  if(operacao == IDENTIFICADOR)
  {printf("{ID}(%.*s",tamanho, cadeia);}

  NoSintaticoHelper* no = primeiroFilho;
  if(no){ no->print();}
  no = segundoFilho;
  if(no)
  { printf(",");
    no->print();
  }
  printf(")");
}


//Helper
Preprocessador::Helper::Helper(char* cadeia, int tamanho, Preprocessador::Helper* proximo)
{
  this->cadeia = cadeia;
  this->tamanho = tamanho;
  this->proximo = proximo;
}

bool Preprocessador::Helper::iguais(Preprocessador::Helper* a, Preprocessador::Helper* b)
{ int i;
  if(a->tamanho != b->tamanho) return false;
  for(i = 0; i < a->tamanho; i++)
  {
    if(a->cadeia[i] != b->cadeia[i]) return false;
  }
  return true;
}

int Preprocessador::Helper::passarParaArray(int* saida)
{
  int i = 0,j;
  Helper* h = this;
  saida[i++] = ABRE_PARENTESES;
  while(h)
  {
    for(j = 0; j < h->tamanho; j++)
    {
      saida[i++] = (unsigned char)(h->cadeia[j]);
    }
    if(h->proximo) saida[i++] = OU;
    h = h->proximo;
  }
  saida[i++] = FECHA_PARENTESES;
  return i;
}

int Preprocessador::Helper::getTamanhoIntArray()
{
  int tam = 2;
  Helper* h = this;
  while(h)
  {
    tam += h->tamanho;
    if(h->proximo) tam++;
    h = h->proximo;
  }
  return tam;
}

void Preprocessador::Helper::add(Preprocessador::Helper* h)
{
  Helper* aux = h;
  Helper* aux2;
  Helper* adicao = NULL;
  while(aux)
  {
    aux2 = this;
    while(aux2)
    {
      if(iguais(aux,aux2)) break;
      aux2 = aux2->proximo;
    }
    if(!aux2)
    {
      adicao = new Helper(to_string(aux->cadeia, aux->tamanho), aux->tamanho, adicao);
    }
    aux = aux->proximo;
  }
  aux2 = this;
  while(aux2->proximo)
  {
    aux2 = aux2->proximo;
  }
  aux2->proximo = adicao;
}

void Preprocessador::Helper::sub(Preprocessador::Helper* h)
{
  Helper* anterior = NULL;
  Helper* aux = this;
  Helper* aux2;
  while(aux)
  {
    aux2 = h;
    while(aux2)
    {
      if(iguais(aux,aux2))
      {
        if(anterior)
        {
          anterior->proximo = aux->proximo;
          aux2 = aux;
          aux = anterior->proximo;
          delete aux2;
        }else
        {
          cadeia = proximo->cadeia;
          tamanho = proximo->tamanho;
          aux2 = proximo;
          proximo = aux2->proximo;
          delete aux2;
        }
        break;
      }
      aux2 = aux2->proximo;
    }
    if(aux2 == NULL)
    {
      anterior = aux;
      aux = aux->proximo;
    }
  }
}

void Preprocessador::Helper::mul(Preprocessador::Helper* h)
{
  //a implementar... Essa funcao n�o parece ser muito legal...
  //Ela meio que simula uma miniexpress�o o que pode levar a um jeito errado de trabalho por parte do usuario
}

Preprocessador::Helper* Preprocessador::Helper::expandir(int inicio, int fim)
{
  int i;
  Helper* retorno = NULL;
  for(i = fim; i >= inicio; i--)
  {
    retorno = new Helper(to_string((char)i),1,retorno);
  }
  return retorno;
}

void Preprocessador::Helper::destruir(Helper* h)
{
  if(h == NULL) return;
  if(h->proximo) destruir(h->proximo);
  delete h;
}

Preprocessador::Helper::~Helper()
{
  if(cadeia) delete cadeia;
}

//Linha
/*
  char* atrubuido;
  void* atributo;
  int tamanho;
  Linha* proxima;
*/

//Linha
Preprocessador::Linha::Linha(char* atribuido, void* atributo, int tamanho, Linha* proxima)
{
  this->atribuido = atribuido;
  this->atributo = atributo;
  this->tamanho = tamanho;
  this->proxima = proxima;
}

void Preprocessador::Linha::print()
{
  int i;
  for(i = 0; i < tamanho; i++)
  {
    if(((int*)atributo)[i] == UM_MAIS) printf("+");
    else if(((int*)atributo)[i] == ASTERISCO) printf("*");
    else if(((int*)atributo)[i] == ABRE_PARENTESES) printf("(");
    else if(((int*)atributo)[i] == FECHA_PARENTESES) printf(")");
    else if(((int*)atributo)[i] == OPCIONAL) printf("?");
    else if(((int*)atributo)[i] == OU) printf("|");
    else printf("%c", (unsigned char)((int*)atributo)[i]);
  }
  printf("\ntamanho:%i\n", tamanho);
}

//Preprocessador
/*
int estado;
std::map<char*, char*> helpers;
Linha* tokens;
Linha* producao;
*/


// Preprocessador
Preprocessador::Preprocessador(FILE* file)
{
  modo = NORMAL;
  estado = NENHUM;

  tokens = NULL;
  producoes = NULL;

  char entrada;
  char linha[10000];
  linha[0] = 0;
  int pos = 0;
  bool acabouLinha = false;
  while(fscanf(file, "%c", &entrada) != EOF)
  {
    //printf("%i|%i|%c -> %s\n", estado, modo, entrada, linha);
    //getchar();
    switch(modo)
    {
      case NORMAL: acabouLinha = processarNormal(linha, pos, entrada); break;
      case TEXTO_ESPECIAL:
      case TEXTO: acabouLinha = processarTexto(linha, pos, entrada); break;
      case COMENTARIO: acabouLinha = processarComentario(linha, pos, entrada); break;
    }

    if(acabouLinha)
    {
      acabouLinha = false;
      pos = 0;
    }
  }
}

inline bool Preprocessador::processarNormal(char* linha, int &pos, char entrada)
{
  if(entrada == 10 || entrada == 13) return false;
  switch(entrada)
  {
    case 10:
    case 13: return false;
    case '\'': modo = TEXTO; break;
    case '/': modo = COMENTARIO; return false;
    case ':': linha[pos++] = 0; setEstado(linha); return true;
  }

  if(entrada == ';')
  {
    linha[pos++] = 0;
    switch(estado)
    { case HELPER: processarHelper(linha); break;
      case TOKEN: processarToken(linha); break;
      case PRODUCAO: processarProducao(linha); break;
      case REDUTOR: processarAbstrato(linha); break;
    }
    return true;
  }

  linha[pos++] = entrada;
  return false;
}

inline bool Preprocessador::processarTexto(char* linha, int &pos, char entrada)
{
  if(modo == TEXTO_ESPECIAL)
  {
    // Apesar de estarmos no preprocessador, acho que isso n�o � aqui
    /*switch(entrada)
    {
      case 'n': linha[pos++] = 10; break;
      case 't': linha[pos++] = '  '; break;
      case 'r': linha[pos++] = 13; break;
      default: linha[pos++] = entrada;
    }*/
    modo = TEXTO;
  }else
  {
    switch(entrada)
    {
      case '\\': modo = TEXTO_ESPECIAL; break;
      case '\'': modo = NORMAL; break;
      //default: linha[pos++] = entrada;
    }
  }
  linha[pos++] = entrada;
  return false;
}

inline bool Preprocessador::processarComentario(char* linha, int &pos, char entrada)
{
  if(entrada == 10) modo = NORMAL;
  return false;
}

void Preprocessador::setEstado(char* estado)
{
  int i = 0;
  int j = 0;
  while(estado[i])
  {estado[j] = toupper(estado[i]); i++;
   if(estado[j] != ' ' && estado[j] != '\t' && estado[j] != 10 && estado[j] != 13) j++;
  }
  estado[j] = 0;

  printf("Mudanca de estado! ->|%s|", estado);

  if(!strcmp("HELPERS", estado)) this->estado = HELPER;
  else if(!strcmp("TOKENS", estado)) this->estado = TOKEN;
  else if(!strcmp("PRODUCTIONS", estado)) this->estado = PRODUCAO;
  else if(!strcmp("REDUCER",estado)) this->estado = REDUTOR;
  else this->estado = NENHUM;
}

void Preprocessador::processarHelper(char* linha)
{
  char* divisoria = strstr(linha, "=");
  char* atribuido = trim(linha, divisoria-linha);
  char* atributo = divisoria + 1;
  printf("->helper: %s = %s\n", atribuido, atributo);

  NoSintaticoHelper* raiz = new NoSintaticoHelper();
  raiz->analizar(atributo, strlen(atributo));

  Helper* helperFinal = raiz->extrairHelper(helpers);

  helpers[atribuido] = helperFinal;

  delete [] atribuido;
}

void Preprocessador::processarToken(char* linha)
{
  char* divisoria = strstr(linha, "=");
  char* atribuido = trim(linha, divisoria-linha);
  char* atributo = divisoria + 1;
  printf("->token: %s = %s\n", atribuido, atributo);

  int i;
  int tamanhoFinal = 0;
  bool modoString = false;
  bool modoIdentificador = false;
  int inicioIdentificador = -1;
  bool criarIdentificador = false;

  int *expressaoRegular = NULL;
  while(tamanhoFinal == 0)
  {
    for(i = 0; i <= strlen(atributo); i++)
    {
      //printf("'%c' -> %i, %i\n", atributo[i], tamanhoFinal, modoIdentificador);getchar();

      if(i == strlen(atributo))
      {
        criarIdentificador = true;
      }else
      {
        while(modoString && atributo[i] == '\\')
        { i++;
          if(expressaoRegular != NULL)
          {
            switch(atributo[i])
            {
              case 'n': expressaoRegular[tamanhoFinal] = 10; break;
              case 't': expressaoRegular[tamanhoFinal] = 9; break;
              case 'r': expressaoRegular[tamanhoFinal] = 13; break;
              default: expressaoRegular[tamanhoFinal] = (unsigned char)(atributo[i]);
            }
          }
          i++;
          tamanhoFinal++;
        }
        if(atributo[i] == '\'')
        { modoString = !modoString;
          if(modoIdentificador) criarIdentificador = true;
        }
        else if(modoString)
        { if(expressaoRegular != NULL)
          {expressaoRegular[tamanhoFinal] = (unsigned char)(atributo[i]);}
          tamanhoFinal++;
          continue;
        }
      }

      if(!modoString && (isspace(atributo[i]) ||
        atributo[i] == '(' || atributo[i] == ')' ||
        atributo[i] == '*' || atributo[i] == '+' ||
        atributo[i] == '|' || atributo[i] == '?')
        )
      {
        if(modoIdentificador)
        { criarIdentificador = true;}
      }else if(!modoString && !modoIdentificador && atributo[i] != '\'')
      {
        modoIdentificador = true;
        inicioIdentificador = i;
      }

      if(modoIdentificador && criarIdentificador)
      {
        modoIdentificador = false;
        criarIdentificador = false;
        char* strAux = to_string(atributo + inicioIdentificador, i-inicioIdentificador);
        if(helpers[strAux] != NULL)
        {
          if(expressaoRegular != NULL)
          { helpers[strAux]->passarParaArray(expressaoRegular+tamanhoFinal);}
          tamanhoFinal += helpers[strAux]->getTamanhoIntArray();
        }
        delete [] strAux;
      }

      if(i == strlen(atributo)) break;

      if(!isspace(atributo[i]) && !modoString && !modoIdentificador)
      {
        switch(atributo[i])
        {
          case '(':
            if(expressaoRegular != NULL)
            {expressaoRegular[tamanhoFinal] = ABRE_PARENTESES;}
          break;
          case ')':
            if(expressaoRegular != NULL)
            {expressaoRegular[tamanhoFinal] = FECHA_PARENTESES;}
          break;
          case '*':
            if(expressaoRegular != NULL)
            {expressaoRegular[tamanhoFinal] = ASTERISCO;}
          break;
          case '+':
            if(expressaoRegular != NULL)
            {expressaoRegular[tamanhoFinal] = UM_MAIS;}
          break;
          case '?':
            if(expressaoRegular != NULL)
            {expressaoRegular[tamanhoFinal] = OPCIONAL;}
          break;
          case '|':
            if(expressaoRegular != NULL)
            {expressaoRegular[tamanhoFinal] = OU;}
          break;
          default: tamanhoFinal--;
        }
        tamanhoFinal++;
      }
    }

    if(expressaoRegular == NULL)
    { expressaoRegular = new int[tamanhoFinal+1];
      expressaoRegular[tamanhoFinal] = 0;
      tamanhoFinal = 0;
    }
  }

  tokens = new Linha(atribuido, expressaoRegular, tamanhoFinal, tokens);
}

Preprocessador::Linha* getCombinations(char* atribuido, char* atributo, int length, Preprocessador::Linha* proxima)
{
  bool variant = false;
  int i = 0;
  for(i = 0; i < length; i++)
  {
    if(atributo[i] == '?')
    {
      variant = true;
      break;
    }
  }

  if(variant)
  {
    char* without = to_string(atributo, length);
    atributo[i] = ' ';
    while(!isspace(without[i])) without[i--] = ' ';
    Preprocessador::Linha* with = getCombinations(atribuido, atributo, length, proxima);
    return getCombinations(to_string(atribuido, strlen(atribuido)), without, length, with);
  }
  else
  {
    printf("->producao: %s = %.*s\n", atribuido, length, atributo);
    return new Preprocessador::Linha(atribuido, atributo,length,proxima);
  }
}

void Preprocessador::processarProducao(char* linha)
{
  char* divisoria = strstr(linha, "=");
  char* atribuido = trim(linha, divisoria-linha);
  char* atributo = divisoria + 1;

  int i = 0;
  bool continuaLinha = true;
  while(continuaLinha)
  {
    if(atributo[i] == '|' || atributo[i] == 0 || atributo[i] == ';')
    {
      if(atributo[i] != '|') continuaLinha = false;
      if(i > 0)
      {
        if(producoes == NULL)
        { producoes = getCombinations(to_string(atribuido, strlen(atribuido)), to_string(atributo,i),i,producoes);}
        else
        { producoes->proxima = getCombinations(to_string(atribuido, strlen(atribuido)), to_string(atributo,i),i,producoes->proxima);}

        atributo += i + 1;
        i = 0;
      }
    }
    i++;
  }

  delete [] atribuido;
}

void Preprocessador::processarAbstrato(char* linha)
{
  printf("%s\n", linha);
  char* divisoria = strstr(linha, "<");
  if(divisoria[1] != '-') return;
  char* atribuido = trim(linha, divisoria-linha);
  int atribuidoLength = strlen(atribuido);
  char* atributo = divisoria + 2;
  char* strNovo = NULL;

  bool isList = atribuido[0] == '[' && atribuido[atribuidoLength-1] == ']';
  if(isList) atribuido[atribuidoLength-1] = '\0';

  int i = 0;
  bool continuaLinha = true;
  while(continuaLinha)
  {
    if(atributo[i] == ',' || atributo[i] == 0 || atributo[i] == ';')
    {
      if(atributo[i] != ',') continuaLinha = false;
      if(i > 0)
      {
        strNovo = trim(atributo,i);

        if(!isList)
        {
          reducoes[std::string(strNovo)] = std::string(atribuido);
        }
        else
        {
          lists[std::string(strNovo)] = std::string(atribuido+1);
        }
        delete [] strNovo;

        atributo += i + 1;
        i = 0;
      }
    }
    i++;
  }

  delete [] atribuido;
}

MaquinaToken* Preprocessador::getTokens()
{
  MaquinaToken* maquinas = NULL;
  Linha* linhaToken = tokens;
  while(linhaToken)
  { maquinas = new MaquinaToken(linhaToken->atribuido, (int*)linhaToken->atributo, linhaToken->tamanho, maquinas);
    linhaToken = linhaToken->proxima;
  }
  return maquinas;
}

Producao* Preprocessador::getProducoes(MaquinaToken* tokens)
{
  int i, tam;
  Linha* linhaProducao = producoes;
  Producao *producaoAtual = NULL, *ultimaProducao = NULL, *resposta = NULL;

  while(linhaProducao)
  {
    producaoAtual = new Producao(linhaProducao->atribuido);
    if(ultimaProducao == NULL)
    {
      resposta = producaoAtual;
    }else
    {
      ultimaProducao->proxima = producaoAtual;
    }
    ultimaProducao = producaoAtual;
    linhaProducao = linhaProducao->proxima;
  }

  linhaProducao = producoes;
  producaoAtual = resposta;
  tam = 0;
  while(producaoAtual)
  { tam++;
    int i, inicio = 0;
    bool blank = true;
    char* atributoLinha = (char*)(linhaProducao->atributo);
    for(i = 0; i <= strlen(atributoLinha); i++)
    {
      if(isspace(atributoLinha[i]) && !blank || i == strlen(atributoLinha))
      {
        if(i != inicio)
        {
          char* nomeParte = trim(atributoLinha + inicio, i-inicio);
          MaquinaToken* auxT = tokens;
          Producao* auxP = resposta;//producaoAtual->proxima;
          while(auxT)
          {
            if(!strcmp(auxT->getNome(), nomeParte))
            {
              producaoAtual->appendToken(auxT);
              auxP = NULL;
              break;
            }
            auxT = auxT->getProxima();
          }
          while(auxP)
          {
            if(!strcmp(auxP->getNome(), nomeParte))
            {
              producaoAtual->appendProducao(auxP);
              break;
            }
            auxP = auxP->proxima;
          }
          delete [] nomeParte;
        }
        inicio = i;
        blank = true;
      }else
      {
        blank = false;
      }
    }

    linhaProducao = linhaProducao->proxima;
    producaoAtual = producaoAtual->proxima;
  }

  char** nomesConhecidos = new char*[tam];
  tam = 0;

  producaoAtual = resposta;
  while(producaoAtual)
  {
    for(i = 0; i < tam; i++)
    {
      if(!strcmp(producaoAtual->getNome(), nomesConhecidos[i]))
      { producaoAtual->indice = i;
        break;
      }
    }
    if(i == tam)
    {
      producaoAtual->indice = tam;
      nomesConhecidos[tam] = producaoAtual->getNome();
      tam++;
    }

    producaoAtual = producaoAtual->proxima;
  }

  return resposta;
}

std::map<std::string, std::string> Preprocessador::getReducoes()
{
  return reducoes;
}

std::map<std::string, std::string> Preprocessador::getLists()
{
  return lists;
}

