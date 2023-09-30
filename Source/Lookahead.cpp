#include <stdio.h>
#include <Lookahead.h>

bool Lookahead::igual(Lookahead* A, Lookahead* B)
{
  int a = 0;
  Lookahead* aux = A;
  while(aux)
  {
    a++;
    aux = aux->proximo;
  }

  aux = B;
  while(aux)
  {
    a--;
    aux = aux->proximo;
  }

  if(a != 0) return false;

  while(A)
  {
    aux = B;
    while(aux)
    {
      if(A->tokenEsperado == aux->tokenEsperado) break;
      aux = aux->proximo;
    }
    if(!aux)
    {
      return false;
    }

    A = A->proximo;
  }
  return true;
}

Lookahead* Lookahead::copiar(Lookahead* look)
{
  Lookahead* ret = NULL;
  while(look)
  {
    ret = new Lookahead(look->tokenEsperado, ret);
    look = look->proximo;
  }
  return ret;
}

Lookahead* Lookahead::mesclar(Lookahead* A, Lookahead* B)
{
  Lookahead* look;
  if(!A)
  {
    A = new Lookahead(NULL, B);
  }
  else
  {
    look = A;
    while(look->proximo)
    {
      look = look->proximo;
    }

    if(!B)
    {
      B = new Lookahead(NULL, NULL);
    }
    look->proximo = B;
  }

  look = A;
  while(look)
  {
    Lookahead* anterior = look;
    B = look->proximo;
    while(B)
    {
      if(look->tokenEsperado == B->tokenEsperado)
      {
        anterior->proximo = B->proximo;
        B->proximo = NULL;
        delete B;
        B = anterior;
      }
      anterior = B;
      B = B->proximo;
    }

    look = look->proximo;
  }

  return A;
}

void Lookahead::print(FILE* arquivo)
{
  Lookahead* aux = this;
  while(aux)
  {
    if(aux->tokenEsperado) fprintf(arquivo,"%s", aux->tokenEsperado->getNome());
    else fprintf(arquivo,"$");
    aux = aux->proximo;
    if(aux) fprintf(arquivo,"/");
  }
}

Lookahead::Lookahead(MaquinaToken* token, Lookahead* proximo)
{
  this->tokenEsperado = token;
  this->proximo = proximo;
}

bool Lookahead::possui(MaquinaToken* token)
{
  if(tokenEsperado == token) return true;
  if(proximo) return proximo->possui(token);
  return false;
}

void Lookahead::destruir(Lookahead* lookaheads)
{
  Lookahead* aux = lookaheads;
  while(lookaheads)
  {
    lookaheads = lookaheads->proximo;
    delete aux;
    aux = lookaheads;
  }
}
