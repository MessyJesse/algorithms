CC=gcc
CFLAGS=-I../ -Wall -Wextra -g
DEPS=heap_sort.h
OBJ=test.o heap_sort.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm test *.o
