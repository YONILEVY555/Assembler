
#include "firstRead.h"

static void directiveProcessor(ptrListEror* headListEror, int* dc, int flagLabel, ptrWordMemory* headListDataTable, ptrListTypesDirectiveSentence _listTypesDirectiveSentence, ptrListWord headListWord, ptrSymbolsTable* headSymbolsTable, ptrListOperationCode _listOperationCode, ptrListNamesRegister _listNamesRegister, char* newLine, char* line);
static void operationSentenceProcessor(char* newLine, int* ic, int flagLabel, ptrListWord headListWord, ptrListEror* headListEror, ptrSymbolsTable* headSymbolsTable, ptrWordMemory* headListCode, ptrListOperationCode _listOperationCode, ptrListNamesRegister _listNamesRegister);
static void macroeProcessor(ptrListWord headListWord, ptrListEror* headListEror, ptrSymbolsTable* headSymbolsTable, ptrListOperationCode _listOperationCode, ptrListNamesRegister _listNamesRegister, char* line);
static void ProcessorMethodAddressing(int typeMethodAddressing, ptrListWord headListWord, ptrListWord prev, ptrWordMemory* headCodeTable, int* destinationOperand, int* sourceOperand, int flagSecondOperand, int flagMacro, int valMacro);

void printCodeTable(ptrWordMemory head);
void bin(unsigned n);

static int lineNumber = 1;

int firstRead(FILE* fd,
	const ptrListOperationCode _listOperationCode,
	const ptrDataMacro _dataMacro,
	const ptrListTypesDirectiveSentence _listTypesDirectiveSentence,
	const ptrListNamesRegister _listNamesRegister,
	ptrWordMemory* headListDataTable,
	ptrWordMemory* headListCode,
	ptrSymbolsTable* headSymbolsTable,
	ptrListEror* headListEror) {

	static int ic = 0, dc = 0;
	int typeSentence;

	

	char line[MAX_LENGTH_LINE] = {0};

	char* newLine = NULL;
	int flagLabel;


	ptrListWord _headListWord = NULL;


	while ( (fgets(line, MAX_LENGTH_LINE, fd)) ) {

		if(line[strlen(line) - 1]=='\n')
			line[strlen(line) - 1] = END_STRING;
		newLine = deleteExtraWhiteSpace(line);
		_headListWord = getAlltWord(_headListWord, newLine);

		typeSentence = getTypeSentence(_headListWord,
										_listOperationCode,
										_dataMacro,
										_listTypesDirectiveSentence,
										_listNamesRegister,
										*headSymbolsTable,
										&flagLabel,
										newLine);

		switch (typeSentence) {

		case emptySentence:
			break;

		case noteSentence:
			break;

		case  directiveSentence:

			directiveProcessor(headListEror, &dc, flagLabel, headListDataTable, _listTypesDirectiveSentence, _headListWord, headSymbolsTable, _listOperationCode, _listNamesRegister, newLine, line);

			break;

		case operationSentence:

			operationSentenceProcessor(newLine,&ic,flagLabel,_headListWord,headListEror,headSymbolsTable,headListCode,_listOperationCode,_listNamesRegister);

			break;

		case macroSentence:

			macroeProcessor(_headListWord, headListEror, headSymbolsTable, _listOperationCode, _listNamesRegister, newLine);

			break;

		case eror1:

			insertListEror(headListEror, eror1, lineNumber);

			break;

		}



		lineNumber++;

	}


        lineNumber = 1;
	fixAddresses(headSymbolsTable, ic);

	return TRUE;
}


static void operationSentenceProcessor(char *newLine,
	                                   int* ic,
	                                   int flagLabel,
	                                   ptrListWord headListWord,
	                                   ptrListEror* headListEror,
	                                   ptrSymbolsTable* headSymbolsTable,
	                                   ptrWordMemory *headListCode,
	                                   ptrListOperationCode _listOperationCode,
	                                   ptrListNamesRegister _listNamesRegister
									   ) {


		
		
		

	ptrListWord startSecondOperator = NULL;
	ptrListWord temp = NULL;
	int countComma = 0;
	int i;
	int countOperator = 0;
	int count = 0;
	int type = -1;
	int valMacro1 = 0;
	int valMacro2 = 0;
	int flagMacro = 0;
	int flagMacro1;
	int flagMacro2;
	int sourceOperand = -1;
	int destinationOperand = -1;
	int L;
	int typeMethodAddressing1 = -1;
	int typeMethodAddressing2 = -1;

	newLine = makeSpace(newLine,'[');
	newLine = makeSpace(newLine, ']');
	newLine = makeSpace(newLine, ',');
	newLine = deleteExtraWhiteSpace(newLine);
	headListWord = getAlltWord(headListWord, newLine);

	count = getCountWord(headListWord);

	if (flagLabel) {

		if ( legalLabel(headListWord->word, _listOperationCode, _listNamesRegister, *headSymbolsTable) ) {
			insertDataSymbolsTable(headSymbolsTable, headListWord->word, (*ic) + START_ADDRESS_MEMORY, (int)operationSentence);
		}
		else{
			insertListEror(headListEror, eror16,lineNumber);
		}

		for (i = mov; i <= stop; i++)
			if (!strcmp(_listOperationCode->_operationCode[i].nameAction, headListWord->next->word))
				type = i;

		switch (type) {
		case mov:
		case cmp:
		case add:
		case sub:
		case lea:

			if (count < 4) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

			if (!strcmp(headListWord->next->word, ",")) {
				insertListEror(headListEror, eror5, lineNumber);
				return;
			}

			typeMethodAddressing1 = getTypeMethodAddressing(headListWord->next->next, *headSymbolsTable, _listNamesRegister, _listOperationCode, &valMacro1, &flagMacro);

			if (typeMethodAddressing1 == -1) {
				insertListEror(headListEror, eror4, lineNumber);
				return;
			}

			flagMacro1 = flagMacro;

			for (temp = headListWord->next->next; temp; temp = temp->next) {

				if (countComma == 1 && startSecondOperator==NULL) {
					startSecondOperator = temp;
				}

				if (!strcmp(temp->word, ",")) {
					countComma++;
				}

			}

			if (countComma != 1) {
				insertListEror(headListEror, eror18, lineNumber);
				return;
			}

			if (!startSecondOperator) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

			typeMethodAddressing2 = getTypeMethodAddressing(startSecondOperator, *headSymbolsTable, _listNamesRegister, _listOperationCode, &valMacro2, &flagMacro);

			if (typeMethodAddressing2 == -1) {
				insertListEror(headListEror, eror4, lineNumber);
				return;
			}

			countOperator = getCountWord(headListWord->next->next);

			if (!isLegalOperationSentece(typeMethodAddressing1, typeMethodAddressing2, lineNumber, countOperator, headListEror))
				return;

			flagMacro2 = flagMacro;

			L = getL(typeMethodAddressing1,typeMethodAddressing2);

			*ic += L;

			if (type == mov || type == add || type == sub || type==lea)
				if (typeMethodAddressing2 == numImmediateAddressing) {
					insertListEror(headListEror, eror15, lineNumber);
					return;
				}

			if(type == lea)
				if ( typeMethodAddressing1 == numImmediateAddressing || typeMethodAddressing1 == numDirectRegisterAddressing ) {
					insertListEror(headListEror, eror15, lineNumber);
					return;
				}

			insertCodeTable(headListCode, numFirstWordMemory, 0, 0, type, typeMethodAddressing2, typeMethodAddressing1,0, 0, 0);		
			ProcessorMethodAddressing(typeMethodAddressing1, headListWord->next->next,NULL ,headListCode, &destinationOperand, &sourceOperand, 1, flagMacro1, valMacro1);
			ProcessorMethodAddressing(typeMethodAddressing2, startSecondOperator,headListWord->next->next,headListCode,&destinationOperand,&sourceOperand,2, flagMacro2,valMacro2);

			break;

		case not:
		case clr:
		case inc:
		case dec:
		case jmp:
		case bne:
		case red:
		case prn:
		case jsr:

			if (count < 3) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

				typeMethodAddressing2 = getTypeMethodAddressing(headListWord->next->next, *headSymbolsTable, _listNamesRegister, _listOperationCode, &valMacro2, &flagMacro);

				if (typeMethodAddressing2 == -1) {
					insertListEror(headListEror, eror4, lineNumber);
					return;
				}
					

				flagMacro1 = flagMacro;

				if ( typeMethodAddressing2 == Indexing) {
					if (count != 6) {
						insertListEror(headListEror, eror9, lineNumber);
						return;
					}
				}
				else{
					if (count != 3) {
						insertListEror(headListEror, eror9, lineNumber);
						return;
					}
			    }

				if (type == not || type == clr || type == inc || type == dec || type == red ) 
					if (typeMethodAddressing2 == numImmediateAddressing) {
						insertListEror(headListEror, eror15, lineNumber);
						return;
					}


				if (type == jmp || type == bne || type == jsr )
					if (typeMethodAddressing2 == numImmediateAddressing || typeMethodAddressing2 == Indexing) {
						insertListEror(headListEror, eror15, lineNumber);
						return;
					}

				L = getL(typeMethodAddressing2,-1);

				*ic += L;

				insertCodeTable(headListCode, numFirstWordMemory, 0, 0, type, typeMethodAddressing2, typeMethodAddressing1, 0, 0, 0);

				ProcessorMethodAddressing(typeMethodAddressing2, headListWord->next->next,NULL, headListCode, &destinationOperand, &sourceOperand, 1, flagMacro1, valMacro2);


			break;

		case rts:
		case stop:

			if (count != 2) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

			insertCodeTable(headListCode, numFirstWordMemory, 0, 0, type,0,0, 0, 0, 0);

			(*ic)++;

			break;

			default:
				insertListEror(headListEror,eror3, lineNumber);
		}
	}
	else {

	for (i = mov; i <= stop; i++)
		if (!strcmp(_listOperationCode->_operationCode[i].nameAction, headListWord->word))
			type = i;

		switch (type) {
		case mov:
		case cmp:
		case add:
		case sub:
		case lea:

			if (count < 3) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

			if (!strcmp(headListWord->next->word, ",")) {
				insertListEror(headListEror, eror5, lineNumber);
				return;
			}

			typeMethodAddressing1 = getTypeMethodAddressing(headListWord->next, *headSymbolsTable, _listNamesRegister, _listOperationCode, &valMacro1, &flagMacro);

			if (typeMethodAddressing1 == -1) {
				insertListEror(headListEror, eror4, lineNumber);
				return;
			}

			flagMacro1 = flagMacro;

			for (temp = headListWord->next; temp; temp = temp->next) {

				if ( countComma == 1 && startSecondOperator == NULL ) {
					startSecondOperator = temp;
				}

				if (!strcmp(temp->word, ",")) {
					countComma++;
				}

			}



			if ( countComma != 1 ) {
				insertListEror(headListEror, eror18, lineNumber);
				return;
			}

			if (!startSecondOperator) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

			typeMethodAddressing2 = getTypeMethodAddressing(startSecondOperator, *headSymbolsTable, _listNamesRegister, _listOperationCode, &valMacro2, &flagMacro);

			if (typeMethodAddressing2 == -1) {
				insertListEror(headListEror, eror4, lineNumber);
				return;
			}

			countOperator = getCountWord(headListWord->next);

			if (!isLegalOperationSentece(typeMethodAddressing1, typeMethodAddressing2, lineNumber, countOperator, headListEror))
				return;

			flagMacro2 = flagMacro;

			L = getL(typeMethodAddressing1, typeMethodAddressing2);

			*ic += L;

			if (type == mov || type == add || type == sub || type == lea)
				if (typeMethodAddressing2 == numImmediateAddressing) {
					insertListEror(headListEror, eror15, lineNumber);
					return;
				}

			if (type == lea)
				if (typeMethodAddressing1 == numImmediateAddressing || typeMethodAddressing1 == numDirectRegisterAddressing) {
					insertListEror(headListEror, eror15, lineNumber);
					return;
				}


			insertCodeTable(headListCode, numFirstWordMemory, 0, 0, type, typeMethodAddressing2, typeMethodAddressing1, 0, 0, 0);

			ProcessorMethodAddressing(typeMethodAddressing1, headListWord->next,NULL,headListCode, &destinationOperand, &sourceOperand, 1, flagMacro1, valMacro1);

			ProcessorMethodAddressing(typeMethodAddressing2, startSecondOperator, headListWord->next,headListCode, &destinationOperand, &sourceOperand, 2, flagMacro2, valMacro2);

			break;

		case not:
		case clr:
		case inc:
		case dec:
		case jmp:
		case bne:
		case red:
		case prn:
		case jsr:

			if (count < 2) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

			typeMethodAddressing2 = getTypeMethodAddressing(headListWord->next, *headSymbolsTable, _listNamesRegister, _listOperationCode, &valMacro2, &flagMacro);


			if (typeMethodAddressing2 == -1) {
				insertListEror(headListEror, eror4, lineNumber);
				return;
			}

			flagMacro1 = flagMacro;

			if (typeMethodAddressing2 == Indexing) {
				if (count != 5) {
					insertListEror(headListEror, eror9, lineNumber);
					return;
				}
			}
			else {
				if (count != 2) {
					insertListEror(headListEror, eror9, lineNumber);
					return;
				}
			}

			if (type == not || type == clr || type == inc || type == dec || type == red)
				if (typeMethodAddressing2 == numImmediateAddressing) {
					insertListEror(headListEror, eror15, lineNumber);
					return;
				}


			if (type == jmp || type == bne || type == jsr)
				if (typeMethodAddressing2 == numImmediateAddressing || typeMethodAddressing2 == Indexing) {
					insertListEror(headListEror, eror15, lineNumber);
					return;
				}

			L = getL(typeMethodAddressing2, -1);

			*ic += L;

			insertCodeTable(headListCode, numFirstWordMemory, 0, 0, type, typeMethodAddressing2, typeMethodAddressing1, 0, 0, 0);

			ProcessorMethodAddressing(typeMethodAddressing2, headListWord->next,NULL, headListCode, &destinationOperand, &sourceOperand, 1, flagMacro1, valMacro2);


			break;

		case rts:
		case stop:

			if (count != 1) {
				insertListEror(headListEror, eror17, lineNumber);
				return;
			}

			(*ic)++;

			insertCodeTable(headListCode, numFirstWordMemory, 0, 0, type, 0, 0, 0, 0, 0);

			break;

		  default:
			  insertListEror(headListEror,eror3, lineNumber);
		}

	}

}


static void directiveProcessor(ptrListEror * headListEror, int* dc, int flagLabel, ptrWordMemory * headListDataTable, ptrListTypesDirectiveSentence _listTypesDirectiveSentence, ptrListWord headListWord, ptrSymbolsTable * headSymbolsTable, ptrListOperationCode _listOperationCode, ptrListNamesRegister _listNamesRegister, char* newLine, char* line){

	ptrListWord temp;
	char* myString;
	int count;
	int result = -1;
	

	if (flagLabel) {



		if (!strcmp(headListWord->next->word, _listTypesDirectiveSentence->_directiveSentence[data].names))
			result = data;

		if (!strcmp(headListWord->next->word, _listTypesDirectiveSentence->_directiveSentence[string].names))
			result = string;

		if (!strcmp(headListWord->next->word, _listTypesDirectiveSentence->_directiveSentence[entry].names))
			result = entry;

		if (!strcmp(headListWord->next->word, _listTypesDirectiveSentence->_directiveSentence[externn].names))
			result = externn;


		count = getCountWord(headListWord);

		if (count == 2) {
			insertListEror(headListEror, eror13, lineNumber);
			return;
		}

		switch (result) {

		case data:

			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);

			count = getCountWord(headListWord);

			if (count > 2 && legalLabel(headListWord->word, _listOperationCode, _listNamesRegister, *headSymbolsTable)) {

				insertDataSymbolsTable(headSymbolsTable, headListWord->word, *dc, (int)data);

				(*dc) += insertAllNumber(headListEror, *headSymbolsTable, headListWord->next->next, headListDataTable, lineNumber);

				return;

			}
			else {
				insertListEror(headListEror, eror9, lineNumber);
				return;
			}

			break;
		case string:

			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);

			count = getCountWord(headListWord);

			if (count > 2 && legalLabel(headListWord->word, _listOperationCode, _listNamesRegister, *headSymbolsTable))
				insertDataSymbolsTable(headSymbolsTable, headListWord->word, *dc, (int)string);
			else {
				insertListEror(headListEror, eror13, lineNumber);
				return;
			}

			if (!(myString = getString(line, headListEror, lineNumber)))
				return;

			*dc += strlen(myString)+1;
			insertString(headListDataTable, myString);

			break;

		case entry:

			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);

			count = getCountWord(headListWord);

			if(count>2)
				legalEntryOrExtern(*headSymbolsTable, headListWord->next->next, headListEror, lineNumber, _listOperationCode, _listNamesRegister, *headSymbolsTable);

			break;
		case externn:


			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);

			count = getCountWord(headListWord);

			if(count>2)
				legalEntryOrExtern(*headSymbolsTable, headListWord->next->next, headListEror, lineNumber, _listOperationCode, _listNamesRegister, *headSymbolsTable);

			if (count > 2) {
				for (temp = headListWord->next->next; temp; temp = temp->next) {
					if (legalLabel(temp->word, _listOperationCode, _listNamesRegister, *headSymbolsTable)) {
						insertDataSymbolsTable(headSymbolsTable, temp->word, 0, (int)externn);
					}
				}
			}

			break;

		case eror10:

			break;

		}

	}
	else {

		if (!strcmp(headListWord->word, _listTypesDirectiveSentence->_directiveSentence[data].names))
			result = data;

		if (!strcmp(headListWord->word, _listTypesDirectiveSentence->_directiveSentence[string].names))
			result = string;

		if (!strcmp(headListWord->word, _listTypesDirectiveSentence->_directiveSentence[entry].names))
			result = entry;

		if (!strcmp(headListWord->word, _listTypesDirectiveSentence->_directiveSentence[externn].names))
			result = externn;

		count = getCountWord(headListWord);

		if (count == 1) {
			insertListEror(headListEror, eror13, lineNumber);
			return;
		}

		switch (result) {

		case data:

			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);

			count = getCountWord(headListWord);


			if (count > 1) {

				(*dc) += insertAllNumber(headListEror, *headSymbolsTable, headListWord->next, headListDataTable, lineNumber);
				return;

			}
		

			break;
		case string:

			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);

			count = getCountWord(headListWord);


			if (!(myString = getString(line, headListEror, lineNumber)))
				return;

			*dc += strlen(myString)+1;
			insertString(headListDataTable, myString);

			break;
		case entry:

			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);


			if(getCountWord(headListWord)>1)
				legalEntryOrExtern(*headSymbolsTable,headListWord->next, headListEror, lineNumber, _listOperationCode, _listNamesRegister, *headSymbolsTable);

			break;
		case externn:

			newLine = makeSpace(newLine, COMMA);

			newLine = deleteExtraWhiteSpace(newLine);

			headListWord = getAlltWord(headListWord, newLine);

			count = getCountWord(headListWord);


			if (count > 1)
				legalEntryOrExtern(*headSymbolsTable, headListWord->next, headListEror, lineNumber, _listOperationCode, _listNamesRegister, *headSymbolsTable);

			if (count > 1) {
				for (temp = headListWord->next; temp; temp = temp->next) {
					if (legalLabel(temp->word, _listOperationCode, _listNamesRegister, *headSymbolsTable)) {
						insertDataSymbolsTable(headSymbolsTable, temp->word, 0, (int)externn);
					}
				}
			}

			break;

		case eror10:

			break;

		}

	}

	return;

}


static void ProcessorMethodAddressing(int typeMethodAddressing, ptrListWord headListWord, ptrListWord prev,ptrWordMemory* headCodeTable,int *destinationOperand,int *sourceOperand , int flagSecondOperand,int flagMacro,int valMacro) {


	if ( (*sourceOperand != -1) &&  (typeMethodAddressing == numDirectRegisterAddressing) ) {
		*destinationOperand = atoi(headListWord->word + 1);
		insertCodeTable(headCodeTable, numDirectRegisterAddressing,0,0,0, *destinationOperand,*sourceOperand,0,0,0);
		return;
	}
	else {
		if ( (*sourceOperand != -1) && typeMethodAddressing != numDirectRegisterAddressing ) {
			insertCodeTable(headCodeTable, numDirectRegisterAddressing, 0, 0, 0, 0, *sourceOperand, 0, 0, 0);
		}
	}

	if (typeMethodAddressing == numImmediateAddressing) {
		if (!flagMacro)
			insertCodeTable(headCodeTable, numImmediateAddressing, 0, 0, 0, 0, 0, 0, 0, atoi(headListWord->word + 1));
		else
			insertCodeTable(headCodeTable, numImmediateAddressing, 0, 0, 0, 0, 0, 0, 0, valMacro);
	}

	if (typeMethodAddressing == numDirectRegisterAddressing && flagSecondOperand == 1) {
		*sourceOperand = atoi(headListWord->word + 1);
		return;
	}
	else
		if (typeMethodAddressing == numDirectRegisterAddressing && flagSecondOperand == 2) {
			*destinationOperand = atoi(headListWord->word + 1);
			insertCodeTable(headCodeTable, numDirectRegisterAddressing, 0, 0, 0, *destinationOperand,0, 0, 0, 0);
		}

	if (typeMethodAddressing == Indexing) {
		if (!flagMacro) {
			insertCodeTable(headCodeTable, numArrayStartAddress, 0, 3, 0, 0, 0, 0, 4095, 0);
			insertCodeTable(headCodeTable, numIndexNumber, 0, 0, 0, 0, 0, valMacro, 0, 0);
		}
		else {
			insertCodeTable(headCodeTable, numArrayStartAddress, 0, 3, 0, 0, 0, 0, 4095, 0);
			insertCodeTable(headCodeTable, numIndexNumber, 0, 0, 0, 0, 0, valMacro, 0, 0);
		}
	}

	if (typeMethodAddressing == numDirectAddressing)
		insertCodeTable(headCodeTable, numDirectAddressing, 0, 3, 0, 0, 0, 0, 4095, atoi(headListWord->word + 1));

}

static void macroeProcessor(ptrListWord headListWord, ptrListEror* headListEror, ptrSymbolsTable* headSymbolsTable, ptrListOperationCode _listOperationCode, ptrListNamesRegister _listNamesRegister, char* line) {

	int count;

	char* c1;

	char* c2;

	char* c3;

	line = makeSpace(line, '=');
	line = deleteExtraWhiteSpace(line);
	headListWord = getAlltWord(headListWord, line);

	count = getCountWord(headListWord);

	if (!(count == 4)) {
		insertListEror(headListEror, eror4, lineNumber);
		return;
	}

	c1 = headListWord->next->word;
	c2 = headListWord->next->next->word;
	c3 = headListWord->next->next->next->word;

	if (legalLabel(c1, _listOperationCode, _listNamesRegister, *headSymbolsTable) && (!strcmp(c2, "=")) && (legalNumber(c3))) {
		insertDataSymbolsTable(headSymbolsTable, c1, atoi(c3), (int)macroSentence);
		return;
	}

	if (strcmp(c2, "=") != 0) {
		insertListEror(headListEror, eror2, lineNumber);
		return;
	}

	insertListEror(headListEror, eror3, lineNumber);
}


void printCodeTable(ptrWordMemory head) {

	ptrWordMemory temp;

	for (temp = head; temp; temp = temp->next) {
		bin(temp->data._dataTable.valData);
		printf("\n\n");
	}

}


void bin(unsigned n)
{
	static int i = 0;

	unsigned mask = 8192;

	printf("%d.   ",i);

	i++;

	while (mask) {
		if ((n & mask) != 0)
			printf("1");
		else
			printf("0");

		mask = mask >> 1;
	}
}

void fixAddresses(ptrSymbolsTable* head,int ic) {

	ptrSymbolsTable temp;

	for (temp = *head; temp; temp = temp->next)
		if (temp->isData || temp->isEntry)
			temp->address += START_ADDRESS_MEMORY + ic;

}


