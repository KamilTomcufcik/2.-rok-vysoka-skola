CFLAGS= -std=c99 -g -Wall -Werror

all: station

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

station: main.o a_station.o
	gcc $(CFLAGS) main.o a_station.o -o station

clean:
	rm *.o station