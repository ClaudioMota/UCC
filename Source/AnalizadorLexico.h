#if !defined(AnalizadorLexicoHeaderFile)
#define AnalizadorLexicoHeaderFile 1

#include<Utilitarios.h>
#include<Token.h>
#include<MaquinaToken.h>

namespace AnalizadorLexico
{
  Lista<Token>* getTokensList(MaquinaToken* maquinas, FILE* arquivo);
};

#endif
