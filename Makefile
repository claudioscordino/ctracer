CC=gcc
FLAGS= -Wall -Wextra -g
CFLAGS= $(FLAGS)
ASFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS) --static
TRACEFLAGS= -pg

all: clean main main.dump


main: trace.o main.o trampoline.o

trace.o: trace.c

main.o: main.c
	$(CC) $(CFLAGS) $(TRACEFLAGS) -c -o main.o main.c

trampoline.o: trampoline.S

main.dump: main
	objdump -S -D main > main.dump

.PHONY: clean
clean:
	rm -fr main *.o *.out


