.PHONY: clean exe all 

all: main exe clean


yo: mainyo exe clean

mainyo: mainyo.c
	@gcc -Wall -g -o mainyo.o mainyo.c


main: main.c
	@gcc -Wall -g -o main.o main.c

exe:
	@./*.o

clean:
	@rm -rf *.o