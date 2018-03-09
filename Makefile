CFLAGS=-Wall -Werror
CC=gcc

all:
	$(CC) main.c -o main.out

clean:
	rm main.out