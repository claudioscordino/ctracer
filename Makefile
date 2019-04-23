CC=gcc
FLAGS= -Wall -Wextra -g
CFLAGS= $(FLAGS)
ASFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS) --static
TRACEFLAGS= -pg

all: clean main


main: ctracer.o main.o trampoline.o

ctracer.o: ctracer.c

main.o: main.c
	$(CC) $(CFLAGS) $(TRACEFLAGS) -c -o main.o main.c

trampoline.o: trampoline.S

.PHONY: clean
clean:
	rm -fr main *.o *.out *.btf


