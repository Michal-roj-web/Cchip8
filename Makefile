CC=gcc
CFLAGS= -I . -lSDL2 -std=c99 -Wall -Werror
SRC = src/main.c src/opcodes.c src/platform.c src/tests.c src/chip8.c
START = src/main.c

main:
	$(CC) $(START) -o $@ $(CFLAGS)