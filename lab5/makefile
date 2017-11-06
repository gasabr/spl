FLAGS= -std=c99 -pedantic-errors -Wall -Werror

all: main

main: main.o bmp.o pixel.o image.o
	gcc $(FLAGS) main.o bmp.o image.o pixel.o -o main

main.o: main.c
	gcc -c $(FLAGS) main.c -o main.o

image.o: image.c
	gcc -c $(FLAGS) image.c -o image.o

bmp.o: bmp.c
	gcc -c $(FLAGS) bmp.c -o bmp.o

pixel.o: pixel.c
	gcc -c $(FLAGS) pixel.c -o pixel.o

clean:
	rm -f main
	rm -f main.o
	rm -f pixel.o
	rm -f bmp.o

