

#include "linkedLists.h"

ptrWordMemory Meld(ptrWordMemory List1, ptrWordMemory List2)
{
	ptrWordMemory List1_head = List1;
	if (List1 == NULL) return List2;
	if (List2 == NULL) return List1;
	while (List1->next != NULL)
		List1 = List1->next;
	List1->next = List2;
	return List1_head;
}

ptrListWord insertWord(ptrListWord head, const char* word) {

	ptrListWord newWord = NULL;
	ptrListWord temp = NULL;

	if (!head) {

		head = (ptrListWord)malloc(sizeof(listWord));
		head->word = (char*)malloc(sizeof(char) * (strlen(word) + PLACE_TO_END_STRING));
		head->word[FIRST_CHARACTER] = END_STRING;

		head->next = NULL;

		strcpy(head->word, word);

		return head;

	}

	for (temp = head; temp->next; temp = temp->next);

	newWord = (ptrListWord)malloc(sizeof(listWord));
	newWord->word = (char*)malloc(sizeof(char) * (strlen(word) + PLACE_TO_END_STRING));
	newWord->word[FIRST_CHARACTER] = END_STRING;

	newWord->next = NULL;

	strcpy(newWord->word, word);

	temp->next = newWord;

	return head;
}

void insertWord2(ptrListWord* head, const char* word) {

	ptrListWord   temp;
	ptrListWord   newItem = (ptrListWord)malloc(sizeof(listWord));

	newItem->word = (char*)malloc(sizeof(char)*MAX_LENGTH_LABEL);

	newItem->next = NULL;
	strcpy(newItem->word, word);

	if (!(*head)) {
		*head = newItem;
		return;
	}

	for (temp = *head; temp->next; temp = temp->next);
	temp->next = newItem;

}

void insertDataSymbolsTable(ptrSymbolsTable* head, char* label, int num, int type) {

	ptrSymbolsTable  temp;
	ptrSymbolsTable newItem = (ptrSymbolsTable)malloc(sizeof(symbolsTable));

	newItem->address =FALSE;
	newItem->isData = FALSE;
	newItem->isEntry = FALSE;
	newItem->AttachedOfOperationSentence = FALSE;
	newItem->isExtern = FALSE;
	newItem->isMacro = FALSE;
	newItem->next = FALSE;
	newItem->next = NULL;

	strcpy(newItem->nameLabel, label);

	if (type == macroSentence) {

		newItem->address = num;
		newItem->isMacro = TRUE;

	}
	else {
		if (type == data || type == string) {

			newItem->address = num;
			newItem->isData = TRUE;

		}
		else {

			if (type == externn) {

				newItem->isExtern = TRUE;
				newItem->address = 0;
			}
			else {
				if (type == entry) {

					newItem->isEntry = TRUE;
					newItem->address = num;
				}
				else {

					newItem->address = num;
					newItem->AttachedOfOperationSentence = TRUE;

				}
			}
		}
	}

	if (!(*head)) {

		*head = newItem;
		return;

	}

	for (temp = *head; temp->next; temp = temp->next);

	temp->next = newItem;
	return;
}


void insertCodeTable(ptrWordMemory* head,int type,int operCode,int are,int code,int valDestinationOperand,int valSourceOperand,int index,int address,int val) {

	ptrWordMemory  temp;
	ptrWordMemory newItem = (ptrWordMemory)malloc(sizeof(wordMemory));

	newItem->next = NULL;

	switch (type) {

	case numFirstWordMemory:

		if (valDestinationOperand == -1)
			valDestinationOperand = 0;

		if (valSourceOperand == -1)
			valSourceOperand = 0;

		newItem->data._firstWordMemory.ARE = 0;
		newItem->data._firstWordMemory.unused = 0;
		newItem->data._firstWordMemory.opcode = code;
		newItem->data._firstWordMemory.destinationOperand = valDestinationOperand;
		newItem->data._firstWordMemory.sourceOperand = valSourceOperand;

		break;
	case numImmediateAddressing:		 

		newItem->data._immediateAddressing.ARE = are;
		newItem->data._immediateAddressing.val = val;

		break;
	case numDirectAddressing:

		newItem->data._directAddressing.address = address;
		newItem->data._directAddressing.ARE = are;

		break;
	case numIndexNumber:

		newItem->data._indexNumber.ARE = are;
		newItem->data._indexNumber.index = index;

		break;

	case numArrayStartAddress:

		newItem->data._arrayStartAddress.address = address;
		newItem->data._arrayStartAddress.ARE = are;

		break;
	case numDirectRegisterAddressing:

		newItem->data._directRegisterAddressing.ARE = 0;
		newItem->data._directRegisterAddressing.destinationRegister = valDestinationOperand;
		newItem->data._directRegisterAddressing.sourceRegister = valSourceOperand;
		newItem->data._directRegisterAddressing.unused = 0;

		break;
	}

	if (!(*head)) {

		*head = newItem;

		return;

	}

	for (temp = *head; temp->next; temp = temp->next);

	temp->next = newItem;

	return;
}



void insertListEror(ptrListEror* head, int code,int lineNumber) {

	ptrListEror   temp;
	ptrListEror  newItem = (ptrListEror)malloc(sizeof(listEror));

	newItem->code = code;
	newItem->lineNumber = lineNumber;
	newItem->next = NULL;

	if (!(*head)) {
		*head = newItem;
		return;
	}

	for (temp = *head; temp->next; temp = temp->next);
	temp->next = newItem;

	return;
}


void insertListData(ptrWordMemory* head, int val) {

	ptrWordMemory   temp;
	ptrWordMemory  newItem = (ptrWordMemory)malloc(sizeof(wordMemory));

	newItem->data._dataTable.valData = val;
	newItem->next = NULL;

	if (!(*head)) {
		*head = newItem;
		return;
	}

	for (temp = *head; temp->next; temp = temp->next);
	temp->next = newItem;

	return;
}


int insertAllNumber(ptrListEror* headListEror, ptrSymbolsTable headSymbolTable, ptrListWord headListWord, ptrWordMemory* headListDataTable,int lineNumber) {

	ptrListWord  tempPtrListWord;

	int count = 0;
	int flagMacro;
	int valMacro;
	int flagNumber = 0;
	int flagComma = 0;

	for (tempPtrListWord = headListWord; tempPtrListWord; tempPtrListWord = tempPtrListWord->next) {

		if (strcmp(tempPtrListWord->word, ",") != 0) {
			if (legalNumber(tempPtrListWord->word)) {
				if (flagComma) {

					flagNumber++;
					flagComma--;

				}
				else
					flagNumber++;

				insertListData(headListDataTable, atoi(tempPtrListWord->word));
				count++;
			}

			else {
				valMacro = getvalMacro(headSymbolTable, tempPtrListWord->word, &flagMacro);
				if (flagMacro) {
					if (flagComma) {
						flagNumber++;
						flagComma--;
					}
					else
						flagNumber++;

					insertListData(headListDataTable, valMacro);
					count++;
				}
				else {
					insertListEror(headListEror, eror6, lineNumber);
					return FALSE;
				}
			}
		}

		else {
			if (flagNumber == 1) {
				flagNumber--;
				flagComma++;
			}

			else {
				insertListEror(headListEror, eror7, lineNumber);
				return FALSE;
			}
		}
	}

	if (flagComma) {
		insertListEror(headListEror, eror8, lineNumber);
		return FALSE;
	}



	return count;
}



void insertString(ptrWordMemory* headListDataTable, char* string) {

	int i;

	for (i = 0; i < strlen(string); i++)
		insertListData(headListDataTable, (int)string[i]);

	insertListData(headListDataTable,(int)'\0');

}

ptrListWord getAlltWord(ptrListWord head, const char* line) {

	char* newLine = deleteExtraWhiteSpace(line);
	char* word = NULL;
	int finish = FALSE;
	int index = INDEX_ZERO;
	head = NULL;

	while (!finish) {
		word = getNextWord(index, newLine, &finish);
		head = insertWord(head, word);
		index += (strlen(word) + 1);
	}

	return head;
}

int getCountWord(ptrListWord head){

	int counter = 0;

	while (head != NULL) {
		counter++;
		head = head->next;
	}

	return counter;
}

int getCountWord2(ptrWordMemory head) {

	int counter = 0;

	while (head != NULL) {
		counter++;
		head = head->next;
	}

	return counter;
}


void printEror(ptrListEror listEror, ptrListErorTypes listErorTypes,char *name){

	int i;
	ptrListEror temp1;

	printf("\nSeveral program errors were found.\nProgram name : %s\n\n", name);

	for (temp1 = listEror; temp1; temp1 = temp1->next) {
		for (i = 0; i < NUMBER_EROR;i++) {
			if ( listErorTypes->_EROR[i].errorCode == temp1->code ) {
				printf("\nline number %d : %s\n", temp1->lineNumber, listErorTypes->_EROR[i].erorMessage);
				break;
			}
		}
	}
}

void deleteAllLinkedList(ptrListWord * _headListExt, ptrListEror* headListEror, ptrSymbolsTable* headSymbolsTable, ptrWordMemory* headTableData, ptrWordMemory* headCodeTable) {

	{
		DELETE_LIST(ptrListWord, _headListExt)
	}

	{
		DELETE_LIST(ptrListEror, headListEror)
	}

	{
		DELETE_LIST(ptrSymbolsTable, headSymbolsTable)
	}

	{
		DELETE_LIST(ptrWordMemory, headCodeTable)
	}

	*headTableData = NULL;

}



