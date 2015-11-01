CC=gcc
CFLAGS=-I../ -Wall -Wextra
DEPS=priority_queue.h
OBJ=test.o priority_queue.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -g

clean:
	rm test *.o
