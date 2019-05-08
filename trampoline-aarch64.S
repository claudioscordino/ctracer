// Calling convention: https://en.wikipedia.org/wiki/Calling_convention
.macro SAVE_FRAME
	stp     x29, x30, [sp, #-16]!
        mov     x29, sp
.endm

.macro RESTORE_FRAME
	ldp     x29, x30, [sp], #16
.endm

.global _mcount
_mcount:
	SAVE_FRAME

	mov	x5, x3
	mov	x4, x2
	mov	x3, x1
	ldr	x2, [sp]
	ldr	x2, [x2, #28]

        ldr     x6, ctracer_ptr
        cmp     x6, #0
        b.eq    end

	//str	x2, [x29,#28]

	// x0 <- pc
	sub	x0, x30, 0x10

	// x1 <- lr
	ldr     x1, [x29]	// x29 is the frame pointer
        ldr     x1, [x1, #8]
	sub	x1, x1, 4

        blr     x6		// calls (*ctracer_ptr)(pc, lr);

end:
	RESTORE_FRAME
	ret

