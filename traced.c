#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

extern void tracer_enable(void);
extern void tracer_disable(void);

int func1(int x)
{
	return --x;
}

int func2 (int a)
{
	int b = func1(a);
	b++;
	if (b > 10)
		return b;
	else
		return --b;
}

int main (void)
{
	printf("Running...\n");
	tracer_enable();
	func2(100);
	tracer_disable();
	func2(100);
	return 0;
}




