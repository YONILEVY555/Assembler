


#include "myString.h"

char* deleteExtraWhiteSpace(const char* line) {

	int lastCharacter;
	int length, c, d;
	char* newLine = NULL;

	c = d = 0;

	length = strlen(line);

	newLine = (char*)malloc(length + PLACE_TO_END_STRING);

	if (newLine == NULL)
		exit(EXIT_FAILURE);

	while (*(line + c) != END_STRING) {

		if ((*(line + c) == SPACE) || (*(line + c) == TAB)) {
			int temp = c + 1;

			if (*(line + temp) != END_STRING) {

				while ((*(line + temp) == SPACE && *(line + temp) != END_STRING) ||
					  (*(line + temp) == TAB && *(line + temp) != END_STRING)){

					if ((*(line + temp) == SPACE) || (*(line + temp) == TAB)) {
						c++;
					}
					temp++;
				}
			}
		}

		*(newLine + d) = *(line + c);
		c++;
		d++;
	}

	*(newLine + d) = END_STRING;

	if ((newLine[FIRST_CHARACTER] == SPACE) || (newLine[FIRST_CHARACTER] == TAB))

		newLine++;

	lastCharacter = strlen(newLine) - 1;

	if ((newLine[lastCharacter] == SPACE) || (newLine[lastCharacter] == TAB))

		newLine[lastCharacter] = END_STRING;
	
	return newLine;

}

char* makeSpace(char* line, char c) {

	int i, j;
	char* newline = (char*)malloc(sizeof(char) * (MAX_LENGTH_LINE * 4));

	for (i = 0, j = 0; i < strlen(line); i++) {
		if (line[i] == c) {
			newline[j] = SPACE;
			newline[++j] = line[i];
			newline[++j] = SPACE;
			j++;
		}
		else
			newline[j++] = line[i];
	}

	newline[j] = END_STRING;
	return  newline;
}

