TEST_SRCS = $(wildcard test*.c)
TEST_PROGS = $(patsubst %.c,%,$(TEST_SRCS))

all: main tests

alloc.o: alloc.c alloc.h 
	gcc -std=c99 -c -o alloc.o alloc.c 

memlib.o: memlib.c memlib.h 
	gcc -std=c99 -c -o memlib.o memlib.c 

main: main.c alloc.o memlib.o
	gcc -std=c99 -g -o main main.c alloc.o memlib.o 

tests: $(TEST_PROGS) alloc.o memlib.o

%: %.c
	gcc -std=c99 -g -o $@ $< alloc.o memlib.o

clean:
	-rm -f $(TEST_PROGS)
	-rm -rf *.dSYM
	-rm -f memlib.o alloc.o main

