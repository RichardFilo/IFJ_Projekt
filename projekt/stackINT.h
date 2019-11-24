
/* ****************************** stackINT.h ******************************** */
/*  Předmět: IFJ a IAL						                                  */
/* `Zásobník integerov v poli                                                 */
/*  Vytvořil: RIchard Filo			                                          */
/* ************************************************************************** */
/*
**    stackInit .... inicializace zásobníku
**    stackEmpty ... test na prázdnost zásobníku
**    stackFull .... test na zaplněnost zásobníku
**    stackTop ..... přečte hodnotu z vrcholu zásobníku
**    stackPop ..... odstraní prvek z vrcholu zásobníku
**    stackPush .... vloží prvku do zásobníku
**    stackFree .... uvolni pamat
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