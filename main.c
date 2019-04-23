#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "ctracer.h"

int func1(int x)
{
	fprintf(stderr, "Running func1 %p...\n", func1);
	return --x;
}

int func2 (int a)
{
	fprintf(stderr, "Running func2 %p...\n", func2);
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
	return 0;
}


int main (void)
{
	fprintf(stderr, "Running main %p...\n", main);
	ctracer_enable();
	func2(100);
	func3();
	ctracer_disable();
	func3();
	return 0;
}




