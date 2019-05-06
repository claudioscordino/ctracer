#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#define	LOG_SIZE	1024
#define	EV_START	0x1
#define	EV_END		0x2

struct event {
	uint8_t 	type;
	uint64_t	ip;
	uint64_t	pip;
	uint64_t	arg1;
	uint64_t	arg2;
	uint64_t	arg3;
	uint64_t	arg4;
	uint64_t	time;
};

struct event data [LOG_SIZE];
uint16_t curr = 0;

__attribute__ ((no_instrument_function))
void trace_function(uint64_t ip, uint64_t parent_ip, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	data[curr].type = EV_START;
	data[curr].ip = ip;
	data[curr].pip = parent_ip;
	data[curr].arg1	 = arg1;
	data[curr].arg2	 = arg2;
	data[curr].arg3	 = arg3;
	data[curr].arg4	 = arg4;
	data[curr].time = (ts.tv_sec * 1000000000) + ts.tv_nsec;
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
		if (data[i].type == 0)
			break;
		fprintf(fd, "%u\t%lx\t%lx\t%lu\t%lu\t%lu\t%lu\t%lu\n",
			data[i].type,
			data[i].ip,
			data[i].pip,
			data[i].arg1,
			data[i].arg2,
			data[i].arg3,
			data[i].arg4,
			data[i].time);
	}
	fclose(fd);
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
