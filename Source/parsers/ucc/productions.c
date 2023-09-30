#include<parsers/ucc/productions.h>
VisitFunction UCC_visit_defaultFunction = UCC_visitNodes;
VisitFunction UCC_visit_Total_helpers_tokens_productions_reducer_Reducers = nullptr;
VisitFunction UCC_visit_Total = nullptr;
VisitFunction UCC_visit_Expr_identifier = nullptr;
VisitFunction UCC_visit_Expr = nullptr;
VisitFunction UCC_visit_Expr_Expr_Expr = nullptr;
VisitFunction UCC_visit_Expr_Expr = nullptr;
VisitFunction UCC_visit_Reducer_o_brackets_identifier_c_brackets_reduce_Expr = nullptr;
VisitFunction UCC_visit_Reducer = nullptr;
VisitFunction UCC_visit_Reducer_identifier_reduce_Expr_semicolon = nullptr;
VisitFunction UCC_visit_Reducers_Reducer = nullptr;
VisitFunction UCC_visit_Reducers = nullptr;
VisitFunction UCC_visit_Reducers_Reducers_Reducer = nullptr;
VisitFunction UCC_visit_Op_question = nullptr;
VisitFunction UCC_visit_Op = nullptr;
VisitFunction UCC_visit_Expr_Expr_Op = nullptr;
VisitFunction UCC_visit_Expr_Expr_Op_Expr = nullptr;
VisitFunction UCC_visit_Production_identifier_attrib_Expr_semicolon = nullptr;
VisitFunction UCC_visit_Production = nullptr;
VisitFunction UCC_visit_Productions_Production = nullptr;
VisitFunction UCC_visit_Productions = nullptr;
VisitFunction UCC_visit_Productions_Productions_Production = nullptr;
VisitFunction UCC_visit_Op_mult = nullptr;
VisitFunction UCC_visit_Op_sum = nullptr;
VisitFunction UCC_visit_Op_or = nullptr;
VisitFunction UCC_visit_Expr_o_parentheses_Expr_c_parentheses = nullptr;
VisitFunction UCC_visit_Token_identifier_attrib_Expr_semicolon = nullptr;
VisitFunction UCC_visit_Token = nullptr;
VisitFunction UCC_visit_Tokens_Token = nullptr;
VisitFunction UCC_visit_Tokens = nullptr;
VisitFunction UCC_visit_Tokens_Tokens_Token = nullptr;
VisitFunction UCC_visit_Literal_decimal = nullptr;
VisitFunction UCC_visit_Literal = nullptr;
VisitFunction UCC_visit_Literal_charLiteral = nullptr;
VisitFunction UCC_visit_Op_sub = nullptr;
VisitFunction UCC_visit_Expr_Literal = nullptr;
VisitFunction UCC_visit_Expr_Literal_to_Literal = nullptr;
VisitFunction UCC_visit_Helper_identifier_attrib_Expr_semicolon = nullptr;
VisitFunction UCC_visit_Helper = nullptr;
VisitFunction UCC_visit_Helpers_Helper = nullptr;
VisitFunction UCC_visit_Helpers = nullptr;
VisitFunction UCC_visit_Helpers_Helpers_Helper = nullptr;
VisitFunction UCC_visit_Total_helpers_tokens_productions_Productions_reducer_Reducers = nullptr;
VisitFunction UCC_visit_Total_helpers_tokens_Tokens_productions_reducer_Reducers = nullptr;
VisitFunction UCC_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers = nullptr;
VisitFunction UCC_visit_Total_helpers_Helpers_tokens_productions_reducer_Reducers = nullptr;
VisitFunction UCC_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers = nullptr;
VisitFunction UCC_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers = nullptr;
VisitFunction UCC_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers = nullptr;

bool UCC_visit(Production* production, VisitData* visitData)
{
	VisitFunction visitFunction = nullptr;
	switch(production->type)
	{
		case UCC_P_Total_helpers_tokens_productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_tokens_productions_reducer_Reducers; break;
		case UCC_P_Expr_identifier: visitFunction = UCC_visit_Expr_identifier; break;
		case UCC_P_Expr_Expr_Expr: visitFunction = UCC_visit_Expr_Expr_Expr; break;
		case UCC_P_Expr_Expr: visitFunction = UCC_visit_Expr_Expr; break;
		case UCC_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr: visitFunction = UCC_visit_Reducer_o_brackets_identifier_c_brackets_reduce_Expr; break;
		case UCC_P_Reducer_identifier_reduce_Expr_semicolon: visitFunction = UCC_visit_Reducer_identifier_reduce_Expr_semicolon; break;
		case UCC_P_Reducers_Reducer: visitFunction = UCC_visit_Reducers_Reducer; break;
		case UCC_P_Reducers_Reducers_Reducer: visitFunction = UCC_visit_Reducers_Reducers_Reducer; break;
		case UCC_P_Op_question: visitFunction = UCC_visit_Op_question; break;
		case UCC_P_Expr_Expr_Op: visitFunction = UCC_visit_Expr_Expr_Op; break;
		case UCC_P_Expr_Expr_Op_Expr: visitFunction = UCC_visit_Expr_Expr_Op_Expr; break;
		case UCC_P_Production_identifier_attrib_Expr_semicolon: visitFunction = UCC_visit_Production_identifier_attrib_Expr_semicolon; break;
		case UCC_P_Productions_Production: visitFunction = UCC_visit_Productions_Production; break;
		case UCC_P_Productions_Productions_Production: visitFunction = UCC_visit_Productions_Productions_Production; break;
		case UCC_P_Op_mult: visitFunction = UCC_visit_Op_mult; break;
		case UCC_P_Op_sum: visitFunction = UCC_visit_Op_sum; break;
		case UCC_P_Op_or: visitFunction = UCC_visit_Op_or; break;
		case UCC_P_Expr_o_parentheses_Expr_c_parentheses: visitFunction = UCC_visit_Expr_o_parentheses_Expr_c_parentheses; break;
		case UCC_P_Token_identifier_attrib_Expr_semicolon: visitFunction = UCC_visit_Token_identifier_attrib_Expr_semicolon; break;
		case UCC_P_Tokens_Token: visitFunction = UCC_visit_Tokens_Token; break;
		case UCC_P_Tokens_Tokens_Token: visitFunction = UCC_visit_Tokens_Tokens_Token; break;
		case UCC_P_Literal_decimal: visitFunction = UCC_visit_Literal_decimal; break;
		case UCC_P_Literal_charLiteral: visitFunction = UCC_visit_Literal_charLiteral; break;
		case UCC_P_Op_sub: visitFunction = UCC_visit_Op_sub; break;
		case UCC_P_Expr_Literal: visitFunction = UCC_visit_Expr_Literal; break;
		case UCC_P_Expr_Literal_to_Literal: visitFunction = UCC_visit_Expr_Literal_to_Literal; break;
		case UCC_P_Helper_identifier_attrib_Expr_semicolon: visitFunction = UCC_visit_Helper_identifier_attrib_Expr_semicolon; break;
		case UCC_P_Helpers_Helper: visitFunction = UCC_visit_Helpers_Helper; break;
		case UCC_P_Helpers_Helpers_Helper: visitFunction = UCC_visit_Helpers_Helpers_Helper; break;
		case UCC_P_Total_helpers_tokens_productions_Productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_tokens_productions_Productions_reducer_Reducers; break;
		case UCC_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_tokens_Tokens_productions_reducer_Reducers; break;
		case UCC_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers; break;
		case UCC_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_Helpers_tokens_productions_reducer_Reducers; break;
		case UCC_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers; break;
		case UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers; break;
		case UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers: visitFunction = UCC_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers; break;
	}

	if(visitFunction != nullptr) return visitFunction(production, visitData);

	switch(production->type)
	{
		case UCC_P_Expr_identifier:
		case UCC_P_Expr_Expr_Expr:
		case UCC_P_Expr_Expr:
		case UCC_P_Expr_Expr_Op:
		case UCC_P_Expr_Expr_Op_Expr:
		case UCC_P_Expr_o_parentheses_Expr_c_parentheses:
		case UCC_P_Expr_Literal:
		case UCC_P_Expr_Literal_to_Literal:
			visitFunction = UCC_visit_Expr;
		break;
		case UCC_P_Helper_identifier_attrib_Expr_semicolon:
			visitFunction = UCC_visit_Helper;
		break;
		case UCC_P_Helpers_Helper:
		case UCC_P_Helpers_Helpers_Helper:
			visitFunction = UCC_visit_Helpers;
		break;
		case UCC_P_Literal_decimal:
		case UCC_P_Literal_charLiteral:
			visitFunction = UCC_visit_Literal;
		break;
		case UCC_P_Op_question:
		case UCC_P_Op_mult:
		case UCC_P_Op_sum:
		case UCC_P_Op_or:
		case UCC_P_Op_sub:
			visitFunction = UCC_visit_Op;
		break;
		case UCC_P_Production_identifier_attrib_Expr_semicolon:
			visitFunction = UCC_visit_Production;
		break;
		case UCC_P_Productions_Production:
		case UCC_P_Productions_Productions_Production:
			visitFunction = UCC_visit_Productions;
		break;
		case UCC_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr:
		case UCC_P_Reducer_identifier_reduce_Expr_semicolon:
			visitFunction = UCC_visit_Reducer;
		break;
		case UCC_P_Reducers_Reducer:
		case UCC_P_Reducers_Reducers_Reducer:
			visitFunction = UCC_visit_Reducers;
		break;
		case UCC_P_Token_identifier_attrib_Expr_semicolon:
			visitFunction = UCC_visit_Token;
		break;
		case UCC_P_Tokens_Token:
		case UCC_P_Tokens_Tokens_Token:
			visitFunction = UCC_visit_Tokens;
		break;
		case UCC_P_Total_helpers_tokens_productions_reducer_Reducers:
		case UCC_P_Total_helpers_tokens_productions_Productions_reducer_Reducers:
		case UCC_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers:
		case UCC_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers:
		case UCC_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers:
		case UCC_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers:
		case UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers:
		case UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers:
			visitFunction = UCC_visit_Total;
		break;
	}

	if(visitFunction != nullptr) return visitFunction(production, visitData);

	return UCC_visit_defaultFunction(production, visitData);
}
bool UCC_visitNodes(Production* production, VisitData* visitData)
{ return visitNodes(production, visitData, UCC_visit); }
bool UCC_nodeRedundancyTable[] = {
	false // UNKNOWN
	,false // Total_helpers_tokens_productions_reducer_Reducers
	,false // Expr_identifier
	,false // Expr_Expr_Expr
	,true // Expr_Expr
	,false // Reducer_o_brackets_identifier_c_brackets_reduce_Expr
	,false // Reducer_identifier_reduce_Expr_semicolon
	,false // Reducers_Reducer
	,false // Reducers_Reducers_Reducer
	,false // Op_question
	,false // Expr_Expr_Op
	,false // Expr_Expr_Op_Expr
	,false // Production_identifier_attrib_Expr_semicolon
	,false // Productions_Production
	,false // Productions_Productions_Production
	,false // Op_mult
	,false // Op_sum
	,false // Op_or
	,false // Expr_o_parentheses_Expr_c_parentheses
	,false // Token_identifier_attrib_Expr_semicolon
	,false // Tokens_Token
	,false // Tokens_Tokens_Token
	,false // Literal_decimal
	,false // Literal_charLiteral
	,false // Op_sub
	,false // Expr_Literal
	,false // Expr_Literal_to_Literal
	,false // Helper_identifier_attrib_Expr_semicolon
	,false // Helpers_Helper
	,false // Helpers_Helpers_Helper
	,false // Total_helpers_tokens_productions_Productions_reducer_Reducers
	,false // Total_helpers_tokens_Tokens_productions_reducer_Reducers
	,false // Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers
};
