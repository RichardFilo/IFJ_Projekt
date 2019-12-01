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