CC = clang
CFLAGS = -O0 -std=c99 -Wall -g	# with -Og, the compiler might still optimize-out the parameters for the functions that use only inline assembly
DEPS = alu.h
LIBS = -lm
OBJ = integerlab.o basetwo.o alu.o
EXEC = integerlab

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

integerlab: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean clear all

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
