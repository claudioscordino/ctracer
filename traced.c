#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


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

