
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef  _M_S
#define _M_S

#include "myConstants.h"

#define MAX_LENGTH_LINE 81

#define MAX_LENGTH_MESSAGE 80

#define NUMBER_EROR 23

#define LENGTH_MACRO 8

#define MAX_LENGTH_REGISTER 3

#define NUMBER_REGISTER 8

#define NUMBER_DIRECTIVE_SENTENCE 4

#define MAX_LENGTH_DIRECTIVE_NAME 8

#define MAX_LENGTH_NAME_OPERATION 5

#define NUMBER_OPERATION 16

#define MAX_LENGTH_LABEL 31


typedef enum {numImmediateAddressing, numDirectAddressing, Indexing,numDirectRegisterAddressing,numArrayStartAddress, numIndexNumber, numDataTable,numFirstWordMemory}typeOfAddressingSystem;

typedef enum { eror1 = 1000, eror2, eror3, eror4, eror5, eror6, eror7, eror8, eror9, eror10, eror11, eror12, eror13,eror14,eror15,eror16,eror17,eror18,eror19,eror20,eror21,eror22,eror23 }codeEror;

typedef enum { r0, r1, r2, r3, r4, r5, r6, r7 }numberRegister;

typedef enum { emptySentence = 1, noteSentence, directiveSentence, operationSentence, macroSentence }TypesSentences;

typedef enum { data = 0, string, entry, externn }typesDirectiveSentence;

typedef enum opcode { mov = 0, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop } opcode;

typedef enum { oneBit = 1, twoBits, threeBits, fourBits, fiveBits, sixBits, sevenBits, eightBits, nineBits, tenBits, elevenBits, twelveBits, thirteenBits, fourteenBits } assignBits;


typedef struct Line {
	int lineNumber;
	int skip;
	int sourceOperandAddressingMethod;
	int destinationOperandAddressingMethod;
}Line;



typedef struct listWord* ptrListWord;

typedef struct listWord {

	char* word;
	ptrListWord next;

}listWord;



typedef struct Eror {

	int errorCode;
	char erorMessage[MAX_LENGTH_MESSAGE];

}Eror;

typedef struct  listErorTypes* ptrListErorTypes;

typedef struct listErorTypes {

	Eror _EROR[NUMBER_EROR];

}listErorTypes;


typedef struct  listEror* ptrListEror;

typedef struct listEror {

	int lineNumber;
	int code;
	ptrListEror next;

}listEror;


typedef struct  dataMacro* ptrDataMacro;

typedef struct dataMacro {

	char macro[LENGTH_MACRO];

}dataMacro;


typedef struct {

	char names[MAX_LENGTH_REGISTER];

}Register;


typedef struct listNamesRegister* ptrListNamesRegister;

typedef struct listNamesRegister {

	Register dataRegister[NUMBER_REGISTER];

}listNamesRegister;



typedef struct {

	char names[MAX_LENGTH_DIRECTIVE_NAME];

}DirectiveSentence;

typedef struct listTypesDirectiveSentence* ptrListTypesDirectiveSentence;

typedef struct listTypesDirectiveSentence {

	DirectiveSentence _directiveSentence[NUMBER_DIRECTIVE_SENTENCE];

}listTypesDirectiveSentence;



typedef struct {

	char nameAction[NUMBER_OPERATION];
	opcode _opcode;

}operationCode;


typedef struct listOperationCode* ptrListOperationCode;


typedef struct listOperationCode {

	operationCode _operationCode[NUMBER_OPERATION];

}listOperationCode;



typedef struct symbolsTable* ptrSymbolsTable;

typedef struct symbolsTable {

	char nameLabel[MAX_LENGTH_LABEL];
	int isEntry;
	int isData;
	int isExtern;
	int isMacro;
	int address;
	int AttachedOfOperationSentence;

	ptrSymbolsTable next;

}symbolsTable;



typedef struct {

	unsigned int ARE : twoBits;
	unsigned int destinationOperand : twoBits;
	unsigned int sourceOperand : twoBits;
	unsigned int opcode : fourBits;
	unsigned int unused : fourBits;

}firstWordMemory;

typedef struct {

	unsigned int ARE : twoBits;
	unsigned int val : twelveBits;

}immediateAddressing;

typedef struct {

	unsigned int ARE : twoBits;
	unsigned int address : twelveBits;

}directAddressing;



typedef struct {

	unsigned int ARE : twoBits;
	unsigned int address : twelveBits;

}arrayStartAddress;

typedef struct {

    unsigned int ARE : twoBits;
	unsigned int index : twelveBits;

}indexNumber;

typedef struct {

	unsigned int ARE : twoBits;
	unsigned int destinationRegister : threeBits;
    unsigned int sourceRegister : threeBits;
	unsigned int unused : sixBits;

}directRegisterAddressing;

typedef struct dataTable {

	int valData : fourteenBits;

}dataTable;


typedef struct wordMemory* ptrWordMemory;

typedef struct wordMemory {

	union {
		firstWordMemory _firstWordMemory;
		immediateAddressing _immediateAddressing;
		directAddressing _directAddressing;
		arrayStartAddress _arrayStartAddress;
		indexNumber _indexNumber;
		directRegisterAddressing _directRegisterAddressing;
		dataTable _dataTable;

	}data;

	ptrWordMemory next;

}wordMemory;


ptrListOperationCode createListOperationCode(ptrListOperationCode _listOperationCode);

ptrListTypesDirectiveSentence createListTypesDirectiveSentence(ptrListTypesDirectiveSentence _listTypesDirectiveSentence);

ptrListNamesRegister createListNamesRegister(ptrListNamesRegister _listNamesRegister);

ptrDataMacro createDataMacro(ptrDataMacro _DataMacro);

ptrListErorTypes createListErorTypes(ptrListErorTypes headListErorTypes);

#endif



