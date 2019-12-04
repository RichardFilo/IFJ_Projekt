
/******************************** mystring.c **********************************/
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
#include"mystring.h"

void addChar(char* str, char c){

    str[strlen(str)]=c;
}

char* stringCreate(const char* s){

    char* new=malloc(strlen(s)+1);
    if(new==NULL){
        fprintf(stderr,"ERROR 99: Chyba alokace pamate\n");
        return NULL;
    }
    strcpy(new,s);
    return new;
}

void stringFree(char* s){

    free(s);
}

