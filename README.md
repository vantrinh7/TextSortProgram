# Text Sort Program

This program is a simple version of sorting utility in the Unix operating system. The program can be run from Terminal using the commands: `./textsort filename` or `./textsort -2 filename`. "Filename" is the name of file that contains the text being sorted, and "-2" is an optinal argument that sorts the program based on the 2nd word rather than the first word. Here are some example outputs of the program, as the sentences in one text file are sorted based on words at position 1, 2, 3, etc.:

<br>

![](misc/sort%201.png)  ![](misc/sort%202.png)  ![](misc/sort%203.png)

<br>

## Checking file and arguments

The program first checks whether the given file is not null, the arguments are valid, and the number of parameters are valid.  Next, it checks if file cannot be opened, cannot be closed, or has invalid length. Error messages are printed out when these tests fail.

## Reading input file

Using `fgets()` function in C, the program reads the input file into an array of pointers. Each element points to a character array, which is a line in the file. Using `calloc` function in C, each line of the text file is allocated a memory space with the size of standard `char` variable, and the whole file (the file array) is allocated a memory space corresponding to the number of lines.

## Sorting input file

The file is sorted by `qsort()` function in C, which takes in four parameters: the pointer to a file, number of lines, size of element and a compare function. Methods `compareLines()`, `comparedStrings()` and `compareWords()` were written to be used in this `qsort()` function. `compareLines()` checks the length of two lines to be compared and creates a copy of each original line. `comparedStrings()` chops up words in these lines and save into two strings. `compareWords()` compares words (at the position defined by command line argument) and returns the result. After the file is sorted, method `printOutput()` loops through the array of pointers and prints out the sorted file. 

## Assumptions

- The maximum length of the line in the input file is 128 characters. If a line is longer, the program exits and returns an error.
- Empty line is sorted using an empty string.
- If user wants to sort on a certain position (e.g. the 5th position), but a line has a fewer number of words (e.g. "Example line"), then the last word of the sentence is used to sort (in this case, the word "line" is utilized).

## File description

This program was written is C (as shown in [textsort.c](https://github.com/vantrinh7/TextSortProgram/blob/master/textsort.c) and the [makefile](https://github.com/vantrinh7/TextSortProgram/blob/master/makefile)). Two example text files are included for testing purposes ([rose.txt](https://github.com/vantrinh7/TextSortProgram/blob/master/rose.txt) and [tomatoes.txt](https://github.com/vantrinh7/TextSortProgram/blob/master/tomatoes.txt)).
