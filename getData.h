#include <stdlib.h>

#ifndef  _G_D
#define _G_D

#include "myConstants.h"
#include "myStructure.h"
#include "linkedLists.h"
#include "isLegal.h"

/*A function receives one line from the input and returns the line type.*/
int getTypeSentence(const ptrListWord head, const ptrListOperationCode _listOperationCode, const ptrDataMacro _dataMacro, const ptrListTypesDirectiveSentence _listTypesDirectiveSentence, const ptrListNamesRegister _listNamesRegister, const ptrSymbolsTable _symbolsTable, int* flagLabel, const char* line);

/*A function that receives a parameter and returns its type of method of addressing*/
int getTypeMethodAddressing(ptrListWord listWord, ptrSymbolsTable _SymbolsTable, ptrListNamesRegister _listNamesRegister, ptrListOperationCode _listOperationCode, int* valMacro, int* flagMacro);

/*A function that returns the string from a string directive statement.*/
char* getString(char* line, ptrListEror* headListEror,int lineNumber);

/*The function receives a symbol name, if the symbol name is macro, then the function returns its decimal value.*/
int getvalMacro(ptrSymbolsTable headSymbolsTable, char* name, int* flag);

/*The function gets a string and index, and returns the first word from the same index (no spaces).*/
char* getNextWord(const int index, const char* line, int* finish);

/*The function accepts two types of addressing methods, calculates and returns how many memory words they require.*/
int getL(int typeMethodAddressing1, int typeMethodAddressing2);

#endif
