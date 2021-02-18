# Assignment 3 CSE13S-Fall 19

> Linhao Chen
> 10/19/2019

## Purpose of Program

This program can build a small math library to calculate sin, cos, tan
and exponent of exponent of Euler's number. Use the command-line option
to simply print the chart which contains value x, the result by using
own small math library and the result from math library of C. The chart
also can tells you the difference between the values.

## Building
Typing "make" can built it, as same as "make all".

Typing "./math -(command)" can run the program. (See next part)

Typing "make clean" will clean things up.

Typing "make format" can format the lrc.c document if have file .clang-format.

Typing "make infer" to run infer on all programs.

## How to use the program
Typing "./math -s" can print the chart of sin(x)

Typing "./math -c" can print the chart of cos(x)

Typing "./math -t" can print the chart of tan(x)

Typing "./math -e" can print the exponent of e

Typing "./math -a" can print all the things metioned above

Please do not type other command or enter more than one command
because the program will shows error and you cannot get the thing
you want.
