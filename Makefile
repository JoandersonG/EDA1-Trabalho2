simulacao: simulacao.o avl.o
	gcc-7 simulacao.o avl.o -o simulacao
simulacao.o: simulacao.c
	gcc-7 -c simulacao.c -g -Wall -Wextra -Werror -Wpedantic
avl.o: avl.c avl.h
	gcc-7 -c avl.c -g -Wall -Wextra -Werror -Wpedantic
clean:
	rm *.o simulacao