#include <stdlib.h>
#include <stdio.h>

#ifndef  _F_R
#define _F_R

#include "myConstants.h"
#include "myStructure.h"
#include "myString.h"
#include "getData.h"
#include "linkedLists.h"

/*First pass on the input.
Build a symbol table.
Build the data table.
Partial code table construction.
Error search.*/
int firstRead(FILE* fd,
	const ptrListOperationCode _listOperationCode,
	const ptrDataMacro _dataMacro,
	const ptrListTypesDirectiveSentence _listTypesDirectiveSentence,
	const ptrListNamesRegister _listNamesRegister,
	ptrWordMemory* headListDataTable,
	ptrWordMemory* headListCode,
	ptrSymbolsTable* headSymbolsTable,
	ptrListEror* headListEror);

/*Move over the icon table to correct the address values of data or entry icons.*/
void fixAddresses(ptrSymbolsTable* head, int ic);

#endif
