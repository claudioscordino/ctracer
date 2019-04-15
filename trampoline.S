.global mcount
.global trace_stub

mcount:
	pushq %rax
	pushq %rbx
	pushq %rcx
	pushq %rdx
	pushq %rsi
	pushq %rdi
	pushq %r8
	pushq %r9

	// In 64-bit mode, the first two arguments go to rdi and rsi
	//movq 0x1, %rdi
	//movq 0x2, %rsi

	call *trace_ptr

	popq %r9
	popq %r8
	popq %rdi
	popq %rsi
	popq %rdx
	popq %rcx
	popq %rbx
	popq %rax

trace_stub:
	retq

