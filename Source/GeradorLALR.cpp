#include <Utilitarios.h>
#include <ctype.h>
#include <string.h>
#include <GeradorLALR.h>

FILE * arquivo = NULL;

int salada = 0;

//Item
void GeradorLALR::Item::expandir(Producao* producoes, GeradorLALR::Item* inicial)
{
  Item* aux = inicial;
  while(aux)
  {
    //aux->proximoEstado = NULL;
    //aux->print(0);
    Producao::Parte* parteAtual = NULL;
    if(aux->posicaoPonto < aux->producao->numPartes)
    {
      parteAtual = &(aux->producao->partes[aux->posicaoPonto]);
    }

    if(parteAtual && parteAtual->producao)
    {
      Producao* auxProd = producoes;
      while(auxProd)
      {
        if(!strcmp(parteAtual->producao->getNome(), auxProd->getNome()))
        {
          Item* novo = new Item(auxProd, aux->proximo);
          novo->lookaheads = aux->getSeguinte(producoes);
          if(!inicial->possuiItem(novo))
          {
            aux->proximo = novo;
          }
          else
          {
            novo->proximo = NULL;
            delete novo;
          }
        }
        auxProd = auxProd->proxima;
      }
    }
    aux = aux->proximo;
  }

  Item* aglutinado = inicial;
  while(aglutinado)
  {
    Item* anterior = aglutinado;
    aux = aglutinado->proximo;
    while(aux)
    {
      if(aglutinado->nucleoIgual(aglutinado, aux))
      {
        anterior->proximo = aux->proximo;
        aglutinado->absorver(aux);
        aux = anterior->proximo;
      }
      else
      {
        anterior = aux;
        aux = aux->proximo;
      }
    }

    aglutinado = aglutinado->proximo;
  }
}

Lookahead* GeradorLALR::Item::getSeguinte(Producao* producoes)
{
  if(posicaoPonto+1 >= producao->numPartes){return Lookahead::copiar(lookaheads);}
  if(producao->partes[posicaoPonto+1].token) return new Lookahead(producao->partes[posicaoPonto+1].token, NULL);
  return producao->partes[posicaoPonto+1].producao->getFirsts(producoes);
}

bool GeradorLALR::Item::igual(GeradorLALR::Item* A, GeradorLALR::Item* B)
{
  return (A->producao == B->producao) && (A->posicaoPonto == B->posicaoPonto) && Lookahead::igual(A->lookaheads, B->lookaheads);
}

bool GeradorLALR::Item::nucleoIgual(GeradorLALR::Item* A, GeradorLALR::Item* B)
{
  return (A->producao == B->producao) && (A->posicaoPonto == B->posicaoPonto);
}

bool GeradorLALR::Item::possuiItem(GeradorLALR::Item* item)
{
  Item* auxItem = this;

  while(auxItem)
  {
    if(Item::igual(auxItem, item))
    {
      return true;
    }
    auxItem = auxItem->proximo;
  }
  return false;
}

GeradorLALR::Item* GeradorLALR::Item::possuiItemParecido(GeradorLALR::Item* item)
{
  Item* auxItem = this;

  while(auxItem)
  {
    if(Item::nucleoIgual(auxItem, item))
    {
      return auxItem;
    }
    auxItem = auxItem->proximo;
  }
  return NULL;
}



void GeradorLALR::Item::absorver(GeradorLALR::Item* vitima)
{
  vitima->proximoEstado = NULL;
  lookaheads = Lookahead::mesclar(lookaheads, vitima->lookaheads);
  vitima->lookaheads = NULL;
  vitima->proximo = NULL;
  delete vitima;
}

bool GeradorLALR::Item::esperamAMesmaCoisa(Item* A, Item* B)
{
  if(A->posicaoPonto < A->producao->numPartes && B->posicaoPonto < B->producao->numPartes)
  {
    Producao::Parte* pA = &(A->producao->partes[A->posicaoPonto]);
    Producao::Parte* pB = &(B->producao->partes[B->posicaoPonto]);
    if(pA->token == NULL && pB->token == NULL)
    {
      return !strcmp(pA->producao->getNome(), pB->producao->getNome());
    }else if(pA->producao == NULL && pB->producao == NULL)
    {
      return pA->token == pB->token;
    }
  }
  return false;
}

GeradorLALR::Item::~Item()
{
  if(proximoEstado)
  {
    if(proximoEstado->marca == 0)
    {
      delete proximoEstado;
    }
  }
  if(proximo) delete proximo;
  Lookahead::destruir(lookaheads);
}

void GeradorLALR::Item::print(int identacao)
{
  fprintf(arquivo,"%*s", identacao, "");
  producao->print(arquivo, posicaoPonto);
  fprintf(arquivo," , ");
  if(!lookaheads) fprintf(arquivo,"$");
  else lookaheads->print(arquivo);
  if(proximoEstado) fprintf(arquivo," -> %i", proximoEstado->indice);
  fprintf(arquivo,"\n");
}

GeradorLALR::Item::Item(Producao* producao, GeradorLALR::Item* proximo)
{
  this->producao = producao;
  posicaoPonto = 0;
  lookaheads = NULL;
  proximoEstado = NULL;
  this->proximo = proximo;
}

GeradorLALR::Item::Item(GeradorLALR::Item* anterior, GeradorLALR::Item* proximo)
{
  producao = anterior->producao;
  posicaoPonto = anterior->posicaoPonto+1;
  proximoEstado = NULL;
  lookaheads = Lookahead::copiar(anterior->lookaheads);

  this->proximo = proximo;
}

//Transicao
/*  Estado* proximoEstado;
  Transicao* proxima;
  int producaoEsperada;
  int tokenEsperado;
*/

//Estado

void GeradorLALR::Estado::print()
{
  Item* it = item;
  marca = 1;
  int identacao = 0;
  fprintf(arquivo,"%*s\n",identacao,"(");
  fprintf(arquivo,"%*sindice:%i\n",identacao+2,"", indice);
  while(it)
  {
    it->print(identacao + 2);
    it = it->proximo;
  }
  fprintf(arquivo,"%*s\n",identacao,")");
}

void GeradorLALR::Estado::print(int identacao)
{
  Item* it = item;
  marca = 1;
  fprintf(arquivo,"%*s\n",identacao,"(");
  fprintf(arquivo,"%*sindice:%i\n",identacao+2,"", indice);
  while(it)
  {
    it->print(identacao + 2);
    it = it->proximo;
  }
  fprintf(arquivo,"%*s\n",identacao,")");

  bool temProximo = false;
  it = item;
  while(it)
  {
    if(it->proximoEstado){temProximo = true;}
    it = it->proximo;
  }

  if(temProximo) fprintf(arquivo,"%*s\n",identacao,"{");
  it = item;
  while(it)
  {
    if(it->proximoEstado){
    if(!it->proximoEstado->marca) it->proximoEstado->print(identacao + 2);
    else fprintf(arquivo,"%*s %i\n",identacao+2,"->", it->proximoEstado->indice);}
    it = it->proximo;
  }
  if(temProximo) fprintf(arquivo,"%*s\n",identacao,"}");
}

bool GeradorLALR::Estado::parecido(GeradorLALR::Estado* A, GeradorLALR::Estado* B)
{
  int numItemsA = 0, numItemsB = 0;
  Item* auxA = A->item, *auxB;

  auxA = A->item;
  while(auxA)
  {
    numItemsA++;
    auxA = auxA->proximo;
  }

  auxB = B->item;
  while(auxB)
  {
    numItemsB++;
    auxB = auxB->proximo;
  }

  if(numItemsA != numItemsB) return false;

  auxA = A->item;

  while(auxA)
  {
    auxB = B->item;
    while(auxB)
    {
      if(Item::nucleoIgual(auxA, auxB))
      { break;}
      auxB = auxB->proximo;
    }

    if(!auxB) return false;

    auxA = auxA->proximo;
  }

  return true;
}

bool GeradorLALR::Estado::igual(GeradorLALR::Estado* A, GeradorLALR::Estado* B)
{
  int numItemsA = 0, numItemsB = 0;
  Item* auxA = A->item, *auxB;

  auxA = A->item;
  while(auxA)
  {
    numItemsA++;
    auxA = auxA->proximo;
  }

  auxB = B->item;
  while(auxB)
  {
    numItemsB++;
    auxB = auxB->proximo;
  }

  if(numItemsA != numItemsB) return false;

  auxA = A->item;

  while(auxA)
  {
    auxB = B->item;
    while(auxB)
    {
      if(Item::igual(auxA, auxB))
      { break;}
      auxB = auxB->proximo;
    }

    if(!auxB) return false;

    auxA = auxA->proximo;
  }

  return true;
}

void GeradorLALR::Estado::absorver(GeradorLALR::Estado* B)
{
  Item* aux = item;

  if(!aux) item = B->item;
  else
  {
    while(aux->proximo)
    {
      aux = aux->proximo;
    }
    aux->proximo = B->item;

    removerItensDuplicados();
  }

  B->item = NULL;
}

void GeradorLALR::Estado::joinArray(Estado** vetor, int& indice)
{
  vetor[indice] = this;
  this->indice = indice++;
  marca = 1;
  Item* aux = item;
  while(aux)
  {
    if(aux->proximoEstado && aux->proximoEstado->marca == 0) aux->proximoEstado->joinArray(vetor, indice);
    aux = aux->proximo;
  }
}

void GeradorLALR::Estado::desmarcarTodos()
{
  marca = 0;
  Item* aux = item;
  while(aux)
  {
    if(aux->proximoEstado && aux->proximoEstado->marca != 0)
    {
      aux->proximoEstado->desmarcarTodos();
    }
    aux = aux->proximo;
  }
}

GeradorLALR::Estado::Estado(GeradorLALR::Item* primeiroItem, GeradorLALR::Estado* pai)
{
  this->pai = pai;
  item = primeiroItem;
  marca = 0;
  indice = -1;
}

GeradorLALR::Estado::~Estado()
{
  marca = 1;
  if(item)
  {
    delete item;
  }
}

//Tabela

//GeradorLALR

GeradorLALR::Estado* GeradorLALR::getEstadoIdentico(GeradorLALR::Estado* estado)
{
  Estado* ret = NULL;
  int i;

  for(i = 0; i < numEstados; i++)
  {
    if(todosEstados[i]->igual(todosEstados[i], estado))
    {
      ret = todosEstados[i];
      break;
    }
  }

  for(i = 0; i < numEstados; i++)
  { todosEstados[i]->marca = 0;}

  return ret;
}

void GeradorLALR::expandirEstado(GeradorLALR::Estado* estadoAtual)
{
  todosEstados[numEstados] = estadoAtual;
  estadoAtual->indice = numEstados;
  numEstados++;
  salada = numEstados;

  if(estadoAtual == inicial)
  {
    Item::expandir(producoes, estadoAtual->item);
  }

  printf("Estado: %i\n", numEstados);
  //fprintf(arquivo ,"=== Novo estado ===\n");

  Item* aux = estadoAtual->item;
  while(aux)
  {
    if(aux->posicaoPonto < aux->producao->numPartes && !aux->proximoEstado)
    {
      Item* novos = new Item(aux, NULL);
      Estado* proximoEstado = new Estado(NULL, estadoAtual);
      aux->proximoEstado = proximoEstado;
      Item* mesmaTransicao = aux->proximo;

      while(mesmaTransicao)
      {
        if(mesmaTransicao != aux && Item::esperamAMesmaCoisa(aux, mesmaTransicao))
        {
          mesmaTransicao->proximoEstado = proximoEstado;
          Item* brandNew = new Item(mesmaTransicao, novos);
          Item* parecido = novos->possuiItemParecido(brandNew);
          if(!parecido)
          {
            novos = brandNew;
          }else
          {
            parecido->absorver(brandNew);
          }
        }
        mesmaTransicao = mesmaTransicao->proximo;
      }

      proximoEstado->item = novos;
      Item::expandir(producoes, novos);

      Estado* estadoExistente = getEstadoIdentico(proximoEstado);
      if(estadoExistente)
      {
        mesmaTransicao = aux;
        while(mesmaTransicao)
        {
          if(mesmaTransicao->proximoEstado == proximoEstado)
          {
            mesmaTransicao->proximoEstado = estadoExistente;
          }
          mesmaTransicao = mesmaTransicao->proximo;
        }

        delete proximoEstado;
      }
      else
      {
        expandirEstado(proximoEstado);
      }
    }

    aux = aux->proximo;
  }
}

GeradorLALR::Estado** GeradorLALR::getEstadoArray()
{
  Estado** estados = todosEstados;
  inicial->desmarcarTodos();
  int indice = 0;
  inicial->joinArray(estados, indice);
  return estados;
}

void GeradorLALR::Estado::redirecionar(Estado* de, Estado* para)
{
  Item* aux = item;

  while(aux)
  {
    if(aux->proximoEstado == de)
    {
      aux->proximoEstado = para;
    }
    aux = aux->proximo;
  }
}

void GeradorLALR::Estado::removerItensDuplicados()
{
  Item* principal = item;
  while(principal)
  {
    Item* anterior = principal;
    Item* secundario = principal->proximo;
    while(secundario)
    {
      if(Item::nucleoIgual(principal, secundario))
      {
        anterior->proximo = secundario->proximo;
        principal->absorver(secundario);
        secundario = anterior;
      }
      else
      {
        anterior = secundario;
      }

      secundario = secundario->proximo;
    }

    principal = principal->proximo;
  }
}

void GeradorLALR::reduzirEstados()
{
  //Verifica se o estado possui os mesmos itens que outro (ignorando os lookaheads)
  //Faz o merge (Deve redirecionar todos os itens que apontam para o estado excluido)
  int i,j,k;

  int totalEstadosExcluidos = 0;

  Estado** estados = getEstadoArray();

  Lista<Estado>* aExcluir = NULL;
  inicial->desmarcarTodos();

  // Mescla itens repetidos dentro dos estados
  for(i = 0; i < numEstados; i++)
  {
    estados[i]->removerItensDuplicados();
  }

  // Mescla estados
  for(i = 0; i < numEstados; i++)
  {
    if(estados[i] == NULL) continue;
    int numEstadosParecidos = 0;
    int* indices = new int [numEstados];
    for(j = i; j < numEstados; j++)
    {
      if(i != j && estados[j] && Estado::parecido(estados[i],estados[j]))
      {
        indices[numEstadosParecidos] = j;
        numEstadosParecidos++;
      }
    }
    for(j = 0; j < numEstadosParecidos; j++)
    {
       Estado* vitima = estados[indices[j]];
       estados[i]->absorver(vitima);
       estados[indices[j]] = NULL;

       for(k = 0; k < numEstados; k++)
       { if(estados[k] != NULL) estados[k]->redirecionar(vitima, estados[i]);}

       totalEstadosExcluidos++;
       aExcluir = new Lista<Estado>(vitima, aExcluir);
    }
    delete [] indices;
  }

  Lista<Estado>::destruir(aExcluir);
  numEstados -= totalEstadosExcluidos;
}

bool GeradorLALR::gerarTabela()
{
  bool ret = true;
  Hash<void*, OperacaoTabela>* auxTabela;

  int i;
  Estado* estadoAtual;
  int numEstados = getNumEstados();
  Estado** arrayEstados = getEstadoArray();

  tabelaAcao = new Hash<void*, OperacaoTabela>[numEstados];
  tabelaGoto = new Hash<void*, OperacaoTabela>[numEstados];
  inicial->desmarcarTodos();

  for(i = 0; i < numEstados; i++)
  {
    estadoAtual = arrayEstados[i];
    if(estadoAtual->indice == 395)
    {
      printf("aaaaaa");
    }

    Item* item = estadoAtual->item;
    while(item)
    {
      OperacaoTabela* op, *opAtual;
      void* chave;
      if(item->posicaoPonto < item->producao->numPartes)
      {
        op = new OperacaoTabela;
        op->gotoEstado = item->proximoEstado->indice;
        chave = item->producao->partes[item->posicaoPonto].token;
        if(chave != NULL)
        {
          op->tipo = OperacaoTabela::SHIFT;
          auxTabela = tabelaAcao;

          //printf("Estado %i ao receber %s vai para %i\n", estadoAtual->indice, ((MaquinaToken*)chave)->getNome(), op->gotoEstado);
        }else
        {
          // Caso consumindo uma producao
          chave = (void*)(item->producao->partes[item->posicaoPonto].producao->indice);
          op->tipo = OperacaoTabela::GOTO;
          auxTabela = tabelaGoto;
          //printf("No estado %i a producao receber %s direciona para %i\n", estadoAtual->indice,
          //        item->producao->partes[item->posicaoPonto].producao->getNome(), op->gotoEstado);
        }

        opAtual = auxTabela[estadoAtual->indice].get(chave);

        if(opAtual != NULL && opAtual->tipo == OperacaoTabela::REDUCE)
        {
          if(betterShiftThanReduce)
          {
            printf("Better shift...\n");
            auxTabela[estadoAtual->indice].replace(chave, op);
            delete opAtual;
          }else
          {
            printf("ERRO!\n");
            ret = false;
            delete op;
          }
        }
        else if(opAtual != NULL)
        {
          delete op;
        }
        else
        {
          auxTabela[estadoAtual->indice].add(chave, op);
        }
      }else
      {
        Lookahead* lookahead = item->lookaheads;
        auxTabela = tabelaAcao;

        if(!lookahead)
        {
          op = new OperacaoTabela;
          op->gotoProducao = item->producao;
          if(item->producao->indice == -1) op->tipo = OperacaoTabela::ACCEPT;
          else op->tipo = OperacaoTabela::REDUCE;
          chave = NULL;
          //printf("Estado %i ao ver %s reduz para %s\n", estadoAtual->indice,
          //      "$",item->producao->getNome());
          opAtual = auxTabela[estadoAtual->indice].get(chave);
          if(!opAtual || reduceReduceAccepted)
          {
            if(opAtual) printf("Adding reduce reduce\n");
            auxTabela[estadoAtual->indice].add(chave, op);
          }
          else
          {
            reportarConflito(estadoAtual, (MaquinaToken*)chave, op, op);
            ret = false;

            delete op;
          }
        }

        while(lookahead)
        {
          op = new OperacaoTabela;
          op->gotoProducao = item->producao;
          op->tipo = OperacaoTabela::REDUCE;
          chave = lookahead->tokenEsperado;

          //if(lookahead->tokenEsperado) printf("Estado %i ao ver %s reduz para %s\n", estadoAtual->indice, lookahead->tokenEsperado->getNome(), item->producao->getNome());
          //else printf("Estado %i ao ver %s reduz para %s\n", estadoAtual->indice, "$", item->producao->getNome());

          opAtual = auxTabela[estadoAtual->indice].get(chave);
          if(opAtual == NULL)
          {
            auxTabela[estadoAtual->indice].add(chave, op);
          }else
          {
            if(opAtual->tipo == op->tipo && opAtual->gotoProducao == op->gotoProducao)
            {
              delete op;
              op = opAtual;
            }else if(opAtual->tipo != OperacaoTabela::REDUCE && op->tipo == OperacaoTabela::REDUCE && betterShiftThanReduce)
            {
              //Decide sempre pelo shift e n�o pelo reduce
              delete op;
            }else
            {
              if(!opAtual || reduceReduceAccepted)
              {
                if(opAtual) printf("Adding reduce reduce\n");
                auxTabela[estadoAtual->indice].add(chave, op);
              }
              else
              {
                reportarConflito(estadoAtual, (MaquinaToken*)chave, op, op);
                ret = false;

                delete op;
              }
            }
          }
          lookahead = lookahead->proximo;
        }
      }
      item = item->proximo;
    }
  }

  return ret;
}

void GeradorLALR::reportarConflito(Estado* conflitante, MaquinaToken* chave, OperacaoTabela* a, OperacaoTabela* b)
{
  Estado* hierarquia;
  char* operacao;
  switch(a->tipo)
  {
    case OperacaoTabela::SHIFT: operacao = (char*)"shift"; break;
    case OperacaoTabela::REDUCE: operacao = (char*)"reduce"; break;
    default: operacao = (char*)"goto";
  }
  if(a->tipo == b->tipo && a->tipo == OperacaoTabela::REDUCE)
  {
    printf("Em:\n");
    hierarquia = conflitante;
    while(hierarquia)
    {
      printf("^->"); hierarquia->item->print(0);
      hierarquia = hierarquia->pai;
    }
  }
  printf("Erro (%i, %s): Conflito de %s/", conflitante->indice, chave->getNome(), operacao);
  switch(b->tipo)
  {
    case OperacaoTabela::SHIFT: operacao = (char*)"shift"; break;
    case OperacaoTabela::REDUCE: operacao = (char*)"reduce"; break;
    default: operacao = (char*)"goto";
  }
  printf("%s\n--------------\n", operacao);
  Item* item = conflitante->item;
  while(item)
  {
    if(item->producao->partes[item->posicaoPonto].token == chave || item->lookaheads->possui(chave) && (item->producao->numPartes == item->posicaoPonto))
      item->print(0);
    item = item->proximo;
  }
  printf("\n------------------\n");
}

bool GeradorLALR::analizar(Lista<Token>* tokens)
{
  bool ret = false;
  int i;

  void** pilhaNos = new void*[10000];
  void** pilha = new void*[10000];
  int posNos = 0;
  int posPilha = 0;
  pilha[0] = (void*)0;

  Token* dollar = new Token;
  dollar->tipo = 0;
  dollar->conteudo = (char*)"$";
  dollar->linha = -1;
  dollar->ignorado = false;
  dollar->tamanho = 1;

  Token* objeto = NULL;

  //Estado** estados = getEstadoArray();

  while(posPilha >= 0)
  {
    if(!tokens || (tokens && !tokens->objeto->ignorado))
    {
      objeto = dollar;
      if(tokens) objeto = tokens->objeto;
//      printf("Estado %i -> %s:\n", pilha[posPilha], objeto->conteudo);
      //*
      //estados[(int)(pilha[posPilha])]->print();
      //if(objeto->tipo == NULL) printf("Recebeu token: %s : %s ->\n", "{DOLLAR}", objeto->conteudo);
      //else printf("Recebeu token: %s : %s ->\n", objeto->tipo->getNome(), objeto->conteudo);
      //getchar();
      //*/

      OperacaoTabela* op = tabelaAcao[(long long)(pilha[posPilha])].get(objeto->tipo);
      if(!op)
      {
        if(objeto == dollar){printf("Erro sintatico (%i,%i). Fim da entrada inesperado. Esperava os tokens: ", objeto->linha, objeto->coluna);}
        else printf("Erro sintatico (%i,%i). Encontrou %s e esperava:", objeto->linha, objeto->coluna, objeto->tipo->getNome());
        Lista<void*>* lista = tabelaAcao[(long long)(pilha[posPilha])].getAllKeys();
        while(lista)
        {
          if((*((MaquinaToken**)(lista->objeto))))
          {
            printf("->%s  ", (*((MaquinaToken**)(lista->objeto)))->getNome());
          }else
          {
            printf("o fim da entrada");
          }
          lista = lista->proximo;
        }
        Lista<void*>::desmontar(lista);
        break;
      }else
      {
        if(op->tipo == OperacaoTabela::SHIFT)
        {
          pilhaNos[posNos++] = objeto;
          pilha[posPilha+1] = objeto->tipo;
          pilha[posPilha+2] = (void*)(op->gotoEstado);
          posPilha += 2;
          tokens = tokens->proximo;
        }else if(op->tipo == OperacaoTabela::REDUCE)
        {
          NoProducao* no = new NoProducao(op->gotoProducao);
          posNos -= op->gotoProducao->numPartes;
          for(i = 0; i < op->gotoProducao->numPartes; i++)
          {
            if(op->gotoProducao->partes[i].token)
            { no->addToken((Token*)pilhaNos[posNos+i], i);}
            else
            { no->addProducao((NoProducao*)pilhaNos[posNos+i], i);}
          }
          pilhaNos[posNos] = no;
          posNos++;
          arvoreSintatica = no;

          posPilha -= op->gotoProducao->numPartes*2;
          pilha[posPilha+1] = op->gotoProducao;
          pilha[posPilha+2] = (void*)(tabelaGoto[(long long)(pilha[posPilha])].get((void*)(op->gotoProducao->indice))->gotoEstado);
          posPilha += 2;
        }else if(op->tipo == OperacaoTabela::ACCEPT)
        {
          printf("Sintaticamente correto!\n");
          ret = true;
          break;
        }
      }
    }else
    { tokens = tokens->proximo;}
  }

  delete dollar;
  delete [] pilha;

  return ret;
}

NoProducao* GeradorLALR::getArvoreSintatica()
{
  return arvoreSintatica;
}

Hash<void*, GeradorLALR::OperacaoTabela>* GeradorLALR::getTabelaAcao()
{
  return tabelaAcao;
}

Hash<void*, GeradorLALR::OperacaoTabela>* GeradorLALR::getTabelaGoto()
{
  return tabelaGoto;
}

void GeradorLALR::printArvoreSintatica(NoProducao* no, int identacao)
{
  if(no == NULL) no = arvoreSintatica;
  if(no == NULL) return;

  fprintf(arquivo,"%*s{\n", identacao, no->producao->getNome());
  getchar();
  int i;
  for(i = 0; i < no->producao->numPartes; i++)
  {
    if(no->partes[i].token != NULL)
    { fprintf(arquivo,"%*s\n", identacao+2, no->partes[i].token->conteudo);}
    else
    { printArvoreSintatica(no->partes[i].producao, identacao + 2);}
  }
  fprintf(arquivo,"%*s\n", identacao, "}");
}

int GeradorLALR::getNumEstados()
{
  return numEstados;
}

GeradorLALR::GeradorLALR(Producao* producoes, bool betterShiftThanReduce, bool reduceReduceAccepted)
{
  numEstados = 0;
  arvoreSintatica = NULL;
  if(producoes == NULL) return;
  this->betterShiftThanReduce = betterShiftThanReduce;
  this->reduceReduceAccepted = reduceReduceAccepted;
  this->producoes = new Producao(to_string("S'", 2));
  this->producoes->indice = -1;
  this->producoes->appendProducao(producoes);
  this->producoes->proxima = producoes;
  Item* item = new Item(this->producoes,NULL);
  inicial = new Estado(item, NULL);
  printf("Expandindo...\n");
  inicial->desmarcarTodos();
  arquivo = fopen("debug.txt", "wb");
  expandirEstado(inicial);
  fclose(arquivo);
  inicial->desmarcarTodos();
  arquivo = fopen("ArvoreSintaticaExpandida.txt", "wb");
  inicial->print(0);
  fclose(arquivo);
  inicial->desmarcarTodos();
  printf("Reduzindo...\n");
  reduzirEstados();
  inicial->desmarcarTodos();
  getEstadoArray();
  inicial->desmarcarTodos();
  arquivo = fopen("ArvoreSintaticaReduzida.txt", "wb");
  inicial->print(0);
  fclose(arquivo);
  inicial->desmarcarTodos();
  printf("Gerando tabela...\n");
  gerarTabela();
  printf("Numero de estados: %i\n", getNumEstados());
}

GeradorLALR::~GeradorLALR()
{
  if(inicial)
  {
    inicial->desmarcarTodos();
    delete inicial;
  }
}

