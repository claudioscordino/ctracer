#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

void trace_function(uint64_t ip, uint64_t parent_ip, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("TRACE\t%lu%lu\t0x%lx\n", ts.tv_sec, ts.tv_nsec, ip);
	printf("\t%lx\n", parent_ip);
	printf("\t%lu\n", arg1);
	printf("\t%lu\n", arg2);
	printf("\t%lu\n", arg3);
	printf("\t%lu\n", arg4);
}

typedef void (*ctracer_func_t)(uint64_t ip, uint64_t parent_ip, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4);
ctracer_func_t ctracer_ptr __attribute__((__section__(".data.read_mostly"))) = NULL;

void ctracer_enable(void)
{
	ctracer_ptr = &trace_function;
}

void ctracer_disable(void)
{
	ctracer_ptr = NULL;
}
