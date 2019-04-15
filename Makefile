CC=gcc
FLAGS= -O0 -Wall -Wextra -g
CFLAGS= $(FLAGS)  #-g #--static #-fPIE #-mcmodel=large #-fPIC #-v
ASFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS) --static
TRACEFLAGS= -pg #--static #-fPIE #-mcmodel=large #-fPIC #-v

all: clean test

test: test.o traced.o trampoline.o

test.o: test.c

traced.o: traced.c
	$(CC) $(CFLAGS) $(TRACEFLAGS) -c -o traced.o traced.c

trampoline.o: trampoline.S

clean:
	rm -fr test *.o *.out

