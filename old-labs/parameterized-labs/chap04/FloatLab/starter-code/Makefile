CC = clang
CFLAG = -Og -g -std=c99 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter
LIB = 
DEP = $(wildcard *.h) 
OBJ := $(patsubst %.c,%.o,$(wildcard *.c))
EXEC = floatlab

%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAG) $(OPTION)

floatlab: $(OBJ)
	$(CC) -o $@ $^ $(CFLAG) $(LIB) $(OPTION)

all: $(EXEC)

clean:
	rm -f $(OBJ) *~ core

clear: clean
	rm $(EXEC)
