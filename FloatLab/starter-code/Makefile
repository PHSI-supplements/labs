CC = gcc
CFLAGS = -Og -std=c99 -Wall -g
DEPS = fpu.h
LIBS = -lm
OBJ = floatlab.o fpu.o
EXEC = floatlab

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

floatlab: floatlab.o fpu.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean clear all

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
