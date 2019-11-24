
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

int scanner_init(char* file){

    if(strcmp(file,"stdin")){

        input=fopen(file,"r");
        if(input==NULL) {
            fprintf(stderr,"ERROR 99: Nepodarilo sa otvorit subor");
            return -1;
        }
    }
    else input=stdin;

    stack=stackInit();
    if(stack==NULL){
        fclose(input);
        return -1;
    }

    stackPush(stack,0);
    FTflag=1;
    return 0;
}

void scanner_free(){

    fclose(input);
    stackFree(stack);
}

int getToken(char* atribut){

    int c;
    while((c=fgetc(input))!=-1) putc(c,stdout);

    printf("\n");

    return 0;
}