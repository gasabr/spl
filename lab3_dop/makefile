FLAGS= -std=c99  -pedantic-errors -Wall -Werror

all: main

main: main.o matrix.o
	gcc $(FLAGS) main.o matrix.o -o main

main.o: main.c
	gcc -c $(FlAGS) main.c -o main.o

matrix.o: matrix.c
	gcc -c $(FLAGS) matrix.c -o matrix.o	

clean:
	rm -f main
	rm -f main.o
	rm -f matrix.o

