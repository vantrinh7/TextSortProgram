#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 128
// #define MAX_FILE_LENGTH

int main(int argc, char *argv[]){
  printf("Program name: %s\n", argv[0]); // name of executable as first argument
  char *fileName = NULL; // a pointer to a string containing name of the file
  FILE *file; // file pointers

  if (argc == 2)
    fileName = argv[1];
  else if (argc == 3){ // read through command line arguments
    fileName = argv[2];
    if (argv[1][0] == '-'){ // looks for the dash sign
      int key = -strtol(argv[1], NULL, 10); // covert string to int, base 10
      printf("sort key = %d\n", key);
    }
    else{ // else: not enough parameters have been passed || more than expected
      fprintf(stderr, "Error: Bad command line parameters\n"); // send the error message to standard error
      exit(1);	// exit with return code 1
    }
  }
  if (fileName == NULL)
    fprintf(stderr, "Error: Bad command line parameters\n");

  file = fopen(fileName, "r"); // opens a file for reading
  if(file == NULL)
    fprintf(stderr, "Error: Cannot open file %s\n", fileName );

  fseek(file, 0, SEEK_END); // seek to end of file
  int fileLength = ftell(file); // get current file pointer
  fseek(file, 0, SEEK_SET); // seek back to beginning of file

  char **strArr = (char **) malloc(sizeof(char*) * fileLength);
  char *strLine = (char *) malloc(sizeof(char*) * (MAX_LINE_LENGTH));
  int i = 0;
  while(1){
    if(i >= fileLength)	{
      strArr = (char **) realloc(strArr, fileLength * 2);
    }
    strArr[i] = (char *) malloc(MAX_LINE_LENGTH);
    if(fgets(strLine, MAX_LINE_LENGTH, file) != NULL)	{
      if(strlen(strLine) > MAX_LINE_LENGTH){
	fprintf(stderr, "Line too long");
	exit(1);
      }
      strcpy(strArr[i], strLine); // writing content to array
    }
    else
      break;
    i++;
  }
  fclose(file);
  for (int i = 0; i <= fileLength; i++)
    printf("%s\n", strArr[i]);

  free(strArr);
  return 0;
}
