
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE_LEN 128
#define MAX_FILE_LEN 150

int compare(const void *elem1, const void *elem2);
void printLines (char *ptArray[]);

char line1[] = "bcdea";
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
  printLines(ptArray);
  // Second parameters is number of characters NOT INCLUDING '\0' in the end

  qsort(ptArray, 3, sizeof(char *), compare);
  /* printf("After sorting: \n"); */
  /* printf("Line 1 is: %s \n", line1); */
  /* printf("Line 2 is: %s \n", line2); */
  printLines(ptArray);
  
  return 0;
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
int compare(const void *elem1, const void *elem2) {
  printf("Start \n");
  /* Cast to its actual type */
  char **strptr1 = (char **) elem1;
   
  char **strptr2 = (char **) elem2;
   
  /* Dereference to get the strings */
  char *str1 = *strptr1;

  char *str2 = *strptr2;

   
  // allocates memory for the copy
  // char *str1copy = (char *)malloc(strlen(str1));
  // make a copy of the original line for later use
  // strcpy(str1copy, str1);
  // get the first word from the string, seperated by space character
  // char *chop1 = strtok(str1copy, " ");
 
  //char *temp1 = NULL;
  //int i = 0; // counter
  // loops the rest of the line until reaching key
  // while( i <= key && (chop1 != NULL ))  {
  //  while ((word = strtok(NULL, " ")) != NULL)
  //    printf("Next: %s\n", word);
  //}
  /* Then use strcmp to compare the strings */
  
  //  To compare strings, use the strcmp() function.
  
  
  //  To chop lines into words, you can use strtok(). Be careful, though; it is destructive and will change the contents of the lines. Thus, if you use it, make sure to make a copy of the original line for later use.

  // Use the pointers, not the strings themselves for strcmp function
  int i = strcmp(str1, str2);
  printf("Compare function result: %d \n", i);
  return i;
}

void printLines (char *ptArray[]) {
  for (char **a = ptArray; *a; a++) {
    printf("%s\n", *a);
  }
}
