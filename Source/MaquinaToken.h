#if !defined(MaquinaTokenHeaderFile)
#define MaquinaTokenHeaderFile 1
#define MaquinaTokenMAXESTADOS 50

#include <string>
#include <Utilitarios.h>
class MaquinaToken
{
  enum OperacaoSintatica
  {
    INDEFINIDO,
    PARENTESES,
    UM_MAIS,
    ASTERISCO,
    OU,
    E,
    OPCIONAL,
    FOLHA
  };

  struct NoSintatico
  {
    int tamanho;
    int* cadeia;
    int operacao;

    NoSintatico* primeiroFilho;
    NoSintatico* proximo;

    NoSintatico();

    inline bool analizarOU(int* expr, int tam);
    inline bool analizarE(int* expr, int tam);
    inline bool analizarParenteses(int* expr, int tam);

    void analizar(int* expr, int tam);

    void print();
  };

  public:
  struct Estado;

  struct ListaEstados
  {
    Estado* estado;
    ListaEstados* proximo;
    ListaEstados* ultimo;
    ListaEstados(Estado* e, ListaEstados* p);
    void unir(ListaEstados* nova);
    static bool iguais(ListaEstados* A, ListaEstados* B);
    static void desmontar(ListaEstados* lista);
  };

  struct Transicao
  { int valorEsperado;
    Transicao* proxima;
    Estado* proximoEstado;
    static const int VAZIA;

    Transicao();

    Transicao(Estado* estado, int entrada, Transicao* proxima);

    ListaEstados* getEstadosAtingiveis(int entrada);
    ListaEstados* entradaEsperada(int entrada);
  };

  struct Estado
  {
    int marca;
    int profundidade;
    bool terminado;
    Transicao* transicoes;
    Estado();

    inline void construirE(NoSintatico* no, Estado* estadoFinal);
    inline void construirOU(NoSintatico* no, Estado* estadoFinal);
    inline void construirESP(NoSintatico* no, Estado* estadoFinal);

    ListaEstados* getEstadosAtingiveis(Estado* inicio, int entrada);

    void construir(NoSintatico* no, Estado* estadoFinal);

    void redirecionarTransicoes(Estado* de, Estado* para);

    int contar();
    void joinArray(Estado** lista, int &pos);

    void destruir();

    void desmarcar();
    void print();
  };

  private:
  Estado* estadoInicial;
  int numEstadosAtuais;
  Estado* estadosAtuais[MaquinaTokenMAXESTADOS];
  MaquinaToken* proxima;
  char* nome;

  public:
  MaquinaToken(char* nome, int* expressaoProcessada, int tamanhoExpressao, MaquinaToken* proxima);

  bool possuiEscritaUnica();
  std::string getEscritaUnica();
  void destruirEstados();
  void trasformarEmDeterministico(Estado* estadoAtual = NULL, Lista<Estado>* novosEstados = NULL, Hash<Estado*, ListaEstados> *mapaEstados = NULL);
  char* getNome();
  std::string getNomeCanonico(std::string prefixo);
  bool ignore();
  MaquinaToken* getProxima();
  int getNumEstados();
  Estado** getEstados();
  void print();
  void reiniciar();
  bool finalizada();
  bool operar(int entrada);
  bool isAlive();
  bool validarCadeia(char* cadeia);
};
#endif
