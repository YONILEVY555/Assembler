assembler : myStructure.o linkedLists.o firsRead.o myString.o getData.o isLegal.o secondRead.o buildOutputFiles.o main.o 
	gcc -g -Wall -ansi -pedantic myStructure.o linkedLists.o firsRead.o myString.o main.o getData.o isLegal.o secondRead.o buildOutputFiles.o  -o assembler

main.o : main.c myStructure.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o

myStructure.o : myStructure.c myStructure.h
	gcc -c -Wall -ansi -pedantic myStructure.c -o myStructure.o

myString.o : myString.c myString.h 
	gcc -c -Wall -ansi -pedantic myString.c -o myString.o

linkedLists.o : linkedLists.c linkedLists.h
	gcc -c -Wall -ansi -pedantic linkedLists.c -o linkedLists.o

firsRead.o : firsRead.c firstRead.h
	gcc -c -Wall -ansi -pedantic firsRead.c -o firsRead.o

getData.o : getData.c getData.h
	gcc -c -Wall -ansi -pedantic getData.c -o getData.o

isLegal.o : isLegal.c isLegal.h
	gcc -c -Wall -ansi -pedantic isLegal.c -o isLegal.o

secondRead.o : secondRead.c secondRead.h
	gcc -c -Wall -ansi -pedantic secondRead.c -o secondRead.o

buildOutputFiles.o : buildOutputFiles.c buildOutputFiles.h
	gcc -c -Wall -ansi -pedantic buildOutputFiles.c -o buildOutputFiles.o
