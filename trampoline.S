

.text
.align 16
.globl __lwt_trampoline
__lwt_trampoline:

/* caller saves all registers to stack */
	pushal

/* swap stack pointer with base pointer so we have constant, unchanging frame of reference */
	push %ebp
	mov  %esp, %ebp

/* allocate 32 bytes temp memory for local vars in callee function */
	sub $0x20, %esp

/* push parameters for our function call */
	push 0x18(%ebp)
	push 0x14(%ebp)
	push 0x10(%ebp)
	push 0x0C(%ebp)
	push 0x08(%ebp)

/* call to C function */
	call   __lwt_start_test5

/* swap back base pointer to stack poointer, "leave" */
    mov %ebp, %esp
    pop %ebp

/* pop all registers from stack (undo our pushal) */
	popal
ret




