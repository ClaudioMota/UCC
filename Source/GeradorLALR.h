#if !defined(GeradorLALRHeaderFile)
#define GeradorLALRHeaderFile 1
#include <MaquinaToken.h>
#include <Producao.h>
#include <Lookahead.h>
#include <Token.h>
#include <NoProducao.h>

class GeradorLALR
{
  struct Estado;
  struct Item
  {
    int posicaoPonto;
    Producao* producao;
    Lookahead* lookaheads;
    Item* proximo;

    Estado* proximoEstado;

    Lookahead* getSeguinte(Producao* producoes);

    bool possuiItem(Item* item);

    Item* possuiItemParecido(Item* item);

    void absorver(Item* vitima);

    static void expandir(Producao* producoes, Item* inicial);

    static bool igual(Item* A, Item* B);

    static bool nucleoIgual(Item* A, Item* B);

    static bool esperamAMesmaCoisa(Item* A, Item* B);

    void print(int identacao);

    Item(Producao* producao,Item* proximo);
    Item(Item* anterior, Item* proximo);

    ~Item();
  };

  struct Estado
  {
    Item* item;
    int marca;
    int indice;
    Estado* pai;

    static bool igual(Estado* A, Estado* B);
    static bool parecido(Estado* A, Estado* B);
    void removerItensDuplicados();
    void absorver(Estado* B);
    void redirecionar(Estado* de, Estado* para);
    void joinArray(Estado** vetor, int& indice);
    void desmarcarTodos();
    void print();
    void print(int identacao);
    Estado(Item* primeiroItem, Estado* pai);
    ~Estado();
  };

  public:
  struct OperacaoTabela
  { enum
    { SHIFT,
      REDUCE,
      GOTO,
      ACCEPT
    };

    int tipo;
    int gotoEstado;
    Producao* gotoProducao;
  };

  private:
  bool betterShiftThanReduce;
  bool reduceReduceAccepted;
  Estado* todosEstados[120000];

  int numEstados;

  Producao* producoes;
  Estado* inicial;
  NoProducao* arvoreSintatica;

  Hash<void*, OperacaoTabela>* tabelaAcao;
  Hash<void*, OperacaoTabela>* tabelaGoto;

  void reportarConflito(Estado* conflitante, MaquinaToken* chave, OperacaoTabela* a, OperacaoTabela* b);
  Estado** getEstadoArray();
  Estado* getEstadoIdentico(Estado* estado);
  bool gerarTabela();
  void expandirEstado(Estado* estado);
  void reduzirEstados();

public:
  Hash<void*, OperacaoTabela>* getTabelaAcao();
  Hash<void*, OperacaoTabela>* getTabelaGoto();

  bool analizar(Lista<Token>* tokens);
  NoProducao* getArvoreSintatica();
  int getNumEstados();
  void printArvoreSintatica(NoProducao* no = NULL, int identacao = 0);
  GeradorLALR(Producao* producoes, bool betterShiftThanReduce, bool reduceReduceAccepted);
  ~GeradorLALR();
};

#endif
