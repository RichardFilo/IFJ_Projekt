/********************************* stackTOKEN.c *********************************/
/*  Předmět: IFJ a IAL						 					                */
/*  Zasobnik tokenov v poli                                     	            */
/*  Vytvořil: Richard Filo			                               				*/
/* **************************************************************************** */
/*
**    stackTokenInit .... Inicializace zásobníku
**    stackTokenEmpty ... Test na prázdnost zásobníku
**    stackTokenPop ..... Odstraní prvek z vrcholu zásobníku
**    stackTokenPush .... Vloží prvku do zásobníku
**	  stackTokenFree .... Uvolni pamat
**
**/

#include "stackTOKEN.h"

tStackToken* stackTokenInit () {
	
	tStackToken* new=malloc(sizeof(tStackToken));
	if(new==NULL){
		fprintf(stderr,"ERROR 99: Chyba alokace pamati\n");
		return NULL;	
	}
	new->top=-1;
	return new;
}

int stackTokenEmpty ( const tStackToken* s ) {

	return s->top==-1;
}

tToken stackTokenPop ( tStackToken* s ) {

	return s->arr[(s->top)--];
}

void stackTokenPush ( tStackToken* s, tToken t ) {

	s->arr[++(s->top)]=t;
}

void stackTokenFree( tStackToken* s ) {

	free(s);
}