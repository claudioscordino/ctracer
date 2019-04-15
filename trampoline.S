.global mcount
.global trace_stub

        .macro MCOUNT_SAVE_FRAME
        subq $0x38, %rsp
        movq %rax, (%rsp)
        movq %rcx, 8(%rsp)
        movq %rdx, 16(%rsp)
        movq %rsi, 24(%rsp)
        movq %rdi, 32(%rsp)
        movq %r8, 40(%rsp)
        movq %r9, 48(%rsp)
        .endm

        .macro MCOUNT_RESTORE_FRAME
        movq 48(%rsp), %r9
        movq 40(%rsp), %r8
        movq 32(%rsp), %rdi
        movq 24(%rsp), %rsi
        movq 16(%rsp), %rdx
        movq 8(%rsp), %rcx
        movq (%rsp), %rax
        addq $0x38, %rsp
        .endm



mcount:
	MCOUNT_SAVE_FRAME

	// In 64-bit mode, the first two arguments go to rdi and rsi
        movq 0x38(%rsp), %rdi
        movq 8(%rbp), %rsi // rbp + 8 contains the return address written in the stack frame
	subq $0xe, %rdi // This is the size of the mcount call

	call *trace_ptr

	MCOUNT_RESTORE_FRAME

trace_stub:
	retq

