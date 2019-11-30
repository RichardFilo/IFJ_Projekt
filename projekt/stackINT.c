
/* ***************************** stackINT.c ********************************* */
/*  Předmět: IFJ a IAL				                              */
/*  Zásobník integerov v poli                  				      */
/*  Vytvořil: Richard Filo			                              */
/* ************************************************************************** */
/*
**    stackInit .... Inicializace zásobníku
**    stackEmpty ... Test na prázdnost zásobníku
**    stackFull .... Test na zaplněnost zásobníku
**    stackTop ..... Přečte hodnotu z vrcholu zásobníku
**    stackPop ..... Odstraní prvek z vrcholu zásobníku
**    stackPush .... Vloží prvku do zásobníku
**
**/

#include "stackINT.h"

tStack* stackInit () {
	
	tStack* new=malloc(sizeof(tStack));
	if(new==NULL){
		fprintf(stderr,"ERROR 99: Chyba alokace pamati\n");
		return NULL;	
	}
	new->top=-1;
	return new;
}

int stackEmpty ( const tStack* s ) {

	return s->top==-1;
}

int stackFull ( const tStack* s ) {

	return s->top==MAX_STACK-1;
}

int stackTop ( const tStack* s ) {

	if(stackEmpty(s)) return -1;
	else return s->arr[s->top];
}

int stackPop ( tStack* s ) {

	if(stackEmpty(s)) return -1;
	else return s->arr[(s->top)--];
}

int stackPush ( tStack* s, int c ) {

	if(stackFull(s)) return -1;
	else s->arr[++(s->top)]=c;
	return 0;
}

void stackFree( tStack* s ) {

	free(s);
}
