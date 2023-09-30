#include <stdio.h>
#include <string.h>
#include <Preprocessador.h>
#include <MaquinaToken.h>
#include <Producao.h>
#include <AnalizadorLexico.h>
#include <GeradorLALR.h>
#include <GeradorDeCodigo.h>

bool programaDeTeste(char* progFile, MaquinaToken* maquinas, GeradorLALR* sintatico);

int main(int numArgs, char** args)
{
  char* gramFile = args[1];

  if(numArgs < 3)
  {
    printf("Entrada esperada: <gramatica> <allways-shift> [<diretorio>]\n");
    return 0;
  }

  bool betterShiftThanReduce = false;
  if(numArgs >= 3)
  {
    betterShiftThanReduce = (strcmp(args[2], "Y") == 0);
  }

  printf("=========== COMPILANDO O COMPILADOR ============\n\n");
  FILE* gramatica = fopen(gramFile, "rb");
  if(!gramatica){ printf("arquivo nao encontrado!\n"); return 1;}

  printf("- Proprocessando ----\n");
  Preprocessador* preprocessador = new Preprocessador(gramatica);
  fclose(gramatica);

  printf("- Adquirindo tokens ----\n");
  MaquinaToken* maquinas = preprocessador->getTokens();
  Producao* producoes = preprocessador->getProducoes(maquinas);

  MaquinaToken* auxM = maquinas;
  while(auxM)
  {
    printf("->token : %s\n", auxM->getNome());
    auxM = auxM->getProxima();
  }

  if(producoes != NULL)
  {
    printf("- Gerando analizador sintatico ----\n");

    GeradorLALR* sintatico = new GeradorLALR(producoes, betterShiftThanReduce, true);

    printf("\n\n============   Gerando codigo ==============\n");

    if(numArgs >= 4)
      GeradorDeCodigo::setDiretorioBase(args[3]);

    printf("Gerando infraestrutura\n");
    GeradorDeCodigo::gerarInfraestrutura();

    printf("Gerando lexico\n");
    GeradorDeCodigo::gerarLexico(maquinas);

    printf("Gerando sintatico\n");
    GeradorDeCodigo::gerarSintatico(maquinas, producoes, sintatico, preprocessador->getReducoes(), preprocessador->getLists());

    printf("\n\n============ Geracao terminada com sucesso! ============\n");
  }
  else
  {
    printf("Nao foi possivel ler as producoes da gramatica!\n");
  }

  return 0;
}

bool programaDeTeste(char* progFile, MaquinaToken* maquinas, GeradorLALR* sintatico)
{
  FILE* programa = fopen(progFile, "rb");
  if(!programa){ printf("arquivo nao encontrado!\n"); return false;}

  printf("\n\n============ Tokenizando programa teste ==============\n");
  Lista<Token>* tokens = AnalizadorLexico::getTokensList(maquinas, programa);
  fclose(programa);

  Lista<Token>* aux = tokens;

  while(aux)
  {
    //if(!aux->objeto->ignorado){ printf("->%s : %s (%i,%i)\n", aux->objeto->tipo->getNome(), aux->objeto->conteudo, aux->objeto->linha, aux->objeto->coluna);
    //getchar();
    //}
    aux = aux->proximo;
  }

  printf("\n\n============ Analise sintatica ==============\n");

  aux = tokens;
  return sintatico->analizar(tokens);
}
