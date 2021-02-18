CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

all       : factor

factor    : factor.o bv.o sieve.o
	$(CC) -o factor factor.o bv.o sieve.o -lm
factor.o  : factor.c
	$(CC) -c factor.c
bv.o      : bv.c bv.h
	$(CC) -c bv.c
sieve.o   : sieve.c sieve.h
	$(CC) -c sieve.c
clean	:
	rm -rf factor factor.o sieve.o bv.o infer-out
format	: .clang-format
	clang-format -i -style=file factor.c bv.c bv.h sieve.h sieve.c
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
memcheck:
	valgrind --leak-check=full ./factor -n 100
	valgrind --show-leak-kinds=all ./factor -n 100
