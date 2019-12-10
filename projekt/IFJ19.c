#include"parser.h"

extern int _errNumber;
extern char* code;

int main(int argc, char* argv[]){

	if(argc==2){
		if(scannerInit(argv[1])) return 99;
	}
	else if(scannerInit("stdin")) return 99;


    if(checkSyntax()==0) printf("%s",code);
	stringFree(code);
	scannerFree();
    return _errNumber;

}
