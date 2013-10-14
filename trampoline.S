

.text
.align 16
.globl __lwt_trampoline
__lwt_trampoline:


/* caller saves all registers to stack */
/*
	push %eax
	push %ecx
	push %edx
	push %ebx
	//push 0x20(%esp)
	push %ebp
	push %esi
	push %edi
*/
	push %ebp
	mov  %esp, %ebp

//pushal

	/* 32 bytes temp memory for local vars in callee function */
	sub $0x20, %esp

	push 0x18(%ebp)
	push 0x14(%ebp)
	push 0x10(%ebp)
	push 0x0C(%ebp)
	push 0x08(%ebp)

	call   __lwt_start_test5

/*
	pop (%esp)
	pop (%esp)
	pop (%esp)
	pop (%esp)
	pop (%esp)
	pop (%esp)
	pop (%esp)
	pop (%esp)

*/

//popal
	jmp label1
	label1:
		call __lwt_start_test0

	leave
	ret




