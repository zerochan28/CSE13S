CFLAGS=-Wall -Wextra -Werror -pedantic -O3
CC=clang $(CFLAGS)

all       : sorting

sorting   : sorting.o sortA.o sortB.o sortC.o sortD.o
	clang -o sorting sorting.o sortA.o sortB.o sortC.o sortD.o
sorting.o : sorting.c
	$(CC) -c sorting.c
sortA.o   : sortA.c sortA.h
	$(CC) -c sortA.c
sortB.o   : sortB.c sortB.h
	$(CC) -c sortB.c
sortC.o   : sortC.c sortC.h
	$(CC) -c sortC.c
sortD.o   : sortD.c sortD.h
	$(CC) -c sortD.c
clean     :
	rm -rf sortA.o sortB.o sortC.o sortD.o sorting.o sorting infer-out
format	  : .clang-format
	clang-format -i -style=file sortA.c sortB.c sortC.c sortD.c sorting.c
infer	  :
	make clean; infer-capture -- make; infer-analyze -- make
memcheck  :
	valgrind --leak-check=full ./sorting -A
	valgrind --show-leak-kinds=all ./sorting -A

