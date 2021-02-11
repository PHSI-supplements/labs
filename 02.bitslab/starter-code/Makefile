CC = gcc
CFLAGS = -Og -std=c99 -Wall -g
DEPS = 
LIBS = -lm
OBJ = problem1.o problem2.o problem2main.o problem3.o problem3main.o problem5.o
EXEC = bitslab1 bitslab2 bitslab3 bitslab5

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bitslab1: problem1.o
	$(CC) -o $@ $^ $(CFLAGS)

bitslab2: problem2.o problem2main.o
	$(CC) -o $@ $^ $(CFLAGS)

bitslab3: problem3.o problem3main.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

bitslab5: problem5.o problem2.o problem3.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
