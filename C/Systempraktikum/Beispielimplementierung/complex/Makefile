CC = /usr/bin/gcc
CFLAGS = -Wall -g
LDFLAGS = -lm -lpthread

all: complex

complex.o: complex.c complex.h
	$(CC) $(CFLAGS) -c complex.c

complex: complex.o complex_main.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ complex.o complex_main.c

clean:
	rm -f complex.o complex
