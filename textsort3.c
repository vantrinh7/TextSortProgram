#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LEN 128
#define MAX_FILE_LEN 150

char* checkArgs(int argc, char *argv[]);
int readInput(char *fileArr[], char *lineArr, FILE *file);
void printOutput (char *fileArr[], size_t count);
int compareLines(const void *elem1, const void *elem2);
int compareStrings(char *str1, char *str2);
int compareWords(char *wordArray1[], char *wordArray2[]);
bool isBlankLine(char str[]);
char* getLastWord(char *wordArray[]);

// Variable to hold the default key to sort upon
int key = 0;

/**
 * This method opens, reads, closes and sorts the file given.
 *
 * @param int argc argument count
 * @param char *argv[] argument vector
 * @return 0 if success
 **/
int main(int argc, char *argv[]){
  // Declare file pointer, an array of pointers and array for each line
  FILE *file;
  char **fileArr = (char **) malloc(sizeof(char *) * MAX_FILE_LEN);
  char lineArr[MAX_LINE_LEN];

  // Get the file name after checking arguments
  char *fileName = checkArgs(argc, argv);

  // Opens a file for reading
  file = fopen(fileName, "r");
  if(file == NULL)  {
    fprintf(stderr, "Error: Cannot open file %s\n", fileName );
    exit(1);  // exit with return code 1
  }

  // Read the input and save the number of lines of the file
  int numLines = readInput(fileArr, lineArr, file);

  fclose(file);

  // Sort the file, print before and after sorting
  printf("Before sorting: \n");
  printOutput(fileArr, numLines);

  qsort(fileArr, numLines, sizeof(char *), compareLines);

  printf("\nAfter sorting: \n");
  printOutput(fileArr, numLines);

  // Free memory of each char array element in fileArray
  for (int j = 0; j < numLines; j++)
    free(fileArr[j]);

  // Free memory of fileArray
  free(fileArr);

  return 0;
}

/**
 * This method checks the arguments given by the user
 * and prints error messages if needed
 *
 * @param int argc the argument count
 * @param char *argv[] the argument vector
 * @return the file name if file name is given
 **/
char* checkArgs(int argc, char *argv[]) {
   char *fileName = NULL;
   if (argc == 2)
    fileName = argv[1];
  // reads through command line arguments
  else if (argc == 3){
    fileName = argv[2];
    if (argv[1][0] == '-')  // looks for the dash sign
      key = -strtol(argv[1], NULL, 10) - 1; // coverts string to int, base 10; then convert it to an array position
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
  return fileName;
}

/**
 * This method reads the input file into an array of pointers
 * Each element point to a character array that is a line in the file
 *
 * @param char *fileArr[] the array of pointer
 * @param char *lineArr each element in the array
 * @param FILE *file the file being read
 * @return the number of lines in the file
 **/
int readInput(char *fileArr[], char *lineArr, FILE *file) {
  int i = 0;
  while(fgets(lineArr, MAX_LINE_LEN, file) != NULL) {
    if(strlen(lineArr) > MAX_LINE_LEN){
      fprintf(stderr, "Line too long");
      exit(1);  // exit with return code 1
    }
    if (strchr(lineArr, '\n'))
      lineArr[strlen(lineArr) - 1] = '\0';  // removes the new line character

    fileArr[i] = (char *) calloc(MAX_LINE_LEN, sizeof(char));
    strcpy(fileArr[i], lineArr);  // writing content in one line to the array

    if (fileArr[i] == NULL) {
      fprintf(stderr, "Error: Memory allocation failed for line %d.\n", i);
      exit(1);
    }
    i++;
  }
  return i;
}

/**
 * This method prints out the content of an array
 *
 * @param char *fileArr[] the file array to be printed
 * @param size_t count the number of lines of the file (not the array size)
 **/
void printOutput (char *fileArr[], size_t count ){
  for (size_t i = 0; i < count; i++) {
    printf("%s \n", fileArr[i]);
  }
}

/**
 * Method to create copies of the original lines and call compareStrings
 *
 * @param const void *elemt1 pointer to the first element
 * @param const void *elem2 pointer to the second element
 * @return -1, 0 or 1
 **/
int compareLines(const void *elem1, const void *elem2) {

  // Cast parameters to actual type
  char **strptr1 = (char **) elem1;
  char **strptr2 = (char **) elem2;

  // Dereference from pointers to get values
  char *str1 = *strptr1;
  char *str2 = *strptr2;

  // Check the length of the string & check strlen function for error
  int length1;
  int length2;
  if ((strlen(str1) >= 0) && (strlen(str2) >= 0)) {
      length1 = strlen(str1);
      length2 = strlen(str2);
  } else
    fprintf(stderr, "Invalid string length\n");

  // Allocate memory for the string copies
  char *str1copy = calloc(length1, sizeof(char *)) ;
  char *str2copy = calloc(length2, sizeof(char *));

  // Make copies from originial strings and check result from strcpy function
  char *destination1 = strcpy(str1copy, str1);
  char *destination2 = strcpy(str2copy, str2);

  int compareResult;
  if ((destination1 != NULL) && (destination2 != NULL))// If destination pointers are valid, call compareStrings function
    compareResult = compareStrings(str1copy, str2copy);
  else
    fprintf(stderr, "String copy failed\n");

  // Free the memory
  free(str1copy);
  free(str2copy);
  return compareResult;
}

/**
 * Method to chop up words in two strings, save them in two word arrays
 * and call compareWords
 *
 * @param char *str1copy the first string
 * @param char *str2copy the second string
 * @return -1, 0 or 1
 **/
int compareStrings(char *str1copy, char *str2copy) {
  // Allocate memory for the word arrays
  char **wordArray1 = calloc(MAX_LINE_LEN - 1, sizeof(char *)) ;
  char **wordArray2 = calloc(MAX_LINE_LEN - 1, sizeof(char *)) ;

  // If string 1 is not a blank line, chop up. If it is, give it empty values
  if (!isBlankLine(str1copy)) {
    // On the first call, string to be parsed should be specified
    wordArray1[0] = strtok(str1copy, " ");
    int i = 0;
    // On the subsequent calls, str must be NULL. Save words into an array
    while(wordArray1[i] != NULL){
      i++;
      wordArray1[i] = strtok(NULL, " ");
    }
  } else {
     for (int i = 0; i < MAX_LINE_LEN - 1; i++)
       wordArray1[i] = " ";
  }

  // If string 2 is not a blank line, chop up. If it is, give it empty values
  if (!isBlankLine(str2copy)) {
    // On the first call, string to be parsed should be specified
    wordArray2[0] = strtok(str2copy, " ");

    int j = 0;
    // On the subsequent calls, str must be NULL. Save words into an array
    while(wordArray2[j] != NULL){
      j++;
      wordArray2[j] = strtok(NULL, " ");
    }
  } else {
     for (int j = 0; j < MAX_LINE_LEN - 1; j++) {
       wordArray2[j] = " ";
     }
  }
  int result = compareWords(wordArray1, wordArray2);

  free(wordArray1);
  free(wordArray2);
  return result;
}

/**
 * Method to check if a line is blank.
 *
 * @param char str[] the string to be checked
 * @return false if line is not blank, true otherwise
 **/
bool isBlankLine(char str[]) {
  char *p = str;
  while(*p) {
    if ((*p != ' ') && (*p != '\n') && (*p != '\0'))
      return false;
    p++;
  }
  return true;
}

/**
 * Method to compare words at a certain index (key) in two wordArray
 * Return -1 if wordArray1 < wordArray2, 0 if wordArray1 = wordArray2,
 * 1 if wordArray1 >  wordArray2
 *
 * @param char *wordArray1[] first word array
 * @param char *wordArray2[] second word array
 * @return -1, 0 or 1
 **/
int compareWords(char *wordArray1[], char *wordArray2[]) {
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
  int result;

  // Handle possible error from strcmp function
  if ((word1 != NULL) && (word2 != NULL))
      result = strcmp(word1, word2);
  else
      fprintf (stderr, "Word is null, cannot perform string compare\n");
  return result;
}


/**
 * Method to get the last word of a line
 *
 * @param char *wordArray[] the word array to be considered
 * @return the last word
 **/
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
