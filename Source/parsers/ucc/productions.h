#ifndef ucc_PRODUCTIONS_HEADER
#define ucc_PRODUCTIONS_HEADER
#ifdef __cplusplus
extern "C" {
#endif
#include<parsers/parser.h>
extern VisitFunction ucc_visit_defaultFunction;

extern VisitFunction ucc_visit_Total;
extern VisitFunction ucc_visit_Op;
extern VisitFunction ucc_visit_Expr;
extern VisitFunction ucc_visit_Reducer;
extern VisitFunction ucc_visit_Reducers;
extern VisitFunction ucc_visit_Production;
extern VisitFunction ucc_visit_Productions;
extern VisitFunction ucc_visit_Token;
extern VisitFunction ucc_visit_Tokens;
extern VisitFunction ucc_visit_Literal;
extern VisitFunction ucc_visit_Helper;
extern VisitFunction ucc_visit_Helpers;

extern VisitFunction ucc_visit_Total_helpers_tokens_productions_reducer_Reducers;
extern VisitFunction ucc_visit_Op_comma;
extern VisitFunction ucc_visit_Expr_identifier;
extern VisitFunction ucc_visit_Expr_Expr_Op_Expr;
extern VisitFunction ucc_visit_Expr_Expr;
extern VisitFunction ucc_visit_Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon;
extern VisitFunction ucc_visit_Reducer_identifier_reduce_Expr_semicolon;
extern VisitFunction ucc_visit_Reducers_Reducer;
extern VisitFunction ucc_visit_Reducers_Reducers_Reducer;
extern VisitFunction ucc_visit_Op_question;
extern VisitFunction ucc_visit_Expr_Expr_Op;
extern VisitFunction ucc_visit_Expr_Expr_Expr;
extern VisitFunction ucc_visit_Production_identifier_attrib_Expr_semicolon;
extern VisitFunction ucc_visit_Productions_Production;
extern VisitFunction ucc_visit_Productions_Productions_Production;
extern VisitFunction ucc_visit_Op_mult;
extern VisitFunction ucc_visit_Op_sum;
extern VisitFunction ucc_visit_Op_or;
extern VisitFunction ucc_visit_Expr_charLiteral;
extern VisitFunction ucc_visit_Expr_o_parentheses_Expr_c_parentheses;
extern VisitFunction ucc_visit_Token_identifier_attrib_Expr_semicolon;
extern VisitFunction ucc_visit_Token_mult_identifier_attrib_Expr_semicolon;
extern VisitFunction ucc_visit_Tokens_Token;
extern VisitFunction ucc_visit_Tokens_Tokens_Token;
extern VisitFunction ucc_visit_Literal_decimal;
extern VisitFunction ucc_visit_Literal_charLiteral;
extern VisitFunction ucc_visit_Op_sub;
extern VisitFunction ucc_visit_Expr_Literal;
extern VisitFunction ucc_visit_Expr_Literal_to_Literal;
extern VisitFunction ucc_visit_Helper_identifier_attrib_Expr_semicolon;
extern VisitFunction ucc_visit_Helpers_Helper;
extern VisitFunction ucc_visit_Helpers_Helpers_Helper;
extern VisitFunction ucc_visit_Total_helpers_tokens_productions_Productions_reducer_Reducers;
extern VisitFunction ucc_visit_Total_helpers_tokens_Tokens_productions_reducer_Reducers;
extern VisitFunction ucc_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers;
extern VisitFunction ucc_visit_Total_helpers_Helpers_tokens_productions_reducer_Reducers;
extern VisitFunction ucc_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers;
extern VisitFunction ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers;
extern VisitFunction ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode T_tokens1;
	ProductionNode T_productions2;
	ProductionNode T_reducer3;
	ProductionNode Reducers4;
} ucc_Total_helpers_tokens_productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_comma0;
} ucc_Op_comma;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
} ucc_Expr_identifier;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
	ProductionNode Op1;
	ProductionNode Expr2;
} ucc_Expr_Expr_Op_Expr;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
} ucc_Expr_Expr;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_o_brackets0;
	ProductionNode T_identifier1;
	ProductionNode T_c_brackets2;
	ProductionNode T_reduce3;
	ProductionNode Expr4;
	ProductionNode T_semicolon5;
} ucc_Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_reduce1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} ucc_Reducer_identifier_reduce_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Reducer0;
} ucc_Reducers_Reducer;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Reducers0;
	ProductionNode Reducer1;
} ucc_Reducers_Reducers_Reducer;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_question0;
} ucc_Op_question;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
	ProductionNode Op1;
} ucc_Expr_Expr_Op;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
	ProductionNode Expr1;
} ucc_Expr_Expr_Expr;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_attrib1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} ucc_Production_identifier_attrib_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Production0;
} ucc_Productions_Production;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Productions0;
	ProductionNode Production1;
} ucc_Productions_Productions_Production;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_mult0;
} ucc_Op_mult;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_sum0;
} ucc_Op_sum;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_or0;
} ucc_Op_or;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_charLiteral0;
} ucc_Expr_charLiteral;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_o_parentheses0;
	ProductionNode Expr1;
	ProductionNode T_c_parentheses2;
} ucc_Expr_o_parentheses_Expr_c_parentheses;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_attrib1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} ucc_Token_identifier_attrib_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_mult0;
	ProductionNode T_identifier1;
	ProductionNode T_attrib2;
	ProductionNode Expr3;
	ProductionNode T_semicolon4;
} ucc_Token_mult_identifier_attrib_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Token0;
} ucc_Tokens_Token;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Tokens0;
	ProductionNode Token1;
} ucc_Tokens_Tokens_Token;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_decimal0;
} ucc_Literal_decimal;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_charLiteral0;
} ucc_Literal_charLiteral;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_sub0;
} ucc_Op_sub;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Literal0;
} ucc_Expr_Literal;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Literal0;
	ProductionNode T_to1;
	ProductionNode Literal2;
} ucc_Expr_Literal_to_Literal;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_attrib1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} ucc_Helper_identifier_attrib_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Helper0;
} ucc_Helpers_Helper;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Helpers0;
	ProductionNode Helper1;
} ucc_Helpers_Helpers_Helper;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode T_tokens1;
	ProductionNode T_productions2;
	ProductionNode Productions3;
	ProductionNode T_reducer4;
	ProductionNode Reducers5;
} ucc_Total_helpers_tokens_productions_Productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode T_tokens1;
	ProductionNode Tokens2;
	ProductionNode T_productions3;
	ProductionNode T_reducer4;
	ProductionNode Reducers5;
} ucc_Total_helpers_tokens_Tokens_productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode T_tokens1;
	ProductionNode Tokens2;
	ProductionNode T_productions3;
	ProductionNode Productions4;
	ProductionNode T_reducer5;
	ProductionNode Reducers6;
} ucc_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode Helpers1;
	ProductionNode T_tokens2;
	ProductionNode T_productions3;
	ProductionNode T_reducer4;
	ProductionNode Reducers5;
} ucc_Total_helpers_Helpers_tokens_productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode Helpers1;
	ProductionNode T_tokens2;
	ProductionNode T_productions3;
	ProductionNode Productions4;
	ProductionNode T_reducer5;
	ProductionNode Reducers6;
} ucc_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode Helpers1;
	ProductionNode T_tokens2;
	ProductionNode Tokens3;
	ProductionNode T_productions4;
	ProductionNode T_reducer5;
	ProductionNode Reducers6;
} ucc_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode Helpers1;
	ProductionNode T_tokens2;
	ProductionNode Tokens3;
	ProductionNode T_productions4;
	ProductionNode Productions5;
	ProductionNode T_reducer6;
	ProductionNode Reducers7;
} ucc_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers;

enum ucc_ProductionType
{
	ucc_P_UNKONOWN_PROD,
	ucc_P_Total_helpers_tokens_productions_reducer_Reducers,
	ucc_P_Op_comma,
	ucc_P_Expr_identifier,
	ucc_P_Expr_Expr_Op_Expr,
	ucc_P_Expr_Expr,
	ucc_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon,
	ucc_P_Reducer_identifier_reduce_Expr_semicolon,
	ucc_P_Reducers_Reducer,
	ucc_P_Reducers_Reducers_Reducer,
	ucc_P_Op_question,
	ucc_P_Expr_Expr_Op,
	ucc_P_Expr_Expr_Expr,
	ucc_P_Production_identifier_attrib_Expr_semicolon,
	ucc_P_Productions_Production,
	ucc_P_Productions_Productions_Production,
	ucc_P_Op_mult,
	ucc_P_Op_sum,
	ucc_P_Op_or,
	ucc_P_Expr_charLiteral,
	ucc_P_Expr_o_parentheses_Expr_c_parentheses,
	ucc_P_Token_identifier_attrib_Expr_semicolon,
	ucc_P_Token_mult_identifier_attrib_Expr_semicolon,
	ucc_P_Tokens_Token,
	ucc_P_Tokens_Tokens_Token,
	ucc_P_Literal_decimal,
	ucc_P_Literal_charLiteral,
	ucc_P_Op_sub,
	ucc_P_Expr_Literal,
	ucc_P_Expr_Literal_to_Literal,
	ucc_P_Helper_identifier_attrib_Expr_semicolon,
	ucc_P_Helpers_Helper,
	ucc_P_Helpers_Helpers_Helper,
	ucc_P_Total_helpers_tokens_productions_Productions_reducer_Reducers,
	ucc_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers,
	ucc_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers,
	ucc_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers,
	ucc_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers,
	ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers,
	ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers
};

extern bool ucc_nodeRedundancyTable[];bool ucc_visit(Production*, VisitData*);
bool ucc_visitNodes(Production* production, VisitData* visitData);

#ifdef __cplusplus
}
#endif
#endif
