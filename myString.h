#include <stdlib.h>

#ifndef  _MY_S
#define _MY_S

#include "myConstants.h"
#include "myStructure.h"

/*The function deletes all unnecessary white characters.*/
char* deleteExtraWhiteSpace(const char* line);

/*The function accepts both a string and a single character (c).
The function will create a new string with a space before and after each character equal to c.*/
char* makeSpace(char* line, char c);

#endif
