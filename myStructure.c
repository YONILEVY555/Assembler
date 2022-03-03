



#include "myStructure.h"

static void initializationListOperationCode(ptrListOperationCode _listOperationCode);
static void initializationListTypesDirectiveSentence(ptrListTypesDirectiveSentence _listTypesDirectiveSentence);
static void initializationListNamesRegister(ptrListNamesRegister _listNamesRegister);
static void initializationDataMacro(ptrDataMacro  _DataMacro);
static void initializationListErorTypes(ptrListErorTypes headListErorTypes);

ptrListOperationCode createListOperationCode(ptrListOperationCode _listOperationCode) {

	_listOperationCode = (ptrListOperationCode)malloc(sizeof(listOperationCode));

	if (_listOperationCode == NULL)
		exit(EXIT_FAILURE);

	initializationListOperationCode(_listOperationCode);

	return _listOperationCode;
}

static void initializationListOperationCode(ptrListOperationCode _listOperationCode) {

	int i;

	char names[NUMBER_OPERATION][MAX_LENGTH_NAME_OPERATION] = { "mov", "cmp", "add", "sub", "not", "clr", "lea", "inc",

															"dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop" };

	for (i = 0; i < NUMBER_OPERATION; i++) {
		_listOperationCode->_operationCode[i].nameAction[FIRST_CHARACTER] = END_STRING;
		strcpy(_listOperationCode->_operationCode[i].nameAction, names[i]);
	}

	_listOperationCode->_operationCode[mov]._opcode = mov;
	_listOperationCode->_operationCode[cmp]._opcode = cmp;
	_listOperationCode->_operationCode[add]._opcode = add;
	_listOperationCode->_operationCode[sub]._opcode = sub;
	_listOperationCode->_operationCode[not]._opcode = not;
	_listOperationCode->_operationCode[clr]._opcode = clr;
    _listOperationCode->_operationCode[lea]._opcode = lea;
	_listOperationCode->_operationCode[inc]._opcode = inc;
	_listOperationCode->_operationCode[dec]._opcode = dec;
	_listOperationCode->_operationCode[jmp]._opcode = jmp;
	_listOperationCode->_operationCode[bne]._opcode = bne;
	_listOperationCode->_operationCode[red]._opcode = red;
	_listOperationCode->_operationCode[prn]._opcode = prn;
	_listOperationCode->_operationCode[jsr]._opcode = jsr;
	_listOperationCode->_operationCode[rts]._opcode = rts;
	_listOperationCode->_operationCode[stop]._opcode = stop;

}

ptrListTypesDirectiveSentence createListTypesDirectiveSentence(ptrListTypesDirectiveSentence _listTypesDirectiveSentence) {

	_listTypesDirectiveSentence = (ptrListTypesDirectiveSentence)malloc(sizeof(listTypesDirectiveSentence));

	if (_listTypesDirectiveSentence == NULL)
		exit(EXIT_FAILURE);

	initializationListTypesDirectiveSentence(_listTypesDirectiveSentence);

	return _listTypesDirectiveSentence;

}

static void initializationListTypesDirectiveSentence(ptrListTypesDirectiveSentence _listTypesDirectiveSentence) {

	int i;

	char names[NUMBER_DIRECTIVE_SENTENCE][MAX_LENGTH_DIRECTIVE_NAME] = { ".data", ".string", ".entry", ".extern" };

	for (i = 0; i < NUMBER_DIRECTIVE_SENTENCE; i++) {
		_listTypesDirectiveSentence->_directiveSentence[i].names[FIRST_CHARACTER] = END_STRING;
     	strcpy(_listTypesDirectiveSentence->_directiveSentence[i].names, names[i]);
	}

}

ptrListNamesRegister createListNamesRegister(ptrListNamesRegister _listNamesRegister) {

	_listNamesRegister = (ptrListNamesRegister)malloc(sizeof(listNamesRegister));

	if (_listNamesRegister == NULL)
		exit(EXIT_FAILURE);

	initializationListNamesRegister(_listNamesRegister);

	return _listNamesRegister;
}

static void initializationListNamesRegister(ptrListNamesRegister _listNamesRegister) {

	int i;

	char names[NUMBER_REGISTER][MAX_LENGTH_REGISTER] = { "r0","r1","r2","r3","r4","r5","r6","r7" };

	for (i = 0; i < NUMBER_REGISTER; i++) {
		_listNamesRegister->dataRegister[i].names[FIRST_CHARACTER] = END_STRING;
		strcpy(_listNamesRegister->dataRegister[i].names, names[i]);
	}
}

ptrDataMacro createDataMacro(ptrDataMacro _DataMacro) {

	_DataMacro = (ptrDataMacro)malloc(sizeof(dataMacro));

	if (_DataMacro == NULL)
		exit(EXIT_FAILURE);

	initializationDataMacro(_DataMacro);

	return _DataMacro;
}


static void initializationDataMacro(ptrDataMacro  _DataMacro) {
	char* str = ".define";
	strcpy(_DataMacro->macro, str);
}

ptrListErorTypes createListErorTypes(ptrListErorTypes headListErorTypes) {

	headListErorTypes = (ptrListErorTypes)malloc(sizeof(listErorTypes));

	if (headListErorTypes == NULL)
		exit(EXIT_FAILURE);

	initializationListErorTypes(headListErorTypes);

	return headListErorTypes;

}

static void initializationListErorTypes(ptrListErorTypes headListErorTypes) {

	int i,j;

	char names[NUMBER_EROR][MAX_LENGTH_MESSAGE] = { 
		"Invalid label name or declared twice",
		"Incorrect macro definition command structure",
		"Invalid command name",
		"Incorrect operand",
		"Comma in the wrong place",
		"Invalid parameter", 
		"Two commas (num,,)",
		"eror8",
		"eror9",
		"eror10",
		"Missing (\")",
		"Redundant parameters",
		"Missing parameters",
		"eror14",
		"The type of operands is incorrect for this command",
		"Invalid label name",
		"Incorrect number of parameters",
		"Incorrect number of commas",
		"Invalid parameter for the selected command",
		"Indefinite label",
		"Indefinite label",
		"eror22",
		"eror23" };



	for (i = eror1,j=0; i <= eror23; i++,j++) {
		headListErorTypes->_EROR[j].errorCode = i;
		headListErorTypes->_EROR[j].erorMessage[FIRST_CHARACTER] = END_STRING;
		strcpy(headListErorTypes->_EROR[j].erorMessage, names[j]);
	}


}

