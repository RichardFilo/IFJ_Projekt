
/********************************* mystring.h *********************************/
/*  Předmět: IFJ a IAL						                                  */
/*  Dynamicky alokovaný string                                                */
/*  Vytvořil: Richard Filo			                                          */
/* ************************************************************************** */
/*
**    stringCreate .... Vytvoří dynamicky alokovaný string
**    stringFree ... Uvoľní pamäť
**
**
**/

#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                                  /* Hlavičky funkcí pro práci se stringem */

void addChar(char* str, char c);
char* stringCreate(const char* s);
void stringFree(char* s);


#endif
