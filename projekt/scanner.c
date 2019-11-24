
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

    if(strcmp(str,"def")==0) return 5;
    else if(strcmp(str,"else")==0) return 6;
    else if(strcmp(str,"if")==0) return 7;
    else if(strcmp(str,"none")==0) return 8;
    else if(strcmp(str,"pass")==0) return 9;
    else if(strcmp(str,"return")==0) return 10;
    else if(strcmp(str,"while")==0) return 11;
    else return 0;
}

int scanner_init(char* file){

    if(strcmp(file,"stdin")){

        input=fopen(file,"r");
        if(input==NULL) {
            fprintf(stderr,"ERROR 99: Nepodarilo sa otvorit subor\n");
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

    int c, i=0;
    int state=0;
    char buffer[200]={0};

    while((c=fgetc(input))!=-1){

        switch(state){

            case 0:
                if(FTflag){
                    if(c==' '){
                        i++;
                    }
                    else if(c=='\n'){
                        i=0;
                    }
                    else if(c=='#'){
                        state=1;
                    }
                    else{
                        ungetc(c,input);
                        if(stackTop(stack)<i){
                            FTflag=0;
                            stackPush(stack,i);
                            token.type=TT_INDENT;
                            return 0;
                        }
                        else if(stackTop(stack)>i){
                            stackPop(stack);
                            if(stackTop(stack)==i){
                                token.type=TT_DEDENT;
                                FTflag=0;
                                return 0;
                            }
                            else if(stackTop(stack)<i){
                                fprintf(stderr,"ERROR 1: Zle odsadenie\n");
                                return 1;
                            }
                            else{
                                token.type=TT_DEDENT;
                                FTflag=1;
                                return 0;
                            }
                        }
                        else{
                            FTflag=0;
                        } 
                    }
                }
                else{
                    if(c=='\n'){
                        token.type=TT_EOL;
                        FTflag=1;
                        return 0;
                    }
                    else if(isalpha(c)||c=='_'){
                        state=2;
                        addChar(buffer,c);
                    }
                    else if(c=='#') state=1;
                }
                break;
            case 1:
                if(c=='\n') {
                    state=0;
                    ungetc(c,input);
                }
                break;
            case 2:
                if(isalnum(c)||c=='_') addChar(buffer,c);
                else{
                    ungetc(c,input);
                    int val;
                    if((val=checkKeyWord(buffer))){
                        token.type=val;
                        return 0;
                    }
                    else{
                        token.type=TT_ID;
                        token._string=stringCreate(buffer);
                        return 0;
                    }
                }
                break;
        }


    }
    if(stackPop(stack)!=0){
        token.type=TT_DEDENT;
        return 0;
    }

    token.type=TT_EOF;
    return -1;
}