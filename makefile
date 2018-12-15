CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -std=c99 -pedantic
OBJ = main.o Library.o InternalSorting.o ExternalSorting.o
DEPS = Library.h InternalSorting.h ExternalSorting.h
VFLAGS = -v --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./tp3 input.txt output.txt LIM_M
TIMED_RUN = time ./tp3

all: tp3

tp3: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@ -lm

clean:
	rm -f *.o tp3

valgrind:
	valgrind $(VFLAGS) $(EXEC)

run:
	$(EXEC)

timed:
	$(TIMED_RUN)
