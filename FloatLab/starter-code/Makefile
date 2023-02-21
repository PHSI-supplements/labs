CC = gcc
CFLAGS = -Og -std=c99 -Wall -g
DEPS = fpu.h unnormal.h
LIBS = -lm
OBJ = floatlab.o fpu.o unnormal.o
EXEC = floatlab

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#floatlab: $(OBJS)
floatlab: floatlab.o fpu.o unnormal.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean clear all

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
