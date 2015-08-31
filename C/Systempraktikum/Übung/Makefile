CFLAGS = -g -std=c99

OUT = -o klausur
CC = gcc

all: current clean

current:  structs.c\
					structs.h

	$(CC) $(CFLAGS) -o structs\
		structs.c

klausur: klausur.c\

	$(CC) $(CFLAGS) $(OUT)\
		klausur.c

clean:
	rm -f *.o
	rm -f *.a