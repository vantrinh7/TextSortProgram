
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LEN 128
#define MAX_FILE_LEN 150

int compareLines(const void *elem1, const void *elem2);
int compareString(char *str1, char *str2, int key);
void sort(char *ptArray[]);
void printLines (char *ptArray[]);

char line1[] = "black sheep";
char line2[] = "Nate is cute";
char line3[] = "hi there";

// Define an array of pointers, each element points to a char
char *ptArray[MAX_LINE_LEN];

// Methods to count words on line, check lines and print out lines
int getLineLength(char line[]);

int main(int argc, char *argv[]){
  ptArray[0] = line1;
  ptArray[1] = line2;
  ptArray[2] = line3;
  /* printf("First element in ptArray is: %s \n", ptArray[0] ); */
  /* printf("Second element in ptArray is: %s \n", ptArray[1]); */
  //printLines(ptArray);
  
  // Second parameters is number of characters NOT INCLUDING '\0' in the end

  qsort(ptArray, 3, sizeof(char *), compareLines);
  /* printf("After sorting: \n"); */
  /* printf("Line 1 is: %s \n", line1); */
  /* printf("Line 2 is: %s \n", line2); */
  //printLines(ptArray);
  
  return 0;
}

void sort(char *ptArray[]) {
  
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

//  do the pairwise comparison of values in the array
int compareLines(const void *elem1, const void *elem2) {

  char *wordArray1[MAX_LINE_LEN];
  char *wordArray2[MAX_LINE_LEN];
  
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
  strcpy(str1copy, str1);
  
  // On the first call, string to be parsed should be specified (str1copy)
  wordArray1[0] = strtok(str1copy, " ");
   printf("%s \n", wordArray1[0]);

  int i = 0;
  // On the subsequent calls, str must be NULL. Save words into an array
  while(wordArray1[i] != NULL){
    wordArray1[i] = strtok(NULL, " ");
    i++;
  }
  
  for (int j = 0; j < i-1; j++) {
    printf("%s \n", wordArray1[j]);
  }

  // make a copy of the original line for later use
  strcpy(str2copy, str2);
  
  // On the first call, string to be parsed should be specified (str2copy)
  wordArray2[0] = strtok(str2copy, " ");
   printf("%s \n", wordArray2[0]);

  int m = 0;
  // On the subsequent calls, str must be NULL. Save words into an array
  while(wordArray2[i] != NULL){
    wordArray2[i] = strtok(NULL, " ");
    m++;
  }
  
  for (int n = 0; n < m-1; n++) {
    printf("%s \n", wordArray2[n]);
  }
   
  //char *temp1 = NULL;
  //int i = 0; // counter
  //loops the rest of the line until reaching key
  
  // while( i <= key && (chop1 != NULL ))  {
  //  while ((word = strtok(NULL, " ")) != NULL)
  //    printf("Next: %s\n", word);
  //}
  /* Then use strcmp to compare the strings */
  
  //  To compare strings, use the strcmp() function.
  
  
  //  To chop lines into words, you can use strtok(). Be careful, though; it is destructive and will change the contents of the lines. Thus, if you use it, make sure to make a copy of the original line for later use.

  // Use the strings for strcmp function
  int result  = strcmp(str1, str2);
  
  //printf("Compare function result: %d \n", result);
  return result;
}

void printLines (char *ptArray[]) {
  for (char **a = ptArray; *a; a++) {
    printf("%s\n", *a);
  }
}
