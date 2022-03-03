
#include "isLegal.h"

int legalLabel(char* label, const ptrListOperationCode _listOperationCode, const ptrListNamesRegister _listNamesRegister, const ptrSymbolsTable _symbolsTable) {

	int i, length;
	char firstCharacter;
	ptrSymbolsTable tempSymbolsTable;
	firstCharacter = label[FIRST_CHARACTER];

	if (label[strlen(label) - 1] == ':')
		label[strlen(label) - 1] = END_STRING;;

	length = strlen(label);

	if (!isalpha(firstCharacter))
		return FALSE;

	if (length > MAX_LENGTH_LABEL)
		return FALSE;

	for (i = 0; i < length; i++) {
		if (!(isalpha(label[i]) || isdigit(label[i])))
			return FALSE;
	}

	for (i = mov; i <= stop; i++) {
		if (!strcmp(label, _listOperationCode->_operationCode[i].nameAction))
			return FALSE;
	}


	for (i = r0; i <= r7; i++) {
		if (!strcmp(label, _listNamesRegister->dataRegister[i].names))
			return FALSE;
	}

	for (tempSymbolsTable = _symbolsTable; tempSymbolsTable != NULL; tempSymbolsTable = tempSymbolsTable->next) {
		if (!strcmp(label, tempSymbolsTable->nameLabel))
			return FALSE;
	}

	return TRUE;
}


int legalNumber(char* num) {

	int i;
	int length = strlen(num);

	for (i = 0; i < length; i++)
		if (i == 0) {
			if (!((num[i] == '-') || (num[i] == '+') || (num[i] >= '0' && num[i] <= '9'))) {
				return FALSE;
			}
		}

		else {
			if (!(num[i] >= '0' && num[i] <= '9'))
				return FALSE;
		}

	return TRUE;
}

void legalEntryOrExtern(ptrSymbolsTable headSymbol, ptrListWord _headListWord, ptrListEror* headListEror,int lineNumber, const ptrListOperationCode _listOperationCode, const ptrListNamesRegister _listNamesRegister, const ptrSymbolsTable _symbolsTable) {

	ptrListWord  tempWord = _headListWord;

	int i = 0;
	int flagComma = FALSE;
	int flagLabel = FALSE;

	while (tempWord) {

		if (!strcmp(tempWord->word, ","))
			flagComma++;
		else {

			if (i)
				if (flagLabel && flagComma == FALSE) {
					insertListEror(headListEror, eror7, lineNumber);
					return;
				}

			flagLabel++;

			if (flagComma == 1) {
				flagLabel = FALSE;
				flagComma = FALSE;
			}

			if(!legalLabel(tempWord->word,_listOperationCode,_listNamesRegister,NULL) ){
				insertListEror(headListEror, eror6, lineNumber);
				return;
			}

		}

		if (flagComma > 1) {
			insertListEror(headListEror, eror7, lineNumber);
			return;
		}

		if (!i)
			if (flagLabel == FALSE && flagComma) {
				insertListEror(headListEror, eror5, lineNumber);
				return;
			}

		tempWord = tempWord->next;

		i++;

	}

	if (flagComma)
		insertListEror(headListEror, eror5, lineNumber);

}

int isLegalOperationSentece(int typeMethodAddressing1, int  typeMethodAddressing2,int lineNumber,int countOperator,ptrListEror * headListEror) {

	if (typeMethodAddressing1 == Indexing && typeMethodAddressing2 == Indexing) {
		if (countOperator != 9) {
			insertListEror(headListEror, eror18, lineNumber);
			return FALSE;
		}
	}
	else {
		if (((typeMethodAddressing1 == Indexing) || (typeMethodAddressing2 == Indexing))) {
			if (countOperator != 6) {
				insertListEror(headListEror, eror18, lineNumber);
				return FALSE;
			}
		}
			else {
				if (countOperator != 3) {
					insertListEror(headListEror, eror18, lineNumber);
					return FALSE;
				}
			}
		}

	return TRUE;
}
