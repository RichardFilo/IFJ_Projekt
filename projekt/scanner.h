
/* ****************************** stackINT.c ******************************** */
/*  Předmět: IFJ a IAL						                                  */
/*  Lexikalna analiza                                                         */
/*  Vytvořil: RIchard Filo			                                          */
/* ************************************************************************** */
/*
**    getToken ..... Vrati prislusny token
**
**/

#ifndef SCANNER_H
#define SCANNER_H

#include"stackINT.h"
#include"mystring.h"
#include<ctype.h>

	typedef enum {
		TT_,
		TT_EOF,
		TT_ID,
		TT_VALUE_INT,
		TT_VALUE_DOUBLE,
		TT_VALUE_STRING,
	//key words
		TT_AUTO = TYPE_KEYWORD,
		TT_INT,
		TT_DOUBLE,
		TT_STRING,
		TT_CIN,
		TT_COUT,
		TT_FOR,
		TT_IF,
		TT_ELSE,
		TT_RETURN,
		TT_WHILE,
		TT_DO,
	//delimiters
		TT_COLON,
		TT_INDENT,
		TT_DEDENT,
		TT_L_BRACKET,
		TT_R_BRACKET,
		TT_COMMA,
	//operators
		TT_MULTIPLY,
		TT_DIVIDE,
		TT_ADD,
		TT_SUB,
		TT_L,
		TT_G,
		TT_ASSIGN,
		TT_GE,
		TT_LE,
		TT_E,
		TT_NE,
		TT_IN,
		TT_OUT
	} tToken;

	struct {
		tToken type;
		union {
			int _int;
			double _float;
			char* _string;
		};
	} token;

int scanner_init(char* file);

void scanner_free();

int getToken();

#endif