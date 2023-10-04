#include<parsers/ucc/productions.h>
VisitFunction ucc_visit_defaultFunction = ucc_visitNodes;
VisitFunction ucc_visit_Total_helpers_tokens_productions_reducer = nullptr;
VisitFunction ucc_visit_Total = nullptr;
VisitFunction ucc_visit_Op_comma = nullptr;
VisitFunction ucc_visit_Op = nullptr;
VisitFunction ucc_visit_Expr_identifier = nullptr;
VisitFunction ucc_visit_Expr = nullptr;
VisitFunction ucc_visit_Expr_Expr_comma_Expr = nullptr;
VisitFunction ucc_visit_Expr_Expr = nullptr;
VisitFunction ucc_visit_Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon = nullptr;
VisitFunction ucc_visit_Reducer = nullptr;
VisitFunction ucc_visit_Reducer_identifier_reduce_Expr_semicolon = nullptr;
VisitFunction ucc_visit_Reducers_Reducer = nullptr;
VisitFunction ucc_visit_Reducers = nullptr;
VisitFunction ucc_visit_Reducers_Reducers_Reducer = nullptr;
VisitFunction ucc_visit_Op_question = nullptr;
VisitFunction ucc_visit_Expr_Expr_Op = nullptr;
VisitFunction ucc_visit_Expr_Expr_Expr = nullptr;
VisitFunction ucc_visit_Expr_Expr_Op_Expr = nullptr;
VisitFunction ucc_visit_Production_identifier_attrib_Expr_semicolon = nullptr;
VisitFunction ucc_visit_Production = nullptr;
VisitFunction ucc_visit_Productions_Production = nullptr;
VisitFunction ucc_visit_Productions = nullptr;
VisitFunction ucc_visit_Productions_Productions_Production = nullptr;
VisitFunction ucc_visit_Op_mult = nullptr;
VisitFunction ucc_visit_Op_sum = nullptr;
VisitFunction ucc_visit_Op_or = nullptr;
VisitFunction ucc_visit_Literal_charLiteral = nullptr;
VisitFunction ucc_visit_Literal = nullptr;
VisitFunction ucc_visit_Expr_Literal = nullptr;
VisitFunction ucc_visit_Expr_o_parentheses_Expr_c_parentheses = nullptr;
VisitFunction ucc_visit_Token_identifier_attrib_Expr_semicolon = nullptr;
VisitFunction ucc_visit_Token = nullptr;
VisitFunction ucc_visit_Token_mult_identifier_attrib_Expr_semicolon = nullptr;
VisitFunction ucc_visit_Tokens_Token = nullptr;
VisitFunction ucc_visit_Tokens = nullptr;
VisitFunction ucc_visit_Tokens_Tokens_Token = nullptr;
VisitFunction ucc_visit_Literal_decimal = nullptr;
VisitFunction ucc_visit_Op_sub = nullptr;
VisitFunction ucc_visit_Expr_Literal_to_Literal = nullptr;
VisitFunction ucc_visit_Helper_identifier_attrib_Expr_semicolon = nullptr;
VisitFunction ucc_visit_Helper = nullptr;
VisitFunction ucc_visit_Helpers_Helper = nullptr;
VisitFunction ucc_visit_Helpers = nullptr;
VisitFunction ucc_visit_Helpers_Helpers_Helper = nullptr;
VisitFunction ucc_visit_Total_helpers_tokens_productions_reducer_Reducers = nullptr;
VisitFunction ucc_visit_Total_helpers_tokens_productions_Productions_reducer = nullptr;
VisitFunction ucc_visit_Total_helpers_tokens_productions_Productions_reducer_Reducers = nullptr;
VisitFunction ucc_visit_Total_helpers_tokens_Tokens_productions_reducer = nullptr;
VisitFunction ucc_visit_Total_helpers_tokens_Tokens_productions_reducer_Reducers = nullptr;
VisitFunction ucc_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer = nullptr;
VisitFunction ucc_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_productions_reducer = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_productions_reducer_Reducers = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer = nullptr;
VisitFunction ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers = nullptr;

bool ucc_visit(Production* production, VisitData* visitData)
{
	VisitFunction visitFunction = nullptr;
	switch(production->type)
	{
		case ucc_P_Total_helpers_tokens_productions_reducer: visitFunction = ucc_visit_Total_helpers_tokens_productions_reducer; break;
		case ucc_P_Op_comma: visitFunction = ucc_visit_Op_comma; break;
		case ucc_P_Expr_identifier: visitFunction = ucc_visit_Expr_identifier; break;
		case ucc_P_Expr_Expr_comma_Expr: visitFunction = ucc_visit_Expr_Expr_comma_Expr; break;
		case ucc_P_Expr_Expr: visitFunction = ucc_visit_Expr_Expr; break;
		case ucc_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon: visitFunction = ucc_visit_Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon; break;
		case ucc_P_Reducer_identifier_reduce_Expr_semicolon: visitFunction = ucc_visit_Reducer_identifier_reduce_Expr_semicolon; break;
		case ucc_P_Reducers_Reducer: visitFunction = ucc_visit_Reducers_Reducer; break;
		case ucc_P_Reducers_Reducers_Reducer: visitFunction = ucc_visit_Reducers_Reducers_Reducer; break;
		case ucc_P_Op_question: visitFunction = ucc_visit_Op_question; break;
		case ucc_P_Expr_Expr_Op: visitFunction = ucc_visit_Expr_Expr_Op; break;
		case ucc_P_Expr_Expr_Expr: visitFunction = ucc_visit_Expr_Expr_Expr; break;
		case ucc_P_Expr_Expr_Op_Expr: visitFunction = ucc_visit_Expr_Expr_Op_Expr; break;
		case ucc_P_Production_identifier_attrib_Expr_semicolon: visitFunction = ucc_visit_Production_identifier_attrib_Expr_semicolon; break;
		case ucc_P_Productions_Production: visitFunction = ucc_visit_Productions_Production; break;
		case ucc_P_Productions_Productions_Production: visitFunction = ucc_visit_Productions_Productions_Production; break;
		case ucc_P_Op_mult: visitFunction = ucc_visit_Op_mult; break;
		case ucc_P_Op_sum: visitFunction = ucc_visit_Op_sum; break;
		case ucc_P_Op_or: visitFunction = ucc_visit_Op_or; break;
		case ucc_P_Literal_charLiteral: visitFunction = ucc_visit_Literal_charLiteral; break;
		case ucc_P_Expr_Literal: visitFunction = ucc_visit_Expr_Literal; break;
		case ucc_P_Expr_o_parentheses_Expr_c_parentheses: visitFunction = ucc_visit_Expr_o_parentheses_Expr_c_parentheses; break;
		case ucc_P_Token_identifier_attrib_Expr_semicolon: visitFunction = ucc_visit_Token_identifier_attrib_Expr_semicolon; break;
		case ucc_P_Token_mult_identifier_attrib_Expr_semicolon: visitFunction = ucc_visit_Token_mult_identifier_attrib_Expr_semicolon; break;
		case ucc_P_Tokens_Token: visitFunction = ucc_visit_Tokens_Token; break;
		case ucc_P_Tokens_Tokens_Token: visitFunction = ucc_visit_Tokens_Tokens_Token; break;
		case ucc_P_Literal_decimal: visitFunction = ucc_visit_Literal_decimal; break;
		case ucc_P_Op_sub: visitFunction = ucc_visit_Op_sub; break;
		case ucc_P_Expr_Literal_to_Literal: visitFunction = ucc_visit_Expr_Literal_to_Literal; break;
		case ucc_P_Helper_identifier_attrib_Expr_semicolon: visitFunction = ucc_visit_Helper_identifier_attrib_Expr_semicolon; break;
		case ucc_P_Helpers_Helper: visitFunction = ucc_visit_Helpers_Helper; break;
		case ucc_P_Helpers_Helpers_Helper: visitFunction = ucc_visit_Helpers_Helpers_Helper; break;
		case ucc_P_Total_helpers_tokens_productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_tokens_productions_reducer_Reducers; break;
		case ucc_P_Total_helpers_tokens_productions_Productions_reducer: visitFunction = ucc_visit_Total_helpers_tokens_productions_Productions_reducer; break;
		case ucc_P_Total_helpers_tokens_productions_Productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_tokens_productions_Productions_reducer_Reducers; break;
		case ucc_P_Total_helpers_tokens_Tokens_productions_reducer: visitFunction = ucc_visit_Total_helpers_tokens_Tokens_productions_reducer; break;
		case ucc_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_tokens_Tokens_productions_reducer_Reducers; break;
		case ucc_P_Total_helpers_tokens_Tokens_productions_Productions_reducer: visitFunction = ucc_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer; break;
		case ucc_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers; break;
		case ucc_P_Total_helpers_Helpers_tokens_productions_reducer: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_productions_reducer; break;
		case ucc_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_productions_reducer_Reducers; break;
		case ucc_P_Total_helpers_Helpers_tokens_productions_Productions_reducer: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer; break;
		case ucc_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers; break;
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer; break;
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers; break;
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer; break;
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers: visitFunction = ucc_visit_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers; break;
	}

	if(visitFunction != nullptr) return visitFunction(production, visitData);

	switch(production->type)
	{
		case ucc_P_Expr_identifier:
		case ucc_P_Expr_Expr_comma_Expr:
		case ucc_P_Expr_Expr:
		case ucc_P_Expr_Expr_Op:
		case ucc_P_Expr_Expr_Expr:
		case ucc_P_Expr_Expr_Op_Expr:
		case ucc_P_Expr_Literal:
		case ucc_P_Expr_o_parentheses_Expr_c_parentheses:
		case ucc_P_Expr_Literal_to_Literal:
			visitFunction = ucc_visit_Expr;
		break;
		case ucc_P_Helper_identifier_attrib_Expr_semicolon:
			visitFunction = ucc_visit_Helper;
		break;
		case ucc_P_Helpers_Helper:
		case ucc_P_Helpers_Helpers_Helper:
			visitFunction = ucc_visit_Helpers;
		break;
		case ucc_P_Literal_charLiteral:
		case ucc_P_Literal_decimal:
			visitFunction = ucc_visit_Literal;
		break;
		case ucc_P_Op_comma:
		case ucc_P_Op_question:
		case ucc_P_Op_mult:
		case ucc_P_Op_sum:
		case ucc_P_Op_or:
		case ucc_P_Op_sub:
			visitFunction = ucc_visit_Op;
		break;
		case ucc_P_Production_identifier_attrib_Expr_semicolon:
			visitFunction = ucc_visit_Production;
		break;
		case ucc_P_Productions_Production:
		case ucc_P_Productions_Productions_Production:
			visitFunction = ucc_visit_Productions;
		break;
		case ucc_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon:
		case ucc_P_Reducer_identifier_reduce_Expr_semicolon:
			visitFunction = ucc_visit_Reducer;
		break;
		case ucc_P_Reducers_Reducer:
		case ucc_P_Reducers_Reducers_Reducer:
			visitFunction = ucc_visit_Reducers;
		break;
		case ucc_P_Token_identifier_attrib_Expr_semicolon:
		case ucc_P_Token_mult_identifier_attrib_Expr_semicolon:
			visitFunction = ucc_visit_Token;
		break;
		case ucc_P_Tokens_Token:
		case ucc_P_Tokens_Tokens_Token:
			visitFunction = ucc_visit_Tokens;
		break;
		case ucc_P_Total_helpers_tokens_productions_reducer:
		case ucc_P_Total_helpers_tokens_productions_reducer_Reducers:
		case ucc_P_Total_helpers_tokens_productions_Productions_reducer:
		case ucc_P_Total_helpers_tokens_productions_Productions_reducer_Reducers:
		case ucc_P_Total_helpers_tokens_Tokens_productions_reducer:
		case ucc_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers:
		case ucc_P_Total_helpers_tokens_Tokens_productions_Productions_reducer:
		case ucc_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers:
		case ucc_P_Total_helpers_Helpers_tokens_productions_reducer:
		case ucc_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers:
		case ucc_P_Total_helpers_Helpers_tokens_productions_Productions_reducer:
		case ucc_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers:
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer:
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers:
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer:
		case ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers:
			visitFunction = ucc_visit_Total;
		break;
	}

	if(visitFunction != nullptr) return visitFunction(production, visitData);

	return ucc_visit_defaultFunction(production, visitData);
}
bool ucc_visitNodes(Production* production, VisitData* visitData)
{ return visitNodes(production, visitData, ucc_visit); }
bool ucc_nodeRedundancyTable[] = {
	false // UNKNOWN
	,false // Total_helpers_tokens_productions_reducer
	,false // Op_comma
	,false // Expr_identifier
	,false // Expr_Expr_comma_Expr
	,true // Expr_Expr
	,false // Reducer_o_brackets_identifier_c_brackets_reduce_Expr_semicolon
	,false // Reducer_identifier_reduce_Expr_semicolon
	,false // Reducers_Reducer
	,false // Reducers_Reducers_Reducer
	,false // Op_question
	,false // Expr_Expr_Op
	,false // Expr_Expr_Expr
	,false // Expr_Expr_Op_Expr
	,false // Production_identifier_attrib_Expr_semicolon
	,false // Productions_Production
	,false // Productions_Productions_Production
	,false // Op_mult
	,false // Op_sum
	,false // Op_or
	,false // Literal_charLiteral
	,false // Expr_Literal
	,false // Expr_o_parentheses_Expr_c_parentheses
	,false // Token_identifier_attrib_Expr_semicolon
	,false // Token_mult_identifier_attrib_Expr_semicolon
	,false // Tokens_Token
	,false // Tokens_Tokens_Token
	,false // Literal_decimal
	,false // Op_sub
	,false // Expr_Literal_to_Literal
	,false // Helper_identifier_attrib_Expr_semicolon
	,false // Helpers_Helper
	,false // Helpers_Helpers_Helper
	,false // Total_helpers_tokens_productions_reducer_Reducers
	,false // Total_helpers_tokens_productions_Productions_reducer
	,false // Total_helpers_tokens_productions_Productions_reducer_Reducers
	,false // Total_helpers_tokens_Tokens_productions_reducer
	,false // Total_helpers_tokens_Tokens_productions_reducer_Reducers
	,false // Total_helpers_tokens_Tokens_productions_Productions_reducer
	,false // Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_productions_reducer
	,false // Total_helpers_Helpers_tokens_productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_productions_Productions_reducer
	,false // Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_Tokens_productions_reducer
	,false // Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers
	,false // Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer
	,false // Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers
};
