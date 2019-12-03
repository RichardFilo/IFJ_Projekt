#include"../projekt/parser.h"

extern int _errNumber;

int main(int argc, char* argv[]){

	if(argc==2){
		if(scannerInit(argv[1])) return 99;
	}
	else if(scannerInit("stdin")) return 99;


    if(checkSyntax()==0) printf("Syntax je OK\n");
	scannerFree();
    return _errNumber;
}
