.macro MCOUNT_SAVE_FRAME
	pushq %rax
	pushq %rcx
	pushq %rdx
	pushq %rsi
	pushq %rdi
	pushq %r8
	pushq %r9
.endm

.macro MCOUNT_RESTORE_FRAME
	popq %r9
	popq %r8
	popq %rdi
	popq %rsi
	popq %rdx
	popq %rcx
	popq %rax
.endm


.global mcount
mcount:
	MCOUNT_SAVE_FRAME

	// In 64-bit mode, the first two arguments go to rdi and rsi
        movq 0x38(%rsp), %rdi
        movq 8(%rbp), %rsi // rbp + 8 contains the return address written in the stack frame
	subq $0xa, %rdi // This is the size of the mcount call (taken empirically by looking at main)

	call trace_function

	MCOUNT_RESTORE_FRAME
	retq

