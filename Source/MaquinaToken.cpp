#include <stdio.h>
#include <string.h>
#include <Preprocessador.h>
#include <MaquinaToken.h>

//==================NoSintatico========================
MaquinaToken::NoSintatico::NoSintatico()
{
  operacao = INDEFINIDO;
  proximo = NULL;
  primeiroFilho = NULL;
}

inline bool MaquinaToken::NoSintatico::analizarOU(int* expr, int tam)
{
  int i;
  int inicio = 0;
  int profundidade = 0;
  for(i = 0; i <= tam; i++)
  {
    if(i < tam)
    {
      //if(expr[i] == '\t' || expr[i] == ' ') continue; //funcao atribuida ao preprocessador
      if(expr[i] == Preprocessador::ABRE_PARENTESES) profundidade++;
      if(expr[i] == Preprocessador::FECHA_PARENTESES) profundidade--;
    }
    if((i == tam && primeiroFilho != NULL) || (i < tam && expr[i] == Preprocessador::OU && profundidade == 0))
    {
      operacao = OU;
      NoSintatico* no = new NoSintatico();
      if(!primeiroFilho){primeiroFilho = no;}
      else
      { NoSintatico* aux = primeiroFilho;
        while(aux->proximo){aux = aux->proximo;}
        aux->proximo = no;
      }
      no->analizar(expr + inicio, i-inicio);
      inicio = i+1;
    }
  }
  return primeiroFilho != NULL;
}

inline bool MaquinaToken::NoSintatico::analizarE(int* expr, int tam)
{
  int i;
  int inicio = 0;
  int profundidade = 0;
  for(i = 0; i <= tam; i++)
  {
    if(i < tam)
    {
      //if(expr[i] == '\t' || expr[i] == ' ') continue; //funcao atribuida ao preprocessador
      if(expr[i] == Preprocessador::ABRE_PARENTESES) profundidade++;
      if(expr[i] == Preprocessador::FECHA_PARENTESES) { profundidade--; continue;}
    }
    if(i != inicio && (profundidade == 0 || profundidade == 1 && expr[i] == Preprocessador::ABRE_PARENTESES) &&
       i < tam && expr[i] != Preprocessador::UM_MAIS && expr[i] != Preprocessador::ASTERISCO && expr[i] != Preprocessador::OPCIONAL ||
       primeiroFilho != NULL && tam == i)
    {
      operacao = E;
      NoSintatico* no = new NoSintatico();
      if(!primeiroFilho){primeiroFilho = no;}
      else
      { NoSintatico* aux = primeiroFilho;
        while(aux->proximo){aux = aux->proximo;}
        aux->proximo = no;
      }
      no->analizar(expr + inicio, i-inicio);
      inicio = i;
    }
  }
  return primeiroFilho != NULL;
}

inline bool MaquinaToken::NoSintatico::analizarParenteses(int* expr, int tam)
{
  int i;
  int profundidade = 0;
  if(tam == 1)
  {
    operacao = FOLHA;
    cadeia = expr;
    tamanho = tam;
    return true;
  }else if(tam == 2)
  {
    bool none = false;
    switch(expr[tam-1])
    {
      case Preprocessador::ASTERISCO : operacao = ASTERISCO; break;
      case Preprocessador::UM_MAIS : operacao = UM_MAIS; break;
      case Preprocessador::OPCIONAL : operacao = OPCIONAL; break;
      default: none = true;
    }

    if(!none)
    {
      primeiroFilho = new NoSintatico();
      primeiroFilho->analizar(expr, tam-1);
      return true;
    }
  }
  if(expr[0] != Preprocessador::ABRE_PARENTESES) return false;
  for(i = 0; i < tam; i++)
  {
    if(expr[i] == Preprocessador::ABRE_PARENTESES) profundidade++;
    if(expr[i] == Preprocessador::FECHA_PARENTESES)
    { profundidade--;
      if(profundidade == 0)
      {
        if(i != tam-1 && !(i == tam-2 && (expr[tam-1] == Preprocessador::ASTERISCO ||
                                          expr[tam-1] == Preprocessador::UM_MAIS ||
                                          expr[tam-1] == Preprocessador::OPCIONAL)
                                          )
          )
        {
          return false;
        }else
        {
          switch(expr[tam-1])
          {
            case Preprocessador::ASTERISCO : operacao = ASTERISCO; break;
            case Preprocessador::UM_MAIS : operacao = UM_MAIS; break;
            case Preprocessador::OPCIONAL : operacao = OPCIONAL; break;
            default:
              operacao = PARENTESES;
          }
          primeiroFilho = new NoSintatico();
          primeiroFilho->analizar(expr+1, i-1);
          return true;
        }
      }
    }
  }
  return false;
}

void MaquinaToken::NoSintatico::analizar(int* expr, int tam)
{
  //printf("->%.*s", tam, expr);
  if(analizarParenteses(expr, tam)) return;
  if(analizarOU(expr, tam)) return;
  if(analizarE(expr, tam)) return;
  cadeia = expr;
  tamanho = tam;
  operacao = INDEFINIDO;
}

void MaquinaToken::NoSintatico::print()
{
  if(operacao == ASTERISCO)
  {printf("{AST}(");}
  if(operacao == OU)
  {printf("{OU}(");}
  if(operacao == E)
  {printf("{E}(");}
  if(operacao == PARENTESES)
  {printf("{PAR}(");}
  if(operacao == UM_MAIS)
  {printf("{MAIS}(");}
  if(operacao == OPCIONAL)
  {printf("{OPT}(");}
  if(operacao == INDEFINIDO)
  {printf("{?}(%.*s",tamanho, (char*)cadeia);}
  if(operacao == FOLHA)
  {printf("(%.*s",tamanho, (char*)cadeia);}

  NoSintatico* no = primeiroFilho;
  while(no)
  {
    no->print();
    no = no->proximo;
  }
  printf(")");
}

//===================== ListaEstados ======================
MaquinaToken::ListaEstados::ListaEstados(Estado* e, ListaEstados* p)
{
  estado = e;
  proximo = p;
  ultimo = this;
  if(p != NULL) ultimo = p->ultimo;
}

void MaquinaToken::ListaEstados::unir(ListaEstados* nova)
{
  ultimo->proximo = nova;
  ultimo = nova->ultimo;
}

void MaquinaToken::ListaEstados::desmontar(ListaEstados* lista)
{
  ListaEstados* aux;
  while(lista)
  {
    aux = lista;
    lista = lista->proximo;
    delete aux;
  }
}

bool MaquinaToken::ListaEstados::iguais(ListaEstados* A, ListaEstados* B)
{
  ListaEstados* a, *b;
  a = A;
  while(a != NULL)
  {
    b = B;
    while(b != NULL)
    {
      if(b->estado == a->estado) break;
      b = b->proximo;
    }
    if(b == NULL) break;
    a = a->proximo;
  }
  if(a != NULL) return false;

  b = B;
  while(b != NULL)
  {
    a = A;
    while(a != NULL)
    {
      if(a->estado == b->estado) break;
      a = a->proximo;
    }
    if(a == NULL) break;
    b = b->proximo;
  }
  return b == NULL;
}

//===================== Transicao ======================
const int MaquinaToken::Transicao::VAZIA = 0;

MaquinaToken::Transicao::Transicao(){proxima = NULL;}

MaquinaToken::Transicao::Transicao(Estado* estado, int entrada, Transicao* proxima)
{ this->proximoEstado = estado;
  this->valorEsperado = entrada;
  this->proxima = proxima;
}

MaquinaToken::ListaEstados* MaquinaToken::Transicao::entradaEsperada(int entrada)
{
  ListaEstados* lista = NULL;
  if(entrada == valorEsperado)
  {
    lista = new ListaEstados(proximoEstado, NULL);
    Transicao* trans = proximoEstado->transicoes;
    while(trans != NULL)
    {
      ListaEstados* novos = trans->entradaEsperada(VAZIA);
      if(novos != NULL)
      {
        if(lista != NULL) lista->unir(novos);
        else lista = novos;
      }
      trans = trans->proxima;
    }
  }else if(valorEsperado == VAZIA)
  {
    Transicao* trans = proximoEstado->transicoes;
    while(trans != NULL)
    {
      ListaEstados* novos = trans->entradaEsperada(entrada);
      if(novos != NULL)
      {
        if(lista != NULL) lista->unir(novos);
        else lista = novos;
      }
      trans = trans->proxima;
    }
  }
  return lista;
}

//===================== Estado ======================
MaquinaToken::Estado::Estado(){transicoes = NULL; terminado = false; marca = 0;}

void MaquinaToken::Estado::redirecionarTransicoes(Estado* de, Estado* para)
{
  Transicao* trans = transicoes;
  while(trans)
  { if(trans->proximoEstado == de)
    {
      Estado* novo = new Estado();
      novo->profundidade = this->profundidade+1;
      Transicao* ntrans = de->transicoes;
      while(ntrans)
      {
        novo->transicoes = new Transicao(ntrans->proximoEstado,ntrans->valorEsperado,novo->transicoes);
        if(ntrans->proximoEstado == de) novo->transicoes->proximoEstado = novo;
        ntrans = ntrans->proxima;
      }
      trans->proximoEstado = novo;
      //trans->proximoEstado = para;
    }else
    {
      if(trans->proximoEstado->profundidade > profundidade) trans->proximoEstado->redirecionarTransicoes(de, para);
    }
    trans = trans->proxima;
  }
}

MaquinaToken::ListaEstados* MaquinaToken::Estado::getEstadosAtingiveis(Estado* inicio, int entrada)
{
  ListaEstados* lista = NULL;
  Transicao* trans = transicoes;

  if(entrada == Transicao::VAZIA)
  {
    lista = new ListaEstados(this, lista);
  }
  while(trans)
  {
    if(entrada == trans->valorEsperado)
    {
      lista = new ListaEstados(trans->proximoEstado, lista);
      if(trans->proximoEstado != inicio)
      {
        ListaEstados* novos = trans->proximoEstado->getEstadosAtingiveis(trans->proximoEstado, Transicao::VAZIA);
        if(novos != NULL)
        { lista->unir(novos);}
      }
    }else if(trans->valorEsperado == Transicao::VAZIA && trans->proximoEstado != this)
    {
      lista = new ListaEstados(trans->proximoEstado, lista);
      if(trans->proximoEstado != inicio)
      {
        ListaEstados* novos = trans->proximoEstado->getEstadosAtingiveis(trans->proximoEstado, entrada);
        if(novos != NULL)
        { lista->unir(novos);}
      }
    }
    trans = trans->proxima;
  }
  return lista;
}

void MaquinaToken::Estado::destruir()
{
  marca = 1;
  Transicao* aux;
  while(transicoes)
  {
    if(transicoes->proximoEstado->marca == 0)
    { transicoes->proximoEstado->destruir();
      delete (transicoes->proximoEstado);
    }
    aux = transicoes;
    transicoes = transicoes->proxima;
    delete aux;
  }
}

inline void MaquinaToken::Estado::construirE(NoSintatico* no, Estado* estadoFinal)
{
  NoSintatico* filho = no->primeiroFilho;

  Estado* novoEstado = this;
  while(filho != NULL)
  {
    Estado* proximoEstado = estadoFinal;
    if(filho->proximo != NULL) proximoEstado = new Estado();

    novoEstado->construir(filho, proximoEstado);

    filho = filho->proximo;
    novoEstado = proximoEstado;
  }
}

inline void MaquinaToken::Estado::construirOU(NoSintatico* no, Estado* estadoFinal)
{
  NoSintatico* filho = no->primeiroFilho;
  while(filho != NULL)
  {
    Estado* novo = new Estado();
    transicoes = new Transicao(novo, Transicao::VAZIA, transicoes);
    novo->construir(filho, estadoFinal);
    filho = filho->proximo;
  }
}

inline void MaquinaToken::Estado::construirESP(NoSintatico* no, Estado* estadoFinal)
{
  Estado* novo;
  Estado* intermediario;
  switch(no->operacao)
  {
    case ASTERISCO:
      transicoes = new Transicao(estadoFinal, Transicao::VAZIA, transicoes);
      novo = new Estado();
      transicoes = new Transicao(novo, Transicao::VAZIA, transicoes);
      novo->construir(no->primeiroFilho, this);
    break;
    case UM_MAIS:
      intermediario = new Estado();
      intermediario->transicoes = new Transicao(estadoFinal, Transicao::VAZIA, intermediario->transicoes);
      intermediario->construir(no->primeiroFilho, intermediario);
      construir(no->primeiroFilho, intermediario);
    break;
    case OPCIONAL:
      transicoes = new Transicao(estadoFinal, Transicao::VAZIA, transicoes);
      Estado* novo = new Estado();
      transicoes = new Transicao(novo, Transicao::VAZIA, transicoes);
      novo->construir(no->primeiroFilho, estadoFinal);
    break;
  }
}

void MaquinaToken::Estado::construir(NoSintatico* no, Estado* estadoFinal)
{
  static int profundidade = 0;
  this->profundidade = profundidade++;
  while(no->operacao == PARENTESES) no = no->primeiroFilho;
  switch(no->operacao)
  {
    case OperacaoSintatica::E : construirE(no, estadoFinal); break;
    case OperacaoSintatica::OU : construirOU(no, estadoFinal); break;
    case OperacaoSintatica::FOLHA : transicoes = new Transicao(estadoFinal, no->cadeia[0], transicoes);
    default: construirESP(no, estadoFinal);
  }
}

void MaquinaToken::Estado::desmarcar()
{
  Transicao* t = transicoes;
  marca = 0;
  while(t != NULL)
  {
    if(t->proximoEstado->marca > 0) t->proximoEstado->desmarcar();
    t = t->proxima;
  }
}

void MaquinaToken::Estado::print()
{
  Transicao* t = transicoes;
  marca = 1;
  if(terminado) printf("*");
  while(t != NULL)
  {
    if(t->valorEsperado != 0)
      printf("(%i:%c)->{",profundidade,(char)t->valorEsperado);
    else printf("(%i:$)->{", profundidade);
    if(t->proximoEstado->marca) printf("^%i", t->proximoEstado->profundidade);
    else t->proximoEstado->print();
    printf("}");
    t = t->proxima;
  }
}

void MaquinaToken::Estado::joinArray(Estado** lista, int &pos)
{
  Transicao* t = transicoes;
  marca = 1;
  lista[pos] = this;
  pos++;
  while(t != NULL)
  {
    if(!t->proximoEstado->marca)
    {
      t->proximoEstado->joinArray(lista, pos);
    }
    t = t->proxima;
  }
}

int MaquinaToken::Estado::contar()
{
  Transicao* t = transicoes;
  marca = 1;
  int contador = 1;
  while(t != NULL)
  {
    if(!t->proximoEstado->marca)
    {
      contador += t->proximoEstado->contar();
    }
    t = t->proxima;
  }
  return contador;
}

//===================== MaquinaToken ======================

char* MaquinaToken::getNome()
{
  return nome;
}

int MaquinaToken::getNumEstados()
{
  estadoInicial->desmarcar();
  return estadoInicial->contar();
}

MaquinaToken::Estado** MaquinaToken::getEstados()
{
  int numEstados = getNumEstados();
  Estado** estados = new Estado*[numEstados+1];
  estados[numEstados] = NULL;
  int pos = 0;
  estadoInicial->desmarcar();
  estadoInicial->joinArray(estados, pos);
  return estados;
}

std::string MaquinaToken::getNomeCanonico(std::string prefixo)
{
  if(nome[0] == '*') return prefixo + (nome+1);
  return prefixo + nome;
}

bool MaquinaToken::ignore()
{
  return (nome[0] == '*');
}

void MaquinaToken::print()
{
  estadoInicial->print();
}

MaquinaToken* MaquinaToken::getProxima()
{
  return proxima;
}

void MaquinaToken::trasformarEmDeterministico(Estado* atual, Lista<Estado>* novosEstados,
                                              Hash<Estado*, ListaEstados> *mapaEstados)
{
  bool root = false;
  if(atual == NULL)
  {
    root = true;
    atual = new Estado;

    mapaEstados = new Hash<Estado*, ListaEstados>;

    ListaEstados* atingiveis = estadoInicial->getEstadosAtingiveis(estadoInicial, Transicao::VAZIA);
    novosEstados = new Lista<Estado>(atual, novosEstados);
    mapaEstados->add(atual, atingiveis);

    while(atingiveis)
    {
      if(atingiveis->estado->terminado) atual->terminado = true;
      atingiveis = atingiveis->proximo;
    }
  }

  Hash<int, ListaEstados> transicoesUsadas;

  ListaEstados* atingiveis = mapaEstados->get(atual);
  while(atingiveis != NULL)
  {
    Transicao* trans = atingiveis->estado->transicoes;
    while(trans != NULL)
    {
      if(trans->valorEsperado != NULL)
      {
        ListaEstados* aglomerado = trans->proximoEstado->getEstadosAtingiveis(trans->proximoEstado, Transicao::VAZIA);
        ListaEstados* existente = transicoesUsadas.get(trans->valorEsperado);
        if(existente == NULL)
        {
          transicoesUsadas.add(trans->valorEsperado, aglomerado);
        }else
        {
          existente->unir(aglomerado); //TODO: Remover duplicidades
        }
      }
      trans = trans->proxima;
    }
    atingiveis = atingiveis->proximo;
  }

  Lista<int>* aux;
  Lista<int>* chaves = transicoesUsadas.getAllKeys();
  aux = chaves;
  while(aux)
  {
    ListaEstados* aglomerado = transicoesUsadas.get(*(aux->objeto));
    Lista<Estado>* auxNovos = novosEstados;
    while(auxNovos)
    {
      if(ListaEstados::iguais(aglomerado,mapaEstados->get(auxNovos->objeto)))
      { break;}
      auxNovos = auxNovos->proximo;
    }

    if(auxNovos)
    { //j� existe estado com essa assinatura
      atual->transicoes = new Transicao(auxNovos->objeto, *(aux->objeto), atual->transicoes);
      ListaEstados::desmontar(aglomerado);
    }else
    { //cria estado com a assinatura
      Estado* novo = new Estado;
      novosEstados = new Lista<Estado>(novo, novosEstados);
      atual->transicoes = new Transicao(novo, *(aux->objeto), atual->transicoes);
      mapaEstados->add(novo, aglomerado);

      while(aglomerado)
      {
        if(aglomerado->estado->terminado) novo->terminado = true;
        aglomerado = aglomerado->proximo;
      }

      trasformarEmDeterministico(novo, novosEstados, mapaEstados);
    }
    aux = aux->proximo;
  }

  Lista<int>::desmontar(chaves);

  if(root)
  {
    destruirEstados();
    estadoInicial = atual;
    Lista<Estado>::desmontar(novosEstados);
  }
}

void MaquinaToken::destruirEstados()
{
  estadoInicial->desmarcar();
  estadoInicial->destruir();
  delete estadoInicial;
}

MaquinaToken::MaquinaToken(char* nome, int* expressaoProcessada, int tamanhoExpressao, MaquinaToken* proxima)
{
  this->proxima = proxima;
  this->nome = nome;

  if(tamanhoExpressao == 0) return;
  NoSintatico* raiz = new NoSintatico();
  raiz->analizar(expressaoProcessada, tamanhoExpressao);

  estadoInicial = new Estado();
  Estado* estadoFinal = new Estado();
  estadoFinal->profundidade = 100000;
  estadoFinal->terminado = true;
  estadoInicial->construir(raiz, estadoFinal);
  //printf("\n\nToken: %s\n", nome);//getchar();
  /*printf("Analize sintatica:");
  raiz->print();
  printf("\nAutomato:\n");
  estadoInicial->desmarcar();
  estadoInicial->print();
  estadoInicial->desmarcar();*/
  trasformarEmDeterministico();
  /*printf("\nAutomato deterministico:\n");
  estadoInicial->desmarcar();
  estadoInicial->print();
  printf("\n");
  getchar();*/
  reiniciar();
}

void MaquinaToken::reiniciar()
{
  estadoInicial->desmarcar();
  numEstadosAtuais = 1;
  estadosAtuais[0] = estadoInicial;
  Transicao* transicaoAtual = estadoInicial->transicoes;
  while(transicaoAtual != NULL)
  {
    ListaEstados* listaPossibilidades = transicaoAtual->entradaEsperada(Transicao::VAZIA);
    while(listaPossibilidades != NULL)
    {
      ListaEstados* aux = listaPossibilidades;
      estadosAtuais[numEstadosAtuais] = listaPossibilidades->estado;
      numEstadosAtuais++;
      if(numEstadosAtuais >= MaquinaTokenMAXESTADOS){ throw 1;} //Excedeu o n�mero m�ximo de estados atuais
      listaPossibilidades = listaPossibilidades->proximo;
      delete aux;
    }
    transicaoAtual = transicaoAtual->proxima;
  }
}

bool MaquinaToken::finalizada()
{
  int e;
  for(e = 0; e < numEstadosAtuais; e++)
  {
    if(estadosAtuais[e]->terminado) return true;
  }
  return false;
}

bool MaquinaToken::possuiEscritaUnica()
{
  MaquinaToken::Estado* aux = estadoInicial;

  while(aux != NULL && !aux->terminado)
  {
    if(aux->transicoes != NULL)
    {
      if(aux->transicoes->proxima != NULL) return false;
      aux = aux->transicoes->proximoEstado;
    }else
    { return false;}
  }

  if(aux == NULL) return false;
  if(aux->transicoes != NULL) return false;

  return true;
}

std::string MaquinaToken::getEscritaUnica()
{
  std::string ret = "";
  MaquinaToken::Estado* aux = estadoInicial;

  while(aux != NULL && !aux->terminado)
  {
    if(aux->transicoes != NULL)
    {
      ret += (char)aux->transicoes->valorEsperado;
      if(aux->transicoes->proxima != NULL) return "";
      aux = aux->transicoes->proximoEstado;
    }else
    { return "";}
  }

  if(aux == NULL) return "";
  if(aux->transicoes != NULL) return "";

  return ret;
}

bool MaquinaToken::isAlive()
{
  return numEstadosAtuais > 0;
}

bool MaquinaToken::validarCadeia(char* cadeia)
{
  reiniciar();
  int i;
  for(i = 0; i < strlen(cadeia); i++)
  {
    if(!operar((int)(unsigned char)cadeia[i])) return false;
  }
  return finalizada();
}

bool MaquinaToken::operar(int entrada)
{
  int numNovosEstadosAtuais = 0;
  Estado* novosEstadosAtuais[MaquinaTokenMAXESTADOS]; //estados atuais ap�s a execu��o desta fun��o

  //printf("entrada: %c", entrada); getchar();

  int e; //estados
  for(e = 0; e < numEstadosAtuais; e++)
  {
    Transicao* transicaoAtual;
    for(transicaoAtual = estadosAtuais[e]->transicoes; transicaoAtual != NULL; transicaoAtual = transicaoAtual->proxima)
    {
      ListaEstados* listaPossibilidades = transicaoAtual->entradaEsperada(entrada);
      while(listaPossibilidades != NULL)
      {
        if(transicaoAtual->valorEsperado == Transicao::VAZIA) listaPossibilidades = listaPossibilidades->proximo;
        ListaEstados* aux = listaPossibilidades;
        novosEstadosAtuais[numNovosEstadosAtuais] = listaPossibilidades->estado;
        numNovosEstadosAtuais++;
        if(numNovosEstadosAtuais >= MaquinaTokenMAXESTADOS){ printf("excedeu o numero maximo de estados"); throw 2;} //Excedeu o n�mero m�ximo de estados atuais
        listaPossibilidades = listaPossibilidades->proximo;
        delete aux;
      }
      //printf("transicao: %c -> %i\n", transicaoAtual->valorEsperado,numNovosEstadosAtuais);
      //getchar();
    }
  }

  memcpy(estadosAtuais, novosEstadosAtuais, MaquinaTokenMAXESTADOS*sizeof(Estado*));
  numEstadosAtuais = numNovosEstadosAtuais;
  return numEstadosAtuais > 0;
}
