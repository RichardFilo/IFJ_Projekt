
/* ******************************* stackINT.h ******************************* */
/*  Předmět: IFJ a IAL			 	                              */
/*  Zásobník integerov v poli                                                 */
/*  Vytvořil: Richard Filo			                              */
/* ************************************************************************** */
/*
**    stackInit .... Inicializace zásobníku
**    stackEmpty ... Test na prázdnost zásobníku
**    stackFull .... Test na zaplněnost zásobníku
**    stackTop ..... Přečte hodnotu z vrcholu zásobníku
**    stackPop ..... Odstraní prvek z vrcholu zásobníku
**    stackPush .... Vloží prvek do zásobníku
**    stackFree .... Uvoľní pamäť
**
**/

#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 200

                             /* ADT zásobník implementovaný ve statickém poli */
typedef struct {
	int arr[MAX_STACK];                             /* pole pro uložení hodnot */
	int top;                                /* index prvku na vrcholu zásobníku */
} tStack;

                                  /* Hlavičky funkcí pro práci se zásobníkem. */
tStack* stackInit ();
int stackEmpty ( const tStack* s );
int stackFull ( const tStack* s );
int stackTop ( const tStack* s);
int stackPop ( tStack* s );
int stackPush ( tStack* s, int c );
void stackFree ( tStack* s );

#endif
