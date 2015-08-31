CFLAGS = -g -std=c99

OUT = -o game
CC = gcc

all: client clean

client: GameLife.c\

	$(CC) $(CFLAGS) $(OUT) \
		GameLife.c

clean:
	rm -f src/*.o
	rm -f src/*.a