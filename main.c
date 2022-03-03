



#include <stdio.h>
#include "myStructure.h"
#include "linkedLists.h"
#include "secondRead.h"
#include "buildOutputFiles.h"


int firstRead(FILE* fd,
	const ptrListOperationCode _listOperationCode,
	const ptrDataMacro _dataMacro,
	const ptrListTypesDirectiveSentence _listTypesDirectiveSentence,
	const ptrListNamesRegister _listNamesRegister,
	ptrWordMemory* headListDataTable,
	ptrWordMemory* headListCode,
	ptrSymbolsTable* headSymbolsTable,
	ptrListEror* headListEror);


int main(int argc, char* argv[])

{

    int i;
	int lengthCode;
	int	lengthData;
	char* name = NULL;
	FILE* fd = NULL;
	ptrListWord _headListExt = NULL;
	ptrListOperationCode _listOperationCode = NULL;
	ptrDataMacro _dataMacro = NULL;
	ptrListTypesDirectiveSentence _listTypesDirectiveSentence = NULL;
	ptrListNamesRegister _listNamesRegister = NULL;
	ptrWordMemory headTableData = NULL;
	ptrWordMemory  headCodeTable = NULL;
	ptrListEror headListEror = NULL;
	ptrSymbolsTable headSymbolsTable = NULL;
	ptrListErorTypes headListErorTypes = NULL;

	_listOperationCode = createListOperationCode(_listOperationCode);
	_dataMacro = createDataMacro(_dataMacro);
	_listTypesDirectiveSentence = createListTypesDirectiveSentence(_listTypesDirectiveSentence);
	_listNamesRegister = createListNamesRegister(_listNamesRegister);
	headListErorTypes = createListErorTypes(headListErorTypes);


	for (i = argc; i > 1; i--) {

		name = (char*)malloc(sizeof(char)*(strlen(argv[i-1])+PLACE_TO_END_STRING+3));
		name[FIRST_CHARACTER] = END_STRING;
		strcat(name,argv[i-1]);
		strcat(name,".as");

		fd = fopen(name, "r");
		firstRead(fd, _listOperationCode, _dataMacro, _listTypesDirectiveSentence, _listNamesRegister, &headTableData, &headCodeTable, &headSymbolsTable, &headListEror);
		fclose(fd);
fd=NULL;
		if (headListEror)
			printEror(headListEror, headListErorTypes,name);
		else {

			fd = fopen(name, "r");

			secondRead(headTableData, &headSymbolsTable, &headCodeTable, fd, _listOperationCode, _dataMacro, _listTypesDirectiveSentence, _listNamesRegister, &headListEror, &_headListExt);

			if (headListEror)
				printEror(headListEror, headListErorTypes,name);
			else {

				lengthCode = getCountWord2(headCodeTable);
				lengthData = getCountWord2(headTableData);
				headCodeTable = Meld(headCodeTable, headTableData);

				createFiles(argv[i-1],headCodeTable, headSymbolsTable, lengthCode, lengthData, _headListExt);

			}
		}
		

		deleteAllLinkedList(&_headListExt, &headListEror, &headSymbolsTable, &headTableData, &headCodeTable);

		if(fd)
		fclose(fd);
	}

	

	return 0;
}









