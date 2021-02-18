# Assignment 5 CSE13S - Fall 19

> Linhao Chen
> 11/03/2019

## Purpose of Program

This program will determine whether a number is 
prime number or composite number. The default range
will be 2 to 100000. However, user can provides an
option to set its range. By using -n option and provide
an parameter, the program can print the number from 
2 to n and do the same operation above. The program will
also do prime factorization for each composite number.

## Building

Typing "make" can built it as same as "make all".

Typing "./factor" can run the program by using default value.

Typing "./factor -n (number)" can run program by setting maximum n.

Typing "make clean" can clean things up.

Typing "make format" can format all documents if have .clang-format

Typing "make infer" can run infer on all program.

Typing "make memcheck" can check whether memory leaks.
