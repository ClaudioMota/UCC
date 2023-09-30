#if !defined(LookaheadHeaderFile)
#define LookaheadHeaderFile 1

#include <MaquinaToken.h>

struct Lookahead
{
  MaquinaToken* tokenEsperado;
  Lookahead* proximo;

  static bool igual(Lookahead* A, Lookahead* B);
  static Lookahead* copiar(Lookahead* look);
  static Lookahead* mesclar(Lookahead* A, Lookahead* B);
  static void destruir(Lookahead* look);
  bool possui(MaquinaToken* token);
  void print(FILE* arquivo);

  Lookahead(MaquinaToken* token, Lookahead* proximo);
};

#endif
