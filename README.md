# CPP Occurrence Counter

## Description

This project is a refactored version of an 
assignment originally given in Professor Courtney Brown's CS 177 
Software Engineering class at City College of San Francisco. The original assignent
was called count3s. The program is designed to count the occurrences of a 
specific integer in a binary data file. Originally created to count occurrences 
of the number '3' in `threesData.bin`, it has been expanded to allow users to 
specify a custom value through command-line arguments.

## Installation

To use the CPP Occurrence Counter, follow these steps:

1. Clone the repository:
```
    git clone https://github.com/rf922/cpp-occurance-counter.git
```
2. Navigate to the cloned directory:
```
    cd cpp-occurance-counter
```

# Usage
To run the program, compile it using the provided Makefile and then execute the 
binary:
1. Compile the program:
```
    make
```
2. Run the program:
```
    make run
```
You can specify run time options by setting the RUNOPTIONS variable doing the following :
```
    make run RUNOPTIONS="5"
```

This will count the occurrences of the number 5 in the data file.

3. To run the program with memory leak checking using Valgrind:
```
    make vrun
```

4. To clean up and remove object files :
```
    make clean
```

## Acknowledgments

- Professor Courtney Brown, for the initial assignment in CS 177.