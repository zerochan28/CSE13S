# Assignment 8 CSE13S - Fall 19

> Linhao Chen
> 12/06/2019

## Purpose of Program

This Program will run LZW compression for files. It will use Trie for
compression and word table for decompression. The compressed file will
contain a special magic number, the compressed file without magic number
cannot be decompressed. The program also provide -v mode for showing some
statistics.

## Building

Typing "make" can built it as same as "make all".

Typing "./lzwcoder -v -c -d -i: -o:" can run the program

Typing "make clean" can clean things up

Typing "make infer" can run infer on all program

Typing "make memcheck" can check whether memory leaks

## Usage

"-v" command will use verbose mode

"-c" will run compression

"-d" will run decompression

"-i" will provide the name for infile

"-o" will provide the name for outfile

Warning: You cannot provide both -c and -d mode

## Note

Currently the program will not supply stdin and stdout
please use -i -o for output. Also, the program will not
print the max word length while other function should be
word. If you use memcheck, please make sure there is a 
perfect.lzw file in the directory.
