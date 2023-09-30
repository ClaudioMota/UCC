#ifndef GeradorDeCodigoFile
#define GeradorDeCodigoFile 1

#include <MaquinaToken.h>
#include <GeradorLALR.h>
#include <map>

namespace GeradorDeCodigo
{
  void setDiretorioBase(char* nome);

  void gerarInfraestrutura();

  void gerarLexico(MaquinaToken* maquinas);

  void gerarSintatico(MaquinaToken* maquinas, Producao* producoes, GeradorLALR* lalr,
    std::map<std::string, std::string> reducoes, std::map<std::string, std::string> lists);

  //void gerarRedutor();
}

#endif
