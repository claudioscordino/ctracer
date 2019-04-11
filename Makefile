ASFLAGS=-Wall -Wextra -pg 
CFLAGS=-Wall -Wextra -pg 
LDFLAGS=-Wall -Wextra -pg 

#test: test.c

test: test.o trampoline.o

trampoline.o: trampoline.S

test.o: test.c

clean:
	rm -fr test *.o *.out

