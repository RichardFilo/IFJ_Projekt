#include"../projekt/scanner.h"

int main(int argc, char* argv[]){
/*
	tStack* s=stackInit();

	for(int i=1; i<argc; i++){
		stackPush(s,strlen(argv[i]));
		char* str=stringCreate(argv[i]);
		str[0]=i+(int)'0';
		printf("%s\n",str);
		stringFree(str);
	}

	while(!stackEmpty(s)) printf("%d	",stackPop(s));

	printf("\n");

	char buffer[10]={0};

	addChar(buffer,'R');
	addChar(buffer,'i');
	addChar(buffer,'s');
	addChar(buffer,'o');

	char* st=stringCreate(buffer);
	printf("%s\n",st);
	stringFree(st);
	stackFree(s);
*/
	if(argc==2){
		if(scannerInit(argv[1])) return 99;
	}
	else if(scannerInit("stdin")) return 99;

	if(getToken()==1) {
		scannerFree();
		return 1;
	}
	while(token.type!=TT_EOF){
		
		if(token.type==1) {
			printf("ID:%s\n",token._string);
		}
		
		else if(token.type==2){
			printf("INT:%d\n",token._int);
		}
		else if(token.type==3){
			printf("FLOAT:%g\n",token._float);
		}
		else if(token.type==4){
			printf("STRING:'%s'\n",token._string);
		}
		else if(token.type==5){
			printf("KW:def\n");
		}
		else if(token.type==6){
			printf("KW:else\n");
		}
		else if(token.type==7){
			printf("KW:if\n");
		}
		else if(token.type==8){
			printf("KW:none\n");
		}
		else if(token.type==9){
			printf("KW:pass\n");
		}
		else if(token.type==10){
			printf("KW:return\n");
		}
		else if(token.type==11){
			printf("KW:while\n");
		}
		else if(token.type==12){
			printf("EOL\n");
		}
		else if(token.type==13){
			printf("COLON\n");
		}
		else if(token.type==14){
			printf("INDENT\n");
		}
		else if(token.type==15){
			printf("DEDENT\n");
		}
		else if(token.type==16){
			printf("LEFT BRACKET\n");
		}
		else if(token.type==17){
			printf("RIGHT BRACKET\n");
		}
		else if(token.type==18){
			printf("COMMA\n");
		}
		else if(token.type==19){
			printf("OPERATOR:'*'\n");
		}
		else if(token.type==20){
			printf("OPERATOR:'//'\n");
		}
		else if(token.type==21){
			printf("OPERATOR:'/'\n");
		}
		else if(token.type==22){
			printf("OPERATOR:'+'\n");
		}
		else if(token.type==23){
			printf("OPERATOR:'-'\n");
		}
		else if(token.type==24){
			printf("OPERATOR:'<'\n");
		}
		else if(token.type==25){
			printf("OPERATOR:'>'\n");
		}
		else if(token.type==26){
			printf("OPERATOR:'='\n");
		}
		else if(token.type==27){
			printf("OPERATOR:'>='\n");
		}
		else if(token.type==28){
			printf("OPERATOR:'<='\n");
		}
		else if(token.type==29){
			printf("OPERATOR:'=='\n");
		}
		else if(token.type==30){
			printf("OPERATOR:'!='\n");
		}
		else printf("Neznamy Token!!!\n");
		
		if(getToken()==1) {
			scannerFree();
			return 1;
		}
	}

	scannerFree();
	return 0;
}
