#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#include "ctracer.h"

struct event trace [LOG_SIZE];
static uint16_t curr = 0;

__attribute__ ((no_instrument_function))
void trace_function(uint64_t ip, uint64_t parent_ip, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	trace[curr].type = EV_START;
	trace[curr].ip = ip;
	trace[curr].pip = parent_ip;
	trace[curr].arg1	 = arg1;
	trace[curr].arg2	 = arg2;
	trace[curr].arg3	 = arg3;
	trace[curr].arg4	 = arg4;
	trace[curr].time = (ts.tv_sec * 1000000000) + ts.tv_nsec;
	curr=(curr+1)%LOG_SIZE;
}

__attribute__ ((no_instrument_function))
void trace_dump()
{
	FILE *fd = fopen ("trace.dat", "w+");
	if (fd == NULL)
		return;
	fprintf(fd, "Event:\tIP:\tPIP:\targ1:\targ2:\targ3:\targ4:\ttime:\n");
	fprintf(fd, "==============================================================\n");
	for (int i = 0; i < LOG_SIZE; ++i) {
		if (trace[i].type == 0)
			break;
		fprintf(fd, "%u\t0x%lx\t0x%lx\t0x%lx\t0x%lx\t0x%lx\t0x%lx\t%lu\n",
			trace[i].type,
			trace[i].ip,
			trace[i].pip,
			trace[i].arg1,
			trace[i].arg2,
			trace[i].arg3,
			trace[i].arg4,
			trace[i].time);
	}
	fclose(fd);
}

// Set equal to &trace_function from tracing from beginning (e.g. main function)
ctracer_func_t ctracer_ptr __attribute__((__section__(".data.read_mostly"))) = NULL;

__attribute__ ((no_instrument_function))
void ctracer_enable(void)
{
	ctracer_ptr = &trace_function;
}

__attribute__ ((no_instrument_function))
void ctracer_disable(void)
{
	ctracer_ptr = NULL;
}
