
/* ******************************** scanner.h ******************************* */
/*  Předmět: IFJ a IAL				                              */
/*  Lexikálna analýza                                                         */
/*  Vytvořil: Richard Filo			                              */
/* ************************************************************************** */
/*
**    getToken ..... Vráti príslušný token
**    scannerInit .... Inicializácia skenera
**    scannerFree .... Uvoľnenie pamäte
**
**/

#ifndef SCANNER_H
#define SCANNER_H

#include"stackINT.h"
#include"mystring.h"
#include<ctype.h>

	typedef enum {
		TT_EOF,
		TT_ID,
		TT_VALUE_INT,
		TT_VALUE_DOUBLE,
		TT_VALUE_STRING,
	//key words
		TT_DEF,
		TT_ELSE,
		TT_IF,
		TT_NONE,
		TT_PASS,
		TT_RETURN,
		TT_WHILE,
	//delimiters
		TT_EOL,
		TT_COLON,
		TT_INDENT,
		TT_DEDENT,
		TT_LEFT_BRACKET,
		TT_RIGHT_BRACKET,
		TT_COMMA,
	//operators
		TT_MULTIPLY,
		TT_DIVIDE_INT,
		TT_DIVIDE_FLOAT,
		TT_ADD,
		TT_SUB,
		TT_L,
		TT_G,
		TT_ASSIGN,
		TT_GE,
		TT_LE,
		TT_E,
		TT_NE
	} tToken;

	struct {
		tToken type;
		union {
			int _int;
			double _float;
			char* _string;
		};
	} token;

    int FTflag;
    FILE* input;
	tStack* stack;

int scannerInit(char* file);

void scannerFree();

int getToken();

#endif
