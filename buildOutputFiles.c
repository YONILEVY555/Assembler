
#include "buildOutputFiles.h"

void createFiles(char *name,ptrWordMemory  headCodeTable,ptrSymbolsTable headSymbol,int lengthCode,int lengthData, ptrListWord _headListExt) {
	createObFile(name,headCodeTable,lengthCode,lengthData);
	createEntFile(name, headSymbol);
	createExtFile(name,headCodeTable, headSymbol,_headListExt, lengthCode);
}

void createObFile(char* name, ptrWordMemory  headCodeTable, int lengthCode, int lengthData) {

	int i = 100, val, result1, result2;
	unsigned mask = 8192;
	FILE* fd = NULL;
	ptrWordMemory  temp = NULL;
	char* newName = (char*)malloc(strlen(name) + PLACE_TO_END_STRING + 3);

	strcat(newName, name);
	strcat(newName, ".ob");

	fd = fopen(newName, "w");

	fprintf(fd, "%d  %d %c",lengthCode,lengthData,'\n');

	for (temp = headCodeTable; temp; temp = temp->next) {

		val = temp->data._dataTable.valData;

		if (i <= 999)
			fprintf(fd, "%d%d ", 0, i++);
		else
			fprintf(fd, "%d ", i++);

		while (mask) {

			result1 = mask & val;
			result2 = (mask >> 1) & val;
		
			if( result1 && result2 )
				fprintf(fd, "%c",'!');

			if ( result1 && (!result2) )
				fprintf(fd, "%c", '%');

			if ( (!result1) && (result2) )
				fprintf(fd, "%c", '#');

			if ((!result1) && (!result2))
				fprintf(fd, "%c", '*');

				mask = mask >> 2;
		}

		mask = 8192;

		fprintf(fd, "%c", '\n');
	}
}


void createEntFile(char* name, ptrSymbolsTable headSymbol ) {


	FILE* fd = NULL;
	ptrSymbolsTable temp;
	char* newName = (char*)malloc(strlen(name) + PLACE_TO_END_STRING + 4);

	strcat(newName, name);
	strcat(newName, ".ent");


	for( temp = headSymbol;temp; temp = temp ->next )
		if (temp->isEntry) {
			if (!fd) {
				fd = fopen(newName, "w");
				if (temp->address <= 999)
					fprintf(fd, "%s %c%d%c", temp->nameLabel, '0', temp->address, '\n');
				else
					fprintf(fd, "%s %d%c", temp->nameLabel, temp->address, '\n');
			}
			else {

				if (temp->address <= 999)
					fprintf(fd, "%s %c%d%c", temp->nameLabel, '0', temp->address, '\n');
				else
					fprintf(fd, "%s %d%c", temp->nameLabel, temp->address, '\n');
			}
		}
}

void createExtFile(char* name, ptrWordMemory  headCodeTable, ptrSymbolsTable  headSymbol, ptrListWord  listNameExt,int lengthCode) {

	ptrWordMemory  temp;
	int i = START_ADDRESS_MEMORY;
	int length = 0;
	FILE* fd = NULL;
	char* newName = (char*)malloc(strlen(name) + PLACE_TO_END_STRING + 4);

	strcat(newName, name);
	strcat(newName, ".ext");

	for (temp = headCodeTable; length < lengthCode; temp = temp->next, length++) {

		if (temp->data._directAddressing.ARE == 1) {
			if (!fd) {
				fd = fopen(newName, "w");
				if (i <= 99)
					fprintf(fd, "%s %d%c", listNameExt->word, i, '\n');
				else
					fprintf(fd, "%s %c%d%c", listNameExt->word, '0', i, '\n');

				listNameExt = listNameExt->next;
			}
			else {
				if (i <= 99)
					fprintf(fd, "%s %d%c", listNameExt->word, i, '\n');
				else
					fprintf(fd, "%s %c%d%c", listNameExt->word, '0', i, '\n');

				listNameExt = listNameExt->next;
			}
		}
		i++;
	}


}
