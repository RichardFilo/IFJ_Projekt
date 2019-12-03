
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

int _errNumber=0;

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

int isRule(int rule[3]){
    if(rule[0]==14 && rule[1]==15 && rule[2]==13){
        printf("pravidlo: 2\n");
        return 2;
    }
    else if(rule[0]==15 && rule[2]==15){
        switch (rule[1])
        {
        case 2:
            printf("pravidlo: 3\n");
            return 3;
            break;
        case 3:
            printf("pravidlo: 4\n");
            return 4;
            break;
        case 4:
            printf("pravidlo: 5\n");
            return 5;
            break;
        case 5:
            printf("pravidlo: 6\n");
            return 6;
            break;
        case 6:
            printf("pravidlo: 7\n");
            return 7;
            break;
        case 7:
            printf("pravidlo: 8\n");
            return 8;
            break;
        case 8:
            printf("pravidlo: 9\n");
            return 9;
            break;
        case 9:
            printf("pravidlo: 10\n");
            return 10;
            break;
        case 10:
            printf("pravidlo: 11\n");
            return 11;
            break;
        case 11:
            printf("pravidlo: 12\n");
            return 12;
            break;
        case 12:
            printf("pravidlo: 13\n");
            return 13;
            break;
        default:
            return 0;
        }
    }
    else return 0;
}

int swapRule(tStack* s){

    int count=0;
    int rule[3];
    while(stackTop(s)!=21){
        if(count>2) {
            printf("1\n");
            return 2;
        }
        rule[count]=stackPop(s);
        count++;
    }
    stackPop(s);
    if(count==1){
        if(rule[0]==1){
            printf("pravidlo: 1\n");
            stackPush(s,15);
        }
        else  {
            printf("2\n");
            return 2;
        }
    }
    else if(count==3){
        if(isRule(rule)) stackPush(s,15);
        else {
            printf("%d %d %d\n",rule[0],rule[1],rule[2]);            
            return 2;
        }
    }
    else {
        printf("4\n");
        return 2;
    }

    return 0;
}

int _exp(){
    
    printf("Vchadzam do exp %d\n",token.type);

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

    tStack* stackExp=stackInit();
    if(stackExp==NULL) {
        fprintf(stderr,"ERROR 2: Chyba alokace pamati\n");
        return 99;
    }

    stackPush(stackExp,0);

    int a=top(stackExp),b=getNumber(token.type);
    if(b==-1){
        stackFree(stackExp);
        fprintf(stderr,"ERROR 2: Zle zapisany vyraz1\n");
        return 2;
    }
    do{
 //       printf("a=%d b=%d exp=%d\n",a,b,my_exp_table[a][b]);
        switch(my_exp_table[a][b]){
            case 23:
                stackPush(stackExp,b);
                if(getToken()!=0){
                    stackFree(stackExp);
                    return 1;
                }
                b=getNumber(token.type);
                if(b==-1){
                    stackFree(stackExp);
                    fprintf(stderr,"ERROR 2: Zle zapisany vyraz2\n");
                    return 2;
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
                    return 1;
                }
                b=getNumber(token.type);
                if(b==-1){
                    stackFree(stackExp);
                    fprintf(stderr,"ERROR 2: Zle zapisany vyraz3\n");
                    return 2;
                }
                break;
            case 22:
                if(swapRule(stackExp)){
                    stackFree(stackExp);
                    fprintf(stderr,"ERROR 2: Zle zapisany vyraz4\n");
                    return 2;
                }
                break;
            default:
                fprintf(stderr,"ERROR 2: Zle zapisany vyraz5\n");
                return 1;
        }
        a=top(stackExp);

    }while(!(a==0 && b==0));
    return 0;
}

int body();

int ret(){

    printf("Vchadzam do ret %d\n",token.type);
    if(token.type==TT_EOL) return 0;
    switch(_exp()){
        case 0:
            return 0;
        case 1:
            _errNumber=1;
            return 1;
        case 2:
            _errNumber=2;
            return 2;
        default:
            _errNumber=99;
            return 1;
    }
}

int term(){

    printf("Vchadzam do term %d\n",token.type);
    switch(token.type){
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som TERM %d\n",token.type);
            return 0;
        default: _errNumber=2; return 1;
    }
}

int term_n(){

    printf("Vchadzam do term_n %d\n",token.type);
    switch(token.type){
        case TT_COMMA:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som , %d\n",token.type);
            return !(term()==0 && term_n()==0);
        case TT_RIGHT_BRACKET:
            return 0;
        default: _errNumber=2; return 1;
    }
}

int terms(){

    printf("Vchadzam do terms %d\n",token.type);
    switch(token.type){
        case TT_ID:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE: return !(term()==0 && term_n()==0);
        case TT_RIGHT_BRACKET: return 0;
        default: _errNumber=2; return 1;
    }
}

int param_n(){

    printf("Vchadzam do param_n %d\n",token.type);
    switch(token.type){
        case TT_COMMA:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som , %d\n",token.type);
            if(token.type==TT_ID){
                if(getToken()!=0){
                    _errNumber=1;
                    return 1;
                }
                printf("Pokryl som ID %d\n",token.type);
                return param_n();
            }
            _errNumber=2;
            return 1;
        case TT_RIGHT_BRACKET:
            return 0;
        default: _errNumber=2; return 1;
    }
}

int params(){

    printf("Vchadzam do params %d\n",token.type);
    switch(token.type){
        case TT_ID:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som ID %d\n",token.type);
            return param_n();
        case TT_RIGHT_BRACKET:
            return 0;
        default: _errNumber=2; return 1;
    }
}

int value(){

    printf("Vchadzam do value %d\n",token.type);
    if(token.type==TT_ID){
        if(getToken()!=0){
            _errNumber=1;
            return 1;
        }
        if(token.type==TT_LEFT_BRACKET){
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som ID %d\n",token.type);
            printf("Pokryl som ( %d\n",token.type);
            if(terms()==0){
                if(token.type==TT_RIGHT_BRACKET){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                    printf("Pokryl som ) %d\n",token.type);
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
            switch(_exp()){
                case 0:
                    return 0;
                case 1:
                    _errNumber=1;
                    return 1;
                case 2:
                    _errNumber=2;
                    return 2;
                default:
                    _errNumber=99;
                    return 1;
            }
        default: 
            _errNumber=2;
            return 1;
    }
}

int state(){

    printf("Vchadzam do state %d\n",token.type);
    switch(token.type){
        case TT_LEFT_BRACKET:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som ( %d\n",token.type);
            if(terms()==0){
                if(token.type==TT_RIGHT_BRACKET){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                    printf("Pokryl som ) %d\n",token.type);
                    return 0;
                }
            }
            else return 1;
        case TT_ASSIGN:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som = %d\n",token.type);
            return value();
        default: _errNumber=2; return 1;
    } 
}

int line(){

    printf("Vchadzam do line %d\n", token.type);
    switch(token.type){
        case TT_LEFT_BRACKET:
        case TT_VALUE_INT:
        case TT_VALUE_DOUBLE:
        case TT_VALUE_STRING:
        case TT_NONE:
            switch(_exp()){
                case 0:
                    if(token.type==TT_EOL){
                        if(getToken()!=0){
                            _errNumber=1;
                            return 1;
                        }
                        return 0;
                    }
                    _errNumber=2;
                    return 1;
                case 1:
                    _errNumber=1;
                    return 1;
                case 2:
                    _errNumber=2;
                    return 2;
                default:
                    _errNumber=99;
                    return 1;
            }
        default: break;
    }
    if(token.type==TT_ID){
        if(getToken()!=0){
            _errNumber=1;
            return 1;
        }
        if(getNumber(token.type)>=2 && getNumber(token.type)<=12){
            ungetToken();
            switch(_exp()){
                case 0:
                    if(token.type==TT_EOL){
                        if(getToken()!=0){
                            _errNumber=1;
                            return 1;
                        }
                        return 0;
                    }
                    _errNumber=2;
                    return 1;
                case 1:
                    _errNumber=1;
                    return 1;
                case 2:
                    _errNumber=2;
                    return 2;
                default:
                    _errNumber=99;
                    return 1;
            }
        }
        else{
            ungetToken();
        }
    }
    switch(token.type){
        case TT_ID:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som ID %d\n",token.type);
            if(state()==0){
                if(token.type==TT_EOL) {
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                    printf("Pokryl som EOL %d\n",token.type);
                    return 0;
                } 
            }
            else return 1;
            _errNumber=2;
            return 1;
        case TT_PASS:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som PASS %d\n",token.type);
            if(token.type==TT_EOL){
                if(getToken()!=0){
                    _errNumber=1;
                    return 1;
                }
                printf("Pokryl som EOL %d\n",token.type);
                return 0;
            }
            _errNumber=2;
            return 1;
        case TT_RETURN:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som RETURN %d\n",token.type);
            if(ret()==0){
                if(token.type==TT_EOL) {
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                    printf("Pokryl som EOL %d\n",token.type);
                    return 0;
                } 
            }
            else return 1;
            _errNumber=2;
            return 1;
        case TT_IF:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som IF %d\n",token.type);
            switch(_exp()){                
                case 0:
                    if(token.type==TT_COLON){
                        if(getToken()!=0){
                            _errNumber=1;
                            return 1;
                        }
                        printf("Pokryl som COLON %d\n",token.type);
                        if(token.type==TT_EOL){
                            if(getToken()!=0){
                                _errNumber=1;
                                return 1;
                            }
                            printf("Pokryl som EOL %d\n",token.type);
                            if(token.type==TT_INDENT){
                                if(getToken()!=0){
                                    _errNumber=1;
                                    return 1;
                                }
                                printf("Pokryl som INDENT %d\n",token.type);
                                if(body()==0){
                                    if(token.type==TT_DEDENT){
                                        if(getToken()!=0){
                                            _errNumber=1;
                                            return 1;
                                        }
                                        printf("Pokryl som DEDENT %d\n",token.type);
                                        if(token.type==TT_ELSE){
                                            if(getToken()!=0){
                                                _errNumber=1;
                                                return 1;
                                            }
                                            printf("Pokryl som ELSE %d\n",token.type);
                                            if(token.type==TT_COLON){
                                                if(getToken()!=0){
                                                    _errNumber=1;
                                                    return 1;
                                                }
                                                printf("Pokryl som COLON %d\n",token.type);
                                                if(token.type==TT_EOL){
                                                    if(getToken()!=0){
                                                        _errNumber=1;
                                                        return 1;
                                                    }
                                                    printf("Pokryl som EOL %d\n",token.type);
                                                    if(token.type==TT_INDENT){
                                                        if(getToken()!=0){
                                                            _errNumber=1;
                                                            return 1;
                                                        }
                                                        printf("Pokryl som INDENT %d\n",token.type);
                                                        if(body()==0){
                                                            if(token.type==TT_DEDENT){
                                                                if(getToken()!=0){
                                                                    _errNumber=1;
                                                                    return 1;
                                                                }
                                                                printf("Pokryl som DEDENT %d\n",token.type);
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
                    break;
                case 1:
                    _errNumber=1;
                    return 1;
                case 2:
                    _errNumber=2;
                    return 2;
                default:
                    _errNumber=99;
                    return 1;
            }
            _errNumber=2;
            return 1;
        case TT_WHILE:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som WHILE %d\n",token.type);
            switch(_exp()){
                case 0:
                    if(token.type==TT_COLON){
                        if(getToken()!=0){
                            _errNumber=1;
                            return 1;
                        }
                        printf("Pokryl som COLON %d\n",token.type);
                        if(token.type==TT_EOL){
                            if(getToken()!=0){
                                _errNumber=1;
                                return 1;
                            }
                            printf("Pokryl som EOL %d\n",token.type);
                            if(token.type==TT_INDENT){
                                if(getToken()!=0){
                                    _errNumber=1;
                                    return 1;
                                }
                                printf("Pokryl som INDENT %d\n",token.type);
                                if(body()==0){
                                    if(token.type==TT_DEDENT){
                                        if(getToken()!=0){
                                            _errNumber=1;
                                            return 1;
                                        }
                                        printf("Pokryl som DEDENT %d\n",token.type);
                                        return 0;
                                    }
                                }
                                else return 1;
                            }
                        }
                    }
                    break;
                case 1:
                    _errNumber=1;
                    return 1;
                case 2:
                    _errNumber=2;
                    return 2;
                default:
                    _errNumber=99;
                    return 1;
            }
            _errNumber=2;
            return 1;
        case TT_DEF:
            if(getToken()!=0){
                _errNumber=1;
                return 1;
            }
            printf("Pokryl som DEF %d\n",token.type);
            if(token.type==TT_ID){
                if(getToken()!=0){
                    _errNumber=1;
                    return 1;
                }
                printf("Pokryl som ID %d\n",token.type);
                if(token.type==TT_LEFT_BRACKET){
                    if(getToken()!=0){
                        _errNumber=1;
                        return 1;
                    }
                    printf("Pokryl som ( %d\n",token.type);
                    if(params()==0){
                        if(token.type==TT_RIGHT_BRACKET){
                            if(getToken()!=0){
                                _errNumber=1;
                                return 1;
                            }
                            printf("Pokryl som ) %d\n",token.type);
                            if(token.type==TT_COLON){
                                if(getToken()!=0){
                                    _errNumber=1;
                                    return 1;
                                }
                                printf("Pokryl som COLON %d\n",token.type);
                                if(token.type==TT_EOL){
                                    if(getToken()!=0){
                                        _errNumber=1;
                                        return 1;
                                    }
                                    printf("Pokryl som EOL %d\n",token.type);
                                    if(token.type==TT_INDENT){
                                        if(getToken()!=0){
                                            _errNumber=1;
                                            return 1;
                                        }
                                        printf("Pokryl som INDENT %d\n",token.type);
                                        if(body()==0){
                                            if(token.type==TT_DEDENT){
                                                if(getToken()!=0){
                                                    _errNumber=1;
                                                    return 1;
                                                }
                                                printf("Pokryl som DEDENT %d\n",token.type);
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
            return 1;
        default: _errNumber=2; return 1;
    }
}

int line_n(){

    printf("Vchadzam do line_n %d\n", token.type);
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
        default: _errNumber=2; return 1;
    }    
}

int body(){

    printf("Vchadzam do budy %d\n", token.type);
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
        default: _errNumber=2; return 1;
    }
}

int checkSyntax(){

    if(getToken()!=0){
        _errNumber=1;
        return 1;
    }
    printf("Zacinam SA %d\n",token.type);
    switch(token.type){
        case TT_EOF: return 0;
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
        case TT_DEF: return body();
        default: _errNumber=2; return 1;
    }
}