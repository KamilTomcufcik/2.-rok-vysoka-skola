all: program

maze.o: maze.c
	gcc -c -g -Wall maze.c -o maze.o

main.o: main.c
	gcc -c -g -Wall main.c -o main.o

program: maze.o main.o
	gcc -g -Wall maze.o main.o  -o program

clean:
	rm program
	rm *.o
