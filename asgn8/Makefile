CFLAGS=-Wall -Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)

all      : lzwcoder

lzwcoder   : main.o trie.o io.o word.o
	$(CC) -o lzwcoder main.o trie.o word.o io.o -lm
main.o : main.c
	$(CC) -c main.c
trie.o     : trie.c
	$(CC) -c trie.c
io.o  : io.c
	$(CC) -c io.c
word.o   : word.c
	$(CC) -c word.c
clean    :
	rm -rf lzwcoder main.o word.o trie.o io.o infer-out
memcheck :
	valgrind --leak-check=full lzwcoder -d -i perfect.lzw -o example4.txt 
infer	 :
	make clean; infer-capture -- make; infer-analyze -- make
format	 :
	clang-format -i -style=file main.c trie.c word.c io.c

