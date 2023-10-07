#include "parsers/lexer.h"
#include <string.h>
#include <stdlib.h>

void* new(long long size);
void delete(void* p);

// Process each step of the lexer parse
static LexerState step(int input, Lexer* lexer);

// Creates a token given the lexer state
static int createToken(Lexer* lexer, char* string, int startIndex, int startLine, int startColumn, int lastAcceptedIndex);

Lexer Lexer_create(int stateFunctionsCount, int (**stateFunctions)(int* state, int input), bool (*ignoreFunction)(Token* token))
{
  Lexer ret;
  memset(&ret, 0, sizeof(ret));
  ret.stateFunctionsCount = stateFunctionsCount;
  ret.stateFunctions = stateFunctions;
  ret.states = new(sizeof(int)*stateFunctionsCount);
  memset(ret.states, 0, sizeof(int)*stateFunctionsCount);
  ret.lastAcceptedFunction = -1;
  ret.ignoreCheckFunction = ignoreFunction;
  return ret;
}

void Lexer_parse(Lexer* lexer, char* string)
{
  int length = strlen(string);
  int input;
  int currentIndex = 0;
  int lastAcceptedIndex = -1;

  int startIndex = 0, startLine = 1, startColumn = 1;

  while(currentIndex <= length)
  {
    input = (unsigned char)string[currentIndex];

    switch(step(input, lexer))
    {
      case LEXER_ERROR:
        currentIndex = createToken(lexer, string, startIndex, startLine, startColumn, lastAcceptedIndex);
        
        for(int p = startIndex; p < currentIndex; p++)
        {
          if(string[p] == '\n')
          {
            startLine++;
            startColumn = 1;
          }else
            startColumn++;
        }

        startIndex = currentIndex;

        memset(lexer->states, 0, sizeof(int) * lexer->stateFunctionsCount);
        lexer->lastAcceptedFunction = -1;
        lastAcceptedIndex = -1;

        if(currentIndex >= length) currentIndex++; // forces the loop to break
      break;
      case LEXER_ACCEPTED:
        lastAcceptedIndex = currentIndex;
      default:
        currentIndex++;
    }
  }
}

void Lexer_clean(Lexer* lexer)
{
  if(lexer->states) delete(lexer->states);
  if(lexer->tokens) Token_deleteAll(lexer->tokens);

  memset(lexer, 0, sizeof(Lexer));
}

Token Token_create(int type, char* string, int startIndex, int length, int startLine, int startColumn)
{
  Token ret;
  memset(&ret, 0, sizeof(ret));

  ret.type = type;
  ret.line = startLine;
  ret.column = startColumn;
  ret.index = startIndex;
  ret.length = length;

  ret.content = new(length+1);
  ret.content[length] = '\0';
  memcpy(ret.content, string + startIndex, length);

  return ret;
}

void Token_deleteAll(Token* token)
{
  while(token)
  {
    Token* aux = token;
    token = token->next;
    if(aux->content) delete(aux->content);
    delete(aux);
  }
}

static LexerState step(int input, Lexer* lexer)
{
  LexerState lexerState = LEXER_ERROR;
  if(input)
  {
    int (**stateFunctions)(int* state, int input) = lexer->stateFunctions;
    int count = lexer->stateFunctionsCount;
    for(int i = 0; i < count; i++)
    {
      int *state = &lexer->states[i];
      if(*state != LEXER_ERROR)
      {
        int result = stateFunctions[i](state, input);
        if(*state != LEXER_ERROR)
        {
          if(result == LEXER_ACCEPTED)
          {
            lexer->lastAcceptedFunction = i;
            lexerState = LEXER_ACCEPTED;
          }
          if(lexerState != LEXER_ACCEPTED) lexerState = LEXER_PROCESSING;
        }
      }
    }
  }

  return lexerState;
}

static int createToken(Lexer* lexer, char* string, int startIndex, int startLine, int startColumn, int lastAcceptedIndex)
{
  int type = TOKEN_UNKNOWN, length = 1;
  if(lexer->lastAcceptedFunction >= 0)
  {
    type = lexer->lastAcceptedFunction;
    length = lastAcceptedIndex - startIndex + 1;
  }

  Token* token = new(sizeof(Token));
  *token = Token_create(type, string, startIndex, length, startLine, startColumn);
  token->ignored = lexer->ignoreCheckFunction(token);
  if(lexer->lastToken)
    lexer->lastToken->next = token;
  else
    lexer->tokens = token;

  lexer->lastToken = token;

  return startIndex + length;
}