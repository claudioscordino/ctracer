.global mcount
mcount:
        subq $0x38, %rsp
        movq %rax, (%rsp)
        movq %rcx, 8(%rsp)
        movq %rdx, 16(%rsp)
        movq %rsi, 24(%rsp)
        movq %rdi, 32(%rsp)
        movq %r8, 40(%rsp)
        movq %r9, 48(%rsp)

        movq 48(%rsp), %r9
        movq 40(%rsp), %r8
        movq 32(%rsp), %rdi
        movq 24(%rsp), %rsi
        movq 16(%rsp), %rdx
        movq 8(%rsp), %rcx
        movq (%rsp), %rax
        addq $0x38, %rsp

