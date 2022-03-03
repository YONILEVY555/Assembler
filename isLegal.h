#include <stdlib.h>

#ifndef  _I_L
#define _I_L

#include "myConstants.h"
#include <ctype.h>
#include "myStructure.h"
#include "linkedLists.h"

/*A function that receives a label name and checks and returns true if the label name is valid and false if the label name is invalid.*/
int legalLabel(char* label, const ptrListOperationCode _listOperationCode, const ptrListNamesRegister _listNamesRegister, const ptrSymbolsTable _symbolsTable);

/*The function gets a string that checks and returns true if the string has a valid number structure and false if not.*/
int legalNumber(char* num);

/*Checks a proper entry or external statement sentence structure.
If proper returns true and if not returns false.*/
void legalEntryOrExtern(ptrSymbolsTable headSymbol, ptrListWord _headListWord, ptrListEror* headListEror, int lineNumber, const ptrListOperationCode _listOperationCode, const ptrListNamesRegister _listNamesRegister, const ptrSymbolsTable _symbolsTable);

/*A function that receives an instruction statement and checks that the structure is correct.
If correct, return TRUE if you do not return FALSE.*/
int isLegalOperationSentece(int typeMethodAddressing1, int  typeMethodAddressing2, int lineNumber, int countOperator, ptrListEror* headListEror);

#endif
