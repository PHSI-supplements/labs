CC = gcc
CFLAGS = -Og -std=c99 -Wall -g
DEPS = 
LIBS = -lm
OBJ = keyboardlab.o problem1.o problem2.o problem3.o
EXEC = keyboardlab

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

keyboardlab: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
