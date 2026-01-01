CC = gcc
CFLAGS = -O0 -std=c99 -Wall
DEPS = ssbc.h
LIBS = ~cse231/ssbc.a -lpthread -lncurses

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: demo warmup

demo: demo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
     
warmup: warmup.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

