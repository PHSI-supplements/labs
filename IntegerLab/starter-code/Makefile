CC = clang
CFLAGS = -Og -std=c99 -Wall -g -finstrument-functions
DEPS = alu.h authoritative_results.h profiler.h
LIBS = -lm
OBJ = integerlab.o profiler.o basetwo.o alu.o authoritative_default.o authoritative_x86_64_linux.o authoritative_x86_64_macos.o
EXEC = integerlab

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

integerlab: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean clear all

all: $(EXEC)

clean:
	rm -f $(OBJ) *~ core

clear: clean
	rm $(EXEC)
