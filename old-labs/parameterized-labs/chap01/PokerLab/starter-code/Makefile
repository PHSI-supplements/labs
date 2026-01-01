CC = clang
CFLAG = -O0 -g -std=c99 -Wall -Wextra -Wno-unused-parameter
LIB = 
DEP = $(wildcard *.h) 
OBJ := $(patsubst %.c,%.o,$(wildcard *.c))
EXEC = pokerlab

%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAG) $(OPTION)

pokerlab: $(OBJ)
	$(CC) -o $@ $^ $(CFLAG) $(LIB) $(OPTION)

all: $(EXEC)

clean:
	rm -f $(OBJ) *~ core

clear: clean
	rm $(EXEC)
