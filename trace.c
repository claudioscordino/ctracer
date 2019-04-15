#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

void notrace_stub(unsigned long ip, unsigned long parent_ip);

typedef void (*trace_func_t)(unsigned long ip, unsigned long parent_ip);
void trace_function(unsigned long ip, __attribute__((unused)) unsigned long parent_ip)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("[%lu.%lu]\t Function called: 0x%lx\n", ts.tv_sec, ts.tv_nsec, ip);
}

trace_func_t trace_ptr __attribute__((__section__(".data.read_mostly"))) = notrace_stub;

void tracer_enable(void)
{
	trace_ptr = &trace_function;
}

void tracer_disable(void)
{
	trace_ptr = notrace_stub;
}


