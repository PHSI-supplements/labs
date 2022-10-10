CC = gcc
CFLAGS = -Og -std=c99 -Wall -g
DEPS = duplicator.h
LIBS = -lpthread
OBJ = duplicator.o duplicatorlab.o
EXEC = duplicator

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

duplicator: duplicator.o duplicatorlab.o
	$(CC) -o $@ $^ $(CFLAGS)

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
