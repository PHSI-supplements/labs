CC = clang
CFLAG = -Og -g -std=c99 -Wall -Wextra -Wno-unused-parameter
LIB = 
DEP = $(wildcard *.h) 
OBJ := $(patsubst %.c,%.o,$(wildcard *.c))
EXEC = arraylist linkedlist

%.o: %.c $(DEP)
	$(CC) -c -o $@ $< $(CFLAG) $(OPTION)

arraylist: $(filter-out linked_list.o,$(OBJ))
	$(CC) -o $@ $^ $(CFLAG) $(LIB) $(OPTION)

linkedlist: $(filter-out array_list.o,$(OBJ))
	$(CC) -o $@ $^ $(CFLAG) $(LIB) $(OPTION)

all: $(EXEC)

clean:
	rm -f $(OBJ) *~ core

clear: clean
	rm $(EXEC)
