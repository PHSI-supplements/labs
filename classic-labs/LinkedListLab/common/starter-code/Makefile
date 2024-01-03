CC = gcc
CFLAGS = -Og -std=c99 -Wall -g
DEPS = challenge-response
LIBS = -lm
OBJ = challenge-response.o linkedlistlab.o
EXEC = linkedlistlab

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

linkedlistlab: challenge-response.o linkedlistlab.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: $(EXEC)

clean:
	rm -f $(OBJ) *.s *~ core

clear: clean
	rm $(EXEC)
