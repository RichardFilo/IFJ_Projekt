
/******************************** string.h ************************************/
/*  Předmět: IFJ a IAL						                                  */
/*  Dynamicky alokovany string                                                */
/*  Vytvořil: RIchard Filo			                                          */
/* ************************************************************************** */
/*
**    stringCreate .... vytvori dynamicky alokovany string
**    stringFree ... uvolni pamat
**
**/

#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                                  /* Hlavičky funkcí pro paci s stringem */

void addChar(char* str, char c);
char* stringCreate(const char* s);
void stringFree(char* s);


#endif