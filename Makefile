CC=gcc
FLAGS= -Wall -Wextra -g -pg
CFLAGS= $(FLAGS)
ASFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS) --static

.PHONY: clean all

all: clean main

main: ctracer.o main.o trampoline.o

ctracer.o: ctracer.c

main.o: main.c

trampoline.o: trampoline.S

clean:
	rm -fr main *.o *.out *.btf


