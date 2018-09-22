/**
 * This program sorts a text file based on a word on each line. 
 * The command should be ./textsort <key> <filename>, in which
 * <key> is the number of the word to be sorted by on the line,
 * and <filename> is the name of the file to be sorted.
 * If key is larger than a line, last word of that line is used.
 * File with empty lines will have empty lines sorted at the top, 
 * since space character comes before letters.
 *
 * @author Van Trinh & Zhiling Hu
 * @version Feb 17th 2018
 **/

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
// Empty string to sort empty lines
char emptyArr[MAX_LINE_LEN];

/**
 * This method opens, reads, sorts and closes the file given.
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

  // Opens a file for reading & check fopen result
  file = fopen(fileName, "r"); 
  if(file == NULL)  {
    fprintf(stderr, "Error: Cannot open file %s\n", fileName );
    exit(1);  // exit with return code 1
  }

  // Read the input and save the number of lines of the file
  int numLines = readInput(fileArr, lineArr, file);

  // Close the file & check fclose result
  int close =  fclose(file);
  if (close != 0) {
    fprintf(stderr, "Error: Cannot close file %s\n", fileName );
    exit(1); // exit with return code 1
  }  

  // Sort the file, print before and after sorting
  printf("Before sorting: \n");
  printOutput(fileArr, numLines);

  qsort(fileArr, numLines, sizeof(char *), compareLines);

  printf("\nAfter sorting: \n");
  printOutput(fileArr, numLines);

  // Free memory of each char array element in fileArray
  for (int j = 0; j < numLines; j++) {
    free(fileArr[j]);
  }
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
  if (argc == 2) {
    fileName = argv[1];
  } 
  // Reads through command line arguments
  else if (argc == 3){
    fileName = argv[2];
    if (argv[1][0] == '-'){ // Looks for the dash sign
      // Coverts string to int, base 10; then convert it to an array position
      key = -strtol(argv[1], NULL, 10) - 1;

      // Check strtol return value
      if (key < 0) {
	fprintf(stderr, "Error: Key is invalid, please enter an integer >= 1\n" );
	exit(1);
      }
    }
    // Else: not enough parameters have been passed || more than expected
    else{
      // Send the error message to standard error
      fprintf(stderr, "Error: Bad command line parameters\n"); 
      exit(1);
    }
  }
  // If inputing a null file
  if (fileName == NULL) {
    fprintf(stderr, "Error: Bad command line parameters\n");
    exit(1); 
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
    // Check if line is too long
    if(strlen(lineArr) > MAX_LINE_LEN){
      fprintf(stderr, "Line too long");
      exit(1);  // Exit with return code 1
    }
    // Check for new line character
    if (strchr(lineArr, '\n')) {
      lineArr[strlen(lineArr) - 1] = '\0';  
    }
    // Allocate memory for each element in fileArr
    fileArr[i] = (char *) calloc(MAX_LINE_LEN, sizeof(char));

    // Writing content in one line to the array, check strcpy
    char *destination = strcpy(fileArr[i], lineArr);
    if (destination == NULL) {
      fprintf(stderr, "Error: Cannot write line %s into the file array.\n", lineArr);
      exit(1);
    }
    // Check the allocation
    if (fileArr[i] == NULL) {
      fprintf(stderr, "Error: Memory allocation failed for line %d.\n", i);
      exit(1);
    }
    i++;
    
  }
  return i;
}

/**
 * This method prints out the content of file array 
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
  // Initialize an empty array later used to sort empty lines
  for (int i = 0; i < MAX_LINE_LEN; i++) {
      emptyArr[i] = ' ';
  }
  // Cast parameters to actual type and dereference from pointers to get values
  char *str1 = * (char **) elem1; 
  char *str2 = * (char **) elem2;

  int length1;
  int length2;
  
  // Check the length of the strings and if each string is null
  int checkNull1 = strcmp(str1, "");
  int checkNull2 = strcmp(str2, ""); 
  if (checkNull1 != 0) {
    length1 = strlen(str1);
  } else {
    length1 = MAX_LINE_LEN;
  }
  if (checkNull2 != 0) {
    length2 = strlen(str2);
  } else {
    length2 = MAX_LINE_LEN;
  }

  // Allocate memory for the string copies
  char *str1copy = calloc(length1, sizeof(char *)) ;
  char *str2copy = calloc(length2, sizeof(char *));

  char *destination1;
  char *destination2;
  
  // Make copies from originial strings if not null, copies from empty string if null
  if (checkNull1 != 0) {
    destination1 = strcpy(str1copy, str1);
  } else {
    destination1 = strcpy(str1copy, emptyArr);
  }
  if (checkNull2 != 0) {
    destination2 = strcpy(str2copy, str2);
  } else {
    destination2 = strcpy(str2copy, emptyArr);
  }
 
  int compareResult;

  // If destination pointers are valid, call compareStrings function
  if ((destination1 != NULL) && (destination2 != NULL)) {   
    compareResult = compareStrings(str1copy, str2copy);
  } else {
    fprintf(stderr, "Error: Cannot make copies of the original lines\n");
    exit(1);
  }
  
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
  if (isBlankLine(str1copy) != true) {
   
    // On the first call, string to be parsed should be specified 
    wordArray1[0] = strtok(str1copy, " ");
    if (wordArray1[0] == NULL) { // Check strtok return value
      fprintf(stderr, "Error: Cannot chop line into words\n");
      exit(1);
    }
    
    // On the subsequent calls, str must be NULL. Save words into an array
    int i = 0;
    while(wordArray1[i] != NULL){
      i++;
      wordArray1[i] = strtok(NULL, " ");  
    }  
  } else {
    for (int i = 0; i < MAX_LINE_LEN - 1; i++) {
      wordArray1[i] = " ";
    }
  }
  
  // If string 2 is not a blank line, chop up. If it is, give it empty values
  if (isBlankLine(str2copy) != true) {  
    // On the first call, string to be parsed should be specified 
    wordArray2[0] = strtok(str2copy, " ");
     if (wordArray2[0] == NULL) { // Check strtok return value
      fprintf(stderr, "Error: Cannot chop line into words\n");
      exit(1);
    }   
    
    // On the subsequent calls, str must be NULL. Save words into an array
    int m = 0;
    while(wordArray2[m] != NULL){
      m++;
      wordArray2[m] = strtok(NULL, " ");  
    }
  } else {
     for (int i = 0; i < MAX_LINE_LEN - 1; i++) {
       wordArray2[i] = " ";
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
    if ((*p != ' ') && (*p != '\n') && (*p != '\0')) {
	return false;
    }
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

  // Compare words and check for null values
  if ((word1 != NULL) && (word2 != NULL)) {
      result = strcmp(word1, word2);
  } else {
      fprintf (stderr, "Error: Word is null, cannot perform string compare\n");
      exit(1);
  }
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


