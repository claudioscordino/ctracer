CC=gcc
FLAGS  = -Wall -Wextra -g -pg
CFLAGS = $(FLAGS)
ASFLAGS= $(FLAGS)
LDFLAGS= $(FLAGS) --static

.PHONY: clean all

all: clean main

ifeq ($(shell gcc -dumpmachine | sed -e "s/-linux-gnu//"), x86_64)
CFLAGS   += -mfentry
ASFLAGS  += -mfentry
LDCFLAGS += -mfentry
TRAMPOLINE := trampoline-x86-64
else
TRAMPOLINE := trampoline-aarch64
endif

$(TRAMPOLINE).o: $(TRAMPOLINE).S

ctracer.o: ctracer.c

main.o: main.c

main: ctracer.o main.o $(TRAMPOLINE).o

clean:
	rm -fr main *.o *.out *.btf *.dat


