#ifndef UCC_PRODUCTIONS_HEADER
#define UCC_PRODUCTIONS_HEADER
#ifdef __cplusplus
extern "C" {
#endif
#include<parsers/parser.h>
extern VisitFunction UCC_visit_defaultFunction;

extern VisitFunction UCC_visit_Total;
extern VisitFunction UCC_visit_Expr;
extern VisitFunction UCC_visit_Reducer;
extern VisitFunction UCC_visit_Reducers;
extern VisitFunction UCC_visit_Op;
extern VisitFunction UCC_visit_Production;
extern VisitFunction UCC_visit_Productions;
extern VisitFunction UCC_visit_Token;
extern VisitFunction UCC_visit_Tokens;
extern VisitFunction UCC_visit_Literal;
extern VisitFunction UCC_visit_Helper;
extern VisitFunction UCC_visit_Helpers;

extern VisitFunction UCC_visit_Total_helpers_tokens_productions_reducer_Reducers;
extern VisitFunction UCC_visit_Expr_identifier;
extern VisitFunction UCC_visit_Expr_Expr_Expr;
extern VisitFunction UCC_visit_Expr_Expr;
extern VisitFunction UCC_visit_Reducer_o_brackets_identifier_c_brackets_reduce_Expr;
extern VisitFunction UCC_visit_Reducer_identifier_reduce_Expr_semicolon;
extern VisitFunction UCC_visit_Reducers_Reducer;
extern VisitFunction UCC_visit_Reducers_Reducers_Reducer;
extern VisitFunction UCC_visit_Op_question;
extern VisitFunction UCC_visit_Expr_Expr_Op;
extern VisitFunction UCC_visit_Expr_Expr_Op_Expr;
extern VisitFunction UCC_visit_Production_identifier_attrib_Expr_semicolon;
extern VisitFunction UCC_visit_Productions_Production;
extern VisitFunction UCC_visit_Productions_Productions_Production;
extern VisitFunction UCC_visit_Op_mult;
extern VisitFunction UCC_visit_Op_sum;
extern VisitFunction UCC_visit_Op_or;
extern VisitFunction UCC_visit_Expr_o_parentheses_Expr_c_parentheses;
extern VisitFunction UCC_visit_Token_identifier_attrib_Expr_semicolon;
extern VisitFunction UCC_visit_Tokens_Token;
extern VisitFunction UCC_visit_Tokens_Tokens_Token;
extern VisitFunction UCC_visit_Literal_decimal;
extern VisitFunction UCC_visit_Literal_charLiteral;
extern VisitFunction UCC_visit_Op_sub;
extern VisitFunction UCC_visit_Expr_Literal;
extern VisitFunction UCC_visit_Expr_Literal_to_Literal;
extern VisitFunction UCC_visit_Helper_identifier_attrib_Expr_semicolon;
extern VisitFunction UCC_visit_Helpers_Helper;
extern VisitFunction UCC_visit_Helpers_Helpers_Helper;
extern VisitFunction UCC_visit_Total_helpers_tokens_productions_Productions_reducer_Reducers;
extern VisitFunction UCC_visit_Total_helpers_tokens_Tokens_productions_reducer_Reducers;
extern VisitFunction UCC_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers;
extern VisitFunction UCC_visit_Total_helpers_Helpers_tokens_productions_reducer_Reducers;
extern VisitFunction UCC_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers;
extern VisitFunction UCC_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers;
extern VisitFunction UCC_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_helpers0;
	ProductionNode T_tokens1;
	ProductionNode T_productions2;
	ProductionNode T_reducer3;
	ProductionNode Reducers4;
} UCC_Total_helpers_tokens_productions_reducer_Reducers;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
} UCC_Expr_identifier;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
	ProductionNode Expr1;
} UCC_Expr_Expr_Expr;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
} UCC_Expr_Expr;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_o_brackets0;
	ProductionNode T_identifier1;
	ProductionNode T_c_brackets2;
	ProductionNode T_reduce3;
	ProductionNode Expr4;
} UCC_Reducer_o_brackets_identifier_c_brackets_reduce_Expr;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_reduce1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} UCC_Reducer_identifier_reduce_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Reducer0;
} UCC_Reducers_Reducer;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Reducers0;
	ProductionNode Reducer1;
} UCC_Reducers_Reducers_Reducer;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_question0;
} UCC_Op_question;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
	ProductionNode Op1;
} UCC_Expr_Expr_Op;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Expr0;
	ProductionNode Op1;
	ProductionNode Expr2;
} UCC_Expr_Expr_Op_Expr;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_attrib1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} UCC_Production_identifier_attrib_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Production0;
} UCC_Productions_Production;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Productions0;
	ProductionNode Production1;
} UCC_Productions_Productions_Production;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_mult0;
} UCC_Op_mult;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_sum0;
} UCC_Op_sum;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_or0;
} UCC_Op_or;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_o_parentheses0;
	ProductionNode Expr1;
	ProductionNode T_c_parentheses2;
} UCC_Expr_o_parentheses_Expr_c_parentheses;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_attrib1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} UCC_Token_identifier_attrib_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Token0;
} UCC_Tokens_Token;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Tokens0;
	ProductionNode Token1;
} UCC_Tokens_Tokens_Token;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_decimal0;
} UCC_Literal_decimal;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_charLiteral0;
} UCC_Literal_charLiteral;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_sub0;
} UCC_Op_sub;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Literal0;
} UCC_Expr_Literal;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Literal0;
	ProductionNode T_to1;
	ProductionNode Literal2;
} UCC_Expr_Literal_to_Literal;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode T_identifier0;
	ProductionNode T_attrib1;
	ProductionNode Expr2;
	ProductionNode T_semicolon3;
} UCC_Helper_identifier_attrib_Expr_semicolon;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Helper0;
} UCC_Helpers_Helper;

typedef struct 
{
	int type;
	int nodeCount;
	ProductionNode Helpers0;
	ProductionNode Helper1;
} UCC_Helpers_Helpers_Helper;

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
} UCC_Total_helpers_tokens_productions_Productions_reducer_Reducers;

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
} UCC_Total_helpers_tokens_Tokens_productions_reducer_Reducers;

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
} UCC_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers;

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
} UCC_Total_helpers_Helpers_tokens_productions_reducer_Reducers;

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
} UCC_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers;

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
} UCC_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers;

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
} UCC_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers;

enum UCC_ProductionType
{
	UCC_P_UNKONOWN_PROD,
	UCC_P_Total_helpers_tokens_productions_reducer_Reducers,
	UCC_P_Expr_identifier,
	UCC_P_Expr_Expr_Expr,
	UCC_P_Expr_Expr,
	UCC_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr,
	UCC_P_Reducer_identifier_reduce_Expr_semicolon,
	UCC_P_Reducers_Reducer,
	UCC_P_Reducers_Reducers_Reducer,
	UCC_P_Op_question,
	UCC_P_Expr_Expr_Op,
	UCC_P_Expr_Expr_Op_Expr,
	UCC_P_Production_identifier_attrib_Expr_semicolon,
	UCC_P_Productions_Production,
	UCC_P_Productions_Productions_Production,
	UCC_P_Op_mult,
	UCC_P_Op_sum,
	UCC_P_Op_or,
	UCC_P_Expr_o_parentheses_Expr_c_parentheses,
	UCC_P_Token_identifier_attrib_Expr_semicolon,
	UCC_P_Tokens_Token,
	UCC_P_Tokens_Tokens_Token,
	UCC_P_Literal_decimal,
	UCC_P_Literal_charLiteral,
	UCC_P_Op_sub,
	UCC_P_Expr_Literal,
	UCC_P_Expr_Literal_to_Literal,
	UCC_P_Helper_identifier_attrib_Expr_semicolon,
	UCC_P_Helpers_Helper,
	UCC_P_Helpers_Helpers_Helper,
	UCC_P_Total_helpers_tokens_productions_Productions_reducer_Reducers,
	UCC_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers,
	UCC_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers,
	UCC_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers,
	UCC_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers,
	UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers,
	UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers
};

extern bool UCC_nodeRedundancyTable[];bool UCC_visit(Production*, VisitData*);
bool UCC_visitNodes(Production* production, VisitData* visitData);

#ifdef __cplusplus
}
#endif
#endif
