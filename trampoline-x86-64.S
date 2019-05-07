// XXX: x86-64 needs 16-byte stack alignment
.macro MCOUNT_SAVE_FRAME
	pushq %rax
	pushq %rcx
	pushq %rdx
	pushq %rsi
	pushq %rdi
	pushq %r8
	pushq %r9
	subq $8, %rsp
.endm

.macro MCOUNT_RESTORE_FRAME
	addq $8, %rsp
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
	cmpq $trace_function, ctracer_ptr
	jnz end
	MCOUNT_SAVE_FRAME

	// According to the x86-64 ABI, the first 6 integer/pointer arguments
	// are passed in registers:
	// 1. %rdi
	// 2. %rsi
	// 3. %rdx
	// 4. %rcx
	// 5. %r8
	// 6. %r9
	movq %rcx, %r9
	movq %rdx, %r8
	movq %rsi, %rcx
	movq %rdi, %rdx
        movq 0x40(%rsp), %rdi
        movq 8(%rbp), %rsi // rbp + 8 contains the return address written in the stack frame
	subq $0xe, %rdi // This is the size of the mcount call (taken empirically by looking at main)

	call *ctracer_ptr

	MCOUNT_RESTORE_FRAME
end:
	retq

