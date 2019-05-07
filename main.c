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

int func2 (int a, int b, int c, int d)
{
	fprintf(stderr, "Running func2 %p with args %d %d %d %d...\n", func2, a, b, c ,d);
	int e = func1(a-100+1);
	e++;
	if (e > 10)
		return e;
	else
		return --e;
}

int func3()
{
	fprintf(stderr, "Running func3 %p...\n", func3);
	func1(103);
	func2(204, 214, 224, 234);
	return 10;
}


int main (void)
{
	fprintf(stderr, "Running main %p...\n", main);
	ctracer_enable();
	func2(201, 211, 221, 231);
	int ret = func3();
	fprintf(stderr, "func3() returned %d\n", ret);
	ctracer_disable();
	ret = func3();
	trace_dump();
	return 0;
}




