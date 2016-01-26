CC=gcc
CFLAGS=-I../ -Wextra -Wall -g
DEPS=vector.h vector_def.h stack.h
OBJ=test.o vector.o stack.o
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm test *.o
