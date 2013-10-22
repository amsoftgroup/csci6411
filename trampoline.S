.text
.align 16
.globl __lwt_trampoline
__lwt_trampoline:

/* caller saves registers to stack */
push %ebp
mov  %esp, %ebp

	push 0x0C(%ebp) // (void *) data pointer to lwt_t... this gives us access to the TCB
	//push 0x08(%ebp) // first parameter passed in... function address to call

/* call to C function with above parameters, demonstrating basic understanding of cdecl */
	call 0x08(%ebp)

/* restore our registers */
 mov %ebp, %esp
 pop %ebp
