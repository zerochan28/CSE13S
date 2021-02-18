CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

all      : tower

tower    : tower.o stack.o
	$(CC) -o tower tower.o stack.o -lm
tower.o  : tower.c
	$(CC) -c tower.c
stack.o  : stack.c stack.h
	$(CC) -c stack.c
clean	:
	rm -rf tower tower.o stack.o infer-out
format	: .clang-format
	clang-format -i -style=file tower.c stack.c stack.h
infer	:
	make clean; infer-capture -- make; infer-analyze -- make
memcheck:
	valgrind --leak-check=full tower -s -r
	valgrind --show-leak-kinds=all tower -s -r
