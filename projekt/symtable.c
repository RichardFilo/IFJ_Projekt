
/******************************** symtable.c **********************************/
/*  Předmět: IFJ a IAL						                                  */
/*  Tabulka symbolov                                                          */
/*  Vytvořil: Richard Filo			                                          */
/* ************************************************************************** */
/*
**  HTInit ....... inicializuje tabulku před prvním použitím
**  HTInsert ..... vložení prvku
**  HTSearch ..... zjištění přítomnosti prvku v tabulce
**  HTDelete ..... zrušení prvku
**  HTRead ....... přečtení hodnoty prvku
**  HTClearAll ... zrušení obsahu celé tabulky
**  HTFree ....... Uvoľní pamäť
**
**
**/

#include"symtable.h"

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % MAX_HTSIZE );
}

tHTable* htInit () {

	tHTable* new=malloc(sizeof(tHTable));
	if(new==NULL){
		fprintf(stderr,"ERROR 99: Chyba alokace pamati\n");
		return NULL;
	}

	for(int i=0; i<MAX_HTSIZE; i++){
		(*new)[i]=NULL;
	}

	return new;		
}

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {

	int index= hashCode(key);
	tHTItem* tmp = (*ptrht)[index];

	while(tmp!=NULL){
		if (strcmp(key,tmp->key)==0) return tmp;
		tmp = tmp->ptrnext;
	}
	return NULL;
}

int htInsert ( tHTable* ptrht, tKey key, tData data ) {

	tHTItem* newItem = htSearch(ptrht,key);
	if (newItem != NULL) {
		newItem->data = data;
		return 0;
	}

	newItem=malloc(sizeof(tHTItem));
	if (newItem==NULL){
		htClearAll(ptrht);
		return 1;	
	}

	newItem->data=data;

	newItem->key=malloc(strlen(key)+1);
	if(newItem->key==NULL){
		free(newItem);
		htClearAll(ptrht);
		return 1;
	}
	strcpy(newItem->key,key);

	int index = hashCode(key);
	newItem->ptrnext = (*ptrht)[index];
	(*ptrht)[index] = newItem;

	return 0;
}

tData htRead ( tHTable* ptrht, tKey key ) {

	tHTItem* tmp = htSearch(ptrht,key);
	return tmp->data;
}

void htDelete ( tHTable* ptrht, tKey key ) {

	int index= hashCode(key);
	tHTItem* tmp = (*ptrht)[index];
	tHTItem** ptr = &((*ptrht)[index]);

	while(tmp!=NULL){
		if (strcmp(key,tmp->key)==0){
			*ptr = tmp->ptrnext;
			free(tmp->key);
			free(tmp);
			return;
		}
		ptr = &(tmp->ptrnext);
		tmp = tmp->ptrnext;
	}
}

void htClearAll ( tHTable* ptrht ) {

	for (int i = 0; i < MAX_HTSIZE; i++)
	{
		tHTItem* tmp = (*ptrht)[i];

		while(tmp!=NULL){
			tHTItem* nextTmp = tmp->ptrnext;
			free(tmp->key);
			free(tmp);
			tmp = nextTmp;
		}
	}
}

void htFree ( tHTable* ptrht ){

	htClearAll(ptrht);
	free(ptrht);
}
