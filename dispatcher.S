.text
.align 16
.globl dispatcher
dispatcher:

//  called by dispatcher(next->sp, next->ip, ptr_current_sp, ptr_current_ip);

	push %ebp
	mov %esp, %ebp
    sub $0x20,%esp // room for local variables
	pushal


	movl 0x14(%ebp), %ecx 	// get ptr_to_current_ip from parameter list
	movl 0x10(%ebp), %edx 	// ptr current SP

	movl $1f, (%ecx)
 	movl %esp, (%edx)

 	movl 0x0C(%ebp), %ecx //NEXT IP
    movl 0x08(%ebp), %edx //NEXT SP

 	movl %edx, %esp
 	jmp  %ecx

	1:
	popal
	leave
	ret

.globl tramp_testing
tramp_testing:
	push %ebp
	mov %esp, %ebp
	call __lwt_start_test0
	leave
	ret

.globl tramp_testing_params
tramp_testing_params:
	push %ebp
	mov %esp, %ebp
	push 0x0C(%ebp)
	call 0x08(%ebp)
	leave
	ret
