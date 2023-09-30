#include<Producao.h>

//Parte
Producao::Parte::Parte()
{
  token = NULL;
  producao = NULL;
}

//Producao
Producao::Producao(char* nome)
{
  this->nome = nome;
  numPartes = 0;
  partes = new Parte[20];
  proxima = NULL;
}

void Producao::appendToken(MaquinaToken* token)
{
  partes[numPartes].token = token;
  numPartes++;
}

void Producao::appendProducao(Producao* producao)
{
  partes[numPartes].producao = producao;
  numPartes++;
}

Lookahead* Producao::getFirsts(Producao* producoes, Lookahead* seguintes, int* marca)
{
  Lookahead *lAux;
  Producao* aux = producoes;
  char* nome = this->nome;
  bool deleteMarca = false;
  int i = 0;

  if(marca == NULL)
  { deleteMarca = true;
    while(aux)
    { i++; aux = aux->proxima;}

    marca = new int[i];
    memset(marca, 0, sizeof(int)*i);
    i = 0;
    aux = producoes;
  }

  while(aux)
  {
    if(!strcmp(nome, aux->nome) && marca[i] != 1)
    {
      marca[i] = 1;
      if(aux->partes[0].producao)
      {
        if(strcmp(nome, aux->partes[0].producao->nome))
        {
          seguintes = aux->partes[0].producao->getFirsts(producoes,seguintes, marca);
        }
      }else
      {
        lAux = seguintes;
        while(lAux)
        {
          if(lAux->tokenEsperado == aux->partes[0].token)
          {
            break;
          }
          lAux = lAux->proximo;
        }
        if(!lAux)
        { seguintes = new Lookahead(aux->partes[0].token, seguintes);}
      }
    }
    i++;
    aux = aux->proxima;
  }

  if(deleteMarca) delete [] marca;
  return seguintes;
}

void Producao::print(FILE* arquivo, int posPonto)
{
  fprintf(arquivo, "%s -> ", nome);
  int i;
  for(i = 0; i < numPartes; i++)
  {
    char* nome;
    if(posPonto != -1 && posPonto == i) fprintf(arquivo, ". ");
    if(partes[i].producao) nome = partes[i].producao->getNome();
    else nome = partes[i].token->getNome();
    fprintf(arquivo, "%s ", nome);
  }
  if(posPonto == i) fprintf(arquivo, ". ");
}

char* Producao::getNome()
{
  return nome;
}

std::string Producao::getReducao(std::map<std::string, std::string> reducoes)
{
  std::string ret = nome;

  if(reducoes.find(nome) != reducoes.end())
  {
    ret = reducoes[nome];
  }

  for(int i = 0; i < numPartes; i++)
  {
    ret += "_";
    if(partes[i].token != NULL)
    {
      ret += partes[i].token->getNomeCanonico("");
    }else
    {
      if(reducoes.find(partes[i].producao->getNome()) == reducoes.end())
      {
        ret += partes[i].producao->getNome();
      }else
      {
        ret += reducoes[partes[i].producao->getNome()];
      }
    }
  }

  return ret;
}
