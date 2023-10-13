#include<parsers/parser.h>
#include<parsers/ucc/productions.h>
#include<parsers/ucc/uccParser.h>

static int goToTable(int state, int productionIndex)
{
	switch(state)
	{
		case 0:
		switch(productionIndex)
		{
			case 0: return 1; break;
		}
		break;
		case 2:
		switch(productionIndex)
		{
			case 27: return 76; break;
			case 26: return 110; break;
		}
		break;
		case 3:
		switch(productionIndex)
		{
			case 21: return 4; break;
			case 20: return 69; break;
		}
		break;
		case 4:
		switch(productionIndex)
		{
			case 20: return 43; break;
		}
		break;
		case 5:
		switch(productionIndex)
		{
			case 12: return 6; break;
			case 11: return 40; break;
		}
		break;
		case 6:
		switch(productionIndex)
		{
			case 11: return 25; break;
		}
		break;
		case 7:
		switch(productionIndex)
		{
			case 5: return 8; break;
			case 4: return 24; break;
		}
		break;
		case 8:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 11:
		switch(productionIndex)
		{
			case 3: return 12; break;
			case 2: return 17; break;
		}
		break;
		case 13:
		switch(productionIndex)
		{
			case 2: return 14; break;
		}
		break;
		case 21:
		switch(productionIndex)
		{
			case 3: return 22; break;
			case 2: return 17; break;
		}
		break;
		case 27:
		switch(productionIndex)
		{
			case 10: return 28; break;
			case 9: return 39; break;
			case 8: return 36; break;
			case 7: return 34; break;
		}
		break;
		case 28:
		switch(productionIndex)
		{
			case 14: return 29; break;
		}
		break;
		case 29:
		switch(productionIndex)
		{
			case 9: return 30; break;
			case 8: return 36; break;
			case 7: return 34; break;
		}
		break;
		case 30:
		switch(productionIndex)
		{
			case 8: return 31; break;
			case 7: return 34; break;
		}
		break;
		case 31:
		switch(productionIndex)
		{
			case 6: return 32; break;
		}
		break;
		case 36:
		switch(productionIndex)
		{
			case 6: return 32; break;
		}
		break;
		case 39:
		switch(productionIndex)
		{
			case 8: return 31; break;
			case 7: return 34; break;
		}
		break;
		case 41:
		switch(productionIndex)
		{
			case 5: return 42; break;
			case 4: return 24; break;
		}
		break;
		case 42:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 46:
		switch(productionIndex)
		{
			case 19: return 47; break;
			case 18: return 59; break;
			case 17: return 63; break;
			case 16: return 55; break;
			case 15: return 61; break;
		}
		break;
		case 47:
		switch(productionIndex)
		{
			case 14: return 48; break;
		}
		break;
		case 48:
		switch(productionIndex)
		{
			case 18: return 49; break;
			case 17: return 63; break;
			case 16: return 55; break;
			case 15: return 61; break;
		}
		break;
		case 49:
		switch(productionIndex)
		{
			case 17: return 50; break;
			case 16: return 55; break;
			case 15: return 61; break;
		}
		break;
		case 50:
		switch(productionIndex)
		{
			case 13: return 51; break;
		}
		break;
		case 56:
		switch(productionIndex)
		{
			case 19: return 57; break;
			case 18: return 59; break;
			case 17: return 63; break;
			case 16: return 55; break;
			case 15: return 61; break;
		}
		break;
		case 57:
		switch(productionIndex)
		{
			case 14: return 48; break;
		}
		break;
		case 59:
		switch(productionIndex)
		{
			case 17: return 50; break;
			case 16: return 55; break;
			case 15: return 61; break;
		}
		break;
		case 63:
		switch(productionIndex)
		{
			case 13: return 51; break;
		}
		break;
		case 66:
		switch(productionIndex)
		{
			case 19: return 67; break;
			case 18: return 59; break;
			case 17: return 63; break;
			case 16: return 55; break;
			case 15: return 61; break;
		}
		break;
		case 67:
		switch(productionIndex)
		{
			case 14: return 48; break;
		}
		break;
		case 70:
		switch(productionIndex)
		{
			case 12: return 73; break;
			case 11: return 40; break;
		}
		break;
		case 71:
		switch(productionIndex)
		{
			case 5: return 72; break;
			case 4: return 24; break;
		}
		break;
		case 72:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 73:
		switch(productionIndex)
		{
			case 11: return 25; break;
		}
		break;
		case 74:
		switch(productionIndex)
		{
			case 5: return 75; break;
			case 4: return 24; break;
		}
		break;
		case 75:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 76:
		switch(productionIndex)
		{
			case 26: return 91; break;
		}
		break;
		case 77:
		switch(productionIndex)
		{
			case 21: return 84; break;
			case 20: return 69; break;
		}
		break;
		case 78:
		switch(productionIndex)
		{
			case 12: return 79; break;
			case 11: return 40; break;
		}
		break;
		case 79:
		switch(productionIndex)
		{
			case 11: return 25; break;
		}
		break;
		case 80:
		switch(productionIndex)
		{
			case 5: return 81; break;
			case 4: return 24; break;
		}
		break;
		case 81:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 82:
		switch(productionIndex)
		{
			case 5: return 83; break;
			case 4: return 24; break;
		}
		break;
		case 83:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 84:
		switch(productionIndex)
		{
			case 20: return 43; break;
		}
		break;
		case 85:
		switch(productionIndex)
		{
			case 12: return 88; break;
			case 11: return 40; break;
		}
		break;
		case 86:
		switch(productionIndex)
		{
			case 5: return 87; break;
			case 4: return 24; break;
		}
		break;
		case 87:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 88:
		switch(productionIndex)
		{
			case 11: return 25; break;
		}
		break;
		case 89:
		switch(productionIndex)
		{
			case 5: return 90; break;
			case 4: return 24; break;
		}
		break;
		case 90:
		switch(productionIndex)
		{
			case 4: return 9; break;
		}
		break;
		case 93:
		switch(productionIndex)
		{
			case 25: return 94; break;
			case 24: return 107; break;
			case 22: return 97; break;
		}
		break;
		case 94:
		switch(productionIndex)
		{
			case 23: return 95; break;
		}
		break;
		case 95:
		switch(productionIndex)
		{
			case 24: return 96; break;
			case 22: return 97; break;
		}
		break;
		case 98:
		switch(productionIndex)
		{
			case 22: return 99; break;
		}
		break;
		case 102:
		switch(productionIndex)
		{
			case 25: return 103; break;
			case 24: return 107; break;
			case 22: return 97; break;
		}
		break;
		case 103:
		switch(productionIndex)
		{
			case 23: return 95; break;
		}
		break;
	}
	return 0;
}

Parser ucc_parse(AllProductions* allProductions, Production* (*creationFunction)(AllProductions*), Token* token)
{
	Action state0Actions[] = {
		createShift(T_helpers,2)
	};
	Action state1Actions[] = {
		createAcceptAction()
	};
	Action state2Actions[] = {
		createShift(T_tokens,3),
		createShift(T_identifier,92)
	};
	Action state3Actions[] = {
		createShift(T_identifier,65),
		createShift(T_productions,70),
		createShift(T_mult,44)
	};
	Action state4Actions[] = {
		createShift(T_identifier,65),
		createShift(T_productions,5),
		createShift(T_mult,44)
	};
	Action state5Actions[] = {
		createShift(T_reducer,41),
		createShift(T_identifier,26)
	};
	Action state6Actions[] = {
		createShift(T_reducer,7),
		createShift(T_identifier,26)
	};
	Action state7Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_Tokens_productions_Productions_reducer, 6)
	};
	Action state8Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers, 7)
	};
	Action state9Actions[] = {
		createReduce1(T_identifier, 5, ucc_P_Reducers_Reducers_Reducer, 2),
		createReduce1(T_o_brackets, 5, ucc_P_Reducers_Reducers_Reducer, 2),
		createReduce1(END_OF_INPUT, 5, ucc_P_Reducers_Reducers_Reducer, 2)
	};
	Action state10Actions[] = {
		createShift(T_reduce,11)
	};
	Action state11Actions[] = {
		createShift(T_identifier,15)
	};
	Action state12Actions[] = {
		createShift(T_comma,13),
		createShift(T_semicolon,16)
	};
	Action state13Actions[] = {
		createShift(T_identifier,15)
	};
	Action state14Actions[] = {
		createReduce1(T_comma, 3, ucc_P_Expr_Expr_comma_Expr, 3),
		createReduce1(T_semicolon, 3, ucc_P_Expr_Expr_comma_Expr, 3)
	};
	Action state15Actions[] = {
		createReduce1(T_comma, 2, ucc_P_Expr_identifier, 1),
		createReduce1(T_semicolon, 2, ucc_P_Expr_identifier, 1)
	};
	Action state16Actions[] = {
		createReduce1(T_identifier, 4, ucc_P_Reducer_identifier_reduce_Expr_semicolon, 4),
		createReduce1(T_o_brackets, 4, ucc_P_Reducer_identifier_reduce_Expr_semicolon, 4),
		createReduce1(END_OF_INPUT, 4, ucc_P_Reducer_identifier_reduce_Expr_semicolon, 4)
	};
	Action state17Actions[] = {
		createReduce1(T_comma, 3, ucc_P_Expr_Expr, 1),
		createReduce1(T_semicolon, 3, ucc_P_Expr_Expr, 1)
	};
	Action state18Actions[] = {
		createShift(T_identifier,19)
	};
	Action state19Actions[] = {
		createShift(T_c_brackets,20)
	};
	Action state20Actions[] = {
		createShift(T_reduce,21)
	};
	Action state21Actions[] = {
		createShift(T_identifier,15)
	};
	Action state22Actions[] = {
		createShift(T_comma,13),
		createShift(T_semicolon,23)
	};
	Action state23Actions[] = {
		createReduce1(T_identifier, 4, 1, 6),
		createReduce1(T_o_brackets, 4, 1, 6),
		createReduce1(END_OF_INPUT, 4, 1, 6)
	};
	Action state24Actions[] = {
		createReduce1(T_identifier, 5, ucc_P_Reducers_Reducer, 1),
		createReduce1(T_o_brackets, 5, ucc_P_Reducers_Reducer, 1),
		createReduce1(END_OF_INPUT, 5, ucc_P_Reducers_Reducer, 1)
	};
	Action state25Actions[] = {
		createReduce1(T_reducer, 12, ucc_P_Productions_Productions_Production, 2),
		createReduce1(T_identifier, 12, ucc_P_Productions_Productions_Production, 2)
	};
	Action state26Actions[] = {
		createShift(T_attrib,27)
	};
	Action state27Actions[] = {
		createShift(T_identifier,35)
	};
	Action state28Actions[] = {
		createShift(T_semicolon,38),
		createShift(T_or,37)
	};
	Action state29Actions[] = {
		createShift(T_identifier,35)
	};
	Action state30Actions[] = {
		createShift(T_identifier,35),
		createReduce1(T_semicolon, 10, ucc_P_Expr_Expr_Op_Expr, 3),
		createReduce1(T_or, 10, ucc_P_Expr_Expr_Op_Expr, 3)
	};
	Action state31Actions[] = {
		createReduce1(T_identifier, 9, ucc_P_Expr_Expr_Expr, 2),
		createReduce1(T_semicolon, 9, ucc_P_Expr_Expr_Expr, 2),
		createShift(T_question,33),
		createReduce1(T_or, 9, ucc_P_Expr_Expr_Expr, 2)
	};
	Action state32Actions[] = {
		createReduce1(T_identifier, 8, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_semicolon, 8, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_question, 8, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_or, 8, ucc_P_Expr_Expr_Op, 2)
	};
	Action state33Actions[] = {
		createReduce1(T_identifier, 6, ucc_P_Op_question, 1),
		createReduce1(T_semicolon, 6, ucc_P_Op_question, 1),
		createReduce1(T_question, 6, ucc_P_Op_question, 1),
		createReduce1(T_or, 6, ucc_P_Op_question, 1)
	};
	Action state34Actions[] = {
		createReduce1(T_identifier, 8, ucc_P_Expr_Expr, 1),
		createReduce1(T_semicolon, 8, ucc_P_Expr_Expr, 1),
		createReduce1(T_question, 8, ucc_P_Expr_Expr, 1),
		createReduce1(T_or, 8, ucc_P_Expr_Expr, 1)
	};
	Action state35Actions[] = {
		createReduce1(T_identifier, 7, ucc_P_Expr_identifier, 1),
		createReduce1(T_semicolon, 7, ucc_P_Expr_identifier, 1),
		createReduce1(T_question, 7, ucc_P_Expr_identifier, 1),
		createReduce1(T_or, 7, ucc_P_Expr_identifier, 1)
	};
	Action state36Actions[] = {
		createReduce1(T_identifier, 9, ucc_P_Expr_Expr, 1),
		createReduce1(T_semicolon, 9, ucc_P_Expr_Expr, 1),
		createShift(T_question,33),
		createReduce1(T_or, 9, ucc_P_Expr_Expr, 1)
	};
	Action state37Actions[] = {
		createReduce1(T_charLiteral, 14, ucc_P_Op_or, 1),
		createReduce1(T_identifier, 14, ucc_P_Op_or, 1),
		createReduce1(T_o_parentheses, 14, ucc_P_Op_or, 1)
	};
	Action state38Actions[] = {
		createReduce1(T_reducer, 11, ucc_P_Production_identifier_attrib_Expr_semicolon, 4),
		createReduce1(T_identifier, 11, ucc_P_Production_identifier_attrib_Expr_semicolon, 4)
	};
	Action state39Actions[] = {
		createShift(T_identifier,35),
		createReduce1(T_semicolon, 10, ucc_P_Expr_Expr, 1),
		createReduce1(T_or, 10, ucc_P_Expr_Expr, 1)
	};
	Action state40Actions[] = {
		createReduce1(T_reducer, 12, ucc_P_Productions_Production, 1),
		createReduce1(T_identifier, 12, ucc_P_Productions_Production, 1)
	};
	Action state41Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_Tokens_productions_reducer, 5)
	};
	Action state42Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers, 6)
	};
	Action state43Actions[] = {
		createReduce1(T_identifier, 21, ucc_P_Tokens_Tokens_Token, 2),
		createReduce1(T_productions, 21, ucc_P_Tokens_Tokens_Token, 2),
		createReduce1(T_mult, 21, ucc_P_Tokens_Tokens_Token, 2)
	};
	Action state44Actions[] = {
		createShift(T_identifier,45)
	};
	Action state45Actions[] = {
		createShift(T_attrib,46)
	};
	Action state46Actions[] = {
		createShift(T_charLiteral,62),
		createShift(T_identifier,60),
		createShift(T_o_parentheses,56)
	};
	Action state47Actions[] = {
		createShift(T_semicolon,64),
		createShift(T_or,37)
	};
	Action state48Actions[] = {
		createShift(T_charLiteral,62),
		createShift(T_identifier,60),
		createShift(T_o_parentheses,56)
	};
	Action state49Actions[] = {
		createReduce1(T_c_parentheses, 19, ucc_P_Expr_Expr_Op_Expr, 3),
		createShift(T_charLiteral,62),
		createShift(T_identifier,60),
		createReduce1(T_semicolon, 19, ucc_P_Expr_Expr_Op_Expr, 3),
		createShift(T_o_parentheses,56),
		createReduce1(T_or, 19, ucc_P_Expr_Expr_Op_Expr, 3)
	};
	Action state50Actions[] = {
		createReduce1(T_c_parentheses, 18, ucc_P_Expr_Expr_Expr, 2),
		createReduce1(T_charLiteral, 18, ucc_P_Expr_Expr_Expr, 2),
		createShift(T_sum,52),
		createReduce1(T_identifier, 18, ucc_P_Expr_Expr_Expr, 2),
		createReduce1(T_semicolon, 18, ucc_P_Expr_Expr_Expr, 2),
		createReduce1(T_o_parentheses, 18, ucc_P_Expr_Expr_Expr, 2),
		createShift(T_question,54),
		createReduce1(T_or, 18, ucc_P_Expr_Expr_Expr, 2),
		createShift(T_mult,53)
	};
	Action state51Actions[] = {
		createReduce1(T_c_parentheses, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_charLiteral, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_sum, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_identifier, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_semicolon, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_o_parentheses, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_question, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_or, 17, ucc_P_Expr_Expr_Op, 2),
		createReduce1(T_mult, 17, ucc_P_Expr_Expr_Op, 2)
	};
	Action state52Actions[] = {
		createReduce1(T_c_parentheses, 13, ucc_P_Op_sum, 1),
		createReduce1(T_charLiteral, 13, ucc_P_Op_sum, 1),
		createReduce1(T_sum, 13, ucc_P_Op_sum, 1),
		createReduce1(T_identifier, 13, ucc_P_Op_sum, 1),
		createReduce1(T_semicolon, 13, ucc_P_Op_sum, 1),
		createReduce1(T_o_parentheses, 13, ucc_P_Op_sum, 1),
		createReduce1(T_question, 13, ucc_P_Op_sum, 1),
		createReduce1(T_or, 13, ucc_P_Op_sum, 1),
		createReduce1(T_mult, 13, ucc_P_Op_sum, 1)
	};
	Action state53Actions[] = {
		createReduce1(T_c_parentheses, 13, ucc_P_Op_mult, 1),
		createReduce1(T_charLiteral, 13, ucc_P_Op_mult, 1),
		createReduce1(T_sum, 13, ucc_P_Op_mult, 1),
		createReduce1(T_identifier, 13, ucc_P_Op_mult, 1),
		createReduce1(T_semicolon, 13, ucc_P_Op_mult, 1),
		createReduce1(T_o_parentheses, 13, ucc_P_Op_mult, 1),
		createReduce1(T_question, 13, ucc_P_Op_mult, 1),
		createReduce1(T_or, 13, ucc_P_Op_mult, 1),
		createReduce1(T_mult, 13, ucc_P_Op_mult, 1)
	};
	Action state54Actions[] = {
		createReduce1(T_c_parentheses, 13, ucc_P_Op_question, 1),
		createReduce1(T_charLiteral, 13, ucc_P_Op_question, 1),
		createReduce1(T_sum, 13, ucc_P_Op_question, 1),
		createReduce1(T_identifier, 13, ucc_P_Op_question, 1),
		createReduce1(T_semicolon, 13, ucc_P_Op_question, 1),
		createReduce1(T_o_parentheses, 13, ucc_P_Op_question, 1),
		createReduce1(T_question, 13, ucc_P_Op_question, 1),
		createReduce1(T_or, 13, ucc_P_Op_question, 1),
		createReduce1(T_mult, 13, ucc_P_Op_question, 1)
	};
	Action state55Actions[] = {
		createReduce1(T_c_parentheses, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_charLiteral, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_sum, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_identifier, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_semicolon, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_o_parentheses, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_question, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_or, 17, ucc_P_Expr_Expr, 1),
		createReduce1(T_mult, 17, ucc_P_Expr_Expr, 1)
	};
	Action state56Actions[] = {
		createShift(T_charLiteral,62),
		createShift(T_identifier,60),
		createShift(T_o_parentheses,56)
	};
	Action state57Actions[] = {
		createShift(T_c_parentheses,58),
		createShift(T_or,37)
	};
	Action state58Actions[] = {
		createReduce1(T_c_parentheses, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_charLiteral, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_sum, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_identifier, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_semicolon, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_o_parentheses, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_question, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_or, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_mult, 16, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3)
	};
	Action state59Actions[] = {
		createReduce1(T_c_parentheses, 19, ucc_P_Expr_Expr, 1),
		createShift(T_charLiteral,62),
		createShift(T_identifier,60),
		createReduce1(T_semicolon, 19, ucc_P_Expr_Expr, 1),
		createShift(T_o_parentheses,56),
		createReduce1(T_or, 19, ucc_P_Expr_Expr, 1)
	};
	Action state60Actions[] = {
		createReduce1(T_c_parentheses, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_charLiteral, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_sum, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_identifier, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_semicolon, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_o_parentheses, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_question, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_or, 16, ucc_P_Expr_identifier, 1),
		createReduce1(T_mult, 16, ucc_P_Expr_identifier, 1)
	};
	Action state61Actions[] = {
		createReduce1(T_c_parentheses, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_charLiteral, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_sum, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_identifier, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_semicolon, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_o_parentheses, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_question, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_or, 16, ucc_P_Expr_Literal, 1),
		createReduce1(T_mult, 16, ucc_P_Expr_Literal, 1)
	};
	Action state62Actions[] = {
		createReduce1(T_c_parentheses, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_charLiteral, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_sum, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_identifier, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_semicolon, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_o_parentheses, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_question, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_or, 15, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_mult, 15, ucc_P_Literal_charLiteral, 1)
	};
	Action state63Actions[] = {
		createReduce1(T_c_parentheses, 18, ucc_P_Expr_Expr, 1),
		createReduce1(T_charLiteral, 18, ucc_P_Expr_Expr, 1),
		createShift(T_sum,52),
		createReduce1(T_identifier, 18, ucc_P_Expr_Expr, 1),
		createReduce1(T_semicolon, 18, ucc_P_Expr_Expr, 1),
		createReduce1(T_o_parentheses, 18, ucc_P_Expr_Expr, 1),
		createShift(T_question,54),
		createReduce1(T_or, 18, ucc_P_Expr_Expr, 1),
		createShift(T_mult,53)
	};
	Action state64Actions[] = {
		createReduce1(T_identifier, 20, ucc_P_Token_mult_identifier_attrib_Expr_semicolon, 5),
		createReduce1(T_productions, 20, ucc_P_Token_mult_identifier_attrib_Expr_semicolon, 5),
		createReduce1(T_mult, 20, ucc_P_Token_mult_identifier_attrib_Expr_semicolon, 5)
	};
	Action state65Actions[] = {
		createShift(T_attrib,66)
	};
	Action state66Actions[] = {
		createShift(T_charLiteral,62),
		createShift(T_identifier,60),
		createShift(T_o_parentheses,56)
	};
	Action state67Actions[] = {
		createShift(T_semicolon,68),
		createShift(T_or,37)
	};
	Action state68Actions[] = {
		createReduce1(T_identifier, 20, ucc_P_Token_identifier_attrib_Expr_semicolon, 4),
		createReduce1(T_productions, 20, ucc_P_Token_identifier_attrib_Expr_semicolon, 4),
		createReduce1(T_mult, 20, ucc_P_Token_identifier_attrib_Expr_semicolon, 4)
	};
	Action state69Actions[] = {
		createReduce1(T_identifier, 21, ucc_P_Tokens_Token, 1),
		createReduce1(T_productions, 21, ucc_P_Tokens_Token, 1),
		createReduce1(T_mult, 21, ucc_P_Tokens_Token, 1)
	};
	Action state70Actions[] = {
		createShift(T_reducer,71),
		createShift(T_identifier,26)
	};
	Action state71Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_productions_reducer, 4)
	};
	Action state72Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_productions_reducer_Reducers, 5)
	};
	Action state73Actions[] = {
		createShift(T_reducer,74),
		createShift(T_identifier,26)
	};
	Action state74Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_productions_Productions_reducer, 5)
	};
	Action state75Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_tokens_productions_Productions_reducer_Reducers, 6)
	};
	Action state76Actions[] = {
		createShift(T_tokens,77),
		createShift(T_identifier,92)
	};
	Action state77Actions[] = {
		createShift(T_identifier,65),
		createShift(T_productions,78),
		createShift(T_mult,44)
	};
	Action state78Actions[] = {
		createShift(T_reducer,82),
		createShift(T_identifier,26)
	};
	Action state79Actions[] = {
		createShift(T_reducer,80),
		createShift(T_identifier,26)
	};
	Action state80Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_productions_Productions_reducer, 6)
	};
	Action state81Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers, 7)
	};
	Action state82Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_productions_reducer, 5)
	};
	Action state83Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers, 6)
	};
	Action state84Actions[] = {
		createShift(T_identifier,65),
		createShift(T_productions,85),
		createShift(T_mult,44)
	};
	Action state85Actions[] = {
		createShift(T_reducer,86),
		createShift(T_identifier,26)
	};
	Action state86Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer, 6)
	};
	Action state87Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers, 7)
	};
	Action state88Actions[] = {
		createShift(T_reducer,89),
		createShift(T_identifier,26)
	};
	Action state89Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer, 7)
	};
	Action state90Actions[] = {
		createShift(T_identifier,10),
		createShift(T_o_brackets,18),
		createReduce1(END_OF_INPUT, 0, ucc_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers, 8)
	};
	Action state91Actions[] = {
		createReduce1(T_tokens, 27, ucc_P_Helpers_Helpers_Helper, 2),
		createReduce1(T_identifier, 27, ucc_P_Helpers_Helpers_Helper, 2)
	};
	Action state92Actions[] = {
		createShift(T_attrib,93)
	};
	Action state93Actions[] = {
		createShift(T_charLiteral,100),
		createShift(T_identifier,108),
		createShift(T_decimal,101),
		createShift(T_o_parentheses,102)
	};
	Action state94Actions[] = {
		createShift(T_sub,105),
		createShift(T_sum,104),
		createShift(T_semicolon,109)
	};
	Action state95Actions[] = {
		createShift(T_charLiteral,100),
		createShift(T_identifier,108),
		createShift(T_decimal,101),
		createShift(T_o_parentheses,102)
	};
	Action state96Actions[] = {
		createReduce1(T_c_parentheses, 25, ucc_P_Expr_Expr_Op_Expr, 3),
		createReduce1(T_sub, 25, ucc_P_Expr_Expr_Op_Expr, 3),
		createReduce1(T_sum, 25, ucc_P_Expr_Expr_Op_Expr, 3),
		createReduce1(T_semicolon, 25, ucc_P_Expr_Expr_Op_Expr, 3)
	};
	Action state97Actions[] = {
		createReduce1(T_c_parentheses, 24, ucc_P_Expr_Literal, 1),
		createReduce1(T_sub, 24, ucc_P_Expr_Literal, 1),
		createReduce1(T_sum, 24, ucc_P_Expr_Literal, 1),
		createReduce1(T_semicolon, 24, ucc_P_Expr_Literal, 1),
		createShift(T_to,98)
	};
	Action state98Actions[] = {
		createShift(T_charLiteral,100),
		createShift(T_decimal,101)
	};
	Action state99Actions[] = {
		createReduce1(T_c_parentheses, 24, ucc_P_Expr_Literal_to_Literal, 3),
		createReduce1(T_sub, 24, ucc_P_Expr_Literal_to_Literal, 3),
		createReduce1(T_sum, 24, ucc_P_Expr_Literal_to_Literal, 3),
		createReduce1(T_semicolon, 24, ucc_P_Expr_Literal_to_Literal, 3)
	};
	Action state100Actions[] = {
		createReduce1(T_c_parentheses, 22, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_sub, 22, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_sum, 22, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_semicolon, 22, ucc_P_Literal_charLiteral, 1),
		createReduce1(T_to, 22, ucc_P_Literal_charLiteral, 1)
	};
	Action state101Actions[] = {
		createReduce1(T_c_parentheses, 22, ucc_P_Literal_decimal, 1),
		createReduce1(T_sub, 22, ucc_P_Literal_decimal, 1),
		createReduce1(T_sum, 22, ucc_P_Literal_decimal, 1),
		createReduce1(T_semicolon, 22, ucc_P_Literal_decimal, 1),
		createReduce1(T_to, 22, ucc_P_Literal_decimal, 1)
	};
	Action state102Actions[] = {
		createShift(T_charLiteral,100),
		createShift(T_identifier,108),
		createShift(T_decimal,101),
		createShift(T_o_parentheses,102)
	};
	Action state103Actions[] = {
		createShift(T_c_parentheses,106),
		createShift(T_sub,105),
		createShift(T_sum,104)
	};
	Action state104Actions[] = {
		createReduce1(T_charLiteral, 23, ucc_P_Op_sum, 1),
		createReduce1(T_identifier, 23, ucc_P_Op_sum, 1),
		createReduce1(T_decimal, 23, ucc_P_Op_sum, 1),
		createReduce1(T_o_parentheses, 23, ucc_P_Op_sum, 1)
	};
	Action state105Actions[] = {
		createReduce1(T_charLiteral, 23, ucc_P_Op_sub, 1),
		createReduce1(T_identifier, 23, ucc_P_Op_sub, 1),
		createReduce1(T_decimal, 23, ucc_P_Op_sub, 1),
		createReduce1(T_o_parentheses, 23, ucc_P_Op_sub, 1)
	};
	Action state106Actions[] = {
		createReduce1(T_c_parentheses, 24, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_sub, 24, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_sum, 24, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_semicolon, 24, ucc_P_Expr_o_parentheses_Expr_c_parentheses, 3)
	};
	Action state107Actions[] = {
		createReduce1(T_c_parentheses, 25, ucc_P_Expr_Expr, 1),
		createReduce1(T_sub, 25, ucc_P_Expr_Expr, 1),
		createReduce1(T_sum, 25, ucc_P_Expr_Expr, 1),
		createReduce1(T_semicolon, 25, ucc_P_Expr_Expr, 1)
	};
	Action state108Actions[] = {
		createReduce1(T_c_parentheses, 24, ucc_P_Expr_identifier, 1),
		createReduce1(T_sub, 24, ucc_P_Expr_identifier, 1),
		createReduce1(T_sum, 24, ucc_P_Expr_identifier, 1),
		createReduce1(T_semicolon, 24, ucc_P_Expr_identifier, 1)
	};
	Action state109Actions[] = {
		createReduce1(T_tokens, 26, ucc_P_Helper_identifier_attrib_Expr_semicolon, 4),
		createReduce1(T_identifier, 26, ucc_P_Helper_identifier_attrib_Expr_semicolon, 4)
	};
	Action state110Actions[] = {
		createReduce1(T_tokens, 27, ucc_P_Helpers_Helper, 1),
		createReduce1(T_identifier, 27, ucc_P_Helpers_Helper, 1)
	};
	State states[] = {
		createState(state0Actions, sizeof(state0Actions)/sizeof(Action)),
		createState(state1Actions, sizeof(state1Actions)/sizeof(Action)),
		createState(state2Actions, sizeof(state2Actions)/sizeof(Action)),
		createState(state3Actions, sizeof(state3Actions)/sizeof(Action)),
		createState(state4Actions, sizeof(state4Actions)/sizeof(Action)),
		createState(state5Actions, sizeof(state5Actions)/sizeof(Action)),
		createState(state6Actions, sizeof(state6Actions)/sizeof(Action)),
		createState(state7Actions, sizeof(state7Actions)/sizeof(Action)),
		createState(state8Actions, sizeof(state8Actions)/sizeof(Action)),
		createState(state9Actions, sizeof(state9Actions)/sizeof(Action)),
		createState(state10Actions, sizeof(state10Actions)/sizeof(Action)),
		createState(state11Actions, sizeof(state11Actions)/sizeof(Action)),
		createState(state12Actions, sizeof(state12Actions)/sizeof(Action)),
		createState(state13Actions, sizeof(state13Actions)/sizeof(Action)),
		createState(state14Actions, sizeof(state14Actions)/sizeof(Action)),
		createState(state15Actions, sizeof(state15Actions)/sizeof(Action)),
		createState(state16Actions, sizeof(state16Actions)/sizeof(Action)),
		createState(state17Actions, sizeof(state17Actions)/sizeof(Action)),
		createState(state18Actions, sizeof(state18Actions)/sizeof(Action)),
		createState(state19Actions, sizeof(state19Actions)/sizeof(Action)),
		createState(state20Actions, sizeof(state20Actions)/sizeof(Action)),
		createState(state21Actions, sizeof(state21Actions)/sizeof(Action)),
		createState(state22Actions, sizeof(state22Actions)/sizeof(Action)),
		createState(state23Actions, sizeof(state23Actions)/sizeof(Action)),
		createState(state24Actions, sizeof(state24Actions)/sizeof(Action)),
		createState(state25Actions, sizeof(state25Actions)/sizeof(Action)),
		createState(state26Actions, sizeof(state26Actions)/sizeof(Action)),
		createState(state27Actions, sizeof(state27Actions)/sizeof(Action)),
		createState(state28Actions, sizeof(state28Actions)/sizeof(Action)),
		createState(state29Actions, sizeof(state29Actions)/sizeof(Action)),
		createState(state30Actions, sizeof(state30Actions)/sizeof(Action)),
		createState(state31Actions, sizeof(state31Actions)/sizeof(Action)),
		createState(state32Actions, sizeof(state32Actions)/sizeof(Action)),
		createState(state33Actions, sizeof(state33Actions)/sizeof(Action)),
		createState(state34Actions, sizeof(state34Actions)/sizeof(Action)),
		createState(state35Actions, sizeof(state35Actions)/sizeof(Action)),
		createState(state36Actions, sizeof(state36Actions)/sizeof(Action)),
		createState(state37Actions, sizeof(state37Actions)/sizeof(Action)),
		createState(state38Actions, sizeof(state38Actions)/sizeof(Action)),
		createState(state39Actions, sizeof(state39Actions)/sizeof(Action)),
		createState(state40Actions, sizeof(state40Actions)/sizeof(Action)),
		createState(state41Actions, sizeof(state41Actions)/sizeof(Action)),
		createState(state42Actions, sizeof(state42Actions)/sizeof(Action)),
		createState(state43Actions, sizeof(state43Actions)/sizeof(Action)),
		createState(state44Actions, sizeof(state44Actions)/sizeof(Action)),
		createState(state45Actions, sizeof(state45Actions)/sizeof(Action)),
		createState(state46Actions, sizeof(state46Actions)/sizeof(Action)),
		createState(state47Actions, sizeof(state47Actions)/sizeof(Action)),
		createState(state48Actions, sizeof(state48Actions)/sizeof(Action)),
		createState(state49Actions, sizeof(state49Actions)/sizeof(Action)),
		createState(state50Actions, sizeof(state50Actions)/sizeof(Action)),
		createState(state51Actions, sizeof(state51Actions)/sizeof(Action)),
		createState(state52Actions, sizeof(state52Actions)/sizeof(Action)),
		createState(state53Actions, sizeof(state53Actions)/sizeof(Action)),
		createState(state54Actions, sizeof(state54Actions)/sizeof(Action)),
		createState(state55Actions, sizeof(state55Actions)/sizeof(Action)),
		createState(state56Actions, sizeof(state56Actions)/sizeof(Action)),
		createState(state57Actions, sizeof(state57Actions)/sizeof(Action)),
		createState(state58Actions, sizeof(state58Actions)/sizeof(Action)),
		createState(state59Actions, sizeof(state59Actions)/sizeof(Action)),
		createState(state60Actions, sizeof(state60Actions)/sizeof(Action)),
		createState(state61Actions, sizeof(state61Actions)/sizeof(Action)),
		createState(state62Actions, sizeof(state62Actions)/sizeof(Action)),
		createState(state63Actions, sizeof(state63Actions)/sizeof(Action)),
		createState(state64Actions, sizeof(state64Actions)/sizeof(Action)),
		createState(state65Actions, sizeof(state65Actions)/sizeof(Action)),
		createState(state66Actions, sizeof(state66Actions)/sizeof(Action)),
		createState(state67Actions, sizeof(state67Actions)/sizeof(Action)),
		createState(state68Actions, sizeof(state68Actions)/sizeof(Action)),
		createState(state69Actions, sizeof(state69Actions)/sizeof(Action)),
		createState(state70Actions, sizeof(state70Actions)/sizeof(Action)),
		createState(state71Actions, sizeof(state71Actions)/sizeof(Action)),
		createState(state72Actions, sizeof(state72Actions)/sizeof(Action)),
		createState(state73Actions, sizeof(state73Actions)/sizeof(Action)),
		createState(state74Actions, sizeof(state74Actions)/sizeof(Action)),
		createState(state75Actions, sizeof(state75Actions)/sizeof(Action)),
		createState(state76Actions, sizeof(state76Actions)/sizeof(Action)),
		createState(state77Actions, sizeof(state77Actions)/sizeof(Action)),
		createState(state78Actions, sizeof(state78Actions)/sizeof(Action)),
		createState(state79Actions, sizeof(state79Actions)/sizeof(Action)),
		createState(state80Actions, sizeof(state80Actions)/sizeof(Action)),
		createState(state81Actions, sizeof(state81Actions)/sizeof(Action)),
		createState(state82Actions, sizeof(state82Actions)/sizeof(Action)),
		createState(state83Actions, sizeof(state83Actions)/sizeof(Action)),
		createState(state84Actions, sizeof(state84Actions)/sizeof(Action)),
		createState(state85Actions, sizeof(state85Actions)/sizeof(Action)),
		createState(state86Actions, sizeof(state86Actions)/sizeof(Action)),
		createState(state87Actions, sizeof(state87Actions)/sizeof(Action)),
		createState(state88Actions, sizeof(state88Actions)/sizeof(Action)),
		createState(state89Actions, sizeof(state89Actions)/sizeof(Action)),
		createState(state90Actions, sizeof(state90Actions)/sizeof(Action)),
		createState(state91Actions, sizeof(state91Actions)/sizeof(Action)),
		createState(state92Actions, sizeof(state92Actions)/sizeof(Action)),
		createState(state93Actions, sizeof(state93Actions)/sizeof(Action)),
		createState(state94Actions, sizeof(state94Actions)/sizeof(Action)),
		createState(state95Actions, sizeof(state95Actions)/sizeof(Action)),
		createState(state96Actions, sizeof(state96Actions)/sizeof(Action)),
		createState(state97Actions, sizeof(state97Actions)/sizeof(Action)),
		createState(state98Actions, sizeof(state98Actions)/sizeof(Action)),
		createState(state99Actions, sizeof(state99Actions)/sizeof(Action)),
		createState(state100Actions, sizeof(state100Actions)/sizeof(Action)),
		createState(state101Actions, sizeof(state101Actions)/sizeof(Action)),
		createState(state102Actions, sizeof(state102Actions)/sizeof(Action)),
		createState(state103Actions, sizeof(state103Actions)/sizeof(Action)),
		createState(state104Actions, sizeof(state104Actions)/sizeof(Action)),
		createState(state105Actions, sizeof(state105Actions)/sizeof(Action)),
		createState(state106Actions, sizeof(state106Actions)/sizeof(Action)),
		createState(state107Actions, sizeof(state107Actions)/sizeof(Action)),
		createState(state108Actions, sizeof(state108Actions)/sizeof(Action)),
		createState(state109Actions, sizeof(state109Actions)/sizeof(Action)),
		createState(state110Actions, sizeof(state110Actions)/sizeof(Action))
	};
	return parse(allProductions, creationFunction, states, goToTable, token);
}
