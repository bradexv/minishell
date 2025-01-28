CFLAGS = -g -Wall -Wextra -std=gnu11
BIN = main

all: $(BIN)

main: main.c
	gcc $(CFLAGS) main.c -o main


clean:
	rm -f $(BIN)