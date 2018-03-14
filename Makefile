CFLAGS=-Wall -g
CC=gcc

all:
	$(CC) $(CFLAGS) main.c linked_list.c -o main.out

clean:
	rm main.out