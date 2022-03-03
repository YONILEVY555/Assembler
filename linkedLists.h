
#include <stdlib.h>

#ifndef _L_L
#define _L_L

#include "myConstants.h"
#include "myString.h"
#include "myStructure.h"
#include "isLegal.h"
#include "getData.h"

/*The function gets a single-word string, and puts it in a linked list. */
ptrListWord insertWord(ptrListWord head, const char* word);

/*The function inserts symbol into the symbol table.*/
void insertDataSymbolsTable(ptrSymbolsTable* head, char* label, int num, int type);

/*The function inserts word memory into the code table. */
void insertCodeTable(ptrWordMemory* head, int type, int operCode, int are, int code, int valDestinationOperand, int valSourceOperand, int index, int address, int val);

/*The function inserts a new error code into the linked list and the line where the error was found.*/
void insertListEror(ptrListEror* head, int code,int lineNumber);

/*The function inserts number into the data table.*/
void insertListData(ptrWordMemory* head, int val);

/*The function receives a string of numbers and commas.
The function will enter all numbers into the data table. */
int insertAllNumber(ptrListEror* headListEror, ptrSymbolsTable headSymbolTable, ptrListWord headListWord, ptrWordMemory* headListDataTable,int lineNumber);

/*The function receives a string of characters.
The function will enter the ascii value of each character into the data table. */
void insertString(ptrWordMemory* headListDataTable, char* string);

/*The function gets a string and puts all words into a linked list.*/
ptrListWord getAlltWord(ptrListWord head, const char* line);

/*The function gets a linked list head, and returns the number of parts in the list.*/
int getCountWord(ptrListWord head);

/*A function that merges two linked lists into one linked list.*/
ptrWordMemory Meld(ptrWordMemory List1, ptrWordMemory List2);

/*The function gets a single-word string, and puts it in a linked list.*/
void insertWord2(ptrListWord* head, const char* word);

/*The function gets a linked list with all error codes and the row number where each error occurred.
The function also receives an array of strings with all error messages per error code.
The function will print all errors. */
void printEror(ptrListEror listEror, ptrListErorTypes listErorTypes,char *name);

/*The function deletes all linked lists.*/
void deleteAllLinkedList(ptrListWord* _headListExt, ptrListEror* headListEror, ptrSymbolsTable* headSymbolsTable, ptrWordMemory* headTableData, ptrWordMemory* headCodeTable);

/*The function gets a linked list head, and returns the number of parts in the list.*/
int getCountWord2(ptrWordMemory head);

/*Macro to delete different types of linked lists. */

#define DELETE_LIST(type,head)\
type current = *head;\
type next;\
while (current != NULL)\
{\
	next = current->next;\
	free(current);\
	current = next;\
}\
*head=NULL;

#endif
