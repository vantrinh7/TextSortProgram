#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *elem1, const void *elem2);
char line1[] = "bcdea";
char line2[] = "Nate is cute";
int values[] = {1, 2, 6, 7, 9};
char *p1 = NULL;
char *p2 = NULL;
 

int main(int argc, char *argv[]){
  printf("Before sorting: \n");
  printf("Line 1 is: %s \n", line1);
  printf("Line 2 is: %s \n", line2);
  // Second parameters is number of characters NOT INCLUDING '\0' in the end
  qsort(line1, 5, sizeof(char), compare);

  //p1 = &line1[0];
  //p2 = &line1[1];
  //int i = compare(p1, p2);
  //printf("i is: %d\n", i);
  printf("After sorting: \n");
  printf("Line 1 is: %s \n", line1);
  printf("Line 2 is: %s \n", line2);
  return 0;
}

//  do the pairwise comparison of values in the array
int compare(const void *elem1, const void *elem2) {
   printf("Start \n");
  /* Cast to its actual type */
  char *strptr1 = (char *) elem1;
   
  char *strptr2 = (char *) elem2;
   
  /* Dereference to get the strings */
  //char *str1 = *strptr1;

  //char *str2 = *strptr2;

   
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
   int i = strcmp(strptr1, strptr2);
   printf("Line 1 is: %s \n", line1);
   printf("Compare function result: %d \n", i);
   return i;
}
