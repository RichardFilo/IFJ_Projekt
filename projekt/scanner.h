
/* ******************************** scanner.h ******************************* */
/*  Předmět: IFJ a IAL				                              */
/*  Lexikálna analýza                                                         */
/*  Vytvořil: Richard Filo			                              */
/* ************************************************************************** */
/*
**    getToken ..... Vráti príslušný token
**    scannerInit .... Inicializácia skenera
**    scannerFree .... Uvoľnenie pamäte
**
**/

#ifndef SCANNER_H
#define SCANNER_H

#include"stackTOKEN.h"
#include"stackINT.h"
#include"mystring.h"
#include<ctype.h>


	
int FTflag;
FILE* input;
tStack* stack;


int scannerInit(char* file);

void scannerFree();

int getToken();

void ungetToken();

#endif
