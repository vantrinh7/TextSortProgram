#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 128
// #define MAX_FILE_LENGTH

int main(int argc, char *argv[]){
	
	printf("Program name: %s\n", argv[0]);	// name of executable as first argument
	
	char *fileName = NULL;	// a pointer to a string containing name of the file
	File *file;	// file pointers

	if (argc == 2)
		fileName = argv[1];
	else if (argc == 3)	{	// read through command line arguments
		fileName = argv[2]
		if (argv[1][0] == '-')	// looks for the dash sign
			key = argv[1][1];
	}
	else{	// not enough parameters have been passed or there're more than expected 
		fprintf(stderr, "Error: Bad command line parameters\n");	// send the error message to stderr (standard error)
		exit(1);	// exit with return code 1
	}
	if (fileName == NULL)
		fprintf(stderr, "Error: Bad command line parameters\n");

	file = fopen(fileName, "r");	// opens a file for reading
	if(file == NULL)
		fprintf(stderr, "Error: Cannot open file %s\n", fileName );
	
	fseek(f, 0, SEEK_END);		// seek to end of file
	fileLength = ftell(file);	// get current file pointer
	fseek(f, 0, SEEK_SET);		// seek back to beginning of file

	char **strArr = (char **) malloc(fileLength);

	int i = 0;
	while(1)	{
		if(i >= fileLength)	{
			strArr = (char **) realloc(strArr, MAX_FILE_LENGTH * 2);
		}
		strArr[i] = (char *) malloc(MAX_LINE_LENGTH);

		if(fgets(strlen[i], MAX_LINE_LENGTH, fileName) == NULL)	{
			strcpy(strArr[i], strlen[i]);	// writing content to array
		}
		i++;
	}

	fclose(file);
	for (int i = 0; i <= fileLength; i++)
		printf("%s\n", strArr[i]);

	free(stArr);	
	return 0;
}
