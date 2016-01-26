CC=gcc
CFLAGS=-I../ -g -Wall -Wextra
DEPS=quicksort.h
OBJ=test.o quicksort.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm test *.o
