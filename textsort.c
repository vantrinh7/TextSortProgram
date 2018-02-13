#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LEN 128
#define MAX_FILE_LEN 50

int main(int argc, char *argv[]){
  printf("Running program: %s\n", argv[0]); // the name of executable as first argument

  char *fileName = NULL; // a pointer to a string containing name of the file
  FILE *file;   // file pointer
  int key = 0;  // default key to sort upon - the first word in each line

  if (argc == 2)
    fileName = argv[1];
  // reads through command line arguments
  else if (argc == 3){
    fileName = argv[2];
    if (argv[1][0] == '-'){ // looks for the dash sign
      key = -strtol(argv[1], NULL, 10) - 1; // coverts string to int, base 10; then convert it to an array position
      printf("sort key = %d\n", key + 1); // adds back for a better understanding
    }
    // else: not enough parameters have been passed || more than expected
    else{
      fprintf(stderr, "Error: Bad command line parameters\n"); // send the error message to standard error
      exit(1);	// exit with return code 1
    }
  }
  // if inputing a null file
  if (fileName == NULL) {
    fprintf(stderr, "Error: Bad command line parameters\n");
    exit(1);  // exit with return code 1
  }

  file = fopen(fileName, "r"); // opens a file for reading
  if(file == NULL)  {
    fprintf(stderr, "Error: Cannot open file %s\n", fileName );
    exit(1);  // exit with return code 1
  }

  fseek(file, 0, SEEK_END);   // seek to end of file
  int fileLen = ftell(file);  // get current file pointer
  fseek(file, 0, SEEK_SET);   // seek back to beginning of file
  printf("file length = %d\n", fileLen);

  char **fileArr = (char **) malloc(sizeof(char*) * fileLen);

  char *lineArr = (char *) malloc(sizeof(char*) * (MAX_LINE_LEN));
  int i = 0;
  while(1){
     if(i >= MAX_FILE_LEN)  {
       fileLen = fileLen + MAX_FILE_LEN;
       fileArr = (char **) realloc(fileArr, sizeof(char*) * fileLen);
     }
    fileArr[i] = (char *) malloc(MAX_LINE_LEN);
    if(fgets(lineArr, MAX_LINE_LEN, file) != NULL)	{
      if(strlen(lineArr) > MAX_LINE_LEN){
        fprintf(stderr, "Line too long");
        exit(1);  // exit with return code 1
      }
      strcpy(fileArr[i], lineArr);  // writing content in one line to array
    }
    else { // reach to the end
      break;
    }
    i++;
  }
  fclose(file);
  for (int i = 0; i <= fileLen; i++)
    printf("%s\n", fileArr[i]);

  free(lineArr);
  free(fileArr);
  return 0;
}
