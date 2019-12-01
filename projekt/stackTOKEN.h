#ifndef _STACKT_H_
#define _STACKT_H_

#include <stdio.h>
#include <stdlib.h>

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
	} tTokenType;

	typedef struct {
		tTokenType type;
		union {
			int _int;
			double _float;
			char* _string;
		};
	} tToken;
                             /* ADT zásobník implementovaný ve statickém poli */
typedef struct {
	tToken arr[2];                             /* pole pro uložení hodnot */
	int top;                                /* index prvku na vrcholu zásobníku */
} tStackToken;

tToken token;
tStackToken* stackT;

                                  /* Hlavičky funkcí pro práci se zásobníkem. */
tStackToken* stackTokenInit ();
int stackTokenEmpty ( const tStackToken* s );
tToken stackTokenPop ( tStackToken* s );
void stackTokenPush ( tStackToken* s, tToken t );
void stackTokenFree ( tStackToken* s );

#endif