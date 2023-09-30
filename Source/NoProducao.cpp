#include <NoProducao.h>

//Parte ======================

NoProducao::Parte::Parte()
{
  token = NULL;
  producao = NULL;
}

NoProducao::Parte::~Parte()
{
  if(token != NULL) delete token;
  if(producao != NULL) delete producao;
}

//NoProducao =================

NoProducao::NoProducao(Producao* prod)
{
  producao = prod;
  partes = new Parte[producao->numPartes];
}

void NoProducao::addToken(Token* token, int indice)
{
  partes[indice].token = token;
}

void NoProducao::addProducao(NoProducao* producao, int indice)
{
  partes[indice].producao = producao;
}

NoProducao::~NoProducao()
{
  delete [] partes;
}
