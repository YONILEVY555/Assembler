
#include "secondRead.h"

static int lineNumber = 1;

void secondRead(ptrWordMemory headTableData, ptrSymbolsTable* headSymbolsTable, ptrWordMemory* headCodeTable, FILE* fd, const ptrListOperationCode _listOperationCode, const ptrDataMacro _dataMacro, const ptrListTypesDirectiveSentence _listTypesDirectiveSentence, const ptrListNamesRegister _listNamesRegister, ptrListEror* headListEror, ptrListWord* _headListExt){

	ptrListWord _headListWord = NULL;
	char* line = (char*)malloc(sizeof(char) * MAX_LENGTH_LINE);
	int flagLabel;
	int typeSentence;


	while ( (line = fgets(line, MAX_LENGTH_LINE, fd )) ) {

		line[strlen(line) - 1] = END_STRING;
		line = makeSpace(line, '[');
		line = makeSpace(line, ']');
		line = makeSpace(line, ',');
		line = deleteExtraWhiteSpace(line);
		_headListWord = getAlltWord(_headListWord, line);

		typeSentence = getTypeSentence(_headListWord,
			_listOperationCode,
			_dataMacro,
			_listTypesDirectiveSentence,
			_listNamesRegister,
			NULL,
			&flagLabel,
			line);

		
		if (flagLabel) {
			if (typeSentence == operationSentence) {
				func(headCodeTable, _headListWord->next, _listNamesRegister, headSymbolsTable, _listOperationCode, headListEror, flagLabel, _headListExt);
			}
			if (typeSentence == directiveSentence) {
				if (getCountWord(_headListWord) > 2)
					if(!strcmp(_headListWord->next->word,".entry"))
						markerEntry(*headSymbolsTable, _headListWord->next->next, headListEror);
			}
		}
		else {
			if (typeSentence == operationSentence) {
				func(headCodeTable, _headListWord, _listNamesRegister, headSymbolsTable, _listOperationCode, headListEror, flagLabel, _headListExt);
			}
			if (typeSentence == directiveSentence) {
				if (getCountWord(_headListWord) > 1)
					if (!strcmp(_headListWord->word,".entry"))
						markerEntry(*headSymbolsTable, _headListWord->next, headListEror);
			}
		}

		lineNumber++;

	}
		lineNumber = 1;
}

void func(ptrWordMemory* headListCodeList,ptrListWord _headListWord ,const ptrListNamesRegister _listNamesRegister, ptrSymbolsTable* headSymbolsTable, const ptrListOperationCode _listOperationCode, ptrListEror* headListEror,int flag, ptrListWord* _headListExt) {

        int result;
	int are;
	int address;
	ptrListWord temp;
	

	for (temp = _headListWord; temp; temp = temp->next) {
		if (legalLabel(temp->word, _listOperationCode, _listNamesRegister, NULL)) {

			if (!legalLabel(temp->word, _listOperationCode, _listNamesRegister, *headSymbolsTable)) {

			result = getAddressAndAre(*headSymbolsTable, temp->word, &are, &address);

				if (result)
					fixesCodeTable(headListCodeList, are, address);

				if (are == 1 && result)
					insertWord2(_headListExt, temp->word);

			}
			else {
				insertListEror(headListEror, (int)eror20, lineNumber);
				return;
			}

		}

	}
		
}

void markerEntry(ptrSymbolsTable headSymbol, ptrListWord _headListWord, ptrListEror* headListEror) {

	ptrSymbolsTable tempSymbol;
	ptrListWord  tempWord = _headListWord;
	
	int flagEntry = FALSE;
	
	while (tempWord) {

		flagEntry = FALSE;

		if (strcmp(tempWord->word, ",") !=0 ){

			for (tempSymbol = headSymbol; tempSymbol; tempSymbol = tempSymbol->next)
				if (!strcmp(tempSymbol->nameLabel, tempWord->word)) {
					flagEntry = TRUE;
					tempSymbol->isEntry = TRUE;
				}

			if (!flagEntry)
				insertListEror(headListEror, eror21, lineNumber);

			
		}

		tempWord = tempWord->next;

	}
}

int getAddressAndAre(ptrSymbolsTable headSymbolsTable, char* label,int *are,int *address){

	ptrSymbolsTable temp;

	for (temp = headSymbolsTable; temp; temp = temp->next)
		if (!strcmp(temp->nameLabel, label)) {

			
			if (temp->isMacro)
				return FALSE;

			if (temp->isExtern) 
				*are = 1;
			else
	            *are = 2;
				
			*address = temp->address;
		}

	return TRUE;
}

void fixesCodeTable(ptrWordMemory* listCodeTable,int are, int address) {

	ptrWordMemory temp;

	wordMemory x;

	x.data._dataTable.valData = ~0;

	for (temp = *listCodeTable; temp; temp = temp->next)
		if (temp->data._dataTable.valData == x.data._dataTable.valData) {
			temp->data._directAddressing.ARE = are;
			temp->data._directAddressing.address = address;
			return;
		}

}
