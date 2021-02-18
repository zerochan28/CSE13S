CFLAGS=-Wall -Wextra -Werror -Wpedantic
CC=clang $(CFLAGS)

.PHONY: all clean

all      : newspeak

newspeak   : newspeak.o bf.o bv.o speck.o gs.o hash.o ll.o lex.yy.o
	$(CC) -o newspeak newspeak.o bf.o bv.o speck.o gs.o hash.o ll.o lex.yy.o -lm -lfl
newspeak.o : newspeak.c
	$(CC) -c newspeak.c
bf.o     : bf.c
	$(CC) -c bf.c
bv.o     : bv.c
	$(CC) -c bv.c
speck.o  : speck.c
	$(CC) -c speck.c
gs.o	 : gs.c
	$(CC) -c gs.c
hash.o	 : hash.c
	$(CC) -c hash.c
ll.o	 : ll.c
	$(CC) -c ll.c
lex.yy.o : lex.yy.c
	$(CC) -c lex.yy.c
lex.yy.c : words.l
	flex words.l
clean    :
	rm -rf newspeak newspeak.o bf.o bv.o speck.o gs.o hash.o ll.o lex.yy.o lex.yy.c infer-out
memcheck :
	valgrind --leak-check=full newspeak -b
infer	 :
	make clean; infer-capture -- make; infer-analyze -- make
format	 :
	clang-format -i -style=file newspeak.c
