#if !defined(UtilitariosHeaderFile)
#define UtilitariosHeaderFile 1
#include <stdio.h>
char* trim(char* entrada, int tamanho);
char* to_string(char c);
char* to_string(char* str, int tam);
char* to_ASCII_string(char* str, int tam);

template <class T>
struct Lista
{
  T* objeto;
  Lista<T>* proximo;

  void treta(T* a);

  static void destruir(Lista* lista)
  {
    Lista<T>* aux;
    while(lista)
    {
      aux = lista;
      lista = lista->proximo;
      delete (aux->objeto);
      delete aux;
    }
  }

  static void desmontar(Lista* lista)
  {
    Lista<T>* aux;
    while(lista)
    {
      aux = lista;
      lista = lista->proximo;
      delete aux;
    }
  }

  Lista(T *obj, Lista<T>* prox = NULL)
  {
    objeto = obj;
    proximo = prox;
  }
};

template <class K, class T>
class Hash
{
  struct No
  {
    K chave;
    T* objeto;
  };

  unsigned int (*funcaoHash)(K, unsigned int);

  static unsigned int mod(K chave, unsigned int tamanho)
  {
    return ((unsigned long long)chave) % tamanho;
  }

  int tamanho;
  Lista<No> **vetor;
  public:

  Hash(unsigned int tamanho = 1021, unsigned int (*funcaoHash)(K, unsigned int) = mod)
  {
    this->funcaoHash = mod;
    this->tamanho = tamanho;
    vetor = new Lista<No>*[tamanho];
    memset(vetor, 0, sizeof(Lista<No>*)*tamanho);
  }

  void add(K chave, T* valor)
  {
    unsigned int indice = funcaoHash(chave,tamanho);
    Lista<No>* no = vetor[indice];

    No* novo = new No;
    novo->chave = chave;
    novo->objeto = valor;
    vetor[indice] = new Lista<No>(novo, vetor[indice]);
  }

  void replace(K chave, T* valor)
  {
    unsigned int indice = funcaoHash(chave,tamanho);
    Lista<No>* no = vetor[indice];
    while(no)
    {
      if(no->objeto->chave == chave) break;
      no = no->proximo;
    }
    if(!no)
    {
      No* novo = new No;
      novo->chave = chave;
      novo->objeto = valor;
      vetor[indice] = new Lista<No>(novo, vetor[indice]);
    }else
    {
      no->objeto->objeto = valor;
    }
  }

  T* get(K chave)
  {
    Lista<No>* no = vetor[funcaoHash(chave,tamanho)];
    while(no)
    {
      if(no->objeto->chave == chave) return no->objeto->objeto;
      no = no->proximo;
    }
    return NULL;
  }

  Lista<T>* getAll(K chave)
  {
    Lista<T>* ret = NULL;
    Lista<No>* no = vetor[funcaoHash(chave,tamanho)];
    while(no)
    {
      if(no->objeto->chave == chave)
      {
        ret = new Lista<T>(no->objeto->objeto, ret);
      }

      no = no->proximo;
    }
    return ret;
  }

  Lista<K>* getAllKeys()
  {
    int i;
    Lista<K>* ret = NULL;
    for(i = 0; i < tamanho; i++)
    {
      Lista<No>* aux = vetor[i];
      while(aux)
      {
        ret = new Lista<K>(&(aux->objeto->chave), ret);
        aux = aux->proximo;
      }
    }
    return ret;
  }

  Lista<T>* getAll()
  {
    int i;
    Lista<T>* ret = NULL;
    for(i = 0; i < tamanho; i++)
    {
      Lista<No>* aux = vetor[i];
      while(aux)
      {
        ret = new Lista<T>(aux->objeto->objeto, ret);
        aux = aux->proximo;
      }
    }
    return ret;
  }

  ~Hash()
  {
    int i;
    for(i = 0; i < tamanho; i++)
    {
      Lista<No>::destruir(vetor[i]);
    }
    delete [] vetor;
  }
};
#endif
