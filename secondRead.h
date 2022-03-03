#include <stdlib.h>
#include <stdio.h>

#ifndef  _F_S
#define _F_S

#include "myConstants.h"
#include "myStructure.h"
#include "isLegal.h"
#include "linkedLists.h"

/*Receives input line, opertion sentence type.
The function updates for each such label the value of the are and the address in the code table.
If this label is not set in the symbol table the function will enter an appropriate error code into the error list. */
void func(ptrWordMemory* headListCodeList, ptrListWord _headListWord, const ptrListNamesRegister _listNamesRegister, ptrSymbolsTable* headSymbolsTable, const ptrListOperationCode _listOperationCode, ptrListEror* headListEror, int flag, ptrListWord* _headListExt);

/*Second pass on the input.
  Mark symbol in entry.
  Updating the addresses and "are" field for symbols in the first round we did not know their address yet.
  Search for undefined symbol errors.*/
void secondRead(ptrWordMemory headTableData, ptrSymbolsTable* headSymbolsTable, ptrWordMemory* headCodeTable, FILE* fd, const ptrListOperationCode _listOperationCode, const ptrDataMacro _dataMacro, const ptrListTypesDirectiveSentence _listTypesDirectiveSentence, const ptrListNamesRegister _listNamesRegister, ptrListEror* headListEror, ptrListWord * _headListExt);

/*A function takes a label name and updates the address and are variables for that label.
If the label does not exist in the symbol table, the value will be returned otherwise false will be returned true.*/
int getAddressAndAre(ptrSymbolsTable headSymbolsTable, char* label, int* are, int* address);

/*Updating the addresses and "are" field for symbols in the first round we did not know their address yet.*/
void fixesCodeTable(ptrWordMemory* listCodeTable, int are, int address);

/*Mark symbol in entry.*/
void markerEntry(ptrSymbolsTable headSymbol, ptrListWord _headListWord, ptrListEror* headListEror);

#endif
