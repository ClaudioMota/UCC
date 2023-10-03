#include "parsers/lexer.h"

static int func_identifier(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 65: *estado = 1; break;
				case 66: *estado = 1; break;
				case 67: *estado = 1; break;
				case 68: *estado = 1; break;
				case 69: *estado = 1; break;
				case 70: *estado = 1; break;
				case 71: *estado = 1; break;
				case 72: *estado = 1; break;
				case 73: *estado = 1; break;
				case 74: *estado = 1; break;
				case 75: *estado = 1; break;
				case 76: *estado = 1; break;
				case 77: *estado = 1; break;
				case 78: *estado = 1; break;
				case 79: *estado = 1; break;
				case 80: *estado = 1; break;
				case 81: *estado = 1; break;
				case 82: *estado = 1; break;
				case 83: *estado = 1; break;
				case 84: *estado = 1; break;
				case 85: *estado = 1; break;
				case 86: *estado = 1; break;
				case 87: *estado = 1; break;
				case 88: *estado = 1; break;
				case 89: *estado = 1; break;
				case 90: *estado = 1; break;
				case 95: *estado = 1; break;
				case 97: *estado = 1; break;
				case 98: *estado = 1; break;
				case 99: *estado = 1; break;
				case 100: *estado = 1; break;
				case 101: *estado = 1; break;
				case 102: *estado = 1; break;
				case 103: *estado = 1; break;
				case 104: *estado = 1; break;
				case 105: *estado = 1; break;
				case 106: *estado = 1; break;
				case 107: *estado = 1; break;
				case 108: *estado = 1; break;
				case 109: *estado = 1; break;
				case 110: *estado = 1; break;
				case 111: *estado = 1; break;
				case 112: *estado = 1; break;
				case 113: *estado = 1; break;
				case 114: *estado = 1; break;
				case 115: *estado = 1; break;
				case 116: *estado = 1; break;
				case 117: *estado = 1; break;
				case 118: *estado = 1; break;
				case 119: *estado = 1; break;
				case 120: *estado = 1; break;
				case 121: *estado = 1; break;
				case 122: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 48: *estado = 1; break;
				case 49: *estado = 1; break;
				case 50: *estado = 1; break;
				case 51: *estado = 1; break;
				case 52: *estado = 1; break;
				case 53: *estado = 1; break;
				case 54: *estado = 1; break;
				case 55: *estado = 1; break;
				case 56: *estado = 1; break;
				case 57: *estado = 1; break;
				case 65: *estado = 1; break;
				case 66: *estado = 1; break;
				case 67: *estado = 1; break;
				case 68: *estado = 1; break;
				case 69: *estado = 1; break;
				case 70: *estado = 1; break;
				case 71: *estado = 1; break;
				case 72: *estado = 1; break;
				case 73: *estado = 1; break;
				case 74: *estado = 1; break;
				case 75: *estado = 1; break;
				case 76: *estado = 1; break;
				case 77: *estado = 1; break;
				case 78: *estado = 1; break;
				case 79: *estado = 1; break;
				case 80: *estado = 1; break;
				case 81: *estado = 1; break;
				case 82: *estado = 1; break;
				case 83: *estado = 1; break;
				case 84: *estado = 1; break;
				case 85: *estado = 1; break;
				case 86: *estado = 1; break;
				case 87: *estado = 1; break;
				case 88: *estado = 1; break;
				case 89: *estado = 1; break;
				case 90: *estado = 1; break;
				case 95: *estado = 1; break;
				case 97: *estado = 1; break;
				case 98: *estado = 1; break;
				case 99: *estado = 1; break;
				case 100: *estado = 1; break;
				case 101: *estado = 1; break;
				case 102: *estado = 1; break;
				case 103: *estado = 1; break;
				case 104: *estado = 1; break;
				case 105: *estado = 1; break;
				case 106: *estado = 1; break;
				case 107: *estado = 1; break;
				case 108: *estado = 1; break;
				case 109: *estado = 1; break;
				case 110: *estado = 1; break;
				case 111: *estado = 1; break;
				case 112: *estado = 1; break;
				case 113: *estado = 1; break;
				case 114: *estado = 1; break;
				case 115: *estado = 1; break;
				case 116: *estado = 1; break;
				case 117: *estado = 1; break;
				case 118: *estado = 1; break;
				case 119: *estado = 1; break;
				case 120: *estado = 1; break;
				case 121: *estado = 1; break;
				case 122: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_semicolon(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 59: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_to(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 46: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 46: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 2) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_comma(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 44: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_blank(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 9: *estado = 1; break;
				case 13: *estado = 1; break;
				case 32: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 9: *estado = 1; break;
				case 13: *estado = 1; break;
				case 32: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_breakLine(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 10: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_comment(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 47: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 47: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				case 1: *estado = 2; break;
				case 2: *estado = 2; break;
				case 3: *estado = 2; break;
				case 4: *estado = 2; break;
				case 5: *estado = 2; break;
				case 6: *estado = 2; break;
				case 7: *estado = 2; break;
				case 8: *estado = 2; break;
				case 9: *estado = 2; break;
				case 11: *estado = 2; break;
				case 12: *estado = 2; break;
				case 13: *estado = 2; break;
				case 14: *estado = 2; break;
				case 15: *estado = 2; break;
				case 16: *estado = 2; break;
				case 17: *estado = 2; break;
				case 18: *estado = 2; break;
				case 19: *estado = 2; break;
				case 20: *estado = 2; break;
				case 21: *estado = 2; break;
				case 22: *estado = 2; break;
				case 23: *estado = 2; break;
				case 24: *estado = 2; break;
				case 25: *estado = 2; break;
				case 26: *estado = 2; break;
				case 27: *estado = 2; break;
				case 28: *estado = 2; break;
				case 29: *estado = 2; break;
				case 30: *estado = 2; break;
				case 31: *estado = 2; break;
				case 32: *estado = 2; break;
				case 33: *estado = 2; break;
				case 34: *estado = 2; break;
				case 35: *estado = 2; break;
				case 36: *estado = 2; break;
				case 37: *estado = 2; break;
				case 38: *estado = 2; break;
				case 39: *estado = 2; break;
				case 40: *estado = 2; break;
				case 41: *estado = 2; break;
				case 42: *estado = 2; break;
				case 43: *estado = 2; break;
				case 44: *estado = 2; break;
				case 45: *estado = 2; break;
				case 46: *estado = 2; break;
				case 47: *estado = 2; break;
				case 48: *estado = 2; break;
				case 49: *estado = 2; break;
				case 50: *estado = 2; break;
				case 51: *estado = 2; break;
				case 52: *estado = 2; break;
				case 53: *estado = 2; break;
				case 54: *estado = 2; break;
				case 55: *estado = 2; break;
				case 56: *estado = 2; break;
				case 57: *estado = 2; break;
				case 58: *estado = 2; break;
				case 59: *estado = 2; break;
				case 60: *estado = 2; break;
				case 61: *estado = 2; break;
				case 62: *estado = 2; break;
				case 63: *estado = 2; break;
				case 64: *estado = 2; break;
				case 65: *estado = 2; break;
				case 66: *estado = 2; break;
				case 67: *estado = 2; break;
				case 68: *estado = 2; break;
				case 69: *estado = 2; break;
				case 70: *estado = 2; break;
				case 71: *estado = 2; break;
				case 72: *estado = 2; break;
				case 73: *estado = 2; break;
				case 74: *estado = 2; break;
				case 75: *estado = 2; break;
				case 76: *estado = 2; break;
				case 77: *estado = 2; break;
				case 78: *estado = 2; break;
				case 79: *estado = 2; break;
				case 80: *estado = 2; break;
				case 81: *estado = 2; break;
				case 82: *estado = 2; break;
				case 83: *estado = 2; break;
				case 84: *estado = 2; break;
				case 85: *estado = 2; break;
				case 86: *estado = 2; break;
				case 87: *estado = 2; break;
				case 88: *estado = 2; break;
				case 89: *estado = 2; break;
				case 90: *estado = 2; break;
				case 91: *estado = 2; break;
				case 92: *estado = 2; break;
				case 93: *estado = 2; break;
				case 94: *estado = 2; break;
				case 95: *estado = 2; break;
				case 96: *estado = 2; break;
				case 97: *estado = 2; break;
				case 98: *estado = 2; break;
				case 99: *estado = 2; break;
				case 100: *estado = 2; break;
				case 101: *estado = 2; break;
				case 102: *estado = 2; break;
				case 103: *estado = 2; break;
				case 104: *estado = 2; break;
				case 105: *estado = 2; break;
				case 106: *estado = 2; break;
				case 107: *estado = 2; break;
				case 108: *estado = 2; break;
				case 109: *estado = 2; break;
				case 110: *estado = 2; break;
				case 111: *estado = 2; break;
				case 112: *estado = 2; break;
				case 113: *estado = 2; break;
				case 114: *estado = 2; break;
				case 115: *estado = 2; break;
				case 116: *estado = 2; break;
				case 117: *estado = 2; break;
				case 118: *estado = 2; break;
				case 119: *estado = 2; break;
				case 120: *estado = 2; break;
				case 121: *estado = 2; break;
				case 122: *estado = 2; break;
				case 123: *estado = 2; break;
				case 124: *estado = 2; break;
				case 125: *estado = 2; break;
				case 126: *estado = 2; break;
				case 127: *estado = 2; break;
				case 128: *estado = 2; break;
				case 129: *estado = 2; break;
				case 130: *estado = 2; break;
				case 131: *estado = 2; break;
				case 132: *estado = 2; break;
				case 133: *estado = 2; break;
				case 134: *estado = 2; break;
				case 135: *estado = 2; break;
				case 136: *estado = 2; break;
				case 137: *estado = 2; break;
				case 138: *estado = 2; break;
				case 139: *estado = 2; break;
				case 140: *estado = 2; break;
				case 141: *estado = 2; break;
				case 142: *estado = 2; break;
				case 143: *estado = 2; break;
				case 144: *estado = 2; break;
				case 145: *estado = 2; break;
				case 146: *estado = 2; break;
				case 147: *estado = 2; break;
				case 148: *estado = 2; break;
				case 149: *estado = 2; break;
				case 150: *estado = 2; break;
				case 151: *estado = 2; break;
				case 152: *estado = 2; break;
				case 153: *estado = 2; break;
				case 154: *estado = 2; break;
				case 155: *estado = 2; break;
				case 156: *estado = 2; break;
				case 157: *estado = 2; break;
				case 158: *estado = 2; break;
				case 159: *estado = 2; break;
				case 160: *estado = 2; break;
				case 161: *estado = 2; break;
				case 162: *estado = 2; break;
				case 163: *estado = 2; break;
				case 164: *estado = 2; break;
				case 165: *estado = 2; break;
				case 166: *estado = 2; break;
				case 167: *estado = 2; break;
				case 168: *estado = 2; break;
				case 169: *estado = 2; break;
				case 170: *estado = 2; break;
				case 171: *estado = 2; break;
				case 172: *estado = 2; break;
				case 173: *estado = 2; break;
				case 174: *estado = 2; break;
				case 175: *estado = 2; break;
				case 176: *estado = 2; break;
				case 177: *estado = 2; break;
				case 178: *estado = 2; break;
				case 179: *estado = 2; break;
				case 180: *estado = 2; break;
				case 181: *estado = 2; break;
				case 182: *estado = 2; break;
				case 183: *estado = 2; break;
				case 184: *estado = 2; break;
				case 185: *estado = 2; break;
				case 186: *estado = 2; break;
				case 187: *estado = 2; break;
				case 188: *estado = 2; break;
				case 189: *estado = 2; break;
				case 190: *estado = 2; break;
				case 191: *estado = 2; break;
				case 192: *estado = 2; break;
				case 193: *estado = 2; break;
				case 194: *estado = 2; break;
				case 195: *estado = 2; break;
				case 196: *estado = 2; break;
				case 197: *estado = 2; break;
				case 198: *estado = 2; break;
				case 199: *estado = 2; break;
				case 200: *estado = 2; break;
				case 201: *estado = 2; break;
				case 202: *estado = 2; break;
				case 203: *estado = 2; break;
				case 204: *estado = 2; break;
				case 205: *estado = 2; break;
				case 206: *estado = 2; break;
				case 207: *estado = 2; break;
				case 208: *estado = 2; break;
				case 209: *estado = 2; break;
				case 210: *estado = 2; break;
				case 211: *estado = 2; break;
				case 212: *estado = 2; break;
				case 213: *estado = 2; break;
				case 214: *estado = 2; break;
				case 215: *estado = 2; break;
				case 216: *estado = 2; break;
				case 217: *estado = 2; break;
				case 218: *estado = 2; break;
				case 219: *estado = 2; break;
				case 220: *estado = 2; break;
				case 221: *estado = 2; break;
				case 222: *estado = 2; break;
				case 223: *estado = 2; break;
				case 224: *estado = 2; break;
				case 225: *estado = 2; break;
				case 226: *estado = 2; break;
				case 227: *estado = 2; break;
				case 228: *estado = 2; break;
				case 229: *estado = 2; break;
				case 230: *estado = 2; break;
				case 231: *estado = 2; break;
				case 232: *estado = 2; break;
				case 233: *estado = 2; break;
				case 234: *estado = 2; break;
				case 235: *estado = 2; break;
				case 236: *estado = 2; break;
				case 237: *estado = 2; break;
				case 238: *estado = 2; break;
				case 239: *estado = 2; break;
				case 240: *estado = 2; break;
				case 241: *estado = 2; break;
				case 242: *estado = 2; break;
				case 243: *estado = 2; break;
				case 244: *estado = 2; break;
				case 245: *estado = 2; break;
				case 246: *estado = 2; break;
				case 247: *estado = 2; break;
				case 248: *estado = 2; break;
				case 249: *estado = 2; break;
				case 250: *estado = 2; break;
				case 251: *estado = 2; break;
				case 252: *estado = 2; break;
				case 253: *estado = 2; break;
				case 254: *estado = 2; break;
				case 255: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 2) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_helpers(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 72: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 101: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				case 108: *estado = 3; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 3:
			switch(entrada)
			{
				case 112: *estado = 4; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 4:
			switch(entrada)
			{
				case 101: *estado = 5; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 5:
			switch(entrada)
			{
				case 114: *estado = 6; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 6:
			switch(entrada)
			{
				case 115: *estado = 7; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 7:
			switch(entrada)
			{
				case 58: *estado = 8; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 8:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 8) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_tokens(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 84: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 111: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				case 107: *estado = 3; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 3:
			switch(entrada)
			{
				case 101: *estado = 4; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 4:
			switch(entrada)
			{
				case 110: *estado = 5; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 5:
			switch(entrada)
			{
				case 115: *estado = 6; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 6:
			switch(entrada)
			{
				case 58: *estado = 7; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 7:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 7) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_productions(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 80: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 114: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				case 111: *estado = 3; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 3:
			switch(entrada)
			{
				case 100: *estado = 4; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 4:
			switch(entrada)
			{
				case 117: *estado = 5; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 5:
			switch(entrada)
			{
				case 99: *estado = 6; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 6:
			switch(entrada)
			{
				case 116: *estado = 7; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 7:
			switch(entrada)
			{
				case 105: *estado = 8; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 8:
			switch(entrada)
			{
				case 111: *estado = 9; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 9:
			switch(entrada)
			{
				case 110: *estado = 10; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 10:
			switch(entrada)
			{
				case 115: *estado = 11; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 11:
			switch(entrada)
			{
				case 58: *estado = 12; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 12:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 12) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_reducer(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 82: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 101: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				case 100: *estado = 3; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 3:
			switch(entrada)
			{
				case 117: *estado = 4; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 4:
			switch(entrada)
			{
				case 99: *estado = 5; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 5:
			switch(entrada)
			{
				case 101: *estado = 6; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 6:
			switch(entrada)
			{
				case 114: *estado = 7; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 7:
			switch(entrada)
			{
				case 58: *estado = 8; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 8:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 8) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_attrib(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 61: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_sum(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 43: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_sub(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 45: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_mult(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 42: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_or(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 124: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_reduce(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 60: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 45: *estado = 2; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 2) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_question(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 63: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_o_parentheses(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 40: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_c_parentheses(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 41: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_o_brackets(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 91: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_c_brackets(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 93: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_charLiteral(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 39: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 1: *estado = 1; break;
				case 2: *estado = 1; break;
				case 3: *estado = 1; break;
				case 4: *estado = 1; break;
				case 5: *estado = 1; break;
				case 6: *estado = 1; break;
				case 7: *estado = 1; break;
				case 8: *estado = 1; break;
				case 9: *estado = 1; break;
				case 10: *estado = 1; break;
				case 11: *estado = 1; break;
				case 12: *estado = 1; break;
				case 13: *estado = 1; break;
				case 14: *estado = 1; break;
				case 15: *estado = 1; break;
				case 16: *estado = 1; break;
				case 17: *estado = 1; break;
				case 18: *estado = 1; break;
				case 19: *estado = 1; break;
				case 20: *estado = 1; break;
				case 21: *estado = 1; break;
				case 22: *estado = 1; break;
				case 23: *estado = 1; break;
				case 24: *estado = 1; break;
				case 25: *estado = 1; break;
				case 26: *estado = 1; break;
				case 27: *estado = 1; break;
				case 28: *estado = 1; break;
				case 29: *estado = 1; break;
				case 30: *estado = 1; break;
				case 31: *estado = 1; break;
				case 32: *estado = 1; break;
				case 33: *estado = 1; break;
				case 34: *estado = 1; break;
				case 35: *estado = 1; break;
				case 36: *estado = 1; break;
				case 37: *estado = 1; break;
				case 38: *estado = 1; break;
				case 39: *estado = 2; break;
				case 40: *estado = 1; break;
				case 41: *estado = 1; break;
				case 42: *estado = 1; break;
				case 43: *estado = 1; break;
				case 44: *estado = 1; break;
				case 45: *estado = 1; break;
				case 46: *estado = 1; break;
				case 47: *estado = 1; break;
				case 48: *estado = 1; break;
				case 49: *estado = 1; break;
				case 50: *estado = 1; break;
				case 51: *estado = 1; break;
				case 52: *estado = 1; break;
				case 53: *estado = 1; break;
				case 54: *estado = 1; break;
				case 55: *estado = 1; break;
				case 56: *estado = 1; break;
				case 57: *estado = 1; break;
				case 58: *estado = 1; break;
				case 59: *estado = 1; break;
				case 60: *estado = 1; break;
				case 61: *estado = 1; break;
				case 62: *estado = 1; break;
				case 63: *estado = 1; break;
				case 64: *estado = 1; break;
				case 65: *estado = 1; break;
				case 66: *estado = 1; break;
				case 67: *estado = 1; break;
				case 68: *estado = 1; break;
				case 69: *estado = 1; break;
				case 70: *estado = 1; break;
				case 71: *estado = 1; break;
				case 72: *estado = 1; break;
				case 73: *estado = 1; break;
				case 74: *estado = 1; break;
				case 75: *estado = 1; break;
				case 76: *estado = 1; break;
				case 77: *estado = 1; break;
				case 78: *estado = 1; break;
				case 79: *estado = 1; break;
				case 80: *estado = 1; break;
				case 81: *estado = 1; break;
				case 82: *estado = 1; break;
				case 83: *estado = 1; break;
				case 84: *estado = 1; break;
				case 85: *estado = 1; break;
				case 86: *estado = 1; break;
				case 87: *estado = 1; break;
				case 88: *estado = 1; break;
				case 89: *estado = 1; break;
				case 90: *estado = 1; break;
				case 91: *estado = 1; break;
				case 92: *estado = 3; break;
				case 93: *estado = 1; break;
				case 94: *estado = 1; break;
				case 95: *estado = 1; break;
				case 96: *estado = 1; break;
				case 97: *estado = 1; break;
				case 98: *estado = 1; break;
				case 99: *estado = 1; break;
				case 100: *estado = 1; break;
				case 101: *estado = 1; break;
				case 102: *estado = 1; break;
				case 103: *estado = 1; break;
				case 104: *estado = 1; break;
				case 105: *estado = 1; break;
				case 106: *estado = 1; break;
				case 107: *estado = 1; break;
				case 108: *estado = 1; break;
				case 109: *estado = 1; break;
				case 110: *estado = 1; break;
				case 111: *estado = 1; break;
				case 112: *estado = 1; break;
				case 113: *estado = 1; break;
				case 114: *estado = 1; break;
				case 115: *estado = 1; break;
				case 116: *estado = 1; break;
				case 117: *estado = 1; break;
				case 118: *estado = 1; break;
				case 119: *estado = 1; break;
				case 120: *estado = 1; break;
				case 121: *estado = 1; break;
				case 122: *estado = 1; break;
				case 123: *estado = 1; break;
				case 124: *estado = 1; break;
				case 125: *estado = 1; break;
				case 126: *estado = 1; break;
				case 127: *estado = 1; break;
				case 128: *estado = 1; break;
				case 129: *estado = 1; break;
				case 130: *estado = 1; break;
				case 131: *estado = 1; break;
				case 132: *estado = 1; break;
				case 133: *estado = 1; break;
				case 134: *estado = 1; break;
				case 135: *estado = 1; break;
				case 136: *estado = 1; break;
				case 137: *estado = 1; break;
				case 138: *estado = 1; break;
				case 139: *estado = 1; break;
				case 140: *estado = 1; break;
				case 141: *estado = 1; break;
				case 142: *estado = 1; break;
				case 143: *estado = 1; break;
				case 144: *estado = 1; break;
				case 145: *estado = 1; break;
				case 146: *estado = 1; break;
				case 147: *estado = 1; break;
				case 148: *estado = 1; break;
				case 149: *estado = 1; break;
				case 150: *estado = 1; break;
				case 151: *estado = 1; break;
				case 152: *estado = 1; break;
				case 153: *estado = 1; break;
				case 154: *estado = 1; break;
				case 155: *estado = 1; break;
				case 156: *estado = 1; break;
				case 157: *estado = 1; break;
				case 158: *estado = 1; break;
				case 159: *estado = 1; break;
				case 160: *estado = 1; break;
				case 161: *estado = 1; break;
				case 162: *estado = 1; break;
				case 163: *estado = 1; break;
				case 164: *estado = 1; break;
				case 165: *estado = 1; break;
				case 166: *estado = 1; break;
				case 167: *estado = 1; break;
				case 168: *estado = 1; break;
				case 169: *estado = 1; break;
				case 170: *estado = 1; break;
				case 171: *estado = 1; break;
				case 172: *estado = 1; break;
				case 173: *estado = 1; break;
				case 174: *estado = 1; break;
				case 175: *estado = 1; break;
				case 176: *estado = 1; break;
				case 177: *estado = 1; break;
				case 178: *estado = 1; break;
				case 179: *estado = 1; break;
				case 180: *estado = 1; break;
				case 181: *estado = 1; break;
				case 182: *estado = 1; break;
				case 183: *estado = 1; break;
				case 184: *estado = 1; break;
				case 185: *estado = 1; break;
				case 186: *estado = 1; break;
				case 187: *estado = 1; break;
				case 188: *estado = 1; break;
				case 189: *estado = 1; break;
				case 190: *estado = 1; break;
				case 191: *estado = 1; break;
				case 192: *estado = 1; break;
				case 193: *estado = 1; break;
				case 194: *estado = 1; break;
				case 195: *estado = 1; break;
				case 196: *estado = 1; break;
				case 197: *estado = 1; break;
				case 198: *estado = 1; break;
				case 199: *estado = 1; break;
				case 200: *estado = 1; break;
				case 201: *estado = 1; break;
				case 202: *estado = 1; break;
				case 203: *estado = 1; break;
				case 204: *estado = 1; break;
				case 205: *estado = 1; break;
				case 206: *estado = 1; break;
				case 207: *estado = 1; break;
				case 208: *estado = 1; break;
				case 209: *estado = 1; break;
				case 210: *estado = 1; break;
				case 211: *estado = 1; break;
				case 212: *estado = 1; break;
				case 213: *estado = 1; break;
				case 214: *estado = 1; break;
				case 215: *estado = 1; break;
				case 216: *estado = 1; break;
				case 217: *estado = 1; break;
				case 218: *estado = 1; break;
				case 219: *estado = 1; break;
				case 220: *estado = 1; break;
				case 221: *estado = 1; break;
				case 222: *estado = 1; break;
				case 223: *estado = 1; break;
				case 224: *estado = 1; break;
				case 225: *estado = 1; break;
				case 226: *estado = 1; break;
				case 227: *estado = 1; break;
				case 228: *estado = 1; break;
				case 229: *estado = 1; break;
				case 230: *estado = 1; break;
				case 231: *estado = 1; break;
				case 232: *estado = 1; break;
				case 233: *estado = 1; break;
				case 234: *estado = 1; break;
				case 235: *estado = 1; break;
				case 236: *estado = 1; break;
				case 237: *estado = 1; break;
				case 238: *estado = 1; break;
				case 239: *estado = 1; break;
				case 240: *estado = 1; break;
				case 241: *estado = 1; break;
				case 242: *estado = 1; break;
				case 243: *estado = 1; break;
				case 244: *estado = 1; break;
				case 245: *estado = 1; break;
				case 246: *estado = 1; break;
				case 247: *estado = 1; break;
				case 248: *estado = 1; break;
				case 249: *estado = 1; break;
				case 250: *estado = 1; break;
				case 251: *estado = 1; break;
				case 252: *estado = 1; break;
				case 253: *estado = 1; break;
				case 254: *estado = 1; break;
				case 255: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 2:
			switch(entrada)
			{
				default: *estado = LEXER_ERROR;
			}
		break;
		case 3:
			switch(entrada)
			{
				case 1: *estado = 1; break;
				case 2: *estado = 1; break;
				case 3: *estado = 1; break;
				case 4: *estado = 1; break;
				case 5: *estado = 1; break;
				case 6: *estado = 1; break;
				case 7: *estado = 1; break;
				case 8: *estado = 1; break;
				case 9: *estado = 1; break;
				case 10: *estado = 1; break;
				case 11: *estado = 1; break;
				case 12: *estado = 1; break;
				case 13: *estado = 1; break;
				case 14: *estado = 1; break;
				case 15: *estado = 1; break;
				case 16: *estado = 1; break;
				case 17: *estado = 1; break;
				case 18: *estado = 1; break;
				case 19: *estado = 1; break;
				case 20: *estado = 1; break;
				case 21: *estado = 1; break;
				case 22: *estado = 1; break;
				case 23: *estado = 1; break;
				case 24: *estado = 1; break;
				case 25: *estado = 1; break;
				case 26: *estado = 1; break;
				case 27: *estado = 1; break;
				case 28: *estado = 1; break;
				case 29: *estado = 1; break;
				case 30: *estado = 1; break;
				case 31: *estado = 1; break;
				case 32: *estado = 1; break;
				case 33: *estado = 1; break;
				case 34: *estado = 1; break;
				case 35: *estado = 1; break;
				case 36: *estado = 1; break;
				case 37: *estado = 1; break;
				case 38: *estado = 1; break;
				case 39: *estado = 1; break;
				case 40: *estado = 1; break;
				case 41: *estado = 1; break;
				case 42: *estado = 1; break;
				case 43: *estado = 1; break;
				case 44: *estado = 1; break;
				case 45: *estado = 1; break;
				case 46: *estado = 1; break;
				case 47: *estado = 1; break;
				case 48: *estado = 1; break;
				case 49: *estado = 1; break;
				case 50: *estado = 1; break;
				case 51: *estado = 1; break;
				case 52: *estado = 1; break;
				case 53: *estado = 1; break;
				case 54: *estado = 1; break;
				case 55: *estado = 1; break;
				case 56: *estado = 1; break;
				case 57: *estado = 1; break;
				case 58: *estado = 1; break;
				case 59: *estado = 1; break;
				case 60: *estado = 1; break;
				case 61: *estado = 1; break;
				case 62: *estado = 1; break;
				case 63: *estado = 1; break;
				case 64: *estado = 1; break;
				case 65: *estado = 1; break;
				case 66: *estado = 1; break;
				case 67: *estado = 1; break;
				case 68: *estado = 1; break;
				case 69: *estado = 1; break;
				case 70: *estado = 1; break;
				case 71: *estado = 1; break;
				case 72: *estado = 1; break;
				case 73: *estado = 1; break;
				case 74: *estado = 1; break;
				case 75: *estado = 1; break;
				case 76: *estado = 1; break;
				case 77: *estado = 1; break;
				case 78: *estado = 1; break;
				case 79: *estado = 1; break;
				case 80: *estado = 1; break;
				case 81: *estado = 1; break;
				case 82: *estado = 1; break;
				case 83: *estado = 1; break;
				case 84: *estado = 1; break;
				case 85: *estado = 1; break;
				case 86: *estado = 1; break;
				case 87: *estado = 1; break;
				case 88: *estado = 1; break;
				case 89: *estado = 1; break;
				case 90: *estado = 1; break;
				case 91: *estado = 1; break;
				case 92: *estado = 1; break;
				case 93: *estado = 1; break;
				case 94: *estado = 1; break;
				case 95: *estado = 1; break;
				case 96: *estado = 1; break;
				case 97: *estado = 1; break;
				case 98: *estado = 1; break;
				case 99: *estado = 1; break;
				case 100: *estado = 1; break;
				case 101: *estado = 1; break;
				case 102: *estado = 1; break;
				case 103: *estado = 1; break;
				case 104: *estado = 1; break;
				case 105: *estado = 1; break;
				case 106: *estado = 1; break;
				case 107: *estado = 1; break;
				case 108: *estado = 1; break;
				case 109: *estado = 1; break;
				case 110: *estado = 1; break;
				case 111: *estado = 1; break;
				case 112: *estado = 1; break;
				case 113: *estado = 1; break;
				case 114: *estado = 1; break;
				case 115: *estado = 1; break;
				case 116: *estado = 1; break;
				case 117: *estado = 1; break;
				case 118: *estado = 1; break;
				case 119: *estado = 1; break;
				case 120: *estado = 1; break;
				case 121: *estado = 1; break;
				case 122: *estado = 1; break;
				case 123: *estado = 1; break;
				case 124: *estado = 1; break;
				case 125: *estado = 1; break;
				case 126: *estado = 1; break;
				case 127: *estado = 1; break;
				case 128: *estado = 1; break;
				case 129: *estado = 1; break;
				case 130: *estado = 1; break;
				case 131: *estado = 1; break;
				case 132: *estado = 1; break;
				case 133: *estado = 1; break;
				case 134: *estado = 1; break;
				case 135: *estado = 1; break;
				case 136: *estado = 1; break;
				case 137: *estado = 1; break;
				case 138: *estado = 1; break;
				case 139: *estado = 1; break;
				case 140: *estado = 1; break;
				case 141: *estado = 1; break;
				case 142: *estado = 1; break;
				case 143: *estado = 1; break;
				case 144: *estado = 1; break;
				case 145: *estado = 1; break;
				case 146: *estado = 1; break;
				case 147: *estado = 1; break;
				case 148: *estado = 1; break;
				case 149: *estado = 1; break;
				case 150: *estado = 1; break;
				case 151: *estado = 1; break;
				case 152: *estado = 1; break;
				case 153: *estado = 1; break;
				case 154: *estado = 1; break;
				case 155: *estado = 1; break;
				case 156: *estado = 1; break;
				case 157: *estado = 1; break;
				case 158: *estado = 1; break;
				case 159: *estado = 1; break;
				case 160: *estado = 1; break;
				case 161: *estado = 1; break;
				case 162: *estado = 1; break;
				case 163: *estado = 1; break;
				case 164: *estado = 1; break;
				case 165: *estado = 1; break;
				case 166: *estado = 1; break;
				case 167: *estado = 1; break;
				case 168: *estado = 1; break;
				case 169: *estado = 1; break;
				case 170: *estado = 1; break;
				case 171: *estado = 1; break;
				case 172: *estado = 1; break;
				case 173: *estado = 1; break;
				case 174: *estado = 1; break;
				case 175: *estado = 1; break;
				case 176: *estado = 1; break;
				case 177: *estado = 1; break;
				case 178: *estado = 1; break;
				case 179: *estado = 1; break;
				case 180: *estado = 1; break;
				case 181: *estado = 1; break;
				case 182: *estado = 1; break;
				case 183: *estado = 1; break;
				case 184: *estado = 1; break;
				case 185: *estado = 1; break;
				case 186: *estado = 1; break;
				case 187: *estado = 1; break;
				case 188: *estado = 1; break;
				case 189: *estado = 1; break;
				case 190: *estado = 1; break;
				case 191: *estado = 1; break;
				case 192: *estado = 1; break;
				case 193: *estado = 1; break;
				case 194: *estado = 1; break;
				case 195: *estado = 1; break;
				case 196: *estado = 1; break;
				case 197: *estado = 1; break;
				case 198: *estado = 1; break;
				case 199: *estado = 1; break;
				case 200: *estado = 1; break;
				case 201: *estado = 1; break;
				case 202: *estado = 1; break;
				case 203: *estado = 1; break;
				case 204: *estado = 1; break;
				case 205: *estado = 1; break;
				case 206: *estado = 1; break;
				case 207: *estado = 1; break;
				case 208: *estado = 1; break;
				case 209: *estado = 1; break;
				case 210: *estado = 1; break;
				case 211: *estado = 1; break;
				case 212: *estado = 1; break;
				case 213: *estado = 1; break;
				case 214: *estado = 1; break;
				case 215: *estado = 1; break;
				case 216: *estado = 1; break;
				case 217: *estado = 1; break;
				case 218: *estado = 1; break;
				case 219: *estado = 1; break;
				case 220: *estado = 1; break;
				case 221: *estado = 1; break;
				case 222: *estado = 1; break;
				case 223: *estado = 1; break;
				case 224: *estado = 1; break;
				case 225: *estado = 1; break;
				case 226: *estado = 1; break;
				case 227: *estado = 1; break;
				case 228: *estado = 1; break;
				case 229: *estado = 1; break;
				case 230: *estado = 1; break;
				case 231: *estado = 1; break;
				case 232: *estado = 1; break;
				case 233: *estado = 1; break;
				case 234: *estado = 1; break;
				case 235: *estado = 1; break;
				case 236: *estado = 1; break;
				case 237: *estado = 1; break;
				case 238: *estado = 1; break;
				case 239: *estado = 1; break;
				case 240: *estado = 1; break;
				case 241: *estado = 1; break;
				case 242: *estado = 1; break;
				case 243: *estado = 1; break;
				case 244: *estado = 1; break;
				case 245: *estado = 1; break;
				case 246: *estado = 1; break;
				case 247: *estado = 1; break;
				case 248: *estado = 1; break;
				case 249: *estado = 1; break;
				case 250: *estado = 1; break;
				case 251: *estado = 1; break;
				case 252: *estado = 1; break;
				case 253: *estado = 1; break;
				case 254: *estado = 1; break;
				case 255: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 2) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}
static int func_decimal(int *estado, int entrada)
{
	switch(*estado)
	{
		case 0:
			switch(entrada)
			{
				case 48: *estado = 1; break;
				case 49: *estado = 1; break;
				case 50: *estado = 1; break;
				case 51: *estado = 1; break;
				case 52: *estado = 1; break;
				case 53: *estado = 1; break;
				case 54: *estado = 1; break;
				case 55: *estado = 1; break;
				case 56: *estado = 1; break;
				case 57: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		case 1:
			switch(entrada)
			{
				case 48: *estado = 1; break;
				case 49: *estado = 1; break;
				case 50: *estado = 1; break;
				case 51: *estado = 1; break;
				case 52: *estado = 1; break;
				case 53: *estado = 1; break;
				case 54: *estado = 1; break;
				case 55: *estado = 1; break;
				case 56: *estado = 1; break;
				case 57: *estado = 1; break;
				default: *estado = LEXER_ERROR;
			}
		break;
		default: *estado = LEXER_ERROR;
	}
	if(*estado == LEXER_ERROR) return LEXER_ERROR;
	if(*estado == 1) return LEXER_ACCEPTED;
	return LEXER_PROCESSING;
}

int (*functions[])(int* state, int input) = {
	func_identifier,
	func_semicolon,
	func_to,
	func_comma,
	func_blank,
	func_breakLine,
	func_comment,
	func_helpers,
	func_tokens,
	func_productions,
	func_reducer,
	func_attrib,
	func_sum,
	func_sub,
	func_mult,
	func_or,
	func_reduce,
	func_question,
	func_o_parentheses,
	func_c_parentheses,
	func_o_brackets,
	func_c_brackets,
	func_charLiteral,
	func_decimal
};

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

int (**UCC_lexerFunctions)(int* state, int input) = functions;

bool UCC_shouldIgnore(Token* token)
{
	int type = token->type;
	return type == T_blank || type == T_breakLine || type == T_comment;
}