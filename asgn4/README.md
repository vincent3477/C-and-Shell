sorting.c : This file runs several sorting algorithms for arrays. 

How to execute this file.

1. Be sure to "make" the file first. You can type "make" into the cli.

2. To execute the file type ./sorting, then you can type some options specified:

-a : runs all sorting algorithms.

-s : runs shell sort algorithm.

-b : runs bubble sort algorithm.

-q : runs quick sort algorithm.

-h : runs heap sort algorithm.

-H : prints help.

-p <numeric option> : specify the number of elements to print from sorted array(s)

-n <numeric option> : specify the size of the elements to be sorted. Must be between 1 and 250,000,000 (inclusive.)

-r <numeric option> : set the seed for the random numbers generated.

Note: none of these options are exclusive of eachother.

Files included:

bubble.c - Contains implementation for bubble sort algorithm.

bubble.h - header file for bubble.c

heap.c - Contains the implementation for heap sort algorithm.

heap.h - header file for heap.c

mtrand.c - To generate random numbers based on mersenne twister

mtrand.h - header for mtrand.c

quick.c - Contains implementation for bubble sort algorithm. Note: This sorting algorithm contains some bug where segmentation faults would be given when sorting certain number of array values. However, the sort is relatively accurate.

quick.h - header for quick.c

set.c - contains the stats struct, which can be used in other classes to track down moves and compares.

set.h - header file for set.h

shell.c - Contains the code implementation for shell sort algorithm. 

shell.c - header for shell.h

sorting.c - has the main() function to compile and run all sorting algorithms classes.

README.md - This file. Explains what all the files are, how to run them, and known bugs.

