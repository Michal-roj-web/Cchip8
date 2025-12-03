CC=gcc
CFLAGS= -I . -lSDL2
DEPS = src/chip-8.h src/platform.h src/opcodes.h
OBJ = src/main.c src/chip-8.c src/platform.c src/opcodes.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)