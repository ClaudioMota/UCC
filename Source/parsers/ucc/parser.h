#ifndef UCC_PARSER_HEADER_FILE
#define UCC_PARSER_HEADER_FILE
#include<parsers/parser.h>

enum TokenType
{
  UNKNOWN = -2,
  END_OF_INPUT= -1,
  T_identifier,
  T_semicolon,
  T_to,
  T_comma,
  T_blank,
  T_breakLine,
  T_comment,
  T_helpers,
  T_tokens,
  T_productions,
  T_reducer,
  T_attrib,
  T_sum,
  T_sub,
  T_mult,
  T_or,
  T_reduce,
  T_question,
  T_o_parentheses,
  T_c_parentheses,
  T_o_brackets,
  T_c_brackets,
  T_charLiteral,
  T_decimal
};
Parser UCC_parse(AllProductions* allProductions, Production* (*creationFunction)(AllProductions*), Token* tokens);
#endif
