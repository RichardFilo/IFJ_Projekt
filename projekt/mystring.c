
/******************************** string.c ************************************/
/*  Předmět: IFJ a IAL						                                  */
/*  Dynamicky alokovany string                                                */
/*  Vytvořil: RIchard Filo			                                          */
/* ************************************************************************** */
/*
**    stringCreate .... vytvori dynamicky alokovany string
**    stringFree ... uvolni pamat
**
**/
#include"mystring.h"

char* stringCreate(const char* s){

    char* new=malloc(strlen(s)+1);
    if(new==NULL){
        fprintf(stderr,"ERROR 99: Chyba alokace pamate");
        return NULL;
    }
    strcpy(new,s);
    return new;
}
void stringFree(char* s){

    free(s);
}