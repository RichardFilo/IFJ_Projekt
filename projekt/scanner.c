
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
                    else if(c=='a'){
                        token.type=TT_ID;
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