CC = gcc
CFLAGS = -O0 -std=c99 -Wall
DEPS = ssbc.h
LIBS = ~cse231/ssbc.a -lpthread -lncurses

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

demo: demo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
     
timer: timer.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

interrupt-demo: interrupt-demo.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

