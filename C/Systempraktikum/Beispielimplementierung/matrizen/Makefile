CC = /usr/bin/gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS = -lm -lpthread

all: matrix

matrixBib.o: matrixBib.c matrixBib.h
	$(CC) $(CFLAGS) -c matrixBib.c

matrix: matrixBib.o matrix_testroutine.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ matrixBib.o matrix_testroutine.c

clean:
	rm -f matrixBib.o matrix

