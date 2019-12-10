
/********************************* parser.c ***********************************/
/*  Předmět: IFJ a IAL						                                  */
/*  Syntakticky analizator                                                    */
/*  Vytvořil: Richard Filo			                                          */
/* ************************************************************************** */
/*
**    exp .... precedencna analyza vyrazu
**
**/

#include "parser.h"


int _errNumber=0,frame=0,typExp=0,termsCount=0;
tHTable* GFfunc;
tHTable* GFvar;
tHTable* LFfunc[50];
tHTable* LFvar[50];
char* code=NULL;
tStack* stackTypes=NULL;

int getNumber(int tok){

    switch(tok){
        case TT_EOL:
        case TT_COLON: return 0; break;
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE: return 1; break;
        case TT_ADD: return 2; break;
        case TT_SUB: return 3; break;
        case TT_MULTIPLY: return 4; break;
        case TT_DIVIDE_FLOAT: return 5; break;
        case TT_DIVIDE_INT: return 6; break;
        case TT_L: return 7; break;
        case TT_LE: return 8; break;
        case TT_G: return 9; break;
        case TT_GE: return 10; break;
        case TT_E: return 11; break;
        case TT_NE: return 12; break;
        case TT_LEFT_BRACKET: return 13; break;
        case TT_RIGHT_BRACKET: return 14; break;
        default: return -1;
    }
}

int top(tStack* s){

    int ret=stackTop(s);
    if(ret>14){
        int tmp=stackPop(s);
        ret=stackTop(s);
        stackPush(s,tmp);
    }
    return ret;
}

int generate(int rule){
    int operand[2];
    operand[0]=stackPop(stackTypes);
    operand[1]=stackPop(stackTypes);
    if(operand[0]==2 && operand[1]==3){
        operand[0]=3;
        code=addString(code,"CREATEFRAME\n");
        code=addString(code,"DEFVAR TF@&1\n");
        code=addString(code,"POPS TF@&1\n");
        code=addString(code,"INT2FLOAT TF@&1 TF@&1\n");
        code=addString(code,"PUSHS TF@&1\n");
    }
    if(operand[0]==3 && operand[1]==2){
        operand[1]=3;
        code=addString(code,"CREATEFRAME\n");
        code=addString(code,"DEFVAR TF@&1\n");
        code=addString(code,"DEFVAR TF@&2\n");
        code=addString(code,"POPS TF@&1\n");
        code=addString(code,"POPS TF@&2\n");
        code=addString(code,"INT2FLOAT TF@&2 TF@&2\n");
        code=addString(code,"PUSHS TF@&2\n");
        code=addString(code,"PUSHS TF@&1\n");
    }
    if(operand[0] != operand[1]){
        if(rule==12){
            stackPush(stackTypes,5);
            code=addString(code,"CREATEFRAME\n");
            code=addString(code,"DEFVAR TF@&1\n");
            code=addString(code,"DEFVAR TF@&2\n");
            code=addString(code,"POPS TF@&1\n");
            code=addString(code,"POPS TF@&2\n");
            code=addString(code,"PUSHS bool@false\n");
            return 0;
        }
        if(rule==13){
            stackPush(stackTypes,5);
            code=addString(code,"CREATEFRAME\n");
            code=addString(code,"DEFVAR TF@&1\n");
            code=addString(code,"DEFVAR TF@&2\n");
            code=addString(code,"POPS TF@&1\n");
            code=addString(code,"POPS TF@&2\n");
            code=addString(code,"PUSHS bool@true\n");
            return 0;
        }
        fprintf(stderr,"ERROR 4: Chybna kombinace datovych typu\n");
        _errNumber=4;
        return 1;
    }
    switch (rule){
        case 3:
            if(operand[0]==2){
                stackPush(stackTypes,2);
                code=addString(code,"ADDS\n");
            }
            else if(operand[0]==3){
                stackPush(stackTypes,3);
                code=addString(code,"ADDS\n");
            }
            else if(operand[0]==4){
                stackPush(stackTypes,4);
                code=addString(code,"CREATEFRAME\n");
                code=addString(code,"DEFVAR TF@&1\n");
                code=addString(code,"DEFVAR TF@&2\n");
                code=addString(code,"DEFVAR TF@&3\n");
                code=addString(code,"POPS TF@&1\n");
                code=addString(code,"POPS TF@&2\n");
                code=addString(code,"CONCAT TF@&3 TF@&2 TF@&1\n");
                code=addString(code,"PUSHS TF@&3\n");
            }
            else{
            fprintf(stderr,"ERROR 4: Chybna kombinace datovych typu\n");
            _errNumber=4;
            return 1;
            }
            break;
        case 4:
            if(operand[0]==2){
                stackPush(stackTypes,2);
                code=addString(code,"SUBS\n");
            }
            else if(operand[0]==3){
                stackPush(stackTypes,3);
                code=addString(code,"SUBS\n");
            }
            else{
            fprintf(stderr,"ERROR 4: Chybna kombinace datovych typu\n");
            _errNumber=4;
            return 1;
            }
            break;
        case 5:
            if(operand[0]==2){
                stackPush(stackTypes,2);
                code=addString(code,"MULS\n");
            }
            else if(operand[0]==3){
                stackPush(stackTypes,3);
                code=addString(code,"MULS\n");
            }
            else{
            fprintf(stderr,"ERROR 4: Chybna kombinace datovych typu\n");
            _errNumber=4;
            return 1;
            }
            break;
        case 6:
            if(operand[0]==2){
                stackPush(stackTypes,3);
                code=addString(code,"CREATEFRAME\n");
                code=addString(code,"DEFVAR TF@&1\n");
                code=addString(code,"DEFVAR TF@&2\n");
                code=addString(code,"DEFVAR TF@&3\n");
                code=addString(code,"POPS TF@&1\n");
                code=addString(code,"POPS TF@&2\n");
                code=addString(code,"INT2FLOAT TF@&1 TF@&1\n");
                code=addString(code,"INT2FLOAT TF@&2 TF@&2\n");
                code=addString(code,"DIV TF@&3 TF@&2 TF@&1\n");
                code=addString(code,"PUSHS TF@&3\n");
            }
            else if(operand[0]==3){
                stackPush(stackTypes,3);
                code=addString(code,"DIVS\n");
            }
            else{
            fprintf(stderr,"ERROR 4: Chybna kombinace datovych typu\n");
            _errNumber=4;
            return 1;
            }
            break;
        case 7:
            if(operand[0]==2){
                stackPush(stackTypes,2);
                code=addString(code,"IDIVS\n");
            }
            else{
            fprintf(stderr,"ERROR 4: Chybna kombinace datovych typu\n");
            _errNumber=4;
            return 1;
            }
            break;
        case 8:
            stackPush(stackTypes,5);
            code=addString(code,"LTS\n");
            break;
        case 9:
            stackPush(stackTypes,5);
            code=addString(code,"CREATEFRAME\n");
            code=addString(code,"DEFVAR TF@&1\n");
            code=addString(code,"DEFVAR TF@&2\n");
            code=addString(code,"DEFVAR TF@&3\n");
            code=addString(code,"DEFVAR TF@&4\n");
            code=addString(code,"POPS TF@&1\n");
            code=addString(code,"POPS TF@&2\n");
            code=addString(code,"LT TF@&3 TF@&2 TF@&1\n");
            code=addString(code,"EQ TF@&4 TF@&2 TF@&1\n");
            code=addString(code,"OR TF@&2 TF@&3 TF@&4\n");
            code=addString(code,"PUSHS TF@&2\n");
            break;
        case 10:
            stackPush(stackTypes,5);
            code=addString(code,"GTS\n");
            break;
        case 11:
            stackPush(stackTypes,5);
            code=addString(code,"CREATEFRAME\n");
            code=addString(code,"DEFVAR TF@&1\n");
            code=addString(code,"DEFVAR TF@&2\n");
            code=addString(code,"DEFVAR TF@&3\n");
            code=addString(code,"DEFVAR TF@&4\n");
            code=addString(code,"POPS TF@&1\n");
            code=addString(code,"POPS TF@&2\n");
            code=addString(code,"GT TF@&3 TF@&2 TF@&1\n");
            code=addString(code,"EQ TF@&4 TF@&2 TF@&1\n");
            code=addString(code,"OR TF@&2 TF@&3 TF@&4\n");
            code=addString(code,"PUSHS TF@&2\n");
            break;
        case 12:
            stackPush(stackTypes,5);
            code=addString(code,"EQS\n");
            break;
        case 13:
            stackPush(stackTypes,5);
            code=addString(code,"EQS\nNOTS\n");
            break;
    }
    return 0;
}

int isRule(int rule[3]){
    if(rule[0]==14 && rule[1]==15 && rule[2]==13){
   //printf("pravidlo: 2\n");
        return 0;
    }
    else if(rule[0]==15 && rule[2]==15){
        switch (rule[1])
        {
        case 2:
       //printf("pravidlo: 3\n");
            return generate(3);
            break;
        case 3:
       //printf("pravidlo: 4\n");
            return generate(4);
            break;
        case 4:
       //printf("pravidlo: 5\n");
            return generate(5);
            break;
        case 5:
       //printf("pravidlo: 6\n");
            return generate(6);
            break;
        case 6:
       //printf("pravidlo: 7\n");
            return generate(7);
            break;
        case 7:
       //printf("pravidlo: 8\n");
            return generate(8);
            break;
        case 8:
       //printf("pravidlo: 9\n");
            return generate(9);
            break;
        case 9:
       //printf("pravidlo: 10\n");
            return generate(10);
            break;
        case 10:
       //printf("pravidlo: 11\n");
            return generate(11);
            break;
        case 11:
       //printf("pravidlo: 12\n");
            return generate(12);
            break;
        case 12:
       //printf("pravidlo: 13\n");
            return generate(13);
            break;
        default:
            fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
            _errNumber=2;
            return 1;
        }
    }
    else {
        fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
        _errNumber=2;
        return 1;
    }
}

int swapRule(tStack* s){

    int count=0;
    int rule[3];
    while(stackTop(s)!=21){
        if(count>2) {
            fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
            _errNumber=2;
            return 1;
        }
        rule[count]=stackPop(s);
        count++;
    }
    stackPop(s);
    if(count==1){
        if(rule[0]==1){
       //printf("pravidlo: 1\n");
            stackPush(s,15);
            char buffer[1000]={0};
        //printf("token:%d\n",preToken.type);
            if(preToken.type==1){
                if(frame>0){
                //printf("Search in LF for key:%s\n",preToken._string);
                    if(htSearch(LFvar[frame-1],preToken._string)==NULL){
                    //printf("LF nie\n");
                    //printf("Search in GF for key:%s\n",preToken._string);
                        if(htSearch(GFvar,preToken._string)==NULL){
                            fprintf(stderr,"ERROR 3: Nedefinovana premenna\n");
                            _errNumber=3;
                            return 1;
                        }
                        else {
                            stackPush(stackTypes,htRead(GFvar,preToken._string));
                            sprintf(buffer,"PUSHS GF@%s\n",preToken._string);
                            code=addString(code,buffer);                  
                        }
                    }
                    else {
                        stackPush(stackTypes,htRead(LFvar[frame-1],preToken._string));
                        sprintf(buffer,"PUSHS LF@%s\n",preToken._string);
                        code=addString(code,buffer);
                    }
                }
                else{
                //printf("Search in GF for key:%s\n",preToken._string);
                    if(htSearch(GFvar,preToken._string)==NULL){
                        fprintf(stderr,"ERROR 3: Nedefinovana premenna\n");
                        _errNumber=3;
                        return 1;
                    }
                    else {
                        stackPush(stackTypes,htRead(GFvar,preToken._string));
                        sprintf(buffer,"PUSHS GF@%s\n",preToken._string);
                        code=addString(code,buffer);
                    }
                }
            }
            else {
                stackPush(stackTypes,preToken.type);
                if(stackTop(stackTypes)==2){
                    sprintf(buffer,"PUSHS int@%d\n",preToken._int);
                    code=addString(code,buffer);
                }
                else if(stackTop(stackTypes)==3){
                    sprintf(buffer,"PUSHS float@%a\n",preToken._float);
                    code=addString(code,buffer);
                }
                else if(stackTop(stackTypes)==4){
                    code=addString(code,"PUSHS string@");
                    for(int i=0;preToken._string[i]!=0;i++){
                        if(preToken._string[i]==35||preToken._string[i]==92||(preToken._string[i]<=32 && preToken._string[i]>0)){
                            sprintf(buffer,"\\0%d",preToken._string[i]);
                            code=addString(code,buffer);
                        }
                        else {
                            sprintf(buffer,"%c",preToken._string[i]);
                            code=addString(code,buffer);
                        }
                    }
                    code=addString(code,"\n");
                }
                else {
                    sprintf(buffer,"PUSHS int@%d\n",preToken._int);
                    code=addString(code,"PUSHS nil@nil\n");
                }
            }
        }
        else  {
            fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
            _errNumber=2;
            return 1;
        }
    }
    else if(count==3){
        if((isRule(rule))==0) stackPush(s,15);
        else return 1;
    }
    else {
        fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
        _errNumber=2;
        return 1;
    }

    return 0;
}

int _exp(){
    
//printf("Vchadzam do exp %d\n",token.type);

    int my_exp_table[15][15]={
    //    $   t   +   -   *   /   //  <   <=  >   >=  ==  !=  (   ) 
        { 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20 }, // $
        { 22, 20, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 20, 22 }, // t
        { 22, 21, 22, 22, 21, 21, 21, 22, 22, 22, 22, 22, 22, 21, 22 }, // +
        { 22, 21, 22, 22, 21, 21, 21, 22, 22, 22, 22, 22, 22, 21, 22 }, // -
        { 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 21, 22 }, // *
        { 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 21, 22 }, // /
        { 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 21, 22 }, // //
        { 22, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 21, 22 }, // <
        { 22, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 21, 22 }, // <=
        { 22, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 21, 22 }, // >
        { 22, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 21, 22 }, // >=
        { 22, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 21, 22 }, // ==
        { 22, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 21, 22 }, // !=
        { 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 23 }, // (
        { 22, 20, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 20, 22 }  // )
    };
    stackTypes=stackInit();
    if(stackTypes==NULL) {
        fprintf(stderr,"ERROR 2: Chyba alokace pamati\n");
        _errNumber=99;
        return 1;
    }

    tStack* stackExp=stackInit();
    if(stackExp==NULL) {
        fprintf(stderr,"ERROR 2: Chyba alokace pamati\n");
        _errNumber=99;
        return 1;
    }

    stackPush(stackExp,0);

    int a=top(stackExp),b=getNumber(token.type);
    if(b==-1){
        stackFree(stackExp);
        stackFree(stackTypes);
        fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
        _errNumber=2;
        return 1;
    }
    do{
   //printf("a=%d b=%d exp=%d\n",a,b,my_exp_table[a][b]);
        switch(my_exp_table[a][b]){
            case 23:
                stackPush(stackExp,b);
                if(getToken()!=0){
                    stackFree(stackExp);
                    stackFree(stackTypes);
                    _errNumber=1;
                    return 1;
                }
                b=getNumber(token.type);
                if(b==-1){
                    stackFree(stackExp);
                    stackFree(stackTypes);
                    fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
                    _errNumber=2;
                    return 1;
                }
                break;
            case 21:
                if(stackTop(stackExp)==a) stackPush(stackExp,21);
                else{
                    int tmp=stackPop(stackExp);
                    stackPush(stackExp,21);
                    stackPush(stackExp,tmp);
                }
                stackPush(stackExp,b);
                if(getToken()!=0){
                    stackFree(stackExp);
                    stackFree(stackTypes);
                    _errNumber=1;
                    return 1;
                }
                b=getNumber(token.type);
                if(b==-1){
                    stackFree(stackExp);
                    stackFree(stackTypes);
                    fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
                    _errNumber=2;
                    return 1;
                }
                break;
            case 22:
                if(swapRule(stackExp)!=0) return 1;
                break;
            default:
                fprintf(stderr,"ERROR 2: Zle zapisany vyraz\n");
                _errNumber=2;
                return 1;
        }
        a=top(stackExp);

    }while(!(a==0 && b==0));
    typExp=stackPop(stackTypes);
    stackFree(stackExp);
    stackFree(stackTypes);
    code=addString(code,"CREATEFRAME\n");
    code=addString(code,"DEFVAR TF@&1\n");
    code=addString(code,"POPS TF@&1\n");
    return 0;
}

int body();

int ret(){

//printf("Vchadzam do ret %d\n",token.type);
    if(token.type==TT_EOL) return 0;
    return _exp();
}

int term(){

    char buffer[1000];
    termsCount++;
//printf("Vchadzam do term %d\n",token.type);
    switch(token.type){
        case TT_ID:
            sprintf(buffer,"DEFVAR TF@&%d\nMOVE TF@&%d GF@%s\n",termsCount,termsCount,token._string);
            code=addString(code,buffer);
            break;
        case TT_VALUE_INT:
            sprintf(buffer,"DEFVAR TF@&%d\nMOVE TF@&%d int@%d\n",termsCount,termsCount,token._int);
            code=addString(code,buffer);
            break;
        case TT_VALUE_DOUBLE:
            sprintf(buffer,"DEFVAR TF@&%d\nMOVE TF@&%d float@%a\n",termsCount,termsCount,token._float);
            code=addString(code,buffer);
            break;
        case TT_VALUE_STRING:
            sprintf(buffer,"DEFVAR TF@&%d\nMOVE TF@&%d string@",termsCount,termsCount);
            code=addString(code,buffer);
            for(int i=0;token._string[i]!=0;i++){
                if(token._string[i]==35||token._string[i]==92||(token._string[i]<=32 && token._string[i]>0)){
                    sprintf(buffer,"\\0%d",token._string[i]);
                    code=addString(code,buffer);
                }
                else {
                    sprintf(buffer,"%c",token._string[i]);
                    code=addString(code,buffer);
                }
            }
            code=addString(code,"\n");
            break;
        case TT_NONE:
            sprintf(buffer,"DEFVAR TF@&%d\nMOVE TF@&%d nil@nil\n",termsCount,termsCount);
            code=addString(code,buffer);
            break;
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Zle zapisane parametre volanej funkcie\n"); return 1;
    }
    if(getToken()!=0){
        _errNumber=1;
        return 1;
    }
 //printf("Pokryl som TERM %d\n",token.type);
    return 0;
}

int term_n(){

//printf("Vchadzam do term_n %d\n",token.type);
    switch(token.type){
        case TT_COMMA:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som , %d\n",token.type);
            return !(term()==0 && term_n()==0);
        case TT_RIGHT_BRACKET:
            return 0;
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Zle zapisane parametre volanej funkcie\n"); return 1;
    }
}

int terms(){

//printf("Vchadzam do terms %d\n",token.type);
    switch(token.type){
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE: return !(term()==0 && term_n()==0);
        case TT_RIGHT_BRACKET: return 0;
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Zle zapisane parametre volanej funkcie\n"); return 1;
    }
}

int param_n(){

//printf("Vchadzam do param_n %d\n",token.type);
    switch(token.type){
        case TT_COMMA:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som , %d\n",token.type);
            if(token.type==TT_ID){
                if(getToken()!=0){
                    _errNumber=1;
                    return 1;
                }
           //printf("Pokryl som ID %d\n",token.type);
                return param_n();
            }
            _errNumber=2;
            return 1;
        case TT_RIGHT_BRACKET:
            return 0;
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Zle zapisane parametre funkcie\n"); return 1;
    }
}

int params(){

//printf("Vchadzam do params %d\n",token.type);
    switch(token.type){
        case TT_ID:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som ID %d\n",token.type);
            return param_n();
        case TT_RIGHT_BRACKET:
            return 0;
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Zle zapisane parametre funkcie\n"); return 1;
    }
}

int value(char* id){

//printf("Vchadzam do value %s %d\n",id,token.type);
    if(token.type==TT_ID){
        char* funcId=token._string;
        if(getToken()!=0){
            _errNumber=1;
            return 1;
        }
        if(token.type==TT_LEFT_BRACKET){
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som ID %d\n",token.type);
        //printf("Pokryl som ( %d\n",token.type);
            termsCount=0;
            code=addString(code,"CREATEFRAME\n");
            if(terms()==0){
                if(token.type==TT_RIGHT_BRACKET){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                  //printf("%s %d\n",id, termsCount);
                    if(strcmp(funcId,"print")==0){
                        char buffer[1000];
                        for(int i=0;i<termsCount;i++){
                            sprintf(buffer,"WRITE TF@&%d\n",i+1);
                            code=addString(code,buffer);
                        }
                    }
               //printf("Pokryl som ) %d\n",token.type);
                    return 0;
                }
            }
            else return 1;
        }
        else ungetToken();
    }
    switch(token.type){
        case TT_LEFT_BRACKET:
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE: 
            if(_exp()==0){
                char buffer[1000];
                if(frame==0) {
                    if(htSearch(GFvar,id)==NULL){
                        sprintf(buffer,"DEFVAR GF@%s\n",id);
                        code=addString(code,buffer);
                    }
                    sprintf(buffer,"MOVE GF@%s TF@&1\n",id);
                    code=addString(code,buffer);
                    htInsert(GFvar,id,typExp);

                }
                else {
                    if(htSearch(GFvar,id)==NULL){
                        sprintf(buffer,"DEFVAR LF@%s\n",id);
                        code=addString(code,buffer);
                    }
                    sprintf(buffer,"MOVE LF@%s TF@&1\n",id);
                    code=addString(code,buffer);
                    htInsert(LFvar[frame-1],id,typExp);
                }
                return 0;
            }
            else return 1;
        default: 
            _errNumber=2;
            fprintf(stderr,"ERROR 2: Zle zapisany prikaz\n");
            return 1;
    }
}

int state(char* id){

//printf("Vchadzam do state %s %d\n",id,token.type);
    switch(token.type){
        case TT_LEFT_BRACKET:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            termsCount=0;
            code=addString(code,"CREATEFRAME\n");
       //printf("Pokryl som ( %d\n",token.type);
            if(terms()==0){
                if(token.type==TT_RIGHT_BRACKET){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                //printf("%s %d\n",id, termsCount);
                    if(strcmp(id,"print")==0){
                        char buffer[1000];
                        for(int i=0;i<termsCount;i++){
                            sprintf(buffer,"WRITE TF@&%d\n",i+1);
                            code=addString(code,buffer);
                        }
                    }
               //printf("Pokryl som ) %d\n",token.type);
                    return 0;
                }
            }
            else return 1;
        case TT_ASSIGN:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som = %d\n",token.type);
            return value(id);
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Zle zapisany prikaz\n"); return 1;
    } 
}

int line(){

//printf("Vchadzam do line %d\n", token.type);
    switch(token.type){
        case TT_LEFT_BRACKET:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE:
            if(_exp()==0){
                if(token.type==TT_EOL){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                    return 0;
                }
            }
            else return 1;
        default: break;
    }
    if(token.type==TT_ID){
        if(getToken()!=0){
            _errNumber=1;
            return 1;
        }
        if((getNumber(token.type)>=2 && getNumber(token.type)<=12)|| token.type==TT_EOL){
            ungetToken();
            if(_exp()==0){
                if(token.type==TT_EOL){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                    return 0;
                }
            }
            else return 1;
        }
        else{
            ungetToken();
        }
    }
    char* id=NULL;
    switch(token.type){
        case TT_ID:
            id=token._string;
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som ID %s %d\n",id,token.type);
            if(state(id)==0){
                if(token.type==TT_EOL) {
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
               //printf("Pokryl som EOL %d\n",token.type);
                    return 0;
                } 
            }
            else return 1;
            _errNumber=2;
            fprintf(stderr,"ERROR 2: Zle zapisany prikaz (chybajuci EOL)\n");
            return 1;
        case TT_PASS:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som PASS %d\n",token.type);
            if(token.type==TT_EOL){
                if(getToken()!=0){
                    _errNumber=1;
                    return 1;
                }
           //printf("Pokryl som EOL %d\n",token.type);
                return 0;
            }
            _errNumber=2;
            fprintf(stderr,"ERROR 2: Zle zapisany prikaz PASS\n");
            return 1;
        case TT_RETURN:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som RETURN %d\n",token.type);
            if(ret()==0){
                if(token.type==TT_EOL) {
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
               //printf("Pokryl som EOL %d\n",token.type);
                    if(frame==0){
                        _errNumber=6;
                        fprintf(stderr,"ERROR 6: RETURN na globalnej urovni\n");
                        return 1;
                    }
                    return 0;
                } 
            }
            else return 1;
            _errNumber=2;
            fprintf(stderr,"ERROR 2: Zle zapisany prikaz RETURN\n");
            return 1;
        case TT_IF:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som IF %d\n",token.type);
            if(_exp()==0){
                if(token.type==TT_COLON){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                //printf("Pokryl som COLON %d\n",token.type);
                    if(token.type==TT_EOL){
                        if(getToken()!=0){
                            _errNumber=1;
                            return 1;
                        }
                    //printf("Pokryl som EOL %d\n",token.type);
                        if(token.type==TT_INDENT){
                            if(getToken()!=0){
                                _errNumber=1;
                                return 1;
                            }
                        //printf("Pokryl som INDENT %d\n",token.type);
                            if(body()==0){
                                if(token.type==TT_DEDENT){
                                    if(getToken()!=0){
                                        _errNumber=1;
                                        return 1;
                                    }
                                //printf("Pokryl som DEDENT %d\n",token.type);
                                    if(token.type==TT_ELSE){
                                        if(getToken()!=0){
                                            _errNumber=1;
                                            return 1;
                                        }
                                    //printf("Pokryl som ELSE %d\n",token.type);
                                        if(token.type==TT_COLON){
                                            if(getToken()!=0){
                                                _errNumber=1;
                                                return 1;
                                            }
                                        //printf("Pokryl som COLON %d\n",token.type);
                                            if(token.type==TT_EOL){
                                                if(getToken()!=0){
                                                    _errNumber=1;
                                                    return 1;
                                                }
                                            //printf("Pokryl som EOL %d\n",token.type);
                                                if(token.type==TT_INDENT){
                                                    if(getToken()!=0){
                                                        _errNumber=1;
                                                        return 1;
                                                    }
                                                //printf("Pokryl som INDENT %d\n",token.type);
                                                    if(body()==0){
                                                        if(token.type==TT_DEDENT){
                                                            if(getToken()!=0){
                                                                _errNumber=1;
                                                                return 1;
                                                            }
                                                        //printf("Pokryl som DEDENT %d\n",token.type);
                                                            return 0;
                                                        }
                                                    }
                                                    else return 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else return 1;
                        }
                    }
                }
            }
            else return 1;
            _errNumber=2;
            fprintf(stderr,"ERROR 2: Zle zapisany prikaz IF\n");
            return 1;
        case TT_WHILE:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som WHILE %d\n",token.type);
            if(_exp()==0){
                if(token.type==TT_COLON){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                //printf("Pokryl som COLON %d\n",token.type);
                    if(token.type==TT_EOL){
                        if(getToken()!=0){
                            _errNumber=1;
                            return 1;
                        }
                    //printf("Pokryl som EOL %d\n",token.type);
                        if(token.type==TT_INDENT){
                            if(getToken()!=0){
                                _errNumber=1;
                                return 1;
                            }
                        //printf("Pokryl som INDENT %d\n",token.type);
                            if(body()==0){
                                if(token.type==TT_DEDENT){
                                    if(getToken()!=0){
                                        _errNumber=1;
                                        return 1;
                                    }
                                //printf("Pokryl som DEDENT %d\n",token.type);
                                    return 0;
                                }
                            }
                            else return 1;
                        }
                    }
                }
            }
            else return 1;
            _errNumber=2;
            fprintf(stderr,"ERROR 2: Zle zapisany prikaz WHILE\n");
            return 1;
        case TT_DEF:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
       //printf("Pokryl som DEF %d\n",token.type);
            if(token.type==TT_ID){
                if(getToken()!=0){
                    _errNumber=1;
                    return 1;
                }
           //printf("Pokryl som ID %d\n",token.type);
                if(token.type==TT_LEFT_BRACKET){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
               //printf("Pokryl som ( %d\n",token.type);
                    if(params()==0){
                        if(token.type==TT_RIGHT_BRACKET){
                            if(getToken()!=0){
                                _errNumber=1;
                                return 1;
                            }
                       //printf("Pokryl som ) %d\n",token.type);
                            if(token.type==TT_COLON){
                                if(getToken()!=0){
                                    _errNumber=1;
                                    return 1;
                                }
                           //printf("Pokryl som COLON %d\n",token.type);
                                if(token.type==TT_EOL){
                                    if(getToken()!=0){
                                        _errNumber=1;
                                        return 1;
                                    }
                               //printf("Pokryl som EOL %d\n",token.type);
                                    if(token.type==TT_INDENT){
                                        if(getToken()!=0){
                                            _errNumber=1;
                                            return 1;
                                        }
                                        frame++;
                                        LFfunc[frame-1]=htInit();
                                        if(LFfunc[frame-1]==NULL){
                                            _errNumber=99;
                                            return 1;
                                        }
                                        LFvar[frame-1]=htInit();
                                        if(LFvar[frame-1]==NULL){
                                            _errNumber=99;
                                            return 1;
                                        }
                                   //printf("Pokryl som INDENT %d\n",token.type);
                                        int r=body();
                                        htFree(LFfunc[frame-1]);
                                        htFree(LFvar[frame-1]);
                                        frame--;
                                        if(r==0){
                                            if(token.type==TT_DEDENT){
                                                if(getToken()!=0){
                                                    _errNumber=1;
                                                    return 1;
                                                }

                                           //printf("Pokryl som DEDENT %d\n",token.type);
                                                return 0;
                                            }
                                        }
                                        else return 1;
                                    }
                                }
                            }
                        }
                    }
                    else return 1;
                }
            }
            _errNumber=2;
            fprintf(stderr,"ERROR 2: Zle zapisana deklaracia funkcie\n");
            return 1;
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Neznamy prikaz\n"); return 1;
    }
}

int line_n(){

//printf("Vchadzam do line_n %d\n", token.type);
    switch(token.type){
        case TT_EOF:
        case TT_DEDENT: return 0;
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE:
        case TT_LEFT_BRACKET:
        case TT_PASS:
        case TT_RETURN:
        case TT_IF:
        case TT_WHILE:
        case TT_DEF: return !(line()==0 && line_n()==0);
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Neznamy prikaz\n"); return 1;
    }    
}

int body(){

//printf("Vchadzam do budy %d\n", token.type);
    switch(token.type){
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE:
        case TT_LEFT_BRACKET:
        case TT_PASS:
        case TT_RETURN:
        case TT_IF:
        case TT_WHILE:
        case TT_DEF: return !(line()==0 && line_n()==0);
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Neznamy prikaz\n"); return 1;
    }
}

int checkSyntax(){

    code=stringInit();
    code=addString(code,".IFJcode19\n");
    GFfunc=htInit();
    if(GFfunc==NULL){
        _errNumber=99;
        return 1;
    }
    GFvar=htInit();
    if(GFvar==NULL){
        _errNumber=99;
        return 1;
    }

    if(getToken()!=0){
        _errNumber=1;
        return 1;
    }
    int r;
    switch(token.type){
        case TT_EOF: htFree(GFfunc); htFree(GFvar); return 0;
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE:
        case TT_LEFT_BRACKET:
        case TT_PASS:
        case TT_RETURN:
        case TT_IF:
        case TT_WHILE:
        case TT_DEF:
            r=body();
            htFree(GFfunc); 
            htFree(GFvar);
            return r;
        default: _errNumber=2; fprintf(stderr,"ERROR 2: Neznamy prikaz\n"); return 1;
    }
}