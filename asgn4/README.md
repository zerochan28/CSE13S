# Assignment 4 CSE13S - Fall 19

> Linhao Chen
> 10/27/2019

##  Purpose of Program

This program will play the game named The Tower of Hanoi,
which have three pegs and the first peg has n - disks,
the sizes of them increases from top to bottom,we need 
to move these disks from first peg to second peg. There are
two rules : 1. only one disk can be moved at a time. 2. No 
larger disk can be placed on top of a smaller disk.The program
can exactly achieve this goal by using recursion and stack, 
which can be selected by user through command line.User also 
required to enter the number of disks in this game, otherwise 
the default value will be 5. The game will print the process of
disk moving and counts the total steps of game.

##  Building 

Typing "make" can built it, as same as "make all"

Typing "./tower [-s] [-r] [-n] (number)" can run the program.

Typing "make clean" will clean things up.

Typing "make format" can format the documents if have file.clang - format.

Typing "make infer" to run infer on all program.

Typing "make memcheck" can check whether memory leaks.
