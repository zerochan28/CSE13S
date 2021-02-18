CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

lrc     : lrc.o
	$(CC) -o lrc lrc.o
lrc.o   : lrc.c
	$(CC) -c lrc.c
clean   :
	rm -f lrc lrc.o
format  : .clang-format
	clang-format -i -style=file lrc.c
infer   :
	make clean; infer-capture -- make; infer-analyze -- make
