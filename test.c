#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

// In ASM:
extern void mcount (void);
void trace_stub(unsigned long ip, unsigned long parent_ip);


extern int func1(int x);
extern int func2 (int a);

volatile int i = 0;

typedef void (*trace_func_t)(unsigned long ip, unsigned long parent_ip);
void trace_function(unsigned long ip, unsigned long parent_ip)
{
	printf("ip = %lu, parent_ip = %lu\n", ip, parent_ip);
	++i;
}

trace_func_t trace_ptr __attribute__((__section__(".data.read_mostly"))) = trace_stub;


int main (void)
{
	printf("Running...\n");
	trace_ptr = &trace_function;
	printf("i = %d\n", i);
	func2(100);
	printf("i = %d\n", i);
	return 0;
}




