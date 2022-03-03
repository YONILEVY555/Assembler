

#include "getData.h"

static char* getCopyWord(char* copyWord, char* word);
static int isEmptySentence(const char* line);
static int isNoteSentence(const char* line);
static int isDirectiveSentence(const char* word, const ptrListTypesDirectiveSentence _listTypesDirectiveSentence);
static int isOperationSentence(char* word, const ptrListOperationCode _listOperationCode);
static int isMacroSentence(char* word, const ptrDataMacro _dataMacro);

int getTypeSentence(const ptrListWord head,
	const ptrListOperationCode _listOperationCode,
	const ptrDataMacro _dataMacro,
	const ptrListTypesDirectiveSentence _listTypesDirectiveSentence,
	const ptrListNamesRegister _listNamesRegister,
	const ptrSymbolsTable _symbolsTable,
	int* flagLabel,
	const char* line) {

	char* copyWord = NULL;
	*flagLabel = FALSE;

	if (isEmptySentence(line))
		return (int)emptySentence;

	if (isNoteSentence(line))
		return (int)noteSentence;

	if (isDirectiveSentence(head->word, _listTypesDirectiveSentence))
		return (int)directiveSentence;

	if (isOperationSentence(head->word, _listOperationCode))
		return (int)operationSentence;

	if (isMacroSentence(head->word, _dataMacro))
		return  (int)macroSentence;

	copyWord = getCopyWord(copyWord, head->word);

	if (copyWord[strlen(copyWord) - 1] != ':')
		return (int)eror1;

	if (legalLabel(copyWord, _listOperationCode, _listNamesRegister, _symbolsTable))
		* flagLabel = TRUE;
	else
		return (int)eror1;

	if (head->next)
		if (isDirectiveSentence(head->next->word, _listTypesDirectiveSentence))
			return (int)directiveSentence;

	if (head->next)
		if (isOperationSentence(head->next->word, _listOperationCode))
			return (int)operationSentence;

	return (int)eror1;
}

static char* getCopyWord(char* copyWord, char* word) {
	copyWord = (char*)malloc(sizeof(char) * strlen(word) + 1);
	copyWord[FIRST_CHARACTER] = END_STRING;
	strcpy(copyWord, word);
	return copyWord;
}

int getTypeMethodAddressing(ptrListWord listWord, ptrSymbolsTable _SymbolsTable, ptrListNamesRegister _listNamesRegister, ptrListOperationCode _listOperationCode, int* valMacro, int* flagMacro) {

	int i;
	int  countWord = getCountWord(listWord);

	if ((listWord->word)[FIRST_CHARACTER] == '#' && legalNumber(listWord->word + 1))
		return (int)numImmediateAddressing;

	*valMacro = getvalMacro(_SymbolsTable, listWord->word + 1, flagMacro);

	if ((listWord->word)[FIRST_CHARACTER] == '#' && *flagMacro)
		return  (int)numImmediateAddressing;

	for (i = r0; i <= r7; i++)
		if (!strcmp(listWord->word, _listNamesRegister->dataRegister[i].names))
			return   (int)numDirectRegisterAddressing;

	if (countWord >= 4)
		if ((!strcmp(listWord->next->word, "[")) && (!strcmp(listWord->next->next->next->word, "]"))) {
			if (legalLabel(listWord->word, _listOperationCode, _listNamesRegister, NULL)) {
				if (legalNumber(listWord->next->next->word)) {
					*valMacro = atoi(listWord->next->next->word);
					return  (int)Indexing;
				}
				else {
					*valMacro = getvalMacro(_SymbolsTable, listWord->next->next->word, flagMacro);
					if (*flagMacro)
						return (int)Indexing;
				}
			}
		}

	if (legalLabel(listWord->word, _listOperationCode, _listNamesRegister, NULL))
		return numDirectAddressing;

	return -1;
}



char* getString(char* line, ptrListEror* headListEror,int lineNumber) {

	int i, j, indexLastString, indexStartString, count = 0;

	char* newLine = (char*)malloc(sizeof(char) * (strlen(line) + PLACE_TO_END_STRING));

	for (i = 0; i < strlen(line); i++) {
		if (line[i] == '"') {
			indexStartString = i;
			break;
		}
	}

	for (i = 0; i < strlen(line); i++)
		if (line[i] == '"') {
			indexLastString = i;
			count++;
		}

	if (count < 2) {
		insertListEror(headListEror, eror11, lineNumber);
		return NULL;
	}

	for (i = indexLastString + 1; i < strlen(line); i++) {
		if (line[i] != TAB && line[i] != SPACE) {
			insertListEror(headListEror, eror12, lineNumber);
			return NULL;
		}
	}

	for (i = indexStartString + 1, j = 0; i < indexLastString; i++)
		newLine[j++] = line[i];

	newLine[j] = END_STRING;

	return newLine;

}


int getvalMacro(ptrSymbolsTable headSymbolsTable, char* name, int* flag) {

	ptrSymbolsTable temp;

	for (temp = headSymbolsTable; temp; temp = temp->next) {
		if ((!strcmp(temp->nameLabel, name)) && temp->isMacro) {
			*flag = TRUE;
			return  temp->address;
		}
	}

	*flag = FALSE;

	return FALSE;
}


char* getNextWord(const int index, const char* line, int* finish) {

	int j, i = index, flag = TRUE;

	char* nextWord = (char*)malloc(sizeof(char) * MAX_LENGTH_LINE);

	if (nextWord == NULL)
		exit(EXIT_FAILURE);

	if (!(line[i] != END_STRING && line[i] != SPACE && line[i] != TAB))
		flag = FALSE;

	if (line[i] == END_STRING)
		* finish = TRUE;


	for (j = 0, i = index; flag; i++, j++) {
		if (!(line[i] != END_STRING && line[i] != SPACE && line[i] != TAB))
			flag = FALSE;

		if (line[i] == END_STRING)
			* finish = TRUE;

		if (flag)
			nextWord[j] = line[i];

		else
			nextWord[j] = END_STRING;
	}

	return nextWord;
}


static int isEmptySentence(const char* line) {

	if (line[FIRST_CHARACTER] == END_STRING)
		return (int)emptySentence;
	else
		return FALSE;
}


static int isNoteSentence(const char* line) {

	if (line[FIRST_CHARACTER] == SEMICOLON)
		return (int)noteSentence;

	return FALSE;
}



static int isDirectiveSentence(const char* word, const ptrListTypesDirectiveSentence _listTypesDirectiveSentence) {

	int i;

	for (i = data; i <= externn; i++) {
		if (!strcmp(word, _listTypesDirectiveSentence->_directiveSentence[i].names))
			return (int)directiveSentence;
	}

	return FALSE;
}


static int isOperationSentence(char* word, const ptrListOperationCode _listOperationCode) {

	int i;
	for (i = mov; i <= stop; i++) {
		if (!strcmp(word, _listOperationCode->_operationCode[i].nameAction))
			return (int)operationSentence;
	}

	return FALSE;
}


static int isMacroSentence(char* word, const ptrDataMacro _dataMacro) {

	if (!strcmp(word, _dataMacro->macro))
		return (int)isMacroSentence;

	return FALSE;
}

int getL(int typeMethodAddressing1, int typeMethodAddressing2) {

	int L = 1;

	if (typeMethodAddressing1 == numImmediateAddressing)
		L++;

	if (typeMethodAddressing2 == numImmediateAddressing)
		L++;

	if (typeMethodAddressing1 == numDirectRegisterAddressing || typeMethodAddressing2 == numDirectRegisterAddressing)
		L++;

	if (typeMethodAddressing1 == Indexing)
		L += 2;

	if (typeMethodAddressing2 == Indexing)
		L += 2;

	if (typeMethodAddressing1 == numDirectAddressing)
		L++;

	if (typeMethodAddressing2 == numDirectAddressing)
		L++;

	return L;
}

