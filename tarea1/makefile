.PHONY: clean exe all

all: main exe clean

main: main.c
	@gcc -Wall -g -o main.o main.c

exe:
	@./main.o

clean:
	@rm -rf *.o