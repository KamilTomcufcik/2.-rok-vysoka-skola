CFLAGS= -std=c99 -g -Wall

all: train

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

train: main.o a_train.o
	gcc main.o a_train.o -o train 

clean:
	rm *.o train

