CFLAGS = -g -std=c99

OUT = -o gol
CC = gcc

all: client clean

client: GameOfLife.c\

	$(CC) $(CFLAGS) $(OUT) \
		GameOfLife.c

clean:
	rm -f src/*.o
	rm -f src/*.a