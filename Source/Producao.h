#if !defined(ProducaoHeaderFile)
#define ProducaoHeaderFile 1
#include <stdio.h>
#include <string.h>
#include <MaquinaToken.h>
#include <Lookahead.h>
#include <string>
#include <map>
struct Producao
{
  struct Parte
  {
    MaquinaToken* token;
    Producao* producao;

    Parte();
  };

  Parte* partes;
  int numPartes;
  char* nome;
  int indice;

  Producao* proxima;

  Producao(char* nome);

  char* getNome();
  std::string getReducao(std::map<std::string, std::string> reducoes);
  Lookahead* getFirsts(Producao* producoes, Lookahead* seguintes = NULL, int* marca = NULL);
  void appendToken(MaquinaToken* token);
  void appendProducao(Producao* producao);

  void print(FILE* arquivo, int posPonto = -1);
};
#endif
