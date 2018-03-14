CFLAGS=-Wall -Werror -g
CC=gcc

all:
	$(CC) $(CFLAGS) main.c -o main.out

clean:
	rm main.out