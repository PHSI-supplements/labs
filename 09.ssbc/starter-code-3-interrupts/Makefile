CC = gcc
CFLAGS = -O0 -std=c99 -Wall
DEPS = ssbc.h
LIBS = ~cse231/ssbc.a -lpthread -lncurses

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: interrupt-calculator

interrupt-calculator: interrupt-calculator.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
