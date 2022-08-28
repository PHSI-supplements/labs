CC = gcc
CFLAGS = -Og -std=c99 -Wall -g
DEPS =
LIBS = -lm
OBJ = problem1.o problem1main.o problem2.o problem2main.o problem3.o problem3main.o challenge-response.o problem5main.o
EXEC = keyboardlab1 keyboardlab2 keyboardlab3

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

keyboardlab1: problem1.o problem1main.o
	$(CC) -o $@ $^ $(CFLAGS)

keyboardlab2: problem2.o problem2main.o
	$(CC) -o $@ $^ $(CFLAGS)

keyboardlab3: problem3.o problem3main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

keyboardlab5: problem2.o problem3.o challenge-response.o problem5main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
