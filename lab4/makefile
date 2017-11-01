all: main

main: main.o list.o
	gcc $(FLAGS) main.o list.o -o main

main.o: main.c
	gcc -c $(FLAGS) main.c -o main.o

list.o: list.c
	gcc -c $(FLAGS) list.c -o list.o

clean:
	rm -f main
	rm -f main.o
	rm -f list.o
