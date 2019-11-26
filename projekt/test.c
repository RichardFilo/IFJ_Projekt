#include"stackINT.h"
#include"mystring.h"
#include"scanner.h"

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
		if(scanner_init(argv[1])) return 99;
	}
	else if(scanner_init("stdin")) return 99;

	int t;
	while((t=getToken())==0){
		
		if(token.type==1) {
			printf("ID:%s\n",token._string);
			stringFree(token._string);
		}
		else if(token.type==4){
			printf("STRING:'%s'\n",token._string);
			stringFree(token._string);
		}
		else if(token.type==2){
			printf("INT:%d\n",token._int);
		}
		else if(token.type==3){
			printf("FLOAT:%g\n",token._float);
		}
		else printf("%d\n",token.type);
	}
	if(t==1) {
		scanner_free();
		return 1;
	}
	else if(t==-1) printf("KONIEC\n");
	scanner_free();

	return 0;
}
