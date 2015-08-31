CC = /usr/bin/gcc
CFLAGS = -Wall -g -D_REENTRANT
LDFLAGS = -lm -lpthread -lgmp

all: checkPrimeMultiThreaded

checkPrimeMultiThreaded: checkPrimeMultiThreaded.c
	$(CC) -o $@ checkPrimeMultiThreaded.c $(CFLAGS) $(LDFLAGS)

clean:
	rm -f checkPrimeMultiThreaded
