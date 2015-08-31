CC = /usr/bin/gcc
CFLAGS = -std=c99 -Wall -g
LDFLAGS = -lm -lpthread

all: zahlenraten

zahlenraten: zahlenraten.c
	$(CC) $(CFLAGS) -o zahlenraten zahlenraten.c

clean:
	rm -f zahlenraten
