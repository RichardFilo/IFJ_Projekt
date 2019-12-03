#include"../projekt/parser.h"

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


    if(getToken()!=0){
        scannerFree();
        return 1;
    }

	int r=_exp();
	scannerFree();
    return r;
}