#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

//void trace(unsigned long ip, unsigned long parent_ip)


extern void mcount (void);

#if 0
void __mcount(void)
{
asm volatile (
	// Save frame
        " subq $0x38, %rsp    \n"
        " movq %rax, (%rsp)   \n"
        " movq %rcx, 8(%rsp)  \n"
        " movq %rdx, 16(%rsp) \n"
        " movq %rsi, 24(%rsp) \n"
        " movq %rdi, 32(%rsp) \n"
        " movq %r8, 40(%rsp)  \n"
        " movq %r9, 48(%rsp)  \n"

	// Restore frame
        " movq 48(%rsp), %r9  \n"
        " movq 40(%rsp), %r8  \n"
        " movq 32(%rsp), %rdi \n"
        " movq 24(%rsp), %rsi \n"
        " movq 16(%rsp), %rdx \n"
        " movq 8(%rsp), %rcx  \n"
        " movq (%rsp), %rax   \n"
        " addq $0x38, %rsp    \n"
);
}
#endif

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
	return func2(100);
}




