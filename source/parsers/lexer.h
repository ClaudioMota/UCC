#ifndef LEXER_HEADER
#define LEXER_HEADER 1

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

#define TOKEN_UNKNOWN -2

typedef struct Token Token;
typedef struct Lexer Lexer;
typedef enum LexerState LexerState;

struct Token
{
  int type;
  int line;
  int column;
  int index;
  Token* next;
  bool ignored;
  void* file;
  char* content;
  int length;
};

enum LexerState
{
  LEXER_ACCEPTED = -2,
  LEXER_ERROR = -1,
  LEXER_PROCESSING = 0
};

struct Lexer
{
  int stateFunctionsCount;
  int (**stateFunctions)(int* state, int input);
  bool (*ignoreCheckFunction)(Token* token);
  int *states;
  Token* tokens;
  Token* lastToken;
  int lastAcceptedFunction;
};

Lexer Lexer_create(int stateFunctionsCount, int (**stateFunctions)(int* state, int input), bool (*ignoreFunction)(Token* token));

void Lexer_parse(Lexer* lexer, char* string);

void Lexer_clean(Lexer* lexer);

Token Token_create(int type, char* string, int startIndex, int length, int startLine, int startColumn);

void Token_deleteAll(Token* token);

#ifdef __cplusplus
}
#endif
#endif