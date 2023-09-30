#include<parsers/parser.h>
#include<parsers/ucc/productions.h>
#include<parsers/ucc/parser.h>

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
			case 25: return 67; break;
			case 24: return 100; break;
		}
		break;
		case 3:
		switch(productionIndex)
		{
			case 19: return 4; break;
			case 18: return 60; break;
		}
		break;
		case 4:
		switch(productionIndex)
		{
			case 18: return 41; break;
		}
		break;
		case 5:
		switch(productionIndex)
		{
			case 11: return 6; break;
			case 10: return 38; break;
		}
		break;
		case 6:
		switch(productionIndex)
		{
			case 10: return 7; break;
		}
		break;
		case 9:
		switch(productionIndex)
		{
			case 9: return 10; break;
			case 8: return 12; break;
			case 7: return 15; break;
			case 6: return 17; break;
		}
		break;
		case 12:
		switch(productionIndex)
		{
			case 13: return 13; break;
		}
		break;
		case 13:
		switch(productionIndex)
		{
			case 8: return 14; break;
			case 7: return 15; break;
			case 6: return 17; break;
		}
		break;
		case 15:
		switch(productionIndex)
		{
			case 7: return 16; break;
			case 6: return 17; break;
		}
		break;
		case 17:
		switch(productionIndex)
		{
			case 5: return 18; break;
		}
		break;
		case 22:
		switch(productionIndex)
		{
			case 4: return 23; break;
			case 3: return 37; break;
		}
		break;
		case 23:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 26:
		switch(productionIndex)
		{
			case 2: return 27; break;
			case 1: return 29; break;
		}
		break;
		case 29:
		switch(productionIndex)
		{
			case 1: return 30; break;
		}
		break;
		case 35:
		switch(productionIndex)
		{
			case 2: return 36; break;
			case 1: return 29; break;
		}
		break;
		case 39:
		switch(productionIndex)
		{
			case 4: return 40; break;
			case 3: return 37; break;
		}
		break;
		case 40:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 43:
		switch(productionIndex)
		{
			case 17: return 44; break;
			case 16: return 46; break;
			case 15: return 49; break;
			case 14: return 51; break;
		}
		break;
		case 46:
		switch(productionIndex)
		{
			case 13: return 47; break;
		}
		break;
		case 47:
		switch(productionIndex)
		{
			case 16: return 48; break;
			case 15: return 49; break;
			case 14: return 51; break;
		}
		break;
		case 49:
		switch(productionIndex)
		{
			case 15: return 50; break;
			case 14: return 51; break;
		}
		break;
		case 51:
		switch(productionIndex)
		{
			case 12: return 52; break;
		}
		break;
		case 56:
		switch(productionIndex)
		{
			case 17: return 57; break;
			case 16: return 46; break;
			case 15: return 49; break;
			case 14: return 51; break;
		}
		break;
		case 61:
		switch(productionIndex)
		{
			case 11: return 64; break;
			case 10: return 38; break;
		}
		break;
		case 62:
		switch(productionIndex)
		{
			case 4: return 63; break;
			case 3: return 37; break;
		}
		break;
		case 63:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 64:
		switch(productionIndex)
		{
			case 10: return 7; break;
		}
		break;
		case 65:
		switch(productionIndex)
		{
			case 4: return 66; break;
			case 3: return 37; break;
		}
		break;
		case 66:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 67:
		switch(productionIndex)
		{
			case 24: return 82; break;
		}
		break;
		case 68:
		switch(productionIndex)
		{
			case 19: return 75; break;
			case 18: return 60; break;
		}
		break;
		case 69:
		switch(productionIndex)
		{
			case 11: return 70; break;
			case 10: return 38; break;
		}
		break;
		case 70:
		switch(productionIndex)
		{
			case 10: return 7; break;
		}
		break;
		case 71:
		switch(productionIndex)
		{
			case 4: return 72; break;
			case 3: return 37; break;
		}
		break;
		case 72:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 73:
		switch(productionIndex)
		{
			case 4: return 74; break;
			case 3: return 37; break;
		}
		break;
		case 74:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 75:
		switch(productionIndex)
		{
			case 18: return 41; break;
		}
		break;
		case 76:
		switch(productionIndex)
		{
			case 11: return 79; break;
			case 10: return 38; break;
		}
		break;
		case 77:
		switch(productionIndex)
		{
			case 4: return 78; break;
			case 3: return 37; break;
		}
		break;
		case 78:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 79:
		switch(productionIndex)
		{
			case 10: return 7; break;
		}
		break;
		case 80:
		switch(productionIndex)
		{
			case 4: return 81; break;
			case 3: return 37; break;
		}
		break;
		case 81:
		switch(productionIndex)
		{
			case 3: return 24; break;
		}
		break;
		case 84:
		switch(productionIndex)
		{
			case 23: return 85; break;
			case 22: return 87; break;
			case 20: return 90; break;
		}
		break;
		case 87:
		switch(productionIndex)
		{
			case 21: return 88; break;
		}
		break;
		case 88:
		switch(productionIndex)
		{
			case 22: return 89; break;
			case 20: return 90; break;
		}
		break;
		case 91:
		switch(productionIndex)
		{
			case 20: return 92; break;
		}
		break;
		case 95:
		switch(productionIndex)
		{
			case 23: return 96; break;
			case 22: return 87; break;
			case 20: return 90; break;
		}
		break;
	}
	return 0;
}

Parser UCC_parse(AllProductions* allProductions, Production* (*creationFunction)(AllProductions*), Token* token)
{
	Action state0Actions[] = {
		createShift(T_helpers,2)
	};
	Action state1Actions[] = {
		createAcceptAction()
	};
	Action state2Actions[] = {
		createShift(T_tokens,3),
		createShift(T_identifier,83)
	};
	Action state3Actions[] = {
		createShift(T_productions,61),
		createShift(T_identifier,42)
	};
	Action state4Actions[] = {
		createShift(T_productions,5),
		createShift(T_identifier,42)
	};
	Action state5Actions[] = {
		createShift(T_reducer,39),
		createShift(T_identifier,8)
	};
	Action state6Actions[] = {
		createShift(T_reducer,22),
		createShift(T_identifier,8)
	};
	Action state7Actions[] = {
		createReduce1(T_reducer, 11, UCC_P_Productions_Productions_Production, 2),
		createReduce1(T_identifier, 11, UCC_P_Productions_Productions_Production, 2)
	};
	Action state8Actions[] = {
		createShift(T_attrib,9)
	};
	Action state9Actions[] = {
		createShift(T_identifier,20)
	};
	Action state10Actions[] = {
		createShift(T_semicolon,11)
	};
	Action state11Actions[] = {
		createReduce1(T_reducer, 10, UCC_P_Production_identifier_attrib_Expr_semicolon, 4),
		createReduce1(T_identifier, 10, UCC_P_Production_identifier_attrib_Expr_semicolon, 4)
	};
	Action state12Actions[] = {
		createReduce1(T_semicolon, 9, UCC_P_Expr_Expr, 1),
		createShift(T_or,21)
	};
	Action state13Actions[] = {
		createShift(T_identifier,20)
	};
	Action state14Actions[] = {
		createReduce1(T_semicolon, 9, UCC_P_Expr_Expr_Op_Expr, 3)
	};
	Action state15Actions[] = {
		createReduce1(T_semicolon, 8, UCC_P_Expr_Expr, 1),
		createReduce1(T_or, 8, UCC_P_Expr_Expr, 1),
		createShift(T_identifier,20)
	};
	Action state16Actions[] = {
		createReduce1(T_semicolon, 8, UCC_P_Expr_Expr_Expr, 2),
		createReduce1(T_or, 8, UCC_P_Expr_Expr_Expr, 2)
	};
	Action state17Actions[] = {
		createReduce1(T_semicolon, 7, UCC_P_Expr_Expr, 1),
		createShift(T_question,19),
		createReduce1(T_or, 7, UCC_P_Expr_Expr, 1),
		createReduce1(T_identifier, 7, UCC_P_Expr_Expr, 1)
	};
	Action state18Actions[] = {
		createReduce1(T_semicolon, 7, UCC_P_Expr_Expr_Op, 2),
		createReduce1(T_or, 7, UCC_P_Expr_Expr_Op, 2),
		createReduce1(T_identifier, 7, UCC_P_Expr_Expr_Op, 2)
	};
	Action state19Actions[] = {
		createReduce1(T_semicolon, 5, UCC_P_Op_question, 1),
		createReduce1(T_or, 5, UCC_P_Op_question, 1),
		createReduce1(T_identifier, 5, UCC_P_Op_question, 1)
	};
	Action state20Actions[] = {
		createReduce1(T_semicolon, 6, UCC_P_Expr_identifier, 1),
		createReduce1(T_question, 6, UCC_P_Expr_identifier, 1),
		createReduce1(T_or, 6, UCC_P_Expr_identifier, 1),
		createReduce1(T_identifier, 6, UCC_P_Expr_identifier, 1)
	};
	Action state21Actions[] = {
		createReduce1(T_o_parentheses, 13, UCC_P_Op_or, 1),
		createReduce1(T_identifier, 13, UCC_P_Op_or, 1)
	};
	Action state22Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state23Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_tokens_Tokens_productions_Productions_reducer_Reducers, 7)
	};
	Action state24Actions[] = {
		createReduce1(T_identifier, 4, UCC_P_Reducers_Reducers_Reducer, 2),
		createReduce1(T_o_brackets, 4, UCC_P_Reducers_Reducers_Reducer, 2),
		createReduce1(END_OF_INPUT, 4, UCC_P_Reducers_Reducers_Reducer, 2)
	};
	Action state25Actions[] = {
		createShift(T_reduce,26)
	};
	Action state26Actions[] = {
		createShift(T_identifier,31)
	};
	Action state27Actions[] = {
		createShift(T_semicolon,28)
	};
	Action state28Actions[] = {
		createReduce1(T_identifier, 3, UCC_P_Reducer_identifier_reduce_Expr_semicolon, 4),
		createReduce1(T_o_brackets, 3, UCC_P_Reducer_identifier_reduce_Expr_semicolon, 4),
		createReduce1(END_OF_INPUT, 3, UCC_P_Reducer_identifier_reduce_Expr_semicolon, 4)
	};
	Action state29Actions[] = {
		createReduce1(T_semicolon, 2, UCC_P_Expr_Expr, 1),
		createShift(T_identifier,31),
		createReduce1(T_o_brackets, 2, UCC_P_Expr_Expr, 1),
		createReduce1(END_OF_INPUT, 2, UCC_P_Expr_Expr, 1)
	};
	Action state30Actions[] = {
		createReduce1(T_semicolon, 2, UCC_P_Expr_Expr_Expr, 2),
		createReduce1(T_identifier, 2, UCC_P_Expr_Expr_Expr, 2),
		createReduce1(T_o_brackets, 2, UCC_P_Expr_Expr_Expr, 2),
		createReduce1(END_OF_INPUT, 2, UCC_P_Expr_Expr_Expr, 2)
	};
	Action state31Actions[] = {
		createReduce1(T_semicolon, 1, UCC_P_Expr_identifier, 1),
		createReduce1(T_identifier, 1, UCC_P_Expr_identifier, 1),
		createReduce1(T_o_brackets, 1, UCC_P_Expr_identifier, 1),
		createReduce1(END_OF_INPUT, 1, UCC_P_Expr_identifier, 1)
	};
	Action state32Actions[] = {
		createShift(T_identifier,33)
	};
	Action state33Actions[] = {
		createShift(T_c_brackets,34)
	};
	Action state34Actions[] = {
		createShift(T_reduce,35)
	};
	Action state35Actions[] = {
		createShift(T_identifier,31)
	};
	Action state36Actions[] = {
		createReduce1(T_identifier, 3, UCC_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr, 5),
		createReduce1(T_o_brackets, 3, UCC_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr, 5),
		createReduce1(END_OF_INPUT, 3, UCC_P_Reducer_o_brackets_identifier_c_brackets_reduce_Expr, 5)
	};
	Action state37Actions[] = {
		createReduce1(T_identifier, 4, UCC_P_Reducers_Reducer, 1),
		createReduce1(T_o_brackets, 4, UCC_P_Reducers_Reducer, 1),
		createReduce1(END_OF_INPUT, 4, UCC_P_Reducers_Reducer, 1)
	};
	Action state38Actions[] = {
		createReduce1(T_reducer, 11, UCC_P_Productions_Production, 1),
		createReduce1(T_identifier, 11, UCC_P_Productions_Production, 1)
	};
	Action state39Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state40Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_tokens_Tokens_productions_reducer_Reducers, 6)
	};
	Action state41Actions[] = {
		createReduce1(T_productions, 19, UCC_P_Tokens_Tokens_Token, 2),
		createReduce1(T_identifier, 19, UCC_P_Tokens_Tokens_Token, 2)
	};
	Action state42Actions[] = {
		createShift(T_attrib,43)
	};
	Action state43Actions[] = {
		createShift(T_o_parentheses,56),
		createShift(T_identifier,59)
	};
	Action state44Actions[] = {
		createShift(T_semicolon,45)
	};
	Action state45Actions[] = {
		createReduce1(T_productions, 18, UCC_P_Token_identifier_attrib_Expr_semicolon, 4),
		createReduce1(T_identifier, 18, UCC_P_Token_identifier_attrib_Expr_semicolon, 4)
	};
	Action state46Actions[] = {
		createReduce1(T_semicolon, 17, UCC_P_Expr_Expr, 1),
		createShift(T_or,21),
		createReduce1(T_c_parentheses, 17, UCC_P_Expr_Expr, 1)
	};
	Action state47Actions[] = {
		createShift(T_o_parentheses,56),
		createShift(T_identifier,59)
	};
	Action state48Actions[] = {
		createReduce1(T_semicolon, 17, UCC_P_Expr_Expr_Op_Expr, 3),
		createReduce1(T_c_parentheses, 17, UCC_P_Expr_Expr_Op_Expr, 3)
	};
	Action state49Actions[] = {
		createReduce1(T_semicolon, 16, UCC_P_Expr_Expr, 1),
		createShift(T_o_parentheses,56),
		createReduce1(T_or, 16, UCC_P_Expr_Expr, 1),
		createReduce1(T_c_parentheses, 16, UCC_P_Expr_Expr, 1),
		createShift(T_identifier,59)
	};
	Action state50Actions[] = {
		createReduce1(T_semicolon, 16, UCC_P_Expr_Expr_Expr, 2),
		createReduce1(T_or, 16, UCC_P_Expr_Expr_Expr, 2),
		createReduce1(T_c_parentheses, 16, UCC_P_Expr_Expr_Expr, 2)
	};
	Action state51Actions[] = {
		createReduce1(T_semicolon, 15, UCC_P_Expr_Expr, 1),
		createReduce1(T_o_parentheses, 15, UCC_P_Expr_Expr, 1),
		createShift(T_question,55),
		createReduce1(T_or, 15, UCC_P_Expr_Expr, 1),
		createShift(T_mult,54),
		createReduce1(T_c_parentheses, 15, UCC_P_Expr_Expr, 1),
		createShift(T_sum,53),
		createReduce1(T_identifier, 15, UCC_P_Expr_Expr, 1)
	};
	Action state52Actions[] = {
		createReduce1(T_semicolon, 15, UCC_P_Expr_Expr_Op, 2),
		createReduce1(T_o_parentheses, 15, UCC_P_Expr_Expr_Op, 2),
		createReduce1(T_or, 15, UCC_P_Expr_Expr_Op, 2),
		createReduce1(T_c_parentheses, 15, UCC_P_Expr_Expr_Op, 2),
		createReduce1(T_identifier, 15, UCC_P_Expr_Expr_Op, 2)
	};
	Action state53Actions[] = {
		createReduce1(T_semicolon, 12, UCC_P_Op_sum, 1),
		createReduce1(T_o_parentheses, 12, UCC_P_Op_sum, 1),
		createReduce1(T_or, 12, UCC_P_Op_sum, 1),
		createReduce1(T_c_parentheses, 12, UCC_P_Op_sum, 1),
		createReduce1(T_identifier, 12, UCC_P_Op_sum, 1)
	};
	Action state54Actions[] = {
		createReduce1(T_semicolon, 12, UCC_P_Op_mult, 1),
		createReduce1(T_o_parentheses, 12, UCC_P_Op_mult, 1),
		createReduce1(T_or, 12, UCC_P_Op_mult, 1),
		createReduce1(T_c_parentheses, 12, UCC_P_Op_mult, 1),
		createReduce1(T_identifier, 12, UCC_P_Op_mult, 1)
	};
	Action state55Actions[] = {
		createReduce1(T_semicolon, 12, UCC_P_Op_question, 1),
		createReduce1(T_o_parentheses, 12, UCC_P_Op_question, 1),
		createReduce1(T_or, 12, UCC_P_Op_question, 1),
		createReduce1(T_c_parentheses, 12, UCC_P_Op_question, 1),
		createReduce1(T_identifier, 12, UCC_P_Op_question, 1)
	};
	Action state56Actions[] = {
		createShift(T_o_parentheses,56),
		createShift(T_identifier,59)
	};
	Action state57Actions[] = {
		createShift(T_c_parentheses,58)
	};
	Action state58Actions[] = {
		createReduce1(T_semicolon, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_o_parentheses, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_question, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_or, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_mult, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_c_parentheses, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_sum, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_identifier, 14, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3)
	};
	Action state59Actions[] = {
		createReduce1(T_semicolon, 14, UCC_P_Expr_identifier, 1),
		createReduce1(T_o_parentheses, 14, UCC_P_Expr_identifier, 1),
		createReduce1(T_question, 14, UCC_P_Expr_identifier, 1),
		createReduce1(T_or, 14, UCC_P_Expr_identifier, 1),
		createReduce1(T_mult, 14, UCC_P_Expr_identifier, 1),
		createReduce1(T_c_parentheses, 14, UCC_P_Expr_identifier, 1),
		createReduce1(T_sum, 14, UCC_P_Expr_identifier, 1),
		createReduce1(T_identifier, 14, UCC_P_Expr_identifier, 1)
	};
	Action state60Actions[] = {
		createReduce1(T_productions, 19, UCC_P_Tokens_Token, 1),
		createReduce1(T_identifier, 19, UCC_P_Tokens_Token, 1)
	};
	Action state61Actions[] = {
		createShift(T_reducer,62),
		createShift(T_identifier,8)
	};
	Action state62Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state63Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_tokens_productions_reducer_Reducers, 5)
	};
	Action state64Actions[] = {
		createShift(T_reducer,65),
		createShift(T_identifier,8)
	};
	Action state65Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state66Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_tokens_productions_Productions_reducer_Reducers, 6)
	};
	Action state67Actions[] = {
		createShift(T_tokens,68),
		createShift(T_identifier,83)
	};
	Action state68Actions[] = {
		createShift(T_productions,69),
		createShift(T_identifier,42)
	};
	Action state69Actions[] = {
		createShift(T_reducer,73),
		createShift(T_identifier,8)
	};
	Action state70Actions[] = {
		createShift(T_reducer,71),
		createShift(T_identifier,8)
	};
	Action state71Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state72Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_Helpers_tokens_productions_Productions_reducer_Reducers, 7)
	};
	Action state73Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state74Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_Helpers_tokens_productions_reducer_Reducers, 6)
	};
	Action state75Actions[] = {
		createShift(T_productions,76),
		createShift(T_identifier,42)
	};
	Action state76Actions[] = {
		createShift(T_reducer,77),
		createShift(T_identifier,8)
	};
	Action state77Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state78Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_reducer_Reducers, 7)
	};
	Action state79Actions[] = {
		createShift(T_reducer,80),
		createShift(T_identifier,8)
	};
	Action state80Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32)
	};
	Action state81Actions[] = {
		createShift(T_identifier,25),
		createShift(T_o_brackets,32),
		createReduce1(END_OF_INPUT, 0, UCC_P_Total_helpers_Helpers_tokens_Tokens_productions_Productions_reducer_Reducers, 8)
	};
	Action state82Actions[] = {
		createReduce1(T_tokens, 25, UCC_P_Helpers_Helpers_Helper, 2),
		createReduce1(T_identifier, 25, UCC_P_Helpers_Helpers_Helper, 2)
	};
	Action state83Actions[] = {
		createShift(T_attrib,84)
	};
	Action state84Actions[] = {
		createShift(T_o_parentheses,95),
		createShift(T_charLiteral,93),
		createShift(T_decimal,94)
	};
	Action state85Actions[] = {
		createShift(T_semicolon,86)
	};
	Action state86Actions[] = {
		createReduce1(T_tokens, 24, UCC_P_Helper_identifier_attrib_Expr_semicolon, 4),
		createReduce1(T_identifier, 24, UCC_P_Helper_identifier_attrib_Expr_semicolon, 4)
	};
	Action state87Actions[] = {
		createReduce1(T_semicolon, 23, UCC_P_Expr_Expr, 1),
		createReduce1(T_c_parentheses, 23, UCC_P_Expr_Expr, 1),
		createShift(T_sub,99),
		createShift(T_sum,98)
	};
	Action state88Actions[] = {
		createShift(T_o_parentheses,95),
		createShift(T_charLiteral,93),
		createShift(T_decimal,94)
	};
	Action state89Actions[] = {
		createReduce1(T_semicolon, 23, UCC_P_Expr_Expr_Op_Expr, 3),
		createReduce1(T_c_parentheses, 23, UCC_P_Expr_Expr_Op_Expr, 3)
	};
	Action state90Actions[] = {
		createReduce1(T_semicolon, 22, UCC_P_Expr_Literal, 1),
		createShift(T_to,91),
		createReduce1(T_c_parentheses, 22, UCC_P_Expr_Literal, 1),
		createReduce1(T_sub, 22, UCC_P_Expr_Literal, 1),
		createReduce1(T_sum, 22, UCC_P_Expr_Literal, 1)
	};
	Action state91Actions[] = {
		createShift(T_charLiteral,93),
		createShift(T_decimal,94)
	};
	Action state92Actions[] = {
		createReduce1(T_semicolon, 22, UCC_P_Expr_Literal_to_Literal, 3),
		createReduce1(T_c_parentheses, 22, UCC_P_Expr_Literal_to_Literal, 3),
		createReduce1(T_sub, 22, UCC_P_Expr_Literal_to_Literal, 3),
		createReduce1(T_sum, 22, UCC_P_Expr_Literal_to_Literal, 3)
	};
	Action state93Actions[] = {
		createReduce1(T_semicolon, 20, UCC_P_Literal_charLiteral, 1),
		createReduce1(T_to, 20, UCC_P_Literal_charLiteral, 1),
		createReduce1(T_c_parentheses, 20, UCC_P_Literal_charLiteral, 1),
		createReduce1(T_sub, 20, UCC_P_Literal_charLiteral, 1),
		createReduce1(T_sum, 20, UCC_P_Literal_charLiteral, 1)
	};
	Action state94Actions[] = {
		createReduce1(T_semicolon, 20, UCC_P_Literal_decimal, 1),
		createReduce1(T_to, 20, UCC_P_Literal_decimal, 1),
		createReduce1(T_c_parentheses, 20, UCC_P_Literal_decimal, 1),
		createReduce1(T_sub, 20, UCC_P_Literal_decimal, 1),
		createReduce1(T_sum, 20, UCC_P_Literal_decimal, 1)
	};
	Action state95Actions[] = {
		createShift(T_o_parentheses,95),
		createShift(T_charLiteral,93),
		createShift(T_decimal,94)
	};
	Action state96Actions[] = {
		createShift(T_c_parentheses,97)
	};
	Action state97Actions[] = {
		createReduce1(T_semicolon, 22, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_c_parentheses, 22, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_sub, 22, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3),
		createReduce1(T_sum, 22, UCC_P_Expr_o_parentheses_Expr_c_parentheses, 3)
	};
	Action state98Actions[] = {
		createReduce1(T_o_parentheses, 21, UCC_P_Op_sum, 1),
		createReduce1(T_charLiteral, 21, UCC_P_Op_sum, 1),
		createReduce1(T_decimal, 21, UCC_P_Op_sum, 1)
	};
	Action state99Actions[] = {
		createReduce1(T_o_parentheses, 21, UCC_P_Op_sub, 1),
		createReduce1(T_charLiteral, 21, UCC_P_Op_sub, 1),
		createReduce1(T_decimal, 21, UCC_P_Op_sub, 1)
	};
	Action state100Actions[] = {
		createReduce1(T_tokens, 25, UCC_P_Helpers_Helper, 1),
		createReduce1(T_identifier, 25, UCC_P_Helpers_Helper, 1)
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
		createState(state100Actions, sizeof(state100Actions)/sizeof(Action))
	};
	return parse(allProductions, creationFunction, states, goToTable, token);
}
