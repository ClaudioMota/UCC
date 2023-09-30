#if !defined(PreprocessadorHeaderFile)
#define PreprocessadorHeaderFile 1

#include<stdio.h>
#include<string.h>
#include<map>
#include<Producao.h>
#include<MaquinaToken.h>
#include <Utilitarios.h>

class Preprocessador
{
  enum OperacaoSintatica
  {
    INDEFINIDO,
    PARENTESES,
    STRING,
    UNIAO,
    PRODUTO,
    ATE,
    SUBTRACAO,
    NUMERO,
    IDENTIFICADOR
  };

  struct Helper
  {
    char* cadeia;
    int tamanho;
    Helper* proximo;

    Helper(char* cadeia, int tamanho, Helper* proximo);
    static bool iguais(Helper* a, Helper* b);
    int passarParaArray(int* saida);
    int getTamanhoIntArray();
    void add(Helper* h);
    void sub(Helper* h);
    void mul(Helper* h);
    static Helper* expandir(int inicio, int fim);
    static void destruir(Helper* h);
    ~Helper();
  };

  struct NoSintaticoHelper
  {
    int tamanho;
    char* cadeia;
    int operacao;

    NoSintaticoHelper* primeiroFilho;
    NoSintaticoHelper* segundoFilho;

    NoSintaticoHelper();

    inline bool analizarOU(char* expr, int tam);
    inline bool analizarE(char* expr, int tam);
    inline bool analizarParenteses(char* expr, int tam);

    Helper* extrairHelper(std::map<std::string, Preprocessador::Helper*> &helpers);

    void analizar(char* expr, int tam);

    void print();
  };

  public:
  enum Operadores
  {
    OU = 100000,
    E,
    NOT,
    ABRE_PARENTESES,
    FECHA_PARENTESES,
    ASTERISCO,
    UM_MAIS,
    OPCIONAL,
  };

  struct Linha
  {
    char* atribuido;
    void* atributo;
    int tamanho;
    Linha* proxima;

    Linha(char* atribuido, void* atributo, int tamanho, Linha* proxima);
    void print();
  };

  private:
  enum Estados
  {
    NENHUM,
    HELPER,
    TOKEN,
    PRODUCAO,
    REDUTOR
  };

  enum Modo
  {
    NORMAL,
    TEXTO,
    TEXTO_ESPECIAL,
    COMENTARIO
  };

  int estado;
  int modo;
  std::map<std::string, Helper*> helpers;
  Linha* tokens;
  Linha* producoes;
  std::map<std::string, std::string> reducoes;
  std::map<std::string, std::string> lists;

  public:
  Preprocessador(FILE* file);

  private:
  inline bool processarNormal(char* linha, int &pos, char entrada);
  inline bool processarTexto(char* linha, int &pos, char entrada);
  inline bool processarComentario(char* linha, int &pos, char entrada);

  void processarHelper(char* linha);
  void processarToken(char* linha);
  void processarProducao(char* linha);
  void processarAbstrato(char* linha);

  void setEstado(char* estado);

  public:
  std::map<std::string, std::string> getReducoes();
  std::map<std::string, std::string> getLists();
  MaquinaToken* getTokens();
  Producao* getProducoes(MaquinaToken*);
};

#endif
