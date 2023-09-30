#if !defined(NoProducaoHeaderFile)
#define NoProducaoHeaderFile 1

#include <Producao.h>
#include <Token.h>

struct NoProducao
{
  struct Parte
  {
    Token* token;
    NoProducao* producao;

    Parte();
    ~Parte();
  };

  Producao* producao;
  Parte* partes;

  NoProducao(Producao* prod);
  void addToken(Token* token, int indice);
  void addProducao(NoProducao* producao, int indice);
  ~NoProducao();
};

#endif
