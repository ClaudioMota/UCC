#if !defined(TokenHeaderFile)
#define TokenHeaderFile 1

#include<MaquinaToken.h>

struct Token
{
  int linha, coluna;
  bool ignorado;
  MaquinaToken* tipo;
  int tamanho;
  char* conteudo;
};

#endif
