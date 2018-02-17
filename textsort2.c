#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LINE_LEN 128
#define MAX_FILE_LEN 150

int compareLines(const void *elem1, const void *elem2);
int compareStrings(char *str1, char *str2);
int compareWords(char *wordArray1[], char *wordArray2[]);
void sort(char *ptArray[]);
void printLines (char *ptArray[], size_t count);
char* getLastWord(char *wordArray[]);
bool isBlankLine(char str[]);
// Methods to count words on line, check lines and print out lines
int getLineLength(char line[]);

char line1[] = "black yummy wolfberry";
char line2[] = "Nate is cutie my baby answer me";
char line3[] = "hi there friend";
char line4[] = "            \0";

// Define an array of pointers, each element points to a char

int key = 7;

int main(int argc, char *argv[]){
  char **ptArray = calloc(4, sizeof(char *));
  ptArray[0] = line1;
  ptArray[1] = line2;
  ptArray[2] = line3;
  ptArray[3] = line4;
    
  printLines(ptArray, 4);
  qsort(ptArray, 4, sizeof(char *), compareLines);
  printLines(ptArray, 4);

  free(ptArray);
  return 0;
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
  } else {
    fprintf(stderr, "Invalid string length\n");
  }

  // Allocate memory for the string copies
  char *str1copy = calloc(length1, sizeof(char *)) ;
  char *str2copy = calloc(length2, sizeof(char *));
  
  // Make copies from originial strings and check result from strcpy function
  char *destination1 = strcpy(str1copy, str1);
  char *destination2 = strcpy(str2copy, str2);

  int compareResult;
  if ((destination1 != NULL) && (destination2 != NULL)) {
    // If destination pointers are valid, call compareStrings function
    compareResult = compareStrings(str1copy, str2copy);
  } else {
    fprintf(stderr, "String copy failed\n");
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
    int i = 0;
    // On the subsequent calls, str must be NULL. Save words into an array
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
   
    int m = 0;
    // On the subsequent calls, str must be NULL. Save words into an array
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
    printf("Case 1 word1 is: %s \n", word1);
    printf("Case 1 word2 is: %s \n", word2);
  } else if ((wordArray1[key] != NULL) && (wordArray2[key] == NULL)) {
    word2 = getLastWord(wordArray2);
    word1 = wordArray1[key];
    printf("Case 2 word1 is: %s \n", word1);
    printf("Case 2 word2 is: %s \n", word2);
  } else if  ((wordArray1[key] == NULL) && (wordArray2[key] == NULL)) {
    word1 = getLastWord(wordArray1);
    word2 = getLastWord(wordArray2);
    printf("Case 3 word1 is: %s \n", word1);
    printf("Case 3 word2 is: %s \n", word2);
  } else if ((wordArray1[key] != NULL) && (wordArray2[key] != NULL)) {
    word1 = wordArray1[key];   
    word2 = wordArray2[key];
    printf("Case 4 word1 is: %s \n", word1);
    printf("Case 4 word2 is: %s \n", word2);
  }
  int result;

  // Handle possible error from strcmp function
  if ((word1 != NULL) && (word2 != NULL)) {
      result = strcmp(word1, word2);
  } else {
      fprintf (stderr, "Word is null, cannot perform string compare\n");
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


void printLines (char *ptArray[], size_t count){
  for (size_t i = 0; i < count; i++) {
    printf("%s\n", ptArray[i]);
  }
}


int getLineLength(char line[]) {
  int counter;
  for (counter = 0; (counter < MAX_LINE_LEN - 1); counter++) {
    if (line[counter] == '\0') {
      break;
    }
  }
  return counter;
}
