CC = clang
CFLAG = -Og -g -std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-value
LIB = -lm
DEP = $(wildcard *.h) 
OBJ := $(patsubst %.c,%.o,$(wildcard *.c))
EXEC = keyboardlab

%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAG) $(OPTION)

keyboardlab: $(OBJ)
	$(CC) -o $@ $^ $(CFLAG) $(LIB) $(OPTION)

all: $(EXEC)

clean:
	rm -f $(OBJ) *~ core

clear: clean
	rm $(EXEC)
