.PHONY: clean exe all mem valgrind

all: main exe clean
all2: main2 exe clean
mem: main valgrind

valgrind:
	@valgrind ./main.o

main: main.c
	@gcc -Wall -g -o main.o main.c
main2: mainsas.c
	@gcc -Wall -g -o mainsas.o mainsas.c
exe:
	@./main.o

clean:
	@rm -rf *.o