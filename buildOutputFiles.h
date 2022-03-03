
#ifndef  _C_F
#define _C_F

#include "myStructure.h"

/*Function Builds all the files that need to be built for the assembler program it received as input.*/
void createFiles(char *name,ptrWordMemory  headCodeTable,ptrSymbolsTable headSymbol,int lengthCode,int lengthData, ptrListWord _headListExt);

/*File builder function with any machine language encoded to a special base*/
void createObFile(char* name, ptrWordMemory  headCodeTable, int lengthCode, int lengthData);

/*The function builds the directory with information about entry type variables*/
void createEntFile(char* name, ptrSymbolsTable headSymbol );

/*The function builds the directory with information about extern type variables*/
void createExtFile(char* name, ptrWordMemory  headCodeTable, ptrSymbolsTable  headSymbol, ptrListWord  listNameExt,int lengthCode);

#endif
