/*This is a test combination of textsort and textsort2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LEN 128
#define MAX_FILE_LEN 150

int compareLines(const void *elem1, const void *elem2);
int compareString(char *str1, char *str2, int key);
void sort(char *ptArray[]);
char* getLastWord(char *wordArray[]);

// Define an array of pointers, each element points to a char
char *ptArray[4];
int key = 0;  // default key to sort upon - the first word in each line


int main(int argc, char *argv[]){
  printf("Running program: %s\n", argv[0]); // the name of executable as first argument

  char *fileName = NULL; // a pointer to a string containing name of the file
  FILE *file;   // file pointer
//  int key = 0;  // default key to sort upon - the first word in each line

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


  char **fileArr = malloc(sizeof(char*) * fileLen);
  char *lineArr = (char *) malloc(sizeof(char*) * (MAX_LINE_LEN + 1));

  int i = 0;
  while(1){
    if(i >= MAX_FILE_LEN)  {
      fileLen = fileLen + MAX_FILE_LEN;
      fileArr = realloc(fileArr, sizeof(char*) * fileLen);
    }
    fileArr[i] = malloc(sizeof(char*) * (MAX_LINE_LEN + 1));
    if(fgets(lineArr, MAX_LINE_LEN, file) != NULL)	{
      if(strlen(lineArr) > MAX_LINE_LEN){
        fprintf(stderr, "Line too long");
        exit(1);  // exit with return code 1
      }
      strcpy(fileArr[i], lineArr);  // writing content in one line to array
    }
    else{  // reach to the end
      free(fileArr[i]);
      break;
    }
    i++;

  }
  fclose(file);

  for (char **a = fileArr; *a; a++){
    printf("%s\n", *a);
    free(*a);
    fileArr[i] = NULL;
  }

  free(lineArr);
  free(fileArr);
  return 0;
}

//  do the pairwise comparison of values in the array
int compareLines(const void *elem1, const void *elem2) {
  
  /* Cast parameters to actual type */
  char **strptr1 = (char **) elem1;  
  char **strptr2 = (char **) elem2;
   
  /* Dereference to get the strings */
  char *str1 = *strptr1;
  char *str2 = *strptr2;

  char str1copy[strlen(str1)];
  char str2copy[strlen(str2)];
   
  // allocates memory for the copy
  // char *str1copy = (char *)malloc(strlen(str1));
  
  // make a copy of the original line for later use
  if ((str1 != NULL) && (str2 != NULL)) {
  strcpy(str1copy, str1);
  strcpy(str2copy, str2);
  }
 
  //printf("Compare function result: %d \n", result);
  return compareString(str1copy, str2copy, key);
}

/**
 * Method to cut and compare strings with a given key
 *
 **/
int compareString(char *str1copy, char *str2copy, int key) {
  char *wordArray1[MAX_LINE_LEN];
  char *wordArray2[MAX_LINE_LEN];
  
  // On the first call, string to be parsed should be specified 
  wordArray1[0] = strtok(str1copy, " ");
  int i = 0;
  // On the subsequent calls, str must be NULL. Save words into an array
  while(wordArray1[i] != NULL){
    i++;
    wordArray1[i] = strtok(NULL, " ");  
  } 

  // On the first call, string to be parsed should be specified 
  wordArray2[0] = strtok(str2copy, " ");
  int m = 0;
  // On the subsequent calls, str must be NULL. Save words into an array
  while(wordArray2[m] != NULL){
    m++;
    wordArray2[m] = strtok(NULL, " ");  
  }

  char *word1 = NULL;
  char *word2 = NULL;

  if ((wordArray1[key] == NULL) && (wordArray2[key] != NULL)) {
    word1 = getLastWord(wordArray1);
    word2 = wordArray2[key];
  } else if ((wordArray1[key] != NULL) && (wordArray2[key] == NULL)) {
    word2 = getLastWord(wordArray2);
    word1 = wordArray1[key];
  } else if  ((wordArray1[key] == NULL) && (wordArray2[key] == NULL)) {
    word1 = getLastWord(wordArray1);
    word2 = getLastWord(wordArray2);
  } else if ((wordArray1[key] != NULL) && (wordArray2[key] != NULL)) {
    word1 = wordArray1[key];   
    word2 = wordArray2[key];
  }
  
  return strcmp(word1, word2);
}

char* getLastWord(char *wordArray[]) {
  if (wordArray[0] != NULL) {
    int i = 0;
    while (wordArray[i] != NULL) {
      i = i + 1;
    }
    return wordArray[i - 1];
  }
  return 0;
}
