# Assignment 7 CSE13S - Fall 19

> Linhao Chen
> 11/24/2019

## Purpose of Program

This Program will scan a list of badspeak words into hash table
and bloom filter. And then store a list of oldspeak-newspeak pairs
to hash table and bloom filter. Then the program will read the user
input from standard input and search all the words from bloom filter
and hash table. Then the program will give a suggestion for error
and revise of some words. The program also support to print some
statistics for hash table and floom filter.

## Building

Typing "make" can built it as same as "make all".

Typing "./newspeak -s -h -f -m -b" can run the program

Typing "make clean" can clean things up

Typing "make infer" can run infer on all program

Typing "make memcheck" can check whether memory leaks

## Usage

"-s" command will only print statistics

"-h" can set the size of hash table

"-f" can set the size of bloom filter

"-m" will use the move-to-front rule

"-b" will not use the move-to-front rule

