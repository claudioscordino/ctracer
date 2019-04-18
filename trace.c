#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>


void trace_function(unsigned long ip, __attribute__((unused)) unsigned long parent_ip)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("TRACE\t%lu%lu\t0x%lx\n", ts.tv_sec, ts.tv_nsec, ip);
}
