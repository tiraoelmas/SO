.PHONY: clean exe all mem valgrind

all: main exe clean

mem: main valgrind

valgrind:
	@valgrind ./main.o

main: main.c
	@gcc -Wall -g -o main.o main.c

exe:
	@./main.o

clean:
	@rm -rf *.o