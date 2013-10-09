

.text
.align 16
.globl lwt_trampoline
__lwt_trampoline:
	movl $0x5, %eax
	movl $0x6, %ecx
	movl $0x7, %edx
	pushal
	push   %eax
	push   %ecx
	push   %edx
	call   __lwt_start_1
	pop (%esp)
	pop (%esp)
	pop (%esp)
	popal

