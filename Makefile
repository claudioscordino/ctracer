CC=gcc
FLAGS= -Wall -Wextra -g
CFLAGS= $(FLAGS)  #-g #--static #-fPIE #-mcmodel=large #-fPIC #-v
ASFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS) --static
TRACEFLAGS= -pg #--static #-fPIE #-mcmodel=large #-fPIC #-v

all: clean main

main: trace.o main.o trampoline.o

trace.o: trace.c

main.o: main.c
	$(CC) $(CFLAGS) $(TRACEFLAGS) -c -o main.o main.c

trampoline.o: trampoline.S

clean:
	rm -fr main *.o *.out

