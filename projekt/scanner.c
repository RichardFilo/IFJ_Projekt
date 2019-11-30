
/* ******************************* scanner.c ******************************** */
/*  Předmět: IFJ a IAL						              */
/*  Lexikálna analýza                                                         */
/*  Vytvořil: Richard Filo			                              */
/* ************************************************************************** */
/*
**    getToken ....... Inicializace zásobníku
**    checkKeyWord ... Test na kľúčové slovo
**    scannerInit .... Inicializácia skenera
**    scannerFree .... Uvoľnenie pamäte
**
**/
#include"scanner.h"

int checkKeyWord(char* str){

    if(strcmp(str,"def")==0) return TT_DEF;
    else if(strcmp(str,"else")==0) return TT_ELSE;
    else if(strcmp(str,"if")==0) return TT_IF;
    else if(strcmp(str,"none")==0) return TT_NONE;
    else if(strcmp(str,"pass")==0) return TT_PASS;
    else if(strcmp(str,"return")==0) return TT_RETURN;
    else if(strcmp(str,"while")==0) return TT_WHILE;
    else return 0;
}

int scannerInit(char* file){

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

void scannerFree(){

    fclose(input);
    stackFree(stack);
}

int getToken(){

    int c, i=0;
    int state=0;
    char buffer[200]={0};

    while((c=fgetc(input))!=-1){

        char uv[3]={0};

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
                    else if(c==':'){
                        token.type=TT_COLON;
                        return 0;
                    }
                    else if(c=='('){
                        token.type=TT_LEFT_BRACKET;
                        return 0;
                    }
                    else if(c==')'){
                        token.type=TT_RIGHT_BRACKET;
                        return 0;
                    }else if(c==','){
                        token.type=TT_COMMA;
                        return 0;
                    }
                    else if(c=='+'){
                        token.type=TT_ADD;
                        return 0;
                    }
                    else if(c=='-'){
                        token.type=TT_SUB;
                        return 0;
                    }
                    else if(c=='*'){
                        token.type=TT_MULTIPLY;
                        return 0;
                    }
                    else if(c=='/') state=13;
                    else if(c=='<') state=14;
                    else if(c=='>') state=15;
                    else if(c=='=') state=16;
                    else if(c=='!') state=17;
                    else if(isalpha(c)||c=='_'){
                        state=2;
                        addChar(buffer,c);
                    }
                    else if(c==39) state=3;
                    else if(c==34) state=4;
                    else if(isdigit(c)) {
                        addChar(buffer,c);
                        if(c=='0') state=6;
                        else state=7;
                    }
                    else if(c=='#') state=1;
                    else if(isspace(c)) state=0;
                    else {
                        fprintf(stderr,"ERROR 1: Neznamy Token\n");
                        return 1;
                    }
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
            case 3:
                if(c==39){
                    token.type=TT_VALUE_STRING;
                    token._string=stringCreate(buffer);
                    return 0;
                }
                else if(c=='\n'){
                    fprintf(stderr,"ERROR 1: Neukonceny retazcovy literal\n");
                    return 1;
                }
                else{
                    addChar(buffer,c);
                }
                break;
            case 4:
                uv[0]=c;
                c=fgetc(input);
                uv[1]=c;
                if(strcmp((char*)uv,"\"\"")==0){
                    state=5;
                }
                else{
                    fprintf(stderr,"ERROR 1: Zle zacaty dokumentacny retazec\n");
                    return 1;
                }
                break;
            case 5:
                if(c==34){
                    c=fgetc(input);
                    uv[0]=c;
                    c=fgetc(input);
                    uv[1]=c;
                    if(strcmp((char*)uv,"\"\"")==0){
                        token.type=TT_VALUE_STRING;
                        token._string=stringCreate(buffer);
                        return 0;
                    }
                    else if(uv[1]==-1){
                        fprintf(stderr,"ERROR 1: Zle ukonceny dokumentacny retazec\n");
                        return 1;
                    }
                    else{
                        ungetc(uv[1],input);
                        ungetc(uv[0],input);
                        addChar(buffer,34);
                    }
                }
                else if(c=='\\'){
                    c=fgetc(input);
                    if(c==34) addChar(buffer,34);
                    else{
                        ungetc(c,input);
                        addChar(buffer,'\\');
                    }
                }
                else{
                    addChar(buffer,c);
                }
                break;
            case 6:
                if(c=='.'){
                    state=8;
                    addChar(buffer,c);
                }
                else if(toupper(c)=='E'){
                    state=9;
                    addChar(buffer,c);
                }
                else if(isdigit(c)){
                    fprintf(stderr,"ERROR 1: Prebytocne nuly na zaciatku cisla\n");
                    return 1;
                }
                else{
                    ungetc(c,input);
                    token.type=TT_VALUE_INT;
                    token._int=0;
                    return 0;
                }
                break;
            case 7:
                if(c=='.'){
                    state=8;
                    addChar(buffer,c);
                }
                else if(toupper(c)=='E'){
                    state=9;
                    addChar(buffer,c);
                }
                else if(isdigit(c)){
                    addChar(buffer,c);
                    state=7;
                }
                else{
                    ungetc(c,input);
                    token.type=TT_VALUE_INT;
                    token._int=atoi(buffer);
                    return 0;
                }
                break;
            case 8:
                if(isdigit(c)){
                    state=10;
                    addChar(buffer,c);
                }
                else{
                    fprintf(stderr,"ERROR 1: Zle napisane desatinne cislo\n");
                    return 1;
                }
                break;
            case 9:
                if(c=='+'||c=='-'){
                    state=11;
                    addChar(buffer,c);
                }
                else if(isdigit(c)){
                    state=12;
                    addChar(buffer,c);
                }
                else{
                    fprintf(stderr,"ERROR 1: Zle napisane desatinne cislo\n");
                    return 1;
                }
                break;
            case 10:
                if(toupper(c)=='E'){
                    state=9;
                    addChar(buffer,c);
                }
                else if(isdigit(c)){
                    addChar(buffer,c);
                    state=10;
                }
                else{
                    ungetc(c,input);
                    token.type=TT_VALUE_DOUBLE;
                    token._float=atof(buffer);
                    return 0;
                }
                break;
            case 11:
                if(isdigit(c)){
                    state=10;
                    addChar(buffer,c);
                }
                else{
                    fprintf(stderr,"ERROR 1: Zle napisane desatinne cislo\n");
                    return 1;
                }
                break;
            case 12:
                if(isdigit(c)){
                    addChar(buffer,c);
                    state=12;
                }
                else{
                    ungetc(c,input);
                    token.type=TT_VALUE_DOUBLE;
                    token._float=atof(buffer);
                    return 0;
                }
                break;
            case 13:
                if(c=='/'){
                    token.type=TT_DIVIDE_INT;
                    return 0;
                }
                else
                {
                    ungetc(c,input);
                    token.type=TT_DIVIDE_FLOAT;
                    return 0;
                }
                break;
            case 14:
                if(c=='='){
                    token.type=TT_LE;
                    return 0;
                }
                else
                {
                    ungetc(c,input);
                    token.type=TT_L;
                    return 0;
                }
                break;
            case 15:
                if(c=='='){
                    token.type=TT_GE;
                    return 0;
                }
                else
                {
                    ungetc(c,input);
                    token.type=TT_G;
                    return 0;
                }
                break;
            case 16:
                if(c=='='){
                    token.type=TT_E;
                    return 0;
                }
                else
                {
                    ungetc(c,input);
                    token.type=TT_ASSIGN;
                    return 0;
                }
                break;
            case 17:
                if(c=='='){
                    token.type=TT_NE;
                    return 0;
                }
                else
                {
                    fprintf(stderr,"ERROR 1: Neznamy operator '!'.\n");
                    return 1;
                }
                break;
        }


    }
    if(state==5){
        fprintf(stderr,"ERROR 1: Zle ukonceny dokumentacny retazec\n");
        return 1;
    }
    if(stackPop(stack)!=0){
        token.type=TT_DEDENT;
        return 0;
    }

    token.type=TT_EOF;
    return -1;
}
