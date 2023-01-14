CC = gcc
CFLAGS = -std=c99 -Wall
DEPS = 
LIBS = -lpthread -lrt
OBJ = mergesort.o bookkeeper.o
EXEC = mergesort bookkeeper

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mergesort: mergesort.o
	$(CC) -o $@ $^ -O0 $(CFLAGS) $(LIBS)

bookkeeper: bookkeeper.o
	$(CC) -o $@ $^ -Og $(CFLAGS) $(LIBS)

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
