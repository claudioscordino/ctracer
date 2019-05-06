#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "ctracer.h"

int func1(int x)
{
	fprintf(stderr, "Running func1 %p with args %d...\n", func1, x);
	return --x;
}

int func2 (int a)
{
	fprintf(stderr, "Running func2 %p with args %d...\n", func2, a);
	int b = func1(a);
	b++;
	if (b > 10)
		return b;
	else
		return --b;
}

int func3()
{
	fprintf(stderr, "Running func3 %p...\n", func3);
	func1(1000);
	func2(200);
	return 10;
}


int main (void)
{
	fprintf(stderr, "Running main %p...\n", main);
	ctracer_enable();
	func2(100);
	int ret = func3();
	fprintf(stderr, "func3() returned %d\n", ret);
	ctracer_disable();
	ret = func3();
	trace_dump();
	return 0;
}




