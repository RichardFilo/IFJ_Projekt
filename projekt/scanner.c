
/* ****************************** stackINT.c ******************************** */
/*  Předmět: IFJ a IAL						                                  */
/*  Lexikalna analiza                                                         */
/*  Vytvořil: RIchard Filo			                                          */
/* ************************************************************************** */
/*
**    getToken .... inicializace zásobníku
**    checkKeyWord ... test na klucove slovo
**
**/
#include"scanner.h"

int checkKeyWord(char* str){

    if(strcmp(str,"def")==0) return 0;
    else if(strcmp(str,"else")==0) return 1;
    else if(strcmp(str,"if")==0) return 2;
    else if(strcmp(str,"none")==0) return 3;
    else if(strcmp(str,"pass")==0) return 4;
    else if(strcmp(str,"return")==0) return 5;
    else if(strcmp(str,"while")==0) return 6;
    else return -1;
}

int getToken(char* atribut){
    
    
}